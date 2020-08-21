#ifndef PREFERENCESWINDOWBACKEND_HPP
#define PREFERENCESWINDOWBACKEND_HPP

#include "common/nphelpers.h"

#include <QObject>

class PreferencesWindowBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList shThemeList MEMBER m_shThemeList)
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QString currentName MEMBER m_currentName)

  public:
    PreferencesWindowBackend()
    {
        m_shThemeList = Npanda::common::shThemeList;
    }

    int currentIndex() const
    {
        return Npanda::common::shThemeList.indexOf(m_currentName);
    }

  signals:
    void currentIndexChanged(int curIdx);

  public slots:
    void setCurrentName(const QString &name)
    {
        m_currentName = name;
    }

  private:
    QString m_currentName;
    QStringList m_shThemeList;
};

#endif // PREFERENCESWINDOWBACKEND_HPP
