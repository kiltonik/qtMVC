#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QFile>
#include <QModelIndex>
#include <QXmlStreamReader>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QStringList &headers, const QString &fileName,
              QObject *parent = nullptr);
    ~TreeModel();
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    void setAlbumData(const QModelIndex &index, const QMap<QString, QString> data,
                 int role = Qt::EditRole);

    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    TreeItem *getItem(const QModelIndex &index) const;

private:
    void setupModelData(const QString &fileName, TreeItem *parent);

    TreeItem *rootItem;

    void insertAlbum(TreeItem *parent, QMap<QString, QString> album);


};
#endif // TREEMODEL_H
