#ifndef CODEEDITORBACKEND_H
#define CODEEDITORBACKEND_H

#include <QObject>
#include <QQuickItem>

class CodeEditorBackend : public QObject
{
    Q_OBJECT
public:
    explicit CodeEditorBackend(QObject *parent = nullptr);

signals:

};

#endif // CODEEDITORBACKEND_H
