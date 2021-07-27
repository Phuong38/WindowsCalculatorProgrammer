#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QObject>

class calculator:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainResult READ mainResult WRITE setMainResult NOTIFY mainResultChanged)
public:
    calculator();
    ~calculator();
    static calculator* getInstance();
    QString converInfixToPostfix(QString s);
    int calculate(QString exp);
    QString mainResult();
    void setMainResult(QString);
signals:
    void mainResultChanged(QString mainResult);
public slots:
    Q_INVOKABLE void onTestConnect(const QString &msg);
    Q_INVOKABLE void onDigitClick(QString _digit);

private:
    int checkPriority(QChar c);
    bool isNumber(QString c);
private:
    QString m_exp;
    QString m_mainResult;
    int m_count;
    int m_prePriority;
};

#endif // CALCULATOR_H
