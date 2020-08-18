#ifndef ABOUTWINDOWBACKEND_HPP
#define ABOUTWINDOWBACKEND_HPP

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QUrl>

class AboutwindowBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString creditText READ creditText WRITE setCreditText NOTIFY creditTextChanged)

  public:
    AboutwindowBackend()
    {
        setCreditText(":/assets/CREDIT.md");
    }

    QString creditText()
    {
        return m_creditText;
    }

  signals:
    void creditTextChanged();

  public slots:
    void setCreditText(const QString &creditTextSource)
    {
        QFile file(creditTextSource);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        m_creditText = file.readAll();
        emit creditTextChanged();
        file.close();
    }

  private:
    QString m_creditText;
};

#endif // ABOUTWINDOWBACKEND_HPP
