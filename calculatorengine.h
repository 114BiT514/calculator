#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QString>
#include <QStringList>
#include <QPair>

/*
 * CalculatorEngine - 独立的计算逻辑类（Model层）
 * 负责四则运算、单利/复利计算等核心逻辑
 * 与UI层完全分离，便于测试和维护
 */
class CalculatorEngine
{
public:
    CalculatorEngine();

    /*
     * 四则运算计算
     * @param expression 表达式字符串，如 "1+2*3"
     * @param result 输出参数，计算结果
     * @return 成功返回true，失败返回false（错误信息存储在errorMessage中）
     */
    bool calculate(const QString& expression, QString& result);

    /*
     * 单利计算
     * @param principal 本金
     * @param rate 年利率（小数形式，如0.05表示5%）
     * @param years 年限
     * @return 本息和
     * 公式: A = P(1 + r*t)
     */
    double calculateSimpleInterest(double principal, double rate, int years);

    /*
     * 复利计算
     * @param principal 本金
     * @param rate 年利率（小数形式，如0.05表示5%）
     * @param years 年限
     * @param compoundingPerYear 每年复利次数（默认为12，即按月复利）
     * @return 本息和
     * 公式: A = P(1 + r/n)^(n*t)
     */
    double calculateCompoundInterest(double principal, double rate, int years,
                                     int compoundingPerYear = 12);

    /*
     * 获取最后一次错误信息
     */
    QString getErrorMessage() const;

private:
    QString errorMessage;

    /*
     * 将中缀表达式转换为后缀表达式（逆波兰表达式）
     * 使用调度场算法（Shunting Yard Algorithm）
     */
    QStringList infixToPostfix(const QString& expression);

    /*
     * 计算后缀表达式的值
     */
    double evaluatePostfix(const QStringList& postfix);

    /*
     * 获取运算符优先级
     */
    int getPrecedence(char op);

    /*
     * 执行二元运算
     */
    double applyOperator(double a, double b, char op);

    /*
     * 清理表达式（去除空格等）
     */
    QString cleanExpression(const QString& expression);

    /*
     * 验证表达式格式
     */
    bool validateExpression(const QString& expression);
};

#endif // CALCULATORENGINE_H