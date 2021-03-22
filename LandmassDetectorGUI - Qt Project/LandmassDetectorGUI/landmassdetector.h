#ifndef LANDMASSDETECTOR_H
#define LANDMASSDETECTOR_H
#pragma once
#include <QMainWindow>
#include "string"
#include "dialog.h"
#include "list"
#include "Landmass.h"

namespace Ui {
class LandmassDetector;
}

class LandmassDetector : public QMainWindow
{
    Q_OBJECT

public:
    explicit LandmassDetector(QWidget *parent = 0);
    ~LandmassDetector();
    void detection(std::string, Dialog*);
private slots:
    void on_another_map_clicked();

private:
    Ui::LandmassDetector *ui;
    list<Landmass> *landmasses;
    void merge_landmasses(int left, int mid, int right, Landmass* lm);
};

#endif // LANDMASSDETECTOR_H
