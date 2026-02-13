#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calculator.h"
#include "historymanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Calculator calculator;
    HistoryManager historyManager;


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("calculator", &calculator);
    engine.rootContext()->setContextProperty("historyManager", &historyManager);

    calculator.setHistoryManager(&historyManager);
    engine.loadFromModule("CalculatorApp", "Main");

    historyManager.loadHistory();
    return app.exec();

    if (engine.rootObjects().isEmpty())
        return -1;
}
