#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Конструктор
    ~MainWindow(); // Деструктор

private slots:
    void on_loadData_clicked(); // Слот обрабатывающий сигнал нажатия на кнопку загрузки данных

    void on_saveData_clicked(); // Слот обрабатывающий нажатие на кнопку сохранения данных

private:
    Ui::MainWindow *ui; // Ссылка на интерфейс
};
#endif // MAINWINDOW_H
