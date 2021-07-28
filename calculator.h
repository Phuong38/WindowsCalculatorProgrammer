#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QObject>

class calculator:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainResult READ mainResult WRITE setMainResult NOTIFY mainResultChanged)
    Q_PROPERTY(QString expResult READ expResult WRITE setExpResult NOTIFY expResultChanged)
public:
    calculator();
    ~calculator();
    static calculator* getInstance();
    QString converInfixToPostfix(QString s);
    int calculate(QString exp);
    QString mainResult();
    void setMainResult(QString);
    QString expResult();
    void setExpResult(QString);
signals:
    void mainResultChanged(QString mainResult);
    void expResultChanged(QString expResult);
public slots:
    Q_INVOKABLE void onDigitClick(QString _digit);

private:
    int checkPriority(QChar c);
    bool isNumber(QChar c);
private:
    QString m_exp;
    QString m_mainResult;
    QString m_expResult;
    int m_count;
    int m_prePriority;
};

#endif // CALCULATOR_H
