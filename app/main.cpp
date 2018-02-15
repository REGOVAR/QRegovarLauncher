#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "regovarlauncher.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    app.setApplicationName("Regovar");
    app.setOrganizationName("Regovar");
    app.setOrganizationDomain("regovar.org");
    app.setApplicationVersion("0.0.b");


    // Init regovar model
    RegovarLauncher* regovar = new RegovarLauncher();
    regovar->init();

    // Init QML
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("regovar", regovar);

    // Check whole Regovar system
    if (regovar->check())
    {
        // If true, all is ok and action to do for the user -> auto start the QRegovar client
        regovar->startClient();
    }

    // Else, let QML display informations and let the user choose what to do
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
