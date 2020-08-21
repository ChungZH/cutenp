/**
 * Copyright (c) 2020 ChungZH. ALl Rights Reserved.
 * Licensed under the MIT license.
 * See file LICENSE for detail or copy at <https://opensource.org/licenses/MIT>
 *
 * This file is a part of Notepanda.
 *
 * @file configmanager.h
 * @brief This file declares the ConfigManager class for management
 *        configuration.
 */
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QFont>
#include <QObject>
#include <QSettings>
#include <QString>

/**
 * @brief The ConfigManager class
 */
class ConfigManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString editorFontFamily READ editorFontFamily WRITE setEditorFontFamily NOTIFY editorFontFamilyChanged)
    Q_PROPERTY(int editorFontSize READ editorFontSize WRITE setEditorFontSize NOTIFY editorFontSizeChanged)
    Q_PROPERTY(QString editorColorTheme READ editorColorTheme WRITE setEditorColorTheme NOTIFY editorColorThemeChanged)
    Q_PROPERTY(int editorTabSize READ editorTabSize WRITE setEditorTabSize NOTIFY editorTabSizeChanged)
    Q_PROPERTY(QString editorIndentMode READ editorIndentMode WRITE setEditorIndentMode NOTIFY editorIndentModeChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

  public:
    explicit ConfigManager(QObject *parent = nullptr);
    Q_INVOKABLE void save();
    Q_INVOKABLE void readGeneralSettings();

    static bool readJsonFile(QIODevice &device, QSettings::SettingsMap &map);
    static bool writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map);

    //
    QString editorFontFamily() const;
    int editorFontSize() const;
    QString editorColorTheme() const;
    int editorTabSize() const;
    QString editorIndentMode() const;
    qreal opacity() const;
  public slots:
    void setEditorFontFamily(const QString &fontname);
    void setEditorFontSize(const int &fontsize);
    void setEditorColorTheme(const QString &ctname);
    void setEditorTabSize(const int &tabsize);
    void setEditorIndentMode(const QString &indentmode);
    void setOpacity(const qreal &opacity);

  signals:
    void editorFontFamilyChanged();
    void editorFontSizeChanged();
    void editorColorThemeChanged();
    void editorIndentModeChanged();
    void editorTabSizeChanged();
    void opacityChanged();

  private:
    QSettings *settings;
    QString configFile;
    QString m_editorFontFamily;
    int m_editorFontSize;
    QString m_editorColorTheme;
    int m_editorTabSize;
    QString m_editorIndentMode;
    qreal m_opacity;
};

#endif // CONFIGMANAGER_H
