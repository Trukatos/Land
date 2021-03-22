/********************************************************************************
** Form generated from reading UI file 'landmassdetector.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANDMASSDETECTOR_H
#define UI_LANDMASSDETECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LandmassDetector
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LandmassDetector)
    {
        if (LandmassDetector->objectName().isEmpty())
            LandmassDetector->setObjectName(QStringLiteral("LandmassDetector"));
        LandmassDetector->resize(1106, 522);
        centralWidget = new QWidget(LandmassDetector);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LandmassDetector->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LandmassDetector);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1106, 21));
        LandmassDetector->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LandmassDetector);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LandmassDetector->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LandmassDetector);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LandmassDetector->setStatusBar(statusBar);

        retranslateUi(LandmassDetector);

        QMetaObject::connectSlotsByName(LandmassDetector);
    } // setupUi

    void retranslateUi(QMainWindow *LandmassDetector)
    {
        LandmassDetector->setWindowTitle(QApplication::translate("LandmassDetector", "LandmassDetector", 0));
    } // retranslateUi

};

namespace Ui {
    class LandmassDetector: public Ui_LandmassDetector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANDMASSDETECTOR_H
