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
    else if (c == 'r' || c == 'l'){
        return 2;
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
    return (c == '+' || c == '-' || c == 'x' || c == u'÷' || c =='%'
            || c == 'l' || c == 'r');
}

QString calculator::convertInfixToPostfix(QString s)
{
    QStack<QChar> stack;
    stack.push('N');

    for (int i = 0; i < s.length(); i++){
        if (s[i] == 'R'){
            s.replace(i,3,'r');
        }
        if (s[i] == 'L'){
            s.replace(i,3,'l');
        }
    }

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
        else if (postfixExp[i] == 'r'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 >> tmp1);
        }
        else if (postfixExp[i] == 'l'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 << tmp1);
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
        if (m_needclose){
            m_needclose = false;
            m_exp.append(")");
            setExpResult(m_exp);
        }
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
    else if (m_needclose == true){
//        m_exp.append(_operator);
        m_exp.append(")");
        m_needclose = false;

        setExpResult(m_exp);
        m_exp.append(_operator);
        m_digit = "";
        setExpResult(m_exp);
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
        else if (m_exp[m_exp.length() -1] == '>' || m_exp[m_exp.length() -1] == '<'){
            m_exp.replace(m_exp.length() - 2, m_exp.length(), _operator);
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
    if (_digit == '(' || _digit == ')') {
        m_exp.append(_digit);
        setExpResult(m_exp);
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

void calculator::onFunctionKeypadClick(QString _func)
{
    if (_func == 'C'){
        setMainResult("0");
        setExpResult("");
        setBinResult("0");
        setHexResult("0");
        setOctResult("0");
        setDecResult("0");
        m_exp = "";
        m_digit = "";
        m_done = false;
        m_prePriority = 0;
        m_countOperator = 0;
    }
    else if (_func == "<<" || _func == ">>"){
        if (m_exp.isEmpty() || m_exp.back() == '('){
            m_exp.append("(0");
            m_exp.append(_func);
            setExpResult(m_exp);
            m_needclose = true;
        }
        else if (isOperator(m_exp.back())){
            m_exp.remove(m_exp.length() -1, m_exp.length());
            setExpResult(m_exp);
            m_exp.append(_func);
            setExpResult(m_exp);
            m_digit = "";
        }
        else if (m_exp[m_exp.length() -1] == '>' || m_exp[m_exp.length() -1] == '<'){
           qDebug() << m_exp;
            m_exp.replace(m_exp.length() - 2, m_exp.length(), _func);
            setExpResult(m_exp);
        }
        else{
            m_countOperator++;
            m_prePriority = 2;
            m_exp.append(_func);
            setExpResult(m_exp);
            m_digit = "";
        }
    }
    else if (_func == '%'){

    }
}

//bool calculator::isBitwise(QString _bitw)
//{
//    return (_bitw == ">>" || _bitw == "<<" || _bitw == "AND" || _bitw == "OR" || _bitw == "XOR");
//}

//void calculator::onBitwiseOperatorClick(QString _bitw)
//{
//    if (m_exp.isEmpty() || m_exp.back() == '('){
//        m_exp.append("(0");
//        m_exp.append(_bitw);
//        setExpResult(m_exp);
//        m_needclose = true;
//    }
//    else if  (isOperator(m_exp.back())){

//    }
//}

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
    qDebug() << "_exp before: " << _exp;
    for (int i = 0; i < _exp.length(); i++){
        if (_exp[i] == '<' && _exp[i+1] == '<'){
            _exp.replace(i,2,"Lsh");
        }
        if (_exp[i] == '>' && _exp[i+1] == '>'){
            _exp.replace(i,2,"Rsh");
        }
    }

    qDebug() << "_exp after replace: " << _exp;
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
    if (_binResult.length() > 64)
        _binResult.insert(39,"<br>");
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

QString calculator::DectoBin(signed long int _dec)
{
    QString bin;
    while (_dec > 0) {
            bin.prepend(QString::number(_dec % 2));
            _dec = _dec / 2;
        }

    while(bin.length() % 4 != 0){
         bin.prepend("0");
      }
     for (int i = bin.length() - 1; i > 0; i--){
          if (i % 4 == 0)
             bin.insert(i, " ");

      }
     return bin;
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

void calculator::setSubResult(QString _result)
{
    if (_result == '0'){
        setHexResult(_result);
        setDecResult(_result);
        setOctResult(_result);
        setBinResult(_result);
    }
    else{
        QString bin = convertDectoBin(_result.toInt());
        qDebug() << "bin" << bin;
        setBinResult(bin);

        qDebug() << "C:" << _result.toInt();

        QString hex = convertBintoHex(bin);
        qDebug() << "hex" << hex;
        setHexResult(hex);

        setDecResult(_result);

        QString oct = convertBintoOct(bin);
        qDebug() << "oct" << oct;
        setOctResult(oct);
    }

}

QString calculator::negativeDectoBin(QString a)
{
    QString b = "";
    QString c ="";
    QString tmp = "0";
    for (int i = 0; i < a.length(); i++){
        if (a[i] == '0')
            a[i] = '1';
        else if (a[i] == '1')
            a[i] = '0';
        else
            a[i] = ' ';
    }
    qDebug() << "String a: " << a;
    for (int i = 0; i < a.length(); i++){
        if (a[i] == ' ')
            b.append(" ");
         else
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
            else if (a[i] == ' ')
                c.push_front(' ');
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
    qDebug() << "length: " << c.length();
    for (int i = 0; i < c.length(); i++){
        if (c[i] == ' ')
            c.remove(i,1);
    }
    qDebug() << "c after remove: " << c;
    while(c.length() < 64){
        c.prepend("1");
    }
    for (int i = c.length() - 1; i > 0; i--){
         if (i % 4 == 0)
            c.insert(i, " ");
     }
    qDebug() << "bin am: " << c;
    qDebug() << "length: " << c.length();
    return c;
}


QString calculator::convertBintoHex(QString _bin)
{
    QString hex, tmp;
    for (int i = 0; i < _bin.length(); i+=5){
        tmp = _bin.mid(i, 4);
        if (tmp == "0000")
            hex.append("0");
        else if (tmp == "0001")
            hex.append("1");
        else if (tmp == "0010")
            hex.append("2");
        else if (tmp == "0011")
            hex.append("3");
        else if (tmp == "0100")
            hex.append("4");
        else if (tmp == "0101")
            hex.append("5");
        else if (tmp == "0110")
            hex.append("6");
        else if (tmp == "0111")
            hex.append("7");
        else if (tmp == "1000")
            hex.append("8");
        else if (tmp == "1001")
            hex.append("9");
        else if (tmp == "1010")
            hex.append("A");
        else if (tmp == "1011")
            hex.append("B");
        else if (tmp == "1100")
            hex.append("C");
        else if (tmp  == "1101")
            hex.append("D");
        else if (tmp == "1110")
            hex.append("E");
        else if (tmp == "1111")
            hex.append("F");
        else{

        }

    }

    for (int i = hex.length() - 1; i > 0; i--){
         if (i % 4 == 0)
            hex.insert(i, " ");

     }
    return hex;
}

QString calculator::convertBintoOct(QString _bin)
{
    qDebug() << "bin to oct before remove: " << _bin;
    QString oct, tmp;
    for (int i = 0; i < _bin.length(); i++){
        if (_bin[i] == ' '){
            _bin.remove(i,1);
        }
    }
    qDebug() << "bin to oct after remove: " << _bin;
    while (_bin.length() % 3 != 0) {
        _bin.prepend("0");
    }
    qDebug() << "bin to oct: " << _bin;
    for (int i = 0; i < _bin.length(); i+=3){
        tmp = _bin.mid(i,3);
        if (tmp == "000" && i != 0)
            oct.append("0");
        else if (tmp == "001")
            oct.append("1");
        else if (tmp == "010")
            oct.append("2");
        else if (tmp == "011")
            oct.append("3");
        else if (tmp == "100")
            oct.append("4");
        else if (tmp == "101")
            oct.append("5");
        else if (tmp == "110")
            oct.append("6");
        else if (tmp == "111")
            oct.append("7");
        else{

        }
    }
    for (int i = oct.length() - 3; i > 0; i -= 3){
           oct.insert(i, " ");
     }
    return oct;
}
