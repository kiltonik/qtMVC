#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVector>
#include <QVariant>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setColumnData(int column, const QVariant &value);
    void setData(const QMap<QString, QString> album);
    QMap<QString, QString> getAlbumData();

private:
    QVector<TreeItem*> childItems;
    QVector<QVariant> columnData;
    QMap<QString, QString> albumData;
    TreeItem *parentItem;
};
#endif // TREEITEM_H
