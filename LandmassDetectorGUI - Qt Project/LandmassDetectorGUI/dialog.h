#ifndef DIALOG_H
#define DIALOG_H
#pragma once
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_choose_map_clicked();
    void on_evaluate_map_clicked();
    void on_file_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
