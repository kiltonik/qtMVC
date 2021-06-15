#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVector>
#include <QVariant>

class TreeItem // НОДа дерева
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = nullptr); // Конструктор
    ~TreeItem(); // Деструктор

    TreeItem *child(int number); // Функция получения ссылки на ребенка по его индексу
    int childCount() const; // Функция получения числа детей
    int columnCount() const; // Функция получения числа колонок
    QVariant data(int column) const; // Функция получения данных из колонки по её индексу
    bool insertChildren(int position, int count, int columns); // Функция вставки детей
    bool insertColumns(int position, int columns); // Функция вставки колонок
    TreeItem *parent(); // Функция получения ссылки на родителя
    bool removeChildren(int position, int count); // Функция удаляющая нужное количество детей
    bool removeColumns(int position, int columns); // Функция удаляющая колонки
    int childNumber() const; // Функция возвращает индекс текущей ноды относительно родителя
    bool setColumnData(int column, const QVariant &value); // Функция вставляет данные в нужную колонку
    void setData(const QMap<QString, QString> album); // Функция сохраняет в ноду данные об альбоме
    QMap<QString, QString> getAlbumData(); // Функция возвращает данные об альбоме

private:
    QVector<TreeItem*> childItems; // Вектор ссылок на дочерние ноды
    QVector<QVariant> columnData; // Данные записанные в колонки
    QMap<QString, QString> albumData; // Данные об альбоме
    TreeItem *parentItem; // Ссылка на родительский элемент
};
#endif // TREEITEM_H
