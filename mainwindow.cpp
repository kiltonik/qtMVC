#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "treemodel.h"
#include <QMessageBox>
#include "treeviewdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadData_clicked()
{
    const QStringList headers({tr("Info")});

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Choose data file"), "/", tr("Data file (*.xml)"));
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,
                             "Ошибка файла",
                             "Не удалось открыть файл",
                             QMessageBox::Ok);
    } else {
        file.close();
        TreeModel *model = new TreeModel(headers, fileName);
        this->ui->treeView->setModel(model);
        this->ui->treeView->setItemDelegate(new TreeViewDelegate);
        this->ui->treeView->setEditTriggers(QAbstractItemView::DoubleClicked);
        this->ui->treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
    }
}

void MainWindow::on_saveData_clicked()
{
    if(static_cast<TreeModel*>(this->ui->treeView->model())
            ->saveDataToFile(QFileDialog::getSaveFileName(this,
                                                          tr("Save album data"),
                                                          tr("album_data.xml")
                                                          )
                             )
            )
        QMessageBox::information(this,
                                 "Успешно",
                                 "Сохранение в файл выполнено успешно",
                                 QMessageBox::Ok);
    else
        QMessageBox::warning(this,
                             "Ошибка файла",
                             "Не удалось сохранить в файл",
                             QMessageBox::Ok);
}
