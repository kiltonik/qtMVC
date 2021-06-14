#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    : columnData(data),
      parentItem(parent)
{}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int number)
{
    if (number < 0 || number >= childItems.size())
        return nullptr;
    return childItems.at(number);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    return 0;
}

int TreeItem::columnCount() const
{
    return columnData.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= columnData.size())
        return QVariant();
    return columnData.at(column);
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > columnData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        columnData.insert(position, QVariant());

    for (TreeItem *child : qAsConst(childItems))
        child->insertColumns(position, columns);

    return true;
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;
    for (int row = 0; row < count; ++row)
        childItems.remove(position);
    if(this->childCount() == 0){
        parentItem->childItems.remove(0);
    }
    if(parentItem->childCount() == 0){
        parentItem->parentItem->childItems.remove(0);
    }

    return true;
}

bool TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > columnData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        columnData.remove(position);

    for (TreeItem *child : qAsConst(childItems))
        child->removeColumns(position, columns);

    return true;
}

bool TreeItem::setColumnData(int column, const QVariant &value)
{
    if (column < 0 || column >= columnData.size())
        return false;

    columnData[column] = value;
    return true;
}

void TreeItem::setData(const QMap<QString, QString> album){
    this->albumData = album;
}

QMap<QString, QString> TreeItem::getAlbumData(){
    return this->albumData;
}
