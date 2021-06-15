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
    explicit EntryEdit(QWidget *parent = nullptr); // Конструктор
    void setupData(QMap<QString, QString> data); // Функция устанавливает переданные данные в ралзичные поля диалога
    QMap<QString, QString> interpretData(); // Функция считывает с полей диалога данные и возвращает их в качестве словаря строк
    ~EntryEdit(); // Деструктор

signals:
 void save_editing(); // Сигнал показывающий, что требвется сохранить изменения

private slots:
    void on_cancel_button_clicked(); // Слот обрабатывающий сигнал нажатие кнопки "cancel"

    void on_ok_button_clicked(); // Слот обрабатывающий сигнал нажатия кнопки "ok"


private:
    Ui::EntryEdit *ui; // Ссылка на интерфейс
    QString formatDate(); // Функция, считывающая данные из виджета изменения даты и преобразующая их в нужный вид
};

#endif // ENTRYEDIT_H
