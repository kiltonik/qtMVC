#include "entryedit.h"
#include "ui_entryedit.h"
#include <QString>

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
    this->album_data = data;
    this->ui->singer_edit->setText(data["singer"]);
    this->ui->title_edit->setText(data["title"]);
    this->ui->date_spin_box->setDate(QDate::fromString(data["release_date"], "dd/MM/yyyy"));
    this->ui->desctiption_edit->setText(data["description"]);
    this->ui->minutes_spin_box->setValue(data["duration"].toInt()/60);
    this->ui->seconds_spin_box->setValue(data["duration"].toInt() % 60);
    this->ui->genre_edit->setText(data["genre"]);
    this->ui->studio_edit->setText(data["studio"]);
    this->ui->lable_edit->setText(data["label"]);
    this->ui->tracks_number_spin_box->setValue(data["track_number"].toInt());
    this->ui->discs_number_spin_box->setValue(data["disc_number"].toInt());
}


QMap<QString, QString> EntryEdit::interpretData(){
    this->album_data["singer"] = this->ui->singer_edit->text();
    this->album_data["title"] = this->ui->title_edit->text();
    this->album_data["release_date"] = this->formatDate();
    this->album_data["description"] = this->ui->desctiption_edit->toPlainText();
    this->album_data["duration"] = QString::number(
                this->ui->minutes_spin_box->value()*60+this->ui->seconds_spin_box->value()
                );
    this->album_data["genre"] = this->ui->genre_edit->text();
    this->album_data["studio"] = this->ui->studio_edit->text();
    this->album_data["label"] = this->ui->lable_edit->text();
    this->album_data["track_number"] = QString::number(this->ui->tracks_number_spin_box->value());
    this->album_data["disc_number"] = QString::number(this->ui->discs_number_spin_box->value());
    return this->album_data;
}

void EntryEdit::on_ok_button_clicked()
{
    emit save_editing();
}

void EntryEdit::on_cancel_button_clicked()
{
    this->destroy();
}

QString EntryEdit::formatDate(){
    QString day = QString::number(this->ui->date_spin_box->date().day());
    QString month = QString::number(this->ui->date_spin_box->date().month());
    QString year = QString::number(this->ui->date_spin_box->date().year());
    return ((day.length() < 2) ? "0" + day : day)
            + "/" +
            ((month.length() < 2) ? "0" + month : month)
            + "/" +
            year;
}
