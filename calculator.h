#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
class HistoryManager;

class Calculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display NOTIFY displayChanged)
    Q_PROPERTY(QString expression READ expression NOTIFY expressionChanged)


public:
    explicit Calculator(QObject *parent = nullptr);

    enum Operator {
        None,
        Add,
        Subtract,
        Multiply,
        Divide
    };
    Q_ENUM(Operator)

    Q_INVOKABLE void inputNumber(const QString &number);
    Q_INVOKABLE void inputOperator(const QString &op);
    Q_INVOKABLE void calculate();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void clearEntry();
    Q_INVOKABLE void toggleSign();
    Q_INVOKABLE void backspace();



    QString display() const;

    //database
    void setHistoryManager(HistoryManager *manager);

    //expression
    QString expression() const;


signals:
    void displayChanged();
    void expressionChanged();

private:
    //calculator
    int m_firstOperand;
    int m_secondOperand;
    Operator m_operator;

    bool m_waitingForSecondOperand;
    bool m_justCalculated;

    QString m_display;

    //database
    HistoryManager *m_historyManager;
    //expression
    QString m_expression;
    QString operatorToString() const;





};

#endif
