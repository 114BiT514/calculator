#include "calculatorengine.h"
#include <QVector>
#include <QRegularExpression>
#include <cmath>
#include <algorithm>

CalculatorEngine::CalculatorEngine()
{
}

bool CalculatorEngine::calculate(const QString& expression, QString& result)
{
    // 清除之前的错误信息
    errorMessage.clear();

    // 清理表达式
    QString cleaned = cleanExpression(expression);

    // 验证表达式格式
    if (!validateExpression(cleaned)) {
        errorMessage = QString("表达式格式错误");
        return false;
    }

    // 转换为后缀表达式
    QStringList postfix = infixToPostfix(cleaned);

    // 计算后缀表达式
    double res = evaluatePostfix(postfix);

    // 检查计算过程中是否发生错误（如除零）
    if (!errorMessage.isEmpty()) {
        return false;
    }

    // 检查是否溢出
    if (std::isinf(res) || std::isnan(res)) {
        errorMessage = QString("计算结果溢出");
        return false;
    }

    // 格式化结果（去除末尾多余的0）
    result = QString::number(res, 'g', 15);
    return true;
}

double CalculatorEngine::calculateSimpleInterest(double principal, double rate, int years)
{
    // 单利公式: A = P(1 + r*t)
    return principal * (1.0 + rate * years);
}

double CalculatorEngine::calculateCompoundInterest(double principal, double rate, int years, int compoundingPerYear)
{
    // 复利公式: A = P(1 + r/n)^(n*t)
    if (compoundingPerYear <= 0) compoundingPerYear = 1;
    double r = rate / compoundingPerYear;
    int n = compoundingPerYear * years;
    return principal * std::pow(1.0 + r, n);
}

QString CalculatorEngine::getErrorMessage() const
{
    return errorMessage;
}

QString CalculatorEngine::cleanExpression(const QString& expression)
{
    QString cleaned = expression;
    // 去除空格
    cleaned.remove(QRegularExpression("\\s+"));
    // 将中文运算符转换为英文
    cleaned.replace(QChar(0x00D7), '*');  // × 乘法符号
    cleaned.replace(QChar(0x00F7), '/');  // ÷ 除法符号
    return cleaned;
}

bool CalculatorEngine::validateExpression(const QString& expression)
{
    if (expression.isEmpty()) {
        errorMessage = QString("表达式不能为空");
        return false;
    }

    // 不能以运算符开头（除了开头的负号）
    if (expression[0] == '+' || expression[0] == '*' || expression[0] == '/') {
        errorMessage = QString("表达式格式错误");
        return false;
    }

    // 不能以运算符结尾
    if (expression.back() == '+' || expression.back() == '-' ||
        expression.back() == '*' || expression.back() == '/') {
        errorMessage = QString("表达式不能以运算符结尾");
        return false;
    }

    // 检查括号匹配
    int bracketCount = 0;
    for (QChar ch : expression) {
        if (ch == '(') bracketCount++;
        else if (ch == ')') {
            bracketCount--;
            if (bracketCount < 0) {
                errorMessage = QString("括号不匹配");
                return false;
            }
        }
    }
    if (bracketCount != 0) {
        errorMessage = QString("括号不匹配");
        return false;
    }

    // 检查字符合法性
    QRegularExpression re("^[0-9+\\-*/().]+$");
    if (!re.match(expression).hasMatch()) {
        errorMessage = QString("包含非法字符");
        return false;
    }

    // 检查连续小数点
    if (expression.contains("..")) {
        errorMessage = QString("表达式格式错误：连续小数点");
        return false;
    }

    // 检查每个小数点的前后位置是否合法
    for (int i = 0; i < expression.length(); ++i) {
        if (expression[i] == '.') {
            // 小数点前不能是运算符或左括号（也不能在开头）
            if (i == 0 || expression[i-1] == '+' || expression[i-1] == '-' ||
                expression[i-1] == '*' || expression[i-1] == '/' || expression[i-1] == '(') {
                errorMessage = QString("表达式格式错误：小数点位置不合法");
                return false;
            }
            // 小数点后不能是运算符或右括号（也不能在结尾）
            if (i == expression.length() - 1 || expression[i+1] == '+' || expression[i+1] == '-' ||
                expression[i+1] == '*' || expression[i+1] == '/' || expression[i+1] == ')') {
                errorMessage = QString("表达式格式错误：小数点位置不合法");
                return false;
            }
        }
    }

    // 检查运算符是否相邻
    for (int i = 0; i < expression.length() - 1; i++) {
        QChar c1 = expression[i];
        QChar c2 = expression[i + 1];
        bool op1 = (c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/');
        bool op2 = (c2 == '+' || c2 == '-' || c2 == '*' || c2 == '/');
        // 允许负数（减号在开头或左括号后）
        if (op1 && op2 && !(c1 == '(' && c2 == '-')) {
            errorMessage = QString("运算符不能相邻");
            return false;
        }
    }

    return true;
}

QStringList CalculatorEngine::infixToPostfix(const QString& expression)
{
    QStringList postfix;
    QVector<QString> ops;  // Qt6 uses QVector instead of QStack

    QString currentNum;
    for (int i = 0; i < expression.length(); i++) {
        QChar ch = expression[i];

        if (ch.isDigit() || ch == '.') {
            currentNum += ch;
        } else {
            if (!currentNum.isEmpty()) {
                postfix << currentNum;
                currentNum.clear();
            }

            if (ch == '(') {
                ops.push_back(QString(ch));
            } else if (ch == ')') {
                while (!ops.isEmpty() && ops.last() != "(") {
                    postfix << ops.last();
                    ops.pop_back();
                }
                if (!ops.isEmpty()) ops.pop_back(); // 弹出 '('
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                while (!ops.isEmpty() && getPrecedence(ops.last()[0].toLatin1()) >= getPrecedence(ch.toLatin1())) {
                    postfix << ops.last();
                    ops.pop_back();
                }
                ops.push_back(QString(ch));
            }
        }
    }

    if (!currentNum.isEmpty()) {
        postfix << currentNum;
    }

    while (!ops.isEmpty()) {
        postfix << ops.last();
        ops.pop_back();
    }

    return postfix;
}

double CalculatorEngine::evaluatePostfix(const QStringList& postfix)
{
    QVector<double> stack;  // Qt6 uses QVector instead of QStack

    for (const QString& token : postfix) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                errorMessage = QString("表达式格式错误");
                return 0;
            }
            double b = stack.last();
            stack.pop_back();
            double a = stack.last();
            stack.pop_back();
            stack.push_back(applyOperator(a, b, token[0].toLatin1()));
        } else {
            stack.push_back(token.toDouble());
        }
    }

    if (stack.isEmpty()) return 0;
    return stack.last();
}

int CalculatorEngine::getPrecedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double CalculatorEngine::applyOperator(double a, double b, char op)
{
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                errorMessage = QString("除数不能为零");
                return 0;
            }
            return a / b;
        default: return 0;
    }
}