#include "dialog.h"
#include "ui_dialog.h"
#include "landmassdetector.h"
#include <QFileDialog>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->evaluate_map->setDisabled(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_choose_map_clicked()
{
    QString map_name = QFileDialog::getOpenFileName(
                this,
                tr("Open map"),
                "./maps",
                "Text File (*.txt)"
                );
    ui->file->setText(map_name);
}

void Dialog::on_evaluate_map_clicked()
{
    LandmassDetector* ld;
    ld = new LandmassDetector();
    this->hide();
    ld->detection(ui->file->text().toStdString(), this);
}

void Dialog::on_file_textChanged(const QString &arg1)
{
    if(arg1.toStdString() == "")
        ui->evaluate_map->setDisabled(true);
    else
        ui->evaluate_map->setEnabled(true);
}
