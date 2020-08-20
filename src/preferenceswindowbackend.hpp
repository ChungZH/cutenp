#ifndef PREFERENCESWINDOWBACKEND_HPP
#define PREFERENCESWINDOWBACKEND_HPP

#include "common/nphelpers.h"

#include <QObject>

class PreferencesWindowBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList shThemeList READ shThemeList)
    Q_PROPERTY(int currentIndex READ currentIndex)
    Q_PROPERTY(QString currentName WRITE setCurrentName)

  public:
    PreferencesWindowBackend()
    {
    }

    QStringList shThemeList() const
    {
        return Npanda::common::shThemeList;
    }

    int currentIndex() const
    {
        return Npanda::common::shThemeList.indexOf(m_currentName);
    }

  public slots:
    void setCurrentName(const QString &name)
    {
        m_currentName = name;
    }

  private:
    QString m_currentName;
};

#endif // PREFERENCESWINDOWBACKEND_HPP
