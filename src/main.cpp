#include <definition.h>
#include <foldingregion.h>
#include <repository.h>
#include <syntaxhighlighter.h>
#include <theme.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQuickTextDocument>

#include "CodeEditor/Backend/codeeditorbackend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQuickStyle::setStyle("Material");

    qmlRegisterType<CodeEditorBackend>("CodeEditorBackend", 1, 0, "CodeEditorBackend");

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
                break;
            }
        }
    }

    KSyntaxHighlighting::Repository repository;
    auto highlighter = new KSyntaxHighlighting::SyntaxHighlighter(doc->textDocument());
    highlighter->setTheme(repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    const auto def = repository.definitionForFileName("main.cpp");
    highlighter->setDefinition(def);

    return app.exec();
}
