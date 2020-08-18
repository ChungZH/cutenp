#ifndef LINENUMBERS_HPP
#define LINENUMBERS_HPP

#include <QPainter>
#include <QQuickPaintedItem>
#include <algorithm>
#include <cmath>

class LineNumbers : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int lineCount READ lineCount WRITE setLineCount NOTIFY lineCountChanged)
    Q_PROPERTY(int scrollY READ scrollY WRITE setScrollY NOTIFY scrollYChanged)
    Q_PROPERTY(float lineHeight READ lineHeight WRITE setLineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)

  public:
    explicit LineNumbers(QQuickPaintedItem *parent = nullptr)
    {
    }

    int lineCount() const
    {
        return m_lineCount;
    }

    int scrollY() const
    {
        return m_scrollY;
    }

    float lineHeight() const
    {
        return m_lineHeight;
    }

    virtual void paint(QPainter *painter) override
    {
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
        int numLines = lastLineVisible - firstLineVisible;
        for (int i = 0; i < numLines; i++)
        {
            int lineNumber = i + firstLineVisible + 1;
            QFont font("times", 24);
            QFontMetrics fm(font);
            QString text = QString("%1").arg(lineNumber);
            int textWidth = fm.horizontalAdvance(text);
            int textHeight = m_lineHeight;
            float x = width() - textWidth * 0.5 - 5;
            float y = 5 + i * m_lineHeight - rest;
            QRectF textRect(x, y, textWidth, textHeight);

            if (lineNumber >= selectedTextStartLine && lineNumber < selectedTextStartLine + numLinesSelected)
            {
                QRectF selectedTextRect(0, y, width(), textHeight);
                painter->setPen(QColor("#b2d7ff"));
                painter->drawRect(selectedTextRect);
                painter->fillRect(selectedTextRect, QColor("#b2d7ff"));
            }
            if (lineNumber == cursorLine)
            {
                QRectF selectedTextRect(0, y, width(), textHeight);
                painter->setPen(Qt::lightGray);
                painter->drawRect(selectedTextRect);
                painter->fillRect(selectedTextRect, Qt::lightGray);
            }

            painter->setPen(Qt::black);
            painter->drawText(textRect, text);
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
    void lineHeightChanged(float lineHeight);
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

    void setLineHeight(float lineHeight)
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
    int m_lineCount = 0;
    int m_scrollY = 0;
    float m_lineHeight = 0;
    int m_cursorPosition = 0;
    QString m_text;
    int m_selectionStart = 0;
    int m_selectionEnd = 0;
};
#endif // LINENUMBERS_HPP
