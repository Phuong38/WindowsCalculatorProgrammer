#include "calculator.h"
#include  <QStack>
#include <QString>
#include <QChar>

calculator::calculator()
{
    m_mainResultScreen = "";
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
    QStack<char> stack;
    stack.push('N');
    int infixLength = s.length();
    QString posfixOutput;

    for (int i = 0; i < infixLength; i++){
        if (s[i] >= '0' && s[i] <= '9'){
            while (isNumber(s[i])) {
                posfixOutput += s[i];
                i++;
                if (i == infixLength){
                    break;
                }
            }
            posfixOutput += ' ';
            i--;
        }
        else if (s[i] == '('){
            stack.push('(');
        }
        else if (s[i] == ')') {
            while (stack.top() != 'N' && stack.top() != '(') {
                posfixOutput += stack.pop();
                posfixOutput += ' ';
            }
            if (stack.top() == '('){
                stack.pop();
            }
        }
        else {
            while (stack.top() != 'N' && checkPriority(s[i]) <= checkPriority(stack.top())) {
                posfixOutput += stack.pop();
                posfixOutput += ' ';
            }
        }
    }
    while (stack.top() != 'N') {
        posfixOutput += stack.pop();
        posfixOutput += ' ';
    }
    return posfixOutput;
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
