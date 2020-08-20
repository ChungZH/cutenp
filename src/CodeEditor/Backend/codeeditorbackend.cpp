#include "codeeditorbackend.h"

#include "../../common/nphelpers.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include <QUrl>

CodeEditorBackend::CodeEditorBackend(QObject *parent) : QObject(parent)
{
    m_fileName = "Untitled";
    for (const auto &theme : m_repository.themes()) Npanda::common::shThemeList.push_back(theme.name());
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

QColor CodeEditorBackend::bgColor() const
{
    return m_bgColor;
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
    if (m_fileName.isEmpty() || m_fileName == "Untitled")
    {
        // Init syntax highlighting

        // MAGIC! DON'T TOUCH
        m_doc = Npanda::common::doc;
        m_highlighter = new KSyntaxHighlighting::SyntaxHighlighter(m_doc->textDocument());
        // MAGIC! DON'T TOUCH

        setTheme(m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
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

void CodeEditorBackend::setBgColor(const QColor &bgColor)
{
    if (m_bgColor == bgColor)
        return;
    m_bgColor = bgColor;
    emit bgColorChanged(bgColor);
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
    if (m_fileUrl.isEmpty())
    {
        setFileUrl(QFileDialog::getSaveFileUrl());
    }

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

bool CodeEditorBackend::saveAs()
{
    setFileUrl(QFileDialog::getSaveFileUrl());

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

bool CodeEditorBackend::updateShTheme(const QString &themeName)
{
    if (m_fileName.isEmpty() || m_fileName == "Untitled")
        return false;
    const auto theme = m_repository.theme(themeName);
    setTheme(theme);
    return true;
}

void CodeEditorBackend::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    m_highlighter->setTheme(theme);
    m_highlighter->rehighlight();
    Npanda::common::shTheme = m_highlighter->theme();
    setBgColor(m_highlighter->theme().editorColor(KSyntaxHighlighting::Theme::BackgroundColor));
}
