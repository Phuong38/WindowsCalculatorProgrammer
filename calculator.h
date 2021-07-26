#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QObject>

class calculator:public QObject
{
    Q_OBJECT;
    Q_PROPERTY(string mainResultScreen READ mainResultScreen WRITE setMainResultScreen NOTIFY mainResultScreenChanged)

public:
    calculator();
    void mainResultScreen();
    void setMainResultScreen();
    static calculator* getInstance();
    QString converInfixToPostfix(QString s);
    int calculate(QString exp);

public slots:
    void onDigitClick(QString number);

private:
    int checkPriority(QChar c);
    bool isNumber(QString c);

private:
    QString m_mainResultScreen;
};

#endif // CALCULATOR_H
