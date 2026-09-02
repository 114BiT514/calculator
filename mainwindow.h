#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "calculatorengine.h"
#include "financedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * MainWindow - 财务计算器主窗口
 * 负责UI显示与用户交互，计算逻辑委托给CalculatorEngine
 * 实现了鼠标拖拽输入功能（重写鼠标事件）
 * 通过信号与槽与FinanceDialog进行跨窗口通信
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /*
     * 重写鼠标按下事件
     * 当用户在数字/运算符按钮上按下鼠标时，记录拖拽开始状态
     * 创建跟随光标的阴影标签
     */
    void mousePressEvent(QMouseEvent *event) override;

    /*
     * 重写鼠标移动事件
     * 更新跟随光标的阴影标签位置
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /*
     * 重写鼠标释放事件
     * 判断释放位置是否在输入区域，如果是则将拖拽内容追加到表达式
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    /*
     * 数字按钮点击槽函数（0-9）
     * 将对应数字追加到表达式
     */
    void onNumberButtonClicked();

    /*
     * 运算符按钮点击槽函数（+,-,×,÷）
     * 将对应运算符追加到表达式
     */
    void onOperatorButtonClicked();

    /*
     * 计算按钮槽函数
     * 调用CalculatorEngine计算表达式并显示结果
     */
    void onCalculateClicked();

    /*
     * 清除按钮槽函数
     * 清空表达式和结果
     */
    void onClearClicked();

    /*
     * 退格按钮槽函数
     * 删除表达式最后一个字符
     */
    void onBackspaceClicked();

    /*
     * 财务参数设置按钮槽函数
     * 打开FinanceDialog对话框
     */
    void onFinanceSettingsClicked();

    /*
     * 接收财务参数信号槽函数
     * 从FinanceDialog接收参数并执行财务计算
     * 这是跨窗口通信的核心槽函数
     */
    void onFinanceParametersSet(double principal, double rate, int years, int compoundTimes);

    /*
     * 单利计算按钮槽函数
     * 打开财务对话框并默认选择单利计算
     */
    void onSimpleInterestClicked();

    /*
     * 复利计算按钮槽函数
     * 打开财务对话框并默认选择复利计算
     */
    void onCompoundInterestClicked();

private:
    Ui::MainWindow *ui;
    CalculatorEngine *m_engine;  // 计算引擎（Model层）

    /*
     * 初始化按钮信号与槽连接
     */
    void setupButtonConnections();

    /*
     * 追加字符到表达式
     */
    void appendToExpression(const QString &text);

    /*
     * 执行四则运算计算
     */
    void performCalculation();

    /*
     * 执行财务计算（单利/复利）
     */
    void performFinanceCalculation(double principal, double rate, int years, int compoundTimes);

    // 鼠标拖拽相关成员
    bool m_isDragging;           // 是否正在拖拽
    QString m_dragText;          // 拖拽的文本内容
    QLabel *m_dragLabel;         // 跟随光标的阴影标签
    QPushButton *m_sourceButton; // 拖拽来源按钮
};

#endif // MAINWINDOW_H
