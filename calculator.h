#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QObject>

class calculator:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainResult READ mainResult WRITE setMainResult NOTIFY mainResultChanged)
    Q_PROPERTY(QString expResult READ expResult WRITE setExpResult NOTIFY expResultChanged)
    Q_PROPERTY(QString binResult READ binResult WRITE setBinResult NOTIFY binResultChanged)
    Q_PROPERTY(QString hexResult READ hexResult WRITE setHexResult NOTIFY hexResultChanged)
    Q_PROPERTY(QString decResult READ decResult WRITE setDecResult NOTIFY decResultChanged)
    Q_PROPERTY(QString octResult READ octResult WRITE setOctResult NOTIFY octResultChanged)
public:
    calculator();
    ~calculator();
    static calculator* getInstance();
    QString convertInfixToPostfix(QString s);
    int calculate(QString exp);
    QString mainResult();
    void setMainResult(QString);
    QString expResult();
    QString binResult();
    QString hexResult();
    QString decResult();
    QString octResult();
    void setExpResult(QString);
    void setBinResult(QString);
    void setHexResult(QString);
    void setDecResult(QString);
    void setOctResult(QString);
    QString DectoBin(signed long int _dec);
    QString convertDectoBin(int _dec);
    void setSubResult(QString _result);
    QString negativeDectoBin(QString);
    QString convertBintoHex(QString);
    QString convertBintoOct(QString);

signals:
    void mainResultChanged(QString _mainResult);
    void expResultChanged(QString _expResult);
    void binResultChanged(QString _binResult);
    void octResultChanged(QString _octResult);
    void decResultChanged(QString _decResult);
    void hexResultChanged(QString _hexResult);
public slots:
    Q_INVOKABLE void onDigitClick(QString _digit);
    Q_INVOKABLE void onOperatorClick(QString _operator);
    Q_INVOKABLE void onFunctionKeypadClick(QString);
//    Q_INVOKABLE void onBitwiseOperatorClick(QString);

private:
    int checkPriority(QChar c);
    bool isNumber(QChar c);
    bool isOperator(QChar c);
//    bool isBitwise(QString);
private:
    QString m_exp;
    QString m_digit;
    QString m_mainResult;
    QString m_expResult;
    QString m_binResult;
    QString m_decResult;
    QString m_octResult;
    QString m_hexResult;
    int m_countOperator;
    int m_prePriority;
    bool m_done;
    bool m_negate;
    bool m_needclose;
    bool m_isBitwise;
};

#endif // CALCULATOR_H
