#include "entryedit.h"
#include "ui_entryedit.h"

EntryEdit::EntryEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryEdit)
{
    ui->setupUi(this);
}

EntryEdit::~EntryEdit()
{
    delete ui;
}

void EntryEdit::setupData(QMap<QString, QString> data){

}
QMap<QString, QString> EntryEdit::interpretData(){

}

