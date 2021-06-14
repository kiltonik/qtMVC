#ifndef ENTRYEDIT_H
#define ENTRYEDIT_H

#include <QWidget>
#include <QMap>

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

signals:
 void save_editing();

public slots:
    void on_ok_button_clicked();

private slots:
    void on_cancel_button_clicked();

private:
    Ui::EntryEdit *ui;
    QMap<QString, QString> album_data;
    QString formatDate();
};

#endif // ENTRYEDIT_H
