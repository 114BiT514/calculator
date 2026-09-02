/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *centralLayout;
    QWidget *displayWidget;
    QVBoxLayout *displayLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_in;
    QLabel *label_3;
    QLineEdit *lineEdit_out;
    QWidget *buttonWidget;
    QGridLayout *buttonGrid;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_0;
    QPushButton *pushButton_dot;
    QPushButton *pushButton_add;
    QPushButton *pushButton_minu;
    QPushButton *pushButton_mul;
    QPushButton *pushButton_div;
    QPushButton *pushButton_c;
    QPushButton *pushButton_rm;
    QPushButton *pushButton_cal;
    QPushButton *pushButton;
    QPushButton *pushButton_simple;
    QPushButton *pushButton_compound;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 550);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralLayout = new QVBoxLayout(centralwidget);
        centralLayout->setSpacing(10);
        centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
        centralLayout->setContentsMargins(15, 15, 15, 15);
        displayWidget = new QWidget(centralwidget);
        displayWidget->setObjectName(QString::fromUtf8("displayWidget"));
        displayLayout = new QVBoxLayout(displayWidget);
        displayLayout->setObjectName(QString::fromUtf8("displayLayout"));
        displayLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(displayWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold;"));

        displayLayout->addWidget(label);

        label_2 = new QLabel(displayWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        displayLayout->addWidget(label_2);

        lineEdit_in = new QLineEdit(displayWidget);
        lineEdit_in->setObjectName(QString::fromUtf8("lineEdit_in"));
        lineEdit_in->setReadOnly(true);

        displayLayout->addWidget(lineEdit_in);

        label_3 = new QLabel(displayWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        displayLayout->addWidget(label_3);

        lineEdit_out = new QLineEdit(displayWidget);
        lineEdit_out->setObjectName(QString::fromUtf8("lineEdit_out"));
        lineEdit_out->setReadOnly(true);

        displayLayout->addWidget(lineEdit_out);


        centralLayout->addWidget(displayWidget);

        buttonWidget = new QWidget(centralwidget);
        buttonWidget->setObjectName(QString::fromUtf8("buttonWidget"));
        buttonGrid = new QGridLayout(buttonWidget);
        buttonGrid->setObjectName(QString::fromUtf8("buttonGrid"));
        buttonGrid->setHorizontalSpacing(8);
        buttonGrid->setVerticalSpacing(8);
        buttonGrid->setContentsMargins(0, 0, 0, 0);
        pushButton_7 = new QPushButton(buttonWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_7, 0, 0, 1, 1);

        pushButton_8 = new QPushButton(buttonWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_8, 0, 1, 1, 1);

        pushButton_9 = new QPushButton(buttonWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_9, 0, 2, 1, 1);

        pushButton_4 = new QPushButton(buttonWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(buttonWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(buttonWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_1 = new QPushButton(buttonWidget);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_1, 2, 0, 1, 1);

        pushButton_2 = new QPushButton(buttonWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_2, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(buttonWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_3, 2, 2, 1, 1);

        pushButton_0 = new QPushButton(buttonWidget);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_0, 3, 0, 1, 1);

        pushButton_dot = new QPushButton(buttonWidget);
        pushButton_dot->setObjectName(QString::fromUtf8("pushButton_dot"));
        pushButton_dot->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_dot, 3, 1, 1, 1);

        pushButton_add = new QPushButton(buttonWidget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_add, 0, 3, 1, 1);

        pushButton_minu = new QPushButton(buttonWidget);
        pushButton_minu->setObjectName(QString::fromUtf8("pushButton_minu"));
        pushButton_minu->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_minu, 1, 3, 1, 1);

        pushButton_mul = new QPushButton(buttonWidget);
        pushButton_mul->setObjectName(QString::fromUtf8("pushButton_mul"));
        pushButton_mul->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_mul, 2, 3, 1, 1);

        pushButton_div = new QPushButton(buttonWidget);
        pushButton_div->setObjectName(QString::fromUtf8("pushButton_div"));
        pushButton_div->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_div, 3, 3, 1, 1);

        pushButton_c = new QPushButton(buttonWidget);
        pushButton_c->setObjectName(QString::fromUtf8("pushButton_c"));
        pushButton_c->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_c, 0, 4, 1, 1);

        pushButton_rm = new QPushButton(buttonWidget);
        pushButton_rm->setObjectName(QString::fromUtf8("pushButton_rm"));
        pushButton_rm->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_rm, 1, 4, 1, 1);

        pushButton_cal = new QPushButton(buttonWidget);
        pushButton_cal->setObjectName(QString::fromUtf8("pushButton_cal"));
        pushButton_cal->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_cal, 2, 4, 2, 1);

        pushButton = new QPushButton(buttonWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(120, 40));

        buttonGrid->addWidget(pushButton, 0, 5, 4, 1);

        pushButton_simple = new QPushButton(buttonWidget);
        pushButton_simple->setObjectName(QString::fromUtf8("pushButton_simple"));
        pushButton_simple->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_simple, 4, 0, 1, 2);

        pushButton_compound = new QPushButton(buttonWidget);
        pushButton_compound->setObjectName(QString::fromUtf8("pushButton_compound"));
        pushButton_compound->setMinimumSize(QSize(0, 40));

        buttonGrid->addWidget(pushButton_compound, 4, 2, 1, 2);


        centralLayout->addWidget(buttonWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\264\242\345\212\241\350\256\241\347\256\227\345\231\250", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\264\242\345\212\241\350\256\241\347\256\227\345\231\250", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\241\250\350\276\276\345\274\217", nullptr));
        lineEdit_in->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\350\241\250\350\276\276\345\274\217\346\210\226\346\213\226\346\213\275\346\225\260\345\255\227", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\236\234", nullptr));
        lineEdit_out->setText(QString());
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_dot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pushButton_minu->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_mul->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        pushButton_div->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        pushButton_c->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        pushButton_rm->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_cal->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\264\242\345\212\241\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        pushButton_simple->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\345\215\225\345\210\251", nullptr));
        pushButton_compound->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\345\244\215\345\210\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
