#include "financedialog.h"
#include "ui_financedialog.h"
#include <QMessageBox>
#include <QValidator>

/*
 * FinanceDialog 构造函数
 * 初始化UI并设置默认值
 */
FinanceDialog::FinanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinanceDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("财务参数设置"));
    setModal(true);

    // 连接确定按钮信号与槽
    // 当用户点击确定按钮时，执行参数验证并发送信号
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &FinanceDialog::onButtonClick);
}

FinanceDialog::~FinanceDialog()
{
    delete ui;
}

/*
 * 确定按钮槽函数
 * 验证输入参数后发出 parametersSet 信号
 * 这是跨窗口通信的关键：通过信号将对话框数据传递给主窗口
 */
void FinanceDialog::onButtonClick()
{
    if (validateInputs()) {
        double principal = ui->lineEdit_principal->text().toDouble();
        double rate = ui->lineEdit_rate->text().toDouble();
        int years = ui->spinBox_years->value();
        int compoundTimes = ui->comboBox_compound->currentIndex() + 1; // 1=每年, 2=每半年, 4=每季度, 12=每月

        // 发出信号，将参数传递给主窗口
        emit parametersSet(principal, rate, years, compoundTimes);
        accept(); // 关闭对话框
    }
}

/*
 * 验证输入参数
 * 确保本金、利率、年限等参数在合理范围内
 */
bool FinanceDialog::validateInputs()
{
    // 验证本金
    if (ui->lineEdit_principal->text().isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("请输入本金"));
        return false;
    }
    double principal = ui->lineEdit_principal->text().toDouble();
    if (principal <= 0) {
        QMessageBox::warning(this, tr("输入错误"), tr("本金必须大于0"));
        return false;
    }

    // 验证利率
    if (ui->lineEdit_rate->text().isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("请输入年利率"));
        return false;
    }
    double rate = ui->lineEdit_rate->text().toDouble();
    if (rate < 0 || rate > 100) {
        QMessageBox::warning(this, tr("输入错误"), tr("年利率必须在0-100之间"));
        return false;
    }

    return true;
}
