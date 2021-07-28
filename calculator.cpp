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
    m_done = false;
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
    if (c == 'x' || c == u'÷'){
        return 2;
    }
    else if (c == '+' || c == '-'){
        return 1;
    }
    else{
        return -1;
    }
}

bool calculator::isNumber(QChar c)
{
    return (c >= '0' && c <= '9');
}

bool calculator::isOperator(QChar c)
{
    return (c == '+' || c == '-' || c == 'x' || c == u'÷');
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
        if (postfixExp[i] == 'x'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 * tmp2);
        }
        else if (postfixExp[i] == u'÷'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 / tmp1);
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

void calculator::onDigitClick(QString _digit)
{
    if (_digit == 'C'){
        setMainResult("0");
        setExpResult("");
        m_exp = "";
        m_digit = "";
        m_done = false;
    }
    else if (_digit == "del"){
        qDebug() << "del";
        m_exp.remove(m_exp.length() - 1,m_exp.length());
        setExpResult(m_exp);
        m_digit.remove(m_digit.length() - 1, m_digit.length());
        setMainResult(m_digit);
    }
    else if ((_digit == '+' || _digit == '-' || _digit == 'x' || _digit == u'÷')
             && m_count != 0 && checkPriority(_digit.front()) <= m_prePriority && m_done == false){
            setMainResult(QString::number(calculate(expResult())));
            m_digit = "";
            m_exp.append(_digit);
            setExpResult(m_exp);
            m_prePriority = checkPriority(_digit.front());
    }
    else if (_digit != '='){
        if (m_done){
            setExpResult(mainResult());
            if (mainResult().toInt() < 0 && isOperator(_digit.front())){
                m_exp = "(0";
                m_exp.append(mainResult());
                m_exp.append(")");
            }
            else{
                m_exp = mainResult();
            }
            m_digit = "";
            m_done = false;
        }
        if (_digit == '+' || _digit == '-' || _digit == 'x' || _digit == u'÷'){
//            if (isOperator(m_exp.back())){
//                m_exp.remove(m_exp.length() - 1,m_exp.length());
//                setExpResult(m_exp);
//                m_exp.append(_digit);
//                setExpResult(m_exp);
//             }
            // stuck here
            if (_digit == '-' && (m_exp.isEmpty() || isOperator(m_exp.back()) || m_exp.back() == '(')){
                m_exp.append("(0-");
                m_digit = _digit;
                m_negate = true;
            }
            else{
                m_count++;
                m_prePriority = checkPriority(_digit.front());
                m_exp.append(_digit);
                m_digit = "";
            }
        }
        else{
            if (m_exp == mainResult())
                m_exp = "";
            m_exp.append(_digit);
            if (m_negate){
                m_exp.append(")");
                m_negate = false;
            }
            qDebug() << m_exp;
            m_digit.append(_digit);
            setMainResult(m_digit);
        }
        setExpResult(m_exp);
    }
    else{
        qDebug() << "bieu thuc" << expResult();
        qDebug() << "hau to" << converInfixToPostfix(expResult());
        int result = calculate(expResult());
        setMainResult(QString::number(result));
        m_exp.append(_digit);
        setExpResult(m_exp);
        m_done  = true;
        qDebug() << "result" << result;
        qDebug() << "m_done" << m_done;
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

QString calculator::expResult()
{
//    for (int i = 0; i < m_expResult.length(); i++){
//        if (m_expResult[i] == '-' && (!isNumber(m_expResult[i-1]) || m_expResult[i-1] != ')'))
//            m_expResult.insert(i - 1,'0');
//    }
    return m_expResult;
}

void calculator::setExpResult(QString _exp)
{
//    for (int i = 0; i < _exp.length(); i++){
//        if (_exp[i] == '0' && _exp[i+1] == '-'){
//            _exp.remove(i,i);
//        }
//    }
    if (m_expResult == _exp)
        return;
    m_expResult = _exp;
    emit expResultChanged(m_expResult);
}
