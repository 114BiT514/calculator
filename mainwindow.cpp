#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QPoint>
#include <QApplication>
#include <QClipboard>
#include <QFont>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_engine(new CalculatorEngine())
    , m_isDragging(false)
    , m_dragLabel(nullptr)
    , m_sourceButton(nullptr)
{
    ui->setupUi(this);
    
    // 设置窗口大小
    resize(700, 500);
    
    // 初始化按钮信号与槽连接
    setupButtonConnections();
    
    // 初始化拖拽标签
    m_dragLabel = new QLabel(this);
    m_dragLabel->setStyleSheet(
        "background-color: rgba(0, 0, 0, 150);"
        "color: white;"
        "border-radius: 5px;"
        "padding: 5px 10px;"
        "font-size: 14px;"
    );
    m_dragLabel->hide();
    
    // 设置输入区域样式，表示可以接收拖拽
    ui->lineEdit_in->setStyleSheet(
        "QLineEdit {"
        "    background-color: #f5f5f5;"
        "    border: 2px solid #4a90d9;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 16px;"
        "}"
    );
    
    // 在状态栏显示提示信息
    statusBar()->showMessage("欢迎使用财务计算器 - 可以点击按钮或拖拽数字/运算符到输入区域");
}

MainWindow::~MainWindow()
{
    delete m_dragLabel;
    delete m_engine;
    delete ui;
}

void MainWindow::setupButtonConnections()
{
    /*
     * 信号与槽连接说明：
     * 将数字按钮与 onNumberButtonClicked 槽函数连接
     * 使用 sender() 获取触发信号的按钮对象
     */
    
    // 连接数字按钮 0-9
    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    
    // 连接运算符按钮
    connect(ui->pushButton_add, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);
    connect(ui->pushButton_minu, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);
    connect(ui->pushButton_mul, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);
    connect(ui->pushButton_div, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);
    
    // 连接功能按钮
    connect(ui->pushButton_cal, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);
    connect(ui->pushButton_rm, &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);
    
    // 连接财务参数设置按钮
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onFinanceSettingsClicked);
}

/*
 * 数字按钮点击处理
 * 获取发送信号的按钮文本并追加到表达式
 */
void MainWindow::onNumberButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        appendToExpression(btn->text());
    }
}

/*
 * 运算符按钮点击处理
 * 将UI显示的运算符转换为计算引擎可识别的符号
 */
void MainWindow::onOperatorButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        QString op = btn->text();
        // 将显示符号转换为计算符号
        if (op == "×") {
            appendToExpression("*");
        } else if (op == "÷") {
            appendToExpression("/");
        } else {
            appendToExpression(op);
        }
    }
}

void MainWindow::onCalculateClicked()
{
    performCalculation();
}

/*
 * 清除功能
 * 清空表达式和结果显示
 */
void MainWindow::onClearClicked()
{
    ui->lineEdit_in->clear();
    ui->lineEdit_out->clear();
    statusBar()->showMessage("已清除");
}

/*
 * 退格功能
 * 删除表达式最后一个字符
 */
void MainWindow::onBackspaceClicked()
{
    QString expr = ui->lineEdit_in->text();
    if (!expr.isEmpty()) {
        expr.chop(1);
        ui->lineEdit_in->setText(expr);
    }
}

/*
 * 打开财务参数设置对话框
 * 通过信号与槽实现跨窗口通信
 */
void MainWindow::onFinanceSettingsClicked()
{
    FinanceDialog *dialog = new FinanceDialog(this);
    /*
     * 跨窗口通信示例：
     * 当对话框发出 parametersSet 信号时，调用 onFinanceParametersSet 槽函数
     * 这是Qt信号与槽机制的典型应用
     */
    connect(dialog, &FinanceDialog::parametersSet,
            this, &MainWindow::onFinanceParametersSet);
    dialog->exec();
    delete dialog;
}

/*
 * 接收财务参数并执行计算
 * 这是跨窗口通信的接收端槽函数
 */
void MainWindow::onFinanceParametersSet(double principal, double rate, int years, int compoundTimes)
{
    performFinanceCalculation(principal, rate, years, compoundTimes);
}

/*
 * 追加文本到表达式输入框
 */
void MainWindow::appendToExpression(const QString &text)
{
    ui->lineEdit_in->setText(ui->lineEdit_in->text() + text);
}

/*
 * 执行四则运算计算
 * 调用CalculatorEngine进行计算并处理结果
 */
void MainWindow::performCalculation()
{
    QString expression = ui->lineEdit_in->text();
    if (expression.isEmpty()) {
        statusBar()->showMessage("请输入表达式");
        return;
    }
    
    QString result;
    if (m_engine->calculate(expression, result)) {
        ui->lineEdit_out->setText(result);
        statusBar()->showMessage("计算完成");
    } else {
        /*
         * 错误处理：当计算失败时，通过状态栏和消息框提示用户
         * 保证程序不会因错误而崩溃
         */
        QString errorMsg = m_engine->getErrorMessage();
        statusBar()->showMessage(errorMsg);
        QMessageBox::warning(this, "计算错误", errorMsg);
    }
}

/*
 * 执行财务计算
 * 分别计算单利和复利结果并显示
 */
void MainWindow::performFinanceCalculation(double principal, double rate, int years, int compoundTimes)
{
    // 将百分比利率转换为小数
    double rateDecimal = rate / 100.0;
    
    // 计算单利：A = P(1 + r*t)
    double simpleResult = m_engine->calculateSimpleInterest(principal, rateDecimal, years);
    
    // 计算复利：A = P(1 + r/n)^(n*t)
    double compoundResult = m_engine->calculateCompoundInterest(principal, rateDecimal, years, compoundTimes);
    
    // 格式化结果显示
    QString result = QString("本金: ¥%1\n")
                      .arg(principal, 0, 'f', 2)
                   + QString("年利率: %1%\n").arg(rate)
                   + QString("年限: %1年\n").arg(years)
                   + QString("复利次数: %1次/年\n\n").arg(compoundTimes)
                   + QString("单利本息和: ¥%1\n").arg(simpleResult, 0, 'f', 2)
                   + QString("复利本息和: ¥%1\n").arg(compoundResult, 0, 'f', 2)
                   + QString("利息收入: ¥%1").arg(compoundResult - principal, 0, 'f', 2);
    
    // 在结果显示区域显示财务计算结果
    ui->lineEdit_out->setText(QString("单利: ¥%1  复利: ¥%2")
                               .arg(simpleResult, 0, 'f', 2)
                               .arg(compoundResult, 0, 'f', 2));
    
    // 使用消息框显示详细结果
    QMessageBox::information(this, "财务计算结果", result);
    statusBar()->showMessage("财务计算完成");
}

/*
 * 鼠标按下事件处理（事件驱动编程 - 虚函数重写）
 * 选择重写鼠标事件而非事件过滤器的原因：
 * 1. 需要在主窗口级别拦截所有鼠标事件
 * 2. 拖拽逻辑与窗口本身紧密相关，不适合单独安装在某个控件上
 * 3. 虚函数重写代码更清晰，易于理解
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        /*
         * 检查鼠标点击位置是否在某个按钮上
         * 如果是，则开始拖拽操作
         */
        QPoint pos = event->pos();
        
        // 检查所有数字按钮
        QPushButton *buttons[] = {
            ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
            ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
            ui->pushButton_6, ui->pushButton_7, ui->pushButton_8,
            ui->pushButton_9,
            ui->pushButton_add, ui->pushButton_minu,
            ui->pushButton_mul, ui->pushButton_div
        };
        
        for (QPushButton *btn : buttons) {
            if (btn->geometry().contains(pos)) {
                m_isDragging = true;
                m_sourceButton = btn;
                
                // 获取按钮文本作为拖拽内容
                m_dragText = btn->text();
                // 转换显示符号为计算符号
                if (m_dragText == "×") m_dragText = "*";
                else if (m_dragText == "÷") m_dragText = "/";
                
                // 设置并显示拖拽标签
                m_dragLabel->setText(m_dragText);
                m_dragLabel->move(event->globalPosition().toPoint() + QPoint(10, 10));
                m_dragLabel->show();
                
                statusBar()->showMessage(QString("拖拽 %1 到输入区域").arg(btn->text()));
                break;
            }
        }
    }
    
    QMainWindow::mousePressEvent(event);
}

/*
 * 鼠标移动事件处理
 * 更新跟随光标的阴影标签位置
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        // 更新拖拽标签位置，使其跟随光标
        m_dragLabel->move(event->globalPosition().toPoint() + QPoint(10, 10));
    }
    
    QMainWindow::mouseMoveEvent(event);
}

/*
 * 鼠标释放事件处理
 * 判断释放位置是否在输入区域，如果是则将拖拽内容追加到表达式
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        m_isDragging = false;
        m_dragLabel->hide();
        
        /*
         * 检查释放位置是否在输入区域
         * 如果是，则将拖拽内容追加到表达式
         */
        QPoint globalPos = event->globalPosition().toPoint();
        QPoint localPos = ui->lineEdit_in->mapFromGlobal(globalPos);
        
        if (ui->lineEdit_in->geometry().contains(localPos)) {
            // 释放位置在输入区域，追加内容
            appendToExpression(m_dragText);
            statusBar()->showMessage(QString("已添加 %1").arg(m_sourceButton->text()));
        } else {
            statusBar()->showMessage("拖拽取消");
        }
        
        m_sourceButton = nullptr;
        m_dragText.clear();
    }
    
    QMainWindow::mouseReleaseEvent(event);
}

