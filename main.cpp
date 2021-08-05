#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calculator.h"
#include "memory.h"
#include <QtQuick>
#include <QStringListModel>



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext *m_qmlContext = engine.rootContext();
    m_qmlContext->setContextProperty("_calculator", calculator::getInstance());

    memory memoryModel;
    m_qmlContext->setContextProperty("_memoryModel", &memoryModel);
    return app.exec();
}
