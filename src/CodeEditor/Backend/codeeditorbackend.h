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
    Q_PROPERTY(QColor bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_PROPERTY(QColor selectColor READ selectColor WRITE setSelectColor NOTIFY selectColorChanged)

  public:
    explicit CodeEditorBackend(QObject *parent = nullptr);
    QUrl fileUrl() const;
    QString fileName() const;
    QString text() const;
    QColor bgColor() const;
    QColor selectColor() const;
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool saveAs();
    Q_INVOKABLE bool updateShTheme(const QString &themeName);

  signals:
    void fileUrlChanged(const QUrl &fileUrl);
    void fileNameChanged(const QString &fileName);
    void textChanged(const QString &text);
    void bgColorChanged(const QColor &bgColor);
    void selectColorChanged(const QColor &slColor);

  public slots:
    void setFileUrl(const QUrl &fileUrl);
    void setFileName(const QString &fileName);
    void setText(const QString &text);
    void setBgColor(const QColor &color);
    void setSelectColor(const QColor &color);

  private:
    friend class LineNumbers;

    QUrl m_fileUrl;
    QString m_fileName;
    QString m_text;

    QQuickTextDocument *m_doc;

    // Syntax Highlighting
    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;
    QColor m_bgColor;     // Background color
    QColor m_selectColor; // Select color
    void setTheme(const KSyntaxHighlighting::Theme &theme);
};

#endif // CODEEDITORBACKEND_H
