#include "calculator.h"
#include <QDebug>
#include "historymanager.h"

Calculator::Calculator(QObject *parent)
    : QObject(parent),
    m_firstOperand(0),
    m_secondOperand(0),
    m_operator(None),
    m_waitingForSecondOperand(false),
    m_justCalculated(false),
    m_display("0"),
    m_expression(""),
    m_historyManager(nullptr)
{
}

//  GETTERS

QString Calculator::display() const
{
    return m_display;
}

QString Calculator::expression() const
{
    return m_expression;
}

//  HELPER

QString Calculator::operatorToString() const
{
    switch (m_operator) {
    case Add: return "+";
    case Subtract: return "-";
    case Multiply: return "×";
    case Divide: return "÷";
    default: return "";
    }
}

//  NUMBER

void Calculator::inputNumber(const QString &number)
{
    qDebug() << "[KEY]" << number;

    if (m_justCalculated) {
        m_display = number;
        m_justCalculated = false;

        m_expression.clear();              // Clear expression sau "="
        emit expressionChanged();
    }
    else if (m_display == "0" || m_waitingForSecondOperand) {
        m_display = number;
        m_waitingForSecondOperand = false;
    }
    else {
        m_display += number;
    }

    emit displayChanged();

    // Update expression khi nhập số thứ 2
    if (m_operator != None && !m_waitingForSecondOperand) {
        m_expression = QString::number(m_firstOperand) + " "
                       + operatorToString() + " "
                       + m_display;
        emit expressionChanged();
    }
}

//  OPERATOR

void Calculator::inputOperator(const QString &op)
{
    qDebug() << "[KEY]" << op;

    int currentValue = m_display.toInt();

    if (m_operator != None && !m_waitingForSecondOperand) {
        m_secondOperand = currentValue;

        switch (m_operator) {
        case Add:       m_firstOperand += m_secondOperand; break;
        case Subtract:  m_firstOperand -= m_secondOperand; break;
        case Multiply:  m_firstOperand *= m_secondOperand; break;
        case Divide:
            if (m_secondOperand != 0)
                m_firstOperand /= m_secondOperand;
            else {
                m_display = "Error";

                m_firstOperand = 0;
                m_secondOperand = 0;
                m_operator = None;
                m_waitingForSecondOperand = false;
                m_justCalculated = true;

                m_expression.clear();
                emit expressionChanged();
                emit displayChanged();
                return;
            }
            break;
        default: break;
        }

        m_display = QString::number(m_firstOperand);
        emit displayChanged();
    }
    else {
        m_firstOperand = currentValue;
    }

    m_waitingForSecondOperand = true;
    m_justCalculated = false;

    if (op == "+") m_operator = Add;
    else if (op == "-") m_operator = Subtract;
    else if (op == "×") m_operator = Multiply;
    else if (op == "÷") m_operator = Divide;

    m_expression = QString::number(m_firstOperand) + " " + operatorToString();
    emit expressionChanged();
}

//  EQUAL

void Calculator::calculate()
{
    qDebug() << "[KEY] =";

    if (m_operator == None)
        return;

    if (m_waitingForSecondOperand)
        return;

    int originalFirst = m_firstOperand;
    int originalSecond = m_display.toInt();

    m_secondOperand = originalSecond;

    switch (m_operator) {
    case Add:       m_firstOperand += m_secondOperand; break;
    case Subtract:  m_firstOperand -= m_secondOperand; break;
    case Multiply:  m_firstOperand *= m_secondOperand; break;
    case Divide:
        if (m_secondOperand != 0)
            m_firstOperand /= m_secondOperand;
        else {
            m_display = "Error";

            m_firstOperand = 0;
            m_secondOperand = 0;
            m_operator = None;
            m_waitingForSecondOperand = false;
            m_justCalculated = true;

            m_expression.clear();
            emit expressionChanged();
            emit displayChanged();
            return;
        }
        break;
    default: break;
    }

    m_display = QString::number(m_firstOperand);

    // Expression kiểu Windows
    m_expression = QString::number(originalFirst) + " "
                   + operatorToString() + " "
                   + QString::number(originalSecond) + " =";
    emit expressionChanged();

    emit displayChanged();

    // Lưu history
    QString historyEntry =
        QString("%1 %2 %3 = %4")
            .arg(originalFirst)
            .arg(operatorToString())
            .arg(originalSecond)
            .arg(m_display);

    if (m_historyManager)
        m_historyManager->addHistory(historyEntry);

    m_operator = None;
    m_waitingForSecondOperand = false;
    m_justCalculated = true;
}

//  CLEAR ALL

void Calculator::clear()
{
    qDebug() << "[KEY] C";

    m_firstOperand = 0;
    m_secondOperand = 0;
    m_operator = None;
    m_waitingForSecondOperand = false;
    m_justCalculated = false;

    m_display = "0";
    m_expression.clear();

    emit displayChanged();
    emit expressionChanged();
}

//  CLEAR ENTRY

void Calculator::clearEntry()
{
    qDebug() << "[KEY] CE";

    m_display = "0";
    m_justCalculated = false;

    emit displayChanged();
}

//  TOGGLE SIGN

void Calculator::toggleSign()
{
    int value = m_display.toInt();
    value = -value;
    m_display = QString::number(value);

    emit displayChanged();
}

//  BACKSPACE

void Calculator::backspace()
{
    if (m_justCalculated)
        return;

    if (m_display.length() > 1)
        m_display.chop(1);
    else
        m_display = "0";

    if (m_display == "-")
        m_display = "0";

    emit displayChanged();
}

//  DATABASE

void Calculator::setHistoryManager(HistoryManager *manager)
{
    m_historyManager = manager;
}
