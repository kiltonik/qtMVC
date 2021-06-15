#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QFile>
#include <QModelIndex>
#include <QXmlStreamReader>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel // Модель дерева
{
    Q_OBJECT

public:
    TreeModel(const QStringList &headers, const QString &fileName,
              QObject *parent = nullptr); // Конструктор
    ~TreeModel(); // Деструктор
    QVariant data(const QModelIndex &index, int role) const override; // Функция возвращает данные по индексу
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override; // Функция возвращает данные из заголовка столбца

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override; // Функция полчения индекса по строке и столбцу
    QModelIndex parent(const QModelIndex &index) const override; // Функция возвращает индекс родителя по индексу ребенка

    int rowCount(const QModelIndex &parent = QModelIndex()) const override; // Функция возвращает число строк по индексу
    int columnCount(const QModelIndex &parent = QModelIndex()) const override; // Функция возвращает число столбцов по индексу

    Qt::ItemFlags flags(const QModelIndex &index) const override; // Функция возвращает заданыне флаги для модели
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override; // Функция устанавливает в ноду данные

    void setAlbumData(const QModelIndex &index, const QMap<QString, QString> data,
                 int role = Qt::EditRole); // Функция сохраняет в ноде данные об альбоме

    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override; // Функция заполняет заголовок данными

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override; // Функция вставляет колонки
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override; // Функция удаляет колонки
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override; // Функция вставляет ряды
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override; // Функция удаляет ряды
    TreeItem *getItem(const QModelIndex &index) const; // Функция возвращает элемент по индексу

    bool saveDataToFile(QString fileName); // Функция записывает данные в файл

private:
    void setupModelData(const QString &fileName, TreeItem *parent); // Функция считывает данные из файла и создает модель на их основе

    TreeItem *rootItem; // Корневая нода модели

    void insertAlbum(TreeItem *parent, QMap<QString, QString> album); // Функция вставляет альбом в качестве новой ноды
};
#endif // TREEMODEL_H
