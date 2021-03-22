/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *choose_map;
    QPushButton *evaluate_map;
    QLineEdit *file;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(540, 70);
        choose_map = new QPushButton(Dialog);
        choose_map->setObjectName(QStringLiteral("choose_map"));
        choose_map->setGeometry(QRect(360, 40, 81, 21));
        evaluate_map = new QPushButton(Dialog);
        evaluate_map->setObjectName(QStringLiteral("evaluate_map"));
        evaluate_map->setGeometry(QRect(450, 40, 81, 21));
        file = new QLineEdit(Dialog);
        file->setObjectName(QStringLiteral("file"));
        file->setGeometry(QRect(10, 10, 521, 20));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        choose_map->setText(QApplication::translate("Dialog", "Choose map...", 0));
        evaluate_map->setText(QApplication::translate("Dialog", "Evaluate map", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
