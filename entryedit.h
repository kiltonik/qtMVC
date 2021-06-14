#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H

#include <QWidget>

namespace Ui {
class EntryEdit;
}

class EntryEdit : public QWidget
{
    Q_OBJECT

public:
    explicit EntryEdit(QWidget *parent = nullptr);
    void setupData(QMap<QString, QString> data);
    QMap<QString, QString> interpretData();
    ~EntryEdit();

private:
    Ui::EntryEdit *ui;
};

#endif // ENTRYEDIT_H
