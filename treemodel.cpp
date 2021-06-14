#include "treemodel.h"

#include <QtWidgets>
#include<QDebug>

TreeModel::TreeModel(const QStringList &headers, const QString &fileName, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    for (const QString &header : headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(fileName, rootItem);

}


TreeModel::~TreeModel()
{
    delete rootItem;
}



int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return (QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable);
}


TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();



    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}


bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}


bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    const TreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}


bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setColumnData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setColumnData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setupModelData(const QString &fileName, TreeItem *parent)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QVector<TreeItem*> parents;
    QVector<int> indentations;
    parents << parent;
    indentations << 0;

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);

    while(!xmlReader.atEnd() && !xmlReader.hasError()){
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        auto tmp1 = xmlReader.name();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "albums")
                continue;
            if (xmlReader.name() == "album"){
                QVector<QVariant> columnData;
                xmlReader.readNext();
                QMap<QString, QString> album;
                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "album"))
                {
                    auto tmp = xmlReader.name();
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xmlReader.tokenType() != QXmlStreamReader::StartElement)
                            return;
                        QString elementName = xmlReader.name().toString();
                        xmlReader.readNext();
                        album.insert(elementName, xmlReader.text().toString());
                        if(elementName == "genre"
                                || elementName == "singer"
                                || elementName == "title")
                            columnData.append(xmlReader.text().toString());
                    }
                    xmlReader.readNext();
                }
                insertAlbum(parent, album);
            }

        }
    }
    file.close();
}

void TreeModel::insertAlbum(TreeItem *parent, QMap<QString, QString> album){
    bool itemNotInserted = true;
    for(int i = 0; i < parent->childCount(); ++i){
        if(parent->child(i)->getAlbumData()["genre"] == album["genre"]){

            for(int j = 0; j < parent->child(i)->childCount(); ++j){

                if(parent->child(i)->child(j)->getAlbumData()["singer"] == album["singer"]){
                    itemNotInserted = false;

                    parent
                            ->child(i)
                            ->child(j)
                            ->insertChildren(
                                parent->child(i)->child(j)->childCount(),
                                1,
                                rootItem->columnCount()
                                );
                    parent
                            ->child(i)
                            ->child(j)
                            ->child(parent->child(i)->child(j)->childCount() - 1)
                            ->setColumnData(0, album["title"]);
                    parent
                            ->child(i)
                            ->child(j)
                            ->child(parent->child(i)->child(j)->childCount() - 1)
                            ->setData(album);
                }
            }
            if(itemNotInserted){
                itemNotInserted = false;

                parent
                        ->child(i)
                        ->insertChildren(
                            parent->child(i)->childCount(),
                            1,
                            rootItem->columnCount()
                            );
                parent
                        ->child(i)
                        ->child(parent->child(i)->childCount() - 1)
                        ->setColumnData(0, album["singer"]);
                parent
                        ->child(i)
                        ->child(parent->child(i)->childCount() - 1)
                        ->setData(album);

                parent
                        ->child(i)
                        ->child(
                            parent->child(i)->childCount() -1
                            )
                        ->insertChildren(
                            parent->child(i)->child(
                                parent->child(i)->childCount() -1
                                )->childCount(),
                            1,
                            rootItem->columnCount()
                            );
                parent
                        ->child(i)
                        ->child(
                            parent->child(i)->childCount() -1
                            )->child(parent->child(i)->child(
                                         parent->child(i)->childCount() -1
                                         )->childCount() - 1)
                        ->setColumnData(0, album["title"]);
                parent
                        ->child(i)
                        ->child(
                            parent->child(i)->childCount() -1
                            )->child(parent->child(i)->child(
                                         parent->child(i)->childCount() -1
                                         )->childCount() - 1)
                        ->setData(album);
            }
        }
    }
    if(itemNotInserted){
        parent
                ->insertChildren(
                    parent->childCount(),
                    1,
                    rootItem->columnCount()
                    );

        int firstIndex = parent->childCount() - 1;

        parent
                ->child(firstIndex)
                ->setColumnData(0, album["genre"]);
        parent
                ->child(firstIndex)
                ->setData(album);

        parent
                ->child(firstIndex)
                ->insertChildren(
                    parent->child(firstIndex)->childCount(),
                    1,
                    rootItem->columnCount()
                    );

        int secondIndex = parent->child(firstIndex)->childCount() - 1;

        parent
                ->child(firstIndex)
                ->child(secondIndex)
                ->setColumnData(0, album["singer"]);

        parent
                ->child(firstIndex)
                ->child(secondIndex)
                ->setData(album);

        parent
                ->child(firstIndex)
                ->child(secondIndex)
                ->insertChildren(
                    parent->child(firstIndex)->child(secondIndex)->childCount(),
                    1,
                    rootItem->columnCount()
                    );
        parent
                ->child(firstIndex)
                ->child(secondIndex)
                ->child(parent->child(firstIndex)->child(secondIndex)->childCount() - 1)
                ->setColumnData(0, album["title"]);
        parent
                ->child(firstIndex)
                ->child(secondIndex)
                ->child(parent->child(firstIndex)->child(secondIndex)->childCount() - 1)
                ->setData(album);
    }
}

void TreeModel::setAlbumData(const QModelIndex &index, const QMap<QString, QString> albumData, int role){
    TreeItem* currentItem = this->getItem(index);
    if (currentItem->getAlbumData() != albumData) {
        if(currentItem->getAlbumData()["genre"] != albumData["genre"]
                ||
                currentItem->getAlbumData()["singer"] != albumData["singer"]) {
            insertAlbum(this->rootItem, albumData);
            //            if(this->getItem(index.parent())->childCount() == 0)
            currentItem->parent()->removeChildren(index.row(), 1);
        }
        else if(currentItem->data(0) != albumData["title"]){
            currentItem->setColumnData(0, albumData["title"]);
            this->getItem(index)->setData(albumData);
        }
        else this->getItem(index)->setData(albumData);
    }
    qInfo() << rootItem->childCount();
    emit dataChanged(QModelIndex(), QModelIndex(), {Qt::DisplayRole, Qt::EditRole});
}
