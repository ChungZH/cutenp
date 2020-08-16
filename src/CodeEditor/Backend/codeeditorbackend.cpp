#include "codeeditorbackend.h"

#include "../../common/nphelpers.h"

#include <QFile>
#include <QSaveFile>
#include <QUrl>

CodeEditorBackend::CodeEditorBackend(QObject *parent) : QObject(parent)
{
    setFileName("Untitled");
}

QUrl CodeEditorBackend::fileUrl() const
{
    return m_fileUrl;
}

QString CodeEditorBackend::fileName() const
{
    return m_fileName;
}

QString CodeEditorBackend::text() const
{
    return m_text;
}

void CodeEditorBackend::setFileUrl(const QUrl &fileUrl)
{
    if (m_fileUrl == fileUrl)
        return;

    m_fileUrl = fileUrl;
    emit fileUrlChanged(fileUrl);
    setFileName(fileUrl.fileName());
}

void CodeEditorBackend::setFileName(const QString &fileName)
{
    if (m_fileName == fileName)
        return;

    if (m_fileName.isEmpty())
    {
        // Init syntax highlighting
        m_doc = Npanda::common::doc;
        m_highlighter = new KSyntaxHighlighting::SyntaxHighlighter(m_doc->textDocument());
        m_highlighter->setTheme(m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    }
    const auto def = m_repository.definitionForFileName(fileName);
    m_highlighter->setDefinition(def);
    m_fileName = fileName;

    emit fileNameChanged(fileName);
}

void CodeEditorBackend::setText(const QString &text)
{
    if (m_text == text)
        return;

    m_text = text;

    emit textChanged(text);
}

bool CodeEditorBackend::load()
{
    // DO NOT USE `QUrl.path()` !!!!!!
    QFile file(m_fileUrl.toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&file);

    setText(in.readAll());

    file.close();
    return true;
}

bool CodeEditorBackend::save()
{
    QSaveFile file(m_fileUrl.toLocalFile());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);
    out << m_text;

    if (!file.commit())
        return false;
    return true;
}
