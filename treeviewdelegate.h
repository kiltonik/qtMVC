#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include <QItemDelegate>

class TreeViewDelegate: public QItemDelegate // Делегат для изменения данных
{
public:
    TreeViewDelegate(QObject *parent = nullptr); // Конструктор

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override; // Функция создает окно для изменения

    void setEditorData(QWidget *editor, const QModelIndex &index) const override; // Функция заполняет едитор данными
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override; // Функция записывает данные после именений едитора в модель

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override; // Функция контролирует геометрию едитора
    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override; // Функция обрабатывает события начала изменений
};

#endif // TREEVIEWDELEGATE_H
