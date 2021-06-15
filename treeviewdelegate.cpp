#include "treeviewdelegate.h"
#include <QWidget>
#include "entryedit.h"
#include "treemodel.h"
#include<QDebug>
#include <QEvent>
#include <QMetaEnum>
#include <QMouseEvent>
#include <QTreeView>


TreeViewDelegate::TreeViewDelegate(QObject *parent)
    : QItemDelegate(parent) {
}

QWidget *TreeViewDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &/* option */,
                                        const QModelIndex &/* index */) const {
    return new QTreeView(parent);
}

void TreeViewDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const{
    static_cast<EntryEdit*>(editor)->setupData(
                static_cast<const TreeModel*>(index.model())->getItem(index)->getAlbumData()
                );
}

void TreeViewDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index
                                    ) const {
    static_cast<TreeModel*>(model)->setAlbumData(
                index,
                static_cast<EntryEdit*>(editor)->interpretData(),
                Qt::EditRole
                );
}

void TreeViewDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &/* index */) const {
    editor->setGeometry(option.rect);
}

bool TreeViewDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
    qInfo() << index.row() << " " << index.column();

    //Проверяет пришедший евент, если он является двойным кликом, то открывает окно редактирования
    if(!model->hasChildren(index) &&
            static_cast<QMouseEvent*>(event)->type() == QEvent::MouseButtonDblClick){
        EntryEdit *editor = new EntryEdit;
        editor->show();
        this->setEditorData(editor, index);
        connect(editor, &EntryEdit::save_editing, [=](){
            this->setModelData(editor, model, index);
            delete editor;
        }
        );

    }
    return QItemDelegate::editorEvent(event,model,option,index);
}
