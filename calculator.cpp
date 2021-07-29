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
    m_countOperator = 0;
    m_binResult = '0';
    m_decResult = '0';
    m_hexResult = '0';
    m_octResult = '0';
    m_done = false;
    m_needclose = false;
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

QString calculator::convertInfixToPostfix(QString s)
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
    QString postfixExp = convertInfixToPostfix(exp);
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

void calculator::onOperatorClick(QString _operator)
{
    if (_operator == '='){
        qDebug() << "bieu thuc" << expResult();
        qDebug() << "hau to" << convertInfixToPostfix(expResult());
        int result = calculate(expResult());
        setMainResult(QString::number(result));
        setSubResult(mainResult());;
        m_exp.append(_operator);
        setExpResult(m_exp);
        m_done  = true;
        m_countOperator = 0;
        m_prePriority = 0;
        qDebug() << "result" << result;
        qDebug() << "m_done" << m_done;
    }
    else if (_operator == "del"){
        m_exp.remove(m_exp.length() - 1,m_exp.length());
        setExpResult(m_exp);
        m_digit.remove(m_digit.length() - 1, m_digit.length());
        setMainResult(m_digit);
        setSubResult(m_digit);
    }
    else if (m_done == true){
        if (mainResult().toInt() < 0){
            m_exp = "(0";
            m_exp.append(mainResult());
            m_exp.append(")");
            m_exp.append(_operator);
            setExpResult(m_exp);
        }
        else{
            m_exp = mainResult();
            m_exp.append(_operator);
            setExpResult(m_exp);
        }
        m_digit = "";
        m_done = false;
    }
    else{
        if (m_exp.isEmpty() || m_exp.back() == '('){
            m_exp.append("(0");
            m_exp.append(_operator);
            setExpResult(m_exp);
            m_needclose = true;
        }
        else if (isOperator(m_exp.back())){
            m_exp.remove(m_exp.length() - 1,m_exp.length());
            setExpResult(m_exp);
            m_exp.append(_operator);
            setExpResult(m_exp);
        }
        else if (checkPriority(_operator.back()) <= m_prePriority && m_countOperator != 0 && m_done == false){
            setMainResult(QString::number(calculate(expResult())));
            setSubResult(mainResult());
            m_digit = "";
            m_exp.append(_operator);
            setExpResult(m_exp);
            m_prePriority = checkPriority(_operator.back());
        }
        else{
            m_countOperator++;
            m_prePriority = checkPriority(_operator.back());
            m_exp.append(_operator);
            setExpResult(m_exp);
            m_digit = "";
        }
    }
}

void calculator::onDigitClick(QString _digit)
{
    if (_digit == 'C'){
        setMainResult("0");
        setSubResult("0");
        setExpResult("");
        setBinResult("0");
        setHexResult("0");
        m_exp = "";
        m_digit = "";
        m_done = false;
        m_prePriority = 0;
        m_countOperator = 0;
    }
    else {
        if (m_done == true){
            m_exp = "";
            setExpResult(m_exp);
            m_digit = _digit;
            m_exp = _digit;
            setMainResult(m_digit);
            setSubResult(m_digit);
            m_done = false;
        }
        else if (m_needclose == true){
            m_exp.append(_digit);
            m_exp.append(")");
            m_needclose = false;

            setExpResult(m_exp);
            m_digit.append(_digit);
            setMainResult(m_digit);
            setSubResult(m_digit);
        }
        else{
            m_exp.append(_digit);
            m_digit.append(_digit);
            qDebug() << m_exp;
            setExpResult(m_exp);
            setMainResult(m_digit);
            setSubResult(m_digit);
        }
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
    return m_expResult;
}

void calculator::setExpResult(QString _exp)
{
    if (m_expResult == _exp)
        return;
    m_expResult = _exp;
    emit expResultChanged(m_expResult);
}

QString calculator::binResult()
{
    return m_binResult;
}

void calculator::setBinResult(QString _binResult)
{
    if (m_binResult == _binResult)
        return;
    m_binResult = _binResult;
    emit binResultChanged(m_binResult);
}

QString calculator::decResult()
{
    return m_decResult;
}

void calculator::setDecResult(QString _decResult)
{
    if (m_decResult == _decResult)
        return;
    m_decResult = _decResult;
    emit decResultChanged(m_decResult);
}

QString calculator::octResult()
{
    return m_octResult;
}

void calculator::setOctResult(QString _octResult)
{
    if (m_octResult == _octResult)
        return;
    m_octResult = _octResult;
    emit octResultChanged(m_octResult);
}

QString calculator::hexResult()
{
    return m_hexResult;
}

void calculator::setHexResult(QString _hexResult)
{
    if (m_hexResult == _hexResult)
        return;
    m_hexResult = _hexResult;
    emit hexResultChanged(m_hexResult);
}

QString calculator::DectoBin(int _dec)
{
    QString s;
    for( ; _dec > 0; _dec /= 2 )
        s = QString::number(_dec % 2) + s;

    if (s.length() < 5){
        for (int i = 0; i <= 5 - s.length(); i++){
            s = '0' + s;
        }
    }
    return s;
}

QString calculator::convertDectoBin(int _dec)
{
    if (_dec > 0){
        return DectoBin(_dec);
    }
    else{
        int nDec = -_dec;
        return negativeDectoBin(DectoBin(nDec));
    }
}

int calculator::convertDectoOct(int _dec)
{
    int p = 0;
    int octNumber = 0;
    while(_dec > 0){
        octNumber += (_dec % 8) * pow(10, p);
        p++;
        _dec /= 8;
     }
    return octNumber;
}

QString calculator::convertDectoHex(int _dec)
{
    int r;
    QString hex_number = "";
    QChar hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    while (_dec > 0) {
        r = _dec % 16;
        hex_number = hex[r] + hex_number;
        _dec = _dec/16;
    }
    return hex_number;
}

void calculator::setSubResult(QString _result)
{
    qDebug() << "C:" << _result.toInt();
    QString hex = convertDectoHex(_result.toInt());
    qDebug() << "hex" << hex;
    setHexResult(hex);

    setDecResult(_result);

    int oct = convertDectoOct(_result.toInt());
    qDebug() << "oct" << oct;
    setOctResult(QString::number(oct));

    QString bin = convertDectoBin(_result.toInt());
    qDebug() << "bin" << bin;
    setBinResult(bin);
}

QString calculator::negativeDectoBin(QString a)
{
    QString b = "";
    QString c ="";
    QString tmp = "0";
    for (int i = 0; i < a.length(); i++){
        if (a[i] == '0')
            a[i] = '1';
        else
            a[i] = '0';
    }
    qDebug() << "String a: " << a;
    for (int i = 0; i < a.length(); i++){
        b.append('0');
        if (i == a.length() - 1)
           b[i] = '1';
    }
    qDebug() << "b: " << b;
    for (int i = a.length() - 1 ; i >= 0; i--){
        if (a[i] == b[i]){
            if (a[i] == '0' && tmp == '1'){
                c.push_front('1');
                tmp = '0';
            }
            else if (a[i] == '1' && tmp == '1'){
                c.push_front('1');
                tmp = "1";
            }
            else if (a[i] == '0' && tmp == '0'){
                c.push_front('0');
            }
            else{
                c.push_front('0');
                tmp = '1';
            }
        }
        else{
            if (tmp == "1"){
                c.push_front('0');
                tmp = "1";
            }
            else{
                c.push_front('1');
                tmp = "0";
            }
        }
    }
    qDebug() << "string: " << c;
    return c;
}
