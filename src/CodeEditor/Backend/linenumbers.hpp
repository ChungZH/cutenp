#ifndef LINENUMBERS_HPP
#define LINENUMBERS_HPP

#include "../../common/nphelpers.h"
#include "../../settings/configmanager.h"
#include "codeeditorbackend.h"

#include <QPainter>
#include <QQuickPaintedItem>
#include <algorithm>
#include <cmath>
#include <theme.h>

class LineNumbers : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int lineCount READ lineCount WRITE setLineCount NOTIFY lineCountChanged)
    Q_PROPERTY(int scrollY READ scrollY WRITE setScrollY NOTIFY scrollYChanged)
    Q_PROPERTY(double lineHeight READ lineHeight WRITE setLineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)

  public:
    explicit LineNumbers(QQuickPaintedItem *parent = nullptr)
    {
    }

    Q_INVOKABLE void updateConfigs()
    {
        cfManager->readGeneralSettings();
    }

    int lineCount() const
    {
        return m_lineCount;
    }

    int scrollY() const
    {
        return m_scrollY;
    }

    double lineHeight() const
    {
        return m_lineHeight;
    }

    virtual void paint(QPainter *painter) override
    {
        if (!cfManager->showLineNumbers())
            return;

        QFont font(cfManager->editorFontFamily(), cfManager->editorFontSize());
        painter->setFont(font);

        // Find current line
        QString untilSelectedText = m_text.mid(0, selectionStart());
        int selectedTextStartLine = untilSelectedText.count(QRegExp("[\r\n]")) + 1;

        QString selectedText = m_text.mid(selectionStart(), (selectionEnd() - selectionStart()));
        int numLinesSelected = selectedText.count(QRegExp("[\r\n]")) + 1;

        QString textUntilCursorPosition = m_text.mid(0, m_cursorPosition);
        int cursorLine = textUntilCursorPosition.count(QRegExp("[\r\n]")) + 1;

        int firstLineVisible = m_scrollY / m_lineHeight;
        int lineHeight = int(round(m_lineHeight));
        int rest = (m_scrollY > 0) ? (m_scrollY % lineHeight) : 0;
        // The last visible line is either the last line in the textfield or if we have scrolled as far as we get with current size
        int lastLineVisible = std::min(firstLineVisible + int(height() / m_lineHeight) + 1, m_lineCount);
        const int numLines = lastLineVisible - firstLineVisible;
        for (int i = 0; i < int(height() / m_lineHeight) + 2; i++)
        {
            int lineNumber = i + firstLineVisible + 1;
            QFontMetrics fm(font);
            QString text = QString("%1").arg(lineNumber);
            int textWidth = fm.horizontalAdvance(text);
            int textHeight = m_lineHeight;
            double x = width() - textWidth - 5;
            double y = i * m_lineHeight - rest + 3;

            QRectF bgRect;
            if (i == 0)
                bgRect = QRectF(0, y - 5, width(), textHeight + 4);
            else
                bgRect = QRectF(0, y, width(), textHeight);

            QColor linenumbersBg(Npanda::common::shTheme.editorColor(KSyntaxHighlighting::Theme::IconBorder));
            if (linenumbersBg != QColor("#000000"))
            {
                painter->setPen(linenumbersBg);
                painter->drawRect(bgRect);
                painter->fillRect(bgRect, linenumbersBg);
            }

            // paint numbers
            if (i < numLines)
            {
                QRectF textRect(x, y + 5, textWidth, textHeight + 3);
                // Current & Selected
                if ((lineNumber >= selectedTextStartLine && lineNumber < selectedTextStartLine + numLinesSelected) || lineNumber == cursorLine)
                    painter->setPen(Npanda::common::shTheme.editorColor(KSyntaxHighlighting::Theme::CurrentLineNumber));
                else
                    painter->setPen(Npanda::common::shTheme.editorColor(KSyntaxHighlighting::Theme::LineNumbers));

                painter->drawText(textRect, Qt::AlignLeft, text);
            }
        }
    }

    QString text() const
    {
        return m_text;
    }

    int cursorPosition() const
    {
        return m_cursorPosition;
    }

    int selectionStart() const
    {
        return m_selectionStart;
    }

    int selectionEnd() const
    {
        return m_selectionEnd;
    }

  signals:
    void lineCountChanged(int lineCount);
    void scrollYChanged(int scrollY);
    void lineHeightChanged(double lineHeight);
    void textChanged(QString text);
    void cursorPositionChanged(int cursorPosition);

    void selectionStartChanged(int selectionStart);

    void selectionEndChanged(int selectionEnd);

  public slots:
    void setLineCount(int lineCount)
    {
        if (m_lineCount == lineCount)
            return;

        m_lineCount = lineCount;
        emit lineCountChanged(lineCount);
    }

    void setScrollY(int scrollY)
    {
        if (m_scrollY == scrollY)
            return;

        m_scrollY = scrollY;
        emit scrollYChanged(scrollY);
    }

    void setLineHeight(double lineHeight)
    {
        if (m_lineHeight == lineHeight)
            return;

        m_lineHeight = lineHeight;
        emit lineHeightChanged(lineHeight);
    }

    void setText(QString text)
    {
        if (m_text == text)
            return;

        m_text = text;
        emit textChanged(text);
    }

    void setCursorPosition(int cursorPosition)
    {
        if (m_cursorPosition == cursorPosition)
            return;

        m_cursorPosition = cursorPosition;
        emit cursorPositionChanged(cursorPosition);
    }

    void setSelectionStart(int selectionStart)
    {
        if (m_selectionStart == selectionStart)
            return;

        m_selectionStart = selectionStart;
        emit selectionStartChanged(selectionStart);
    }

    void setSelectionEnd(int selectionEnd)
    {
        if (m_selectionEnd == selectionEnd)
            return;

        m_selectionEnd = selectionEnd;
        emit selectionEndChanged(selectionEnd);
    }

  private:
    ConfigManager *cfManager = new ConfigManager;
    int m_lineCount = 0;
    int m_scrollY = 0;
    double m_lineHeight = 0;
    int m_cursorPosition = 0;
    QString m_text;
    int m_selectionStart = 0;
    int m_selectionEnd = 0;
};
#endif // LINENUMBERS_HPP
