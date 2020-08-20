#include "/common/nphelpers.h"
#include "/settings/configmanager.h"
#include "CodeEditor/Backend/codeeditorbackend.h"
#include "CodeEditor/Backend/linenumbers.hpp"
#include "aboutwindowbackend.hpp"
#include "preferenceswindowbackend.hpp"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQuickTextDocument>
#include <definition.h>
#include <foldingregion.h>
#include <repository.h>
#include <syntaxhighlighter.h>
#include <theme.h>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    app.setOrganizationName("ChungZH");
    app.setApplicationName("Notepanda");
    app.setApplicationVersion("0.1.6");

#ifdef Q_OS_WINDOWS
    app.setFont(QFont("Segoe UI"));
#endif

    QQmlApplicationEngine engine;

    QQuickStyle::setStyle("Material");

    qmlRegisterType<CodeEditorBackend>("CodeEditorBackend", 1, 0, "CodeEditorBackend");
    qmlRegisterType<LineNumbers>("LineNumbers", 1, 0, "LineNumbers");
    qmlRegisterType<AboutWindowBackend>("AboutWindowBackend", 1, 0, "AboutWindowBackend");
    qmlRegisterType<PreferencesWindowBackend>("PreferencesWindowBackend", 1, 0, "PreferencesWindowBackend");
    qmlRegisterType<ConfigManager>("ConfigManager", 1, 0, "ConfigManager");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.addImportPath(QStringLiteral("qrc:/"));
    engine.load(url);

    QQuickTextDocument *doc;

    QList<QObject *> rootObjects = engine.rootObjects();
    for (QObject *object : rootObjects)
    {
        QObject *child = object->findChild<QObject *>("textEditor");
        if (child != 0)
        {
            QObject *object = child->property("textDocument").value<QObject *>();
            if (object != 0)
            {
                doc = dynamic_cast<QQuickTextDocument *>(object);
                Npanda::common::doc = doc;
                break;
            }
        }
    }

    return app.exec();
}
