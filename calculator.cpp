#include "calculator.h"
#include  <QStack>
#include <QString>
#include <QChar>
#include <QDebug>
#include <QtQuick>

calculator::calculator()
{
//    m_exp = '0';
    m_mainResult = '0';
    m_count = 0;
}

calculator::~calculator()
{

}
calculator* calculator::getInstance()
{
    static calculator* m_calculator = nullptr;
    if (m_calculator == nullptr){
        m_calculator = new calculator();
    }
    return m_calculator;
}

int calculator::checkPriority(QChar c)
{
    if (c == '*' || c == '/'){
        return 2;
    }
    else if (c == '+' || c == '-'){
        return 1;
    }
    else{
        return -1;
    }
}

bool calculator::isNumber(QString c)
{
    return (c >= '0' && c <= '9');
}

QString calculator::converInfixToPostfix(QString s)
{
    QStack<QChar> stack;
    stack.push('N');
    int infixLength = s.length();
    QString postfixOutput;

    for (int i = 0; i < infixLength; i++){

            if (s[i] >= '0' && s[i] <= '9') {
                while (isNumber(s[i])) {
                    postfixOutput += s[i];
                    i++;
                    if (i == infixLength)
                        break;
                }
                postfixOutput += ' ';
                i--;
            }
            else if (s[i] == '(')
                stack.push('(');
            else if (s[i] == ')') {
                while (stack.top() != 'N' && stack.top() != '(')
                {
                    QChar c = stack.top();
                    stack.pop();
                    postfixOutput += c;
                    postfixOutput += ' ';
                }
                if (stack.top() == '(') {
                    stack.pop();
                }
            }
            else {
                while (stack.top() != 'N' && checkPriority(s[i]) <= checkPriority(stack.top()))
                {
                    QChar c = stack.top();
                    stack.pop();
                    postfixOutput += c;
                    postfixOutput += ' ';
                }
                QChar tmp = s[i];
                stack.push(tmp);
            }
        }

        while (stack.top() != 'N')
        {
            QChar c = stack.top();
            stack.pop();
            postfixOutput += c;
            postfixOutput += ' ';
        }
    return postfixOutput;
}

int calculator::calculate(QString exp)
{
    QString postfixExp = converInfixToPostfix(exp);
    QStack<int> stk;
    int tmp1, tmp2;
    for (int i = 0; i < postfixExp.length(); i++){
        if (postfixExp[i] == '*'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 * tmp2);
        }
        else if (postfixExp[i] == '/'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 / tmp2);
        }
        else if (postfixExp[i] == '-') {
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 - tmp1);
        }
        else if (postfixExp[i] == '+'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 + tmp2);
        }
        else{
            if (isNumber(postfixExp[i])){
                QString tmp;
                while (isNumber(postfixExp[i])) {
                    tmp += postfixExp[i];
                    i++;
                }
                i--;
                stk.push(tmp.toInt());
            }
        }
    }
    return stk.pop();
}

void calculator::onTestConnect(const QString &msg)
{
    qDebug() << "em lam duoc roi " << msg;
}

void calculator::onDigitClick(QString _digit)
{
    if (_digit == 'C'){
        setMainResult("0");
        m_exp = "";
    }
    else if ((_digit == '+' || _digit == '-' || _digit == '*' || _digit == '/')
             && m_count != 0 && checkPriority(_digit.front()) <= m_prePriority){
            setMainResult(QString::number(calculate(mainResult())));
            m_exp = mainResult();
            m_exp.append(_digit);
            setMainResult(m_exp);
            m_prePriority = checkPriority(_digit.front());
    }
    else if (_digit != '='){
        if (_digit == '+' || _digit == '-' || _digit == '*' || _digit == '/'){
            m_count++;
            m_prePriority = checkPriority(_digit.front());
        }
        m_exp.append(_digit);
        qDebug() << m_exp;
        setMainResult(m_exp);
    }
    else{
        qDebug() << "bieu thuc" << mainResult();
        qDebug() << "hau to" << converInfixToPostfix(mainResult());
        int result = calculate(mainResult());
        setMainResult(QString::number(result));
        qDebug() << "result" << result;
    }
}

QString calculator::mainResult()
{
    return m_mainResult;
}
void calculator::setMainResult(QString _mainResult)
{
    if (m_mainResult == _mainResult)
        return;
    m_mainResult = _mainResult;
    emit mainResultChanged(m_mainResult);
}
