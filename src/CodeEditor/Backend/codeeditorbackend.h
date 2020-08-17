#ifndef CODEEDITORBACKEND_H
#define CODEEDITORBACKEND_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <definition.h>
#include <foldingregion.h>
#include <repository.h>
#include <syntaxhighlighter.h>
#include <theme.h>

class CodeEditorBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

  public:
    explicit CodeEditorBackend(QObject *parent = nullptr);
    QUrl fileUrl() const;
    QString fileName() const;
    QString text() const;
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool saveAs();

  signals:
    void fileUrlChanged(const QUrl &fileUrl);
    void fileNameChanged(const QString &fileName);
    void textChanged(const QString &text);

  public slots:
    void setFileUrl(const QUrl &fileUrl);
    void setFileName(const QString &fileName);
    void setText(const QString &text);

  private:
    QUrl m_fileUrl;
    QString m_fileName;
    QString m_text;

    QQuickTextDocument *m_doc;
    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;
};

#endif // CODEEDITORBACKEND_H
