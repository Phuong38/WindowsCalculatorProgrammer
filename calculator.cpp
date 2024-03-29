#include "calculator.h"
#include  <QStack>
#include <QString>
#include <QChar>
#include <QDebug>
#include <QtQuick>

calculator::calculator()
{
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
    if (c == '~'){
        return 6;
    }
    if (c == 'x' || c == u'÷' || c == '%' || c == '>' || c == '<'){
        return 5;
    }
    else if (c == '+' || c == '-'){
        return 4;
    }
    else if (c == '&' || c == '$'){
        return 3;
    }
    else if (c == '^' || c == '#'){
        return 2;
    }
    else if (c == '|' || c == '#'){
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
    return (c == '+' || c == '-' || c == 'x' || c == u'÷' || c =='%');
}

QString calculator::convertInfixToPostfix(QString s)
{
    QStack<QChar> stack;
    stack.push('N');
/*  R: Rsh, L: Lsh, A: AND, X: XOR, O: OR*/
    for (int i = 0; i < s.length(); i++){
        if (s[i] == 'R'){
            s.replace(i,3,'>');
        }
        if (s[i] == 'L'){
            s.replace(i,3,'<');
        }
        if (s[i] == 'A'){
            s.replace(i,3,'&');
        }
        if (s[i] == 'X'){
            s.replace(i,3,'^');
        }
        if (s[i] == 'O'){
            s.replace(i,2,'|');
        }
        if (s[i] == 'N' && s[i + 1] == 'A'){
            s.replace(i,4,'$');
        }
        if (s[i] == 'N' && s[i + 2] == 'R'){
            s.replace(i,3,'#');
        }
        if (s[i] == 'N' && s[i + 2] == 'T'){
            s.replace(i,3,'~');
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

QString calculator::calculate(QString exp)
{
    QString postfixExp = convertInfixToPostfix(exp);
    qDebug() << "converted start calculate" << postfixExp;
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
            if (tmp1 == 0){
                return "Cannot divide by zero";
            }
            else{
                stk.push(tmp2 / tmp1);
            }
        }
        else if (postfixExp[i] == '%'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 % tmp1);
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
        else if (postfixExp[i] == '>'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 >> tmp1);
        }
        else if (postfixExp[i] == '<'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp2 << tmp1);
        }
        else if (postfixExp[i] == '&'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 & tmp2);
        }
        else if (postfixExp[i] == '^'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 ^ tmp2);
        }
        else if (postfixExp[i] == '|'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(tmp1 | tmp2);
        }
        else if (postfixExp[i] == '$'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(~(tmp1 & tmp2));
        }
        else if (postfixExp[i] == '#'){
            tmp1 = stk.pop();
            tmp2 = stk.pop();
            stk.push(~(tmp1 | tmp2));
        }
        else if (postfixExp[i] == '~'){
            tmp1 = stk.pop();
            stk.push(~tmp1);
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
    return QString::number(stk.pop());
}

void calculator::onOperatorClick(QString _operator)
{
    if (_operator == 'C'){
        setMainResult("0");
        setExpResult("");
        setSubResult("0");
        m_exp = "";
        m_digit = "";
        m_done = false;
        m_prePriority = 0;
        m_countOperator = 0;
    }
    else if (_operator == '~'){
        if (mainResult().isEmpty()){
            m_exp.append(_operator);
            m_exp.append("(0)");
            setExpResult(m_exp);
        }
        else if (m_done == true){
            m_done = false;
            m_exp.append(_operator);
            m_exp.append("(" + mainResult() + ")");
            setExpResult(m_exp);
            setMainResult(calculate(expResult()));
            setSubResult(calculate(expResult()));
        }
        else{
            QString tmp;
            if (!isOperator(m_exp.back()) && !isBitwise(m_exp.back())){
                m_exp.remove(mainResult());
            }
            tmp.append(_operator);
            tmp.append("(" + mainResult() + ")");
            m_exp.append(tmp);
            setExpResult(m_exp);
            setMainResult(calculate(tmp));
        }
    }
    else if (_operator == '(' || _operator == ')') {
        m_exp.append(_operator);
        setExpResult(m_exp);
    }
    else if (_operator == '=' && m_done == true){
        QString tmp = expResult().remove("=");
        for (int  i = tmp.length() -1; i >= 0; i--){
            if (isOperator(tmp[i]) || isBitwise(tmp[i])){
                tmp.remove(0,i);
                break;
            }
        }
        if (mainResult().toInt() < 0){
            tmp.prepend("(0" + mainResult() + ")");
        }
        else{
            tmp.prepend(mainResult());
        }
        setExpResult(tmp);
        setMainResult(calculate(tmp));
        m_done = true;
    }
    else if (_operator == '='){
        if (m_needclose){
            m_needclose = false;
            m_exp.append(")");
            setExpResult(m_exp);
        }
        qDebug() << "bieu thuc" << expResult();
        qDebug() << "hau to" << convertInfixToPostfix(expResult());
        QString result = calculate(expResult());
        if (result != "Cannot divide by zero"){
            setMainResult(result);
            setSubResult(mainResult());
            m_exp.append(_operator);
            setExpResult(m_exp);
            m_done  = true;
            m_digit = "";
            m_exp = "";
            m_countOperator = 0;
            m_prePriority = 0;
        }
        else{
            setMainResult(result);
            setSubResult("");
            m_done  = true;
            m_digit = "";
            m_exp = "";
            m_countOperator = 0;
            m_prePriority = 0;
        }
        qDebug() << "result" << result;
        qDebug() << "m_done" << m_done;
    }
    else if (_operator == "del"){
        if (!expResult().isEmpty() && mainResult() != '0'){
            m_exp.remove(m_exp.length() - 1,m_exp.length());
            setExpResult(m_exp);
            m_digit.remove(m_digit.length() - 1, m_digit.length());
            setMainResult(m_digit);
            setSubResult(m_digit);
        }
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
        else if (isOperator(m_exp.back()) || isBitwise(m_exp.back())){
            m_exp.remove(m_exp.length() - 1,m_exp.length());
            setExpResult(m_exp);
            m_exp.append(_operator);
            setExpResult(m_exp);
        }
        else if (checkPriority(_operator.back()) <= m_prePriority && m_countOperator != 0 && m_done == false){
            if (calculate(expResult()) != "Cannot divide by zero"){
                setMainResult(calculate(expResult()));
                setSubResult(mainResult());
                m_digit = "";
                m_exp.append(_operator);
                setExpResult(m_exp);
                m_prePriority = checkPriority(_operator.back());
            }
            else{
                setMainResult(calculate(expResult()));
                setSubResult("");
                m_digit = "";
                m_exp = "";
            }
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

bool calculator::isBitwise(QChar _bitw)
{
    return (_bitw == '>' || _bitw == '<' || _bitw == '&' || _bitw == '|' || _bitw == '^');
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
    for (int i = 0; i < _exp.length(); i++){
        if (_exp[i] == '<'){
            _exp.replace(i,1,"Lsh");
        }
        if (_exp[i] == '>'){
            _exp.replace(i,1,"Rsh");
        }
        if (_exp[i] == '&'){
            _exp.replace(i,1,"AND");
        }
        if (_exp[i] == '^'){
            _exp.replace(i,1,"XOR");
        }
        if (_exp[i] == '|'){
            _exp.replace(i,1,"OR");
        }
        if (_exp[i] == '$'){
            _exp.replace(i,1,"NAND");
        }
        if (_exp[i] == '#'){
            _exp.replace(i,1,"NOR");
        }
        if (_exp[i] == '~'){
            _exp.replace(i,1,"NOT");
        }
    }

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
    if (_result == '0' || _result ==""){
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
    for (int i = 0; i < c.length(); i++){
        if (c[i] == ' ')
            c.remove(i,1);
    }
    while(c.length() < 64){
        c.prepend("1");
    }
    for (int i = c.length() - 1; i > 0; i--){
         if (i % 4 == 0)
            c.insert(i, " ");
     }
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
    QString oct, tmp;
    for (int i = 0; i < _bin.length(); i++){
        if (_bin[i] == ' '){
            _bin.remove(i,1);
        }
    }
    while (_bin.length() % 3 != 0) {
        _bin.prepend("0");
    }
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
