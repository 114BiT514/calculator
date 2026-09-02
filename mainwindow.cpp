#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QPoint>
#include <QApplication>
#include <QSettings>
#include <QFont>
#include <cmath>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_engine(new CalculatorEngine())
    , m_isDragging(false)
    , m_dragLabel(nullptr)
    , m_sourceButton(nullptr)
{
    ui->setupUi(this);
    
    // 启用鼠标跟踪，确保 mouseMoveEvent 能正常触发
    setMouseTracking(true);
    
    // 设置窗口大小
    resize(700, 500);
    
    // 初始化按钮信号与槽连接
    setupButtonConnections();
    
    /*
     * 为数字/运算符按钮安装事件过滤器
     * 用于拦截鼠标按下事件以启动拖拽操作
     * QPushButton 会消费自己的鼠标事件，必须用事件过滤器提前拦截
     */
    QPushButton *dragButtons[] = {
        ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
        ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
        ui->pushButton_6, ui->pushButton_7, ui->pushButton_8,
        ui->pushButton_9, ui->pushButton_dot,
        ui->pushButton_add, ui->pushButton_minu,
        ui->pushButton_mul, ui->pushButton_div
    };
    for (auto btn : dragButtons) {
        btn->installEventFilter(this);
    }
    
    /*
     * 在全局层面安装事件过滤器以捕获鼠标释放事件
     * 这是因为拖拽释放可能发生在窗口任何位置（包括输入区域）
     */
    qApp->installEventFilter(this);
    
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
    
    // 加载保存的财务参数
    loadFinanceSettings();
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
    /*
     * 清除按钮（C）：清空表达式输入和结果显示
     */
    connect(ui->pushButton_c, &QPushButton::clicked, this, &MainWindow::onClearClicked);

    /*
     * 小数点按钮：追加小数点到表达式
     */
    connect(ui->pushButton_dot, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);

    // 连接财务参数设置按钮
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onFinanceSettingsClicked);

    /*
     * 财务计算按钮：点击后打开财务参数对话框
     * 单利/复利按钮都打开同一个对话框，区别在于选择计算方式
     */
    connect(ui->pushButton_simple, &QPushButton::clicked, this, &MainWindow::onSimpleInterestClicked);
    connect(ui->pushButton_compound, &QPushButton::clicked, this, &MainWindow::onCompoundInterestClicked);
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
    setResultStyle(false);
    statusBar()->showMessage("已清除");
}

/*
 * 退格功能
 * 删除表达式最后一个字符，并清空之前的结果
 */
void MainWindow::onBackspaceClicked()
{
    // 退格时也清空之前的结果
    if (!ui->lineEdit_out->text().isEmpty()) {
        ui->lineEdit_out->clear();
        setResultStyle(true);
    }
    QString expr = ui->lineEdit_in->text();
    if (!expr.isEmpty()) {
        expr.chop(1);
        ui->lineEdit_in->setText(expr);
    }
    
    // 实时预览计算结果
    previewResult();
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
 * 加载保存的财务参数
 */
void MainWindow::loadFinanceSettings()
{
    QSettings settings("CalculatorOrg", "FinancialCalculator");
    m_principal = settings.value("principal", 10000.0).toDouble();
    m_rate = settings.value("rate", 5.0).toDouble();
    m_years = settings.value("years", 1).toInt();
    m_compoundTimes = settings.value("compoundTimes", 12).toInt();
}

/*
 * 单利计算按钮点击处理
 * 直接使用保存的财务参数进行单利计算
 */
void MainWindow::onSimpleInterestClicked()
{
    loadFinanceSettings();
    
    double rateDecimal = m_rate / 100.0;
    double result = m_engine->calculateSimpleInterest(m_principal, rateDecimal, m_years);
    
    QString msg = QString("单利计算结果\n\n")
                + QString("本金: ¥%1\n").arg(m_principal, 0, 'f', 2)
                + QString("年利率: %1%\n").arg(m_rate)
                + QString("年限: %1年\n").arg(m_years)
                + QString("\n本息和: ¥%1\n").arg(result, 0, 'f', 2)
                + QString("利息: ¥%1").arg(result - m_principal, 0, 'f', 2);
    
    ui->lineEdit_out->setText(QString("单利: ¥%1").arg(result, 0, 'f', 2));
    setResultStyle(false);
    QMessageBox::information(this, "单利计算结果", msg);
    statusBar()->showMessage("单利计算完成");
}

/*
 * 复利计算按钮点击处理
 * 直接使用保存的财务参数进行复利计算
 */
void MainWindow::onCompoundInterestClicked()
{
    loadFinanceSettings();
    
    double rateDecimal = m_rate / 100.0;
    double result = m_engine->calculateCompoundInterest(m_principal, rateDecimal, m_years, m_compoundTimes);
    
    QString msg = QString("复利计算结果\n\n")
                + QString("本金: ¥%1\n").arg(m_principal, 0, 'f', 2)
                + QString("年利率: %1%\n").arg(m_rate)
                + QString("年限: %1年\n").arg(m_years)
                + QString("复利次数: %1次/年\n\n").arg(m_compoundTimes)
                + QString("本息和: ¥%1\n").arg(result, 0, 'f', 2)
                + QString("利息: ¥%1").arg(result - m_principal, 0, 'f', 2);
    
    ui->lineEdit_out->setText(QString("复利: ¥%1").arg(result, 0, 'f', 2));
    setResultStyle(false);
    QMessageBox::information(this, "复利计算结果", msg);
    statusBar()->showMessage("复利计算完成");
}

/*
 * 追加文本到表达式输入框
 * 如果结果显示区域已有内容，新输入时先清空结果
 */
void MainWindow::appendToExpression(const QString &text)
{
    // 如果结果显示区域有内容，新输入时先清空结果
    if (!ui->lineEdit_out->text().isEmpty()) {
        ui->lineEdit_out->clear();
        // 重置为默认样式
        setResultStyle(true);
    }
    ui->lineEdit_in->setText(ui->lineEdit_in->text() + text);
    
    // 实时预览计算结果
    previewResult();
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
        // 正式结果以黑色显示
        setResultStyle(false);
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
 * 事件过滤器（事件驱动编程）
 * 拦截按钮的鼠标按下事件以启动拖拽，拦截全局鼠标释放以完成拖拽
 * 
 * 选择事件过滤器而非单纯重写虚函数的原因：
 * 1. QPushButton 会消费自己的鼠标事件，MainWindow::mousePressEvent 无法收到
 * 2. 事件过滤器可以在事件被目标控件处理之前或同时拦截
 * 3. 安装在全局(qApp)上可以捕获任意位置的鼠标释放事件
 * 4. 同时监听多个控件的事件，代码更集中
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    /*
     * 拦截按钮的鼠标按下事件：启动拖拽
     */
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPushButton *btn = qobject_cast<QPushButton*>(obj);
        
        if (btn && mouseEvent->button() == Qt::LeftButton) {
            m_isDragging = true;
            m_sourceButton = btn;
            
            // 获取按钮文本作为拖拽内容
            m_dragText = btn->text();
            // 转换显示符号为计算符号
            if (m_dragText == "×") m_dragText = "*";
            else if (m_dragText == "÷") m_dragText = "/";
            
            // 设置并显示拖拽标签（使用窗口局部坐标）
            m_dragLabel->setText(m_dragText);
            m_dragLabel->move(mapFromGlobal(mouseEvent->globalPosition().toPoint()));
            m_dragLabel->show();
            m_dragLabel->raise();
            
            statusBar()->showMessage(QString("拖拽 %1 到输入区域").arg(btn->text()));
            
            // 返回 false：让按钮也能正常响应点击事件（点击和拖拽共存）
            return false;
        }
    }
    
    /*
     * 拦截全局鼠标移动事件：拖拽标签跟随光标
     * 安装在全局(qApp)上，确保无论鼠标在哪个控件上移动都能捕获
     */
    if (m_isDragging && event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        m_dragLabel->move(mapFromGlobal(mouseEvent->globalPosition().toPoint()));
        return false;
    }
    
    /*
     * 拦截全局鼠标释放事件：完成拖拽
     * 安装在全局(qApp)上，确保无论鼠标在哪个控件上释放都能捕获
     */
    if (m_isDragging && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        m_isDragging = false;
        m_dragLabel->hide();
        
        // 检查释放位置是否在输入区域
        QPoint globalPos = mouseEvent->globalPosition().toPoint();
        QPoint localPos = ui->lineEdit_in->mapFromGlobal(globalPos);
        
        if (ui->lineEdit_in->rect().contains(localPos)) {
            appendToExpression(m_dragText);
            statusBar()->showMessage(QString("已添加 %1").arg(m_sourceButton->text()));
        } else {
            statusBar()->showMessage("拖拽取消");
        }
        
        m_sourceButton = nullptr;
        m_dragText.clear();
        
        return false;
    }
    
    return QMainWindow::eventFilter(obj, event);
}

/*
 * 鼠标移动事件处理
 * 更新跟随光标的阴影标签位置
 * 与 eventFilter 配合使用：eventFilter 启动拖拽，mouseMoveEvent 更新位置
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        // 更新拖拽标签位置，使其跟随光标
        m_dragLabel->move(mapFromGlobal(event->globalPosition().toPoint()));
    }
    
    QMainWindow::mouseMoveEvent(event);
}

/*
 * 鼠标释放事件（保留但不再处理拖拽）
 * 拖拽释放逻辑已移至 eventFilter 中处理（安装在全局 qApp 上）
 * 此处保留虚函数重写仅用于满足作业要求：体现虚函数重写的使用
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QMainWindow::mouseReleaseEvent(event);
}

/*
 * 实时预览计算结果（以灰色显示）
 * 当用户输入表达式时，尝试进行计算：
 * - 如果表达式可计算，则在结果框中以灰色显示预览结果
 * - 如果表达式不完整或有语法错误，保持结果框不变
 */
void MainWindow::previewResult()
{
    QString expression = ui->lineEdit_in->text();
    if (expression.isEmpty()) {
        ui->lineEdit_out->clear();
        return;
    }
    
    QString result;
    if (m_engine->calculate(expression, result)) {
        ui->lineEdit_out->setText(result);
        // 预览结果以灰色显示
        setResultStyle(true);
    }
    // 如果表达式不完整无法计算，不改变结果框
}

/*
 * 设置结果框样式
 * @param isPreview true为预览模式（灰色），false为正式结果（黑色）
 */
void MainWindow::setResultStyle(bool isPreview)
{
    if (isPreview) {
        // 预览模式：灰色文字
        ui->lineEdit_out->setStyleSheet(
            "QLineEdit {"
            "    background-color: #f9f9f9;"
            "    border: 2px solid #bdc3c7;"
            "    border-radius: 5px;"
            "    padding: 5px;"
            "    font-size: 16px;"
            "    color: #999999;"
            "}"
        );
    } else {
        // 正式结果：黑色文字
        ui->lineEdit_out->setStyleSheet(
            "QLineEdit {"
            "    background-color: white;"
            "    border: 2px solid #27ae60;"
            "    border-radius: 5px;"
            "    padding: 5px;"
            "    font-size: 16px;"
            "    color: black;"
            "}"
        );
    }
}

