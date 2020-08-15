#include <definition.h>
#include <foldingregion.h>
#include <repository.h>
#include <syntaxhighlighter.h>
#include <theme.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQuickTextDocument>

template <class T>
T childObject(QQmlApplicationEngine& engine, const QString& objectName,
              const QString& propertyName)
{
    QList<QObject*> rootObjects = engine.rootObjects();
    foreach (QObject* object, rootObjects) {
        QObject* child = object->findChild<QObject*>(objectName);
        if (child != 0) {
            std::string s = propertyName.toStdString();
            QObject* object = child->property(s.c_str()).value<QObject*>();
            Q_ASSERT(object != 0);
            T prop = dynamic_cast<T>(object);
            Q_ASSERT(prop != 0);
            return prop;
        }
    }
    return (T)0;
}

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQuickStyle::setStyle("Material");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    QQuickTextDocument* doc;

    QList<QObject*> rootObjects = engine.rootObjects();
    for (QObject* object : rootObjects) {
        QObject* child = object->findChild<QObject*>("textEditor");
        if (child != 0) {
            QObject* object = child->property("textDocument").value<QObject*>();
            if (object != 0) {
                doc = dynamic_cast<QQuickTextDocument*>(object);
                break;
            }
        }
    }

    KSyntaxHighlighting::Repository repository;
    auto highlighter =
        new KSyntaxHighlighting::SyntaxHighlighter(doc->textDocument());
    highlighter->setTheme(
        repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme));
    const auto def = repository.definitionForFileName("main.cpp");
    highlighter->setDefinition(def);

    return app.exec();
}
