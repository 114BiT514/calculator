#ifndef FINANCEDIALOG_H
#define FINANCEDIALOG_H

#include <QDialog>

/*
 * FinanceDialog - 财务参数设置对话框
 * 用于设置财务计算所需的参数（本金、利率、年限、复利方式等）
 * 通过信号与槽将参数传递给主窗口
 */
namespace Ui {
class FinanceDialog;
}

class FinanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FinanceDialog(QWidget *parent = nullptr);
    ~FinanceDialog();

signals:
    /*
     * 当用户点击确定按钮时发出此信号
     * 将财务参数传递给主窗口进行计算
     * @param principal 本金
     * @param rate 年利率（百分比形式，如5表示5%）
     * @param years 年限
     * @param compoundTimes 每年复利次数
     */
    void parametersSet(double principal, double rate, int years, int compoundTimes);

private slots:
    /*
     * 确定按钮槽函数
     * 验证输入参数并发出信号
     */
    void onButtonClick();

private:
    Ui::FinanceDialog *ui;

    /*
     * 验证输入参数是否合法
     */
    bool validateInputs();

    /*
     * 使用 QSettings 加载上次保存的财务参数
     * 实现参数持久化，避免每次重新设置
     */
    void loadSettings();

    /*
     * 使用 QSettings 保存当前财务参数
     * 下次打开对话框时自动恢复
     */
    void saveSettings();
};

#endif // FINANCEDIALOG_H
