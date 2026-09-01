/********************************************************************************
** Form generated from reading UI file 'financedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINANCEDIALOG_H
#define UI_FINANCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FinanceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label_principal;
    QLineEdit *lineEdit_principal;
    QLabel *label_rate;
    QLineEdit *lineEdit_rate;
    QLabel *label_years;
    QSpinBox *spinBox_years;
    QLabel *label_compound;
    QComboBox *comboBox_compound;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FinanceDialog)
    {
        if (FinanceDialog->objectName().isEmpty())
            FinanceDialog->setObjectName(QString::fromUtf8("FinanceDialog"));
        FinanceDialog->resize(400, 250);
        verticalLayout = new QVBoxLayout(FinanceDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(FinanceDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_principal = new QLabel(groupBox);
        label_principal->setObjectName(QString::fromUtf8("label_principal"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_principal);

        lineEdit_principal = new QLineEdit(groupBox);
        lineEdit_principal->setObjectName(QString::fromUtf8("lineEdit_principal"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_principal);

        label_rate = new QLabel(groupBox);
        label_rate->setObjectName(QString::fromUtf8("label_rate"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_rate);

        lineEdit_rate = new QLineEdit(groupBox);
        lineEdit_rate->setObjectName(QString::fromUtf8("lineEdit_rate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_rate);

        label_years = new QLabel(groupBox);
        label_years->setObjectName(QString::fromUtf8("label_years"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_years);

        spinBox_years = new QSpinBox(groupBox);
        spinBox_years->setObjectName(QString::fromUtf8("spinBox_years"));
        spinBox_years->setMinimum(1);
        spinBox_years->setMaximum(50);
        spinBox_years->setValue(1);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBox_years);

        label_compound = new QLabel(groupBox);
        label_compound->setObjectName(QString::fromUtf8("label_compound"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_compound);

        comboBox_compound = new QComboBox(groupBox);
        comboBox_compound->addItem(QString());
        comboBox_compound->addItem(QString());
        comboBox_compound->addItem(QString());
        comboBox_compound->addItem(QString());
        comboBox_compound->setObjectName(QString::fromUtf8("comboBox_compound"));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBox_compound);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(FinanceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(lineEdit_principal, lineEdit_rate);
        QWidget::setTabOrder(lineEdit_rate, spinBox_years);
        QWidget::setTabOrder(spinBox_years, comboBox_compound);

        retranslateUi(FinanceDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, FinanceDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, FinanceDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(FinanceDialog);
    } // setupUi

    void retranslateUi(QDialog *FinanceDialog)
    {
        FinanceDialog->setWindowTitle(QCoreApplication::translate("FinanceDialog", "\350\264\242\345\212\241\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FinanceDialog", "\350\264\242\345\212\241\345\217\202\346\225\260", nullptr));
        label_principal->setText(QCoreApplication::translate("FinanceDialog", "\346\234\254\351\207\221 (\345\205\203)", nullptr));
        label_rate->setText(QCoreApplication::translate("FinanceDialog", "\345\271\264\345\210\251\347\216\207 (%)", nullptr));
        label_years->setText(QCoreApplication::translate("FinanceDialog", "\345\271\264\351\231\220 (\345\271\264)", nullptr));
        label_compound->setText(QCoreApplication::translate("FinanceDialog", "\345\244\215\345\210\251\346\226\271\345\274\217", nullptr));
        comboBox_compound->setItemText(0, QCoreApplication::translate("FinanceDialog", "\346\257\217\345\271\264\345\244\215\345\210\251", nullptr));
        comboBox_compound->setItemText(1, QCoreApplication::translate("FinanceDialog", "\346\257\217\345\215\212\345\271\264\345\244\215\345\210\251", nullptr));
        comboBox_compound->setItemText(2, QCoreApplication::translate("FinanceDialog", "\346\257\217\345\255\243\345\272\246\345\244\215\345\210\251", nullptr));
        comboBox_compound->setItemText(3, QCoreApplication::translate("FinanceDialog", "\346\257\217\346\234\210\345\244\215\345\210\251", nullptr));

    } // retranslateUi

};

namespace Ui {
    class FinanceDialog: public Ui_FinanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINANCEDIALOG_H
