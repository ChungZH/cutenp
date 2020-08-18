/**
 * Copyright (c) 2020 ChungZH. ALl Rights Reserved.
 * Licensed under the MIT license.
 * See file LICENSE for detail or copy at <https://opensource.org/licenses/MIT>
 *
 * This file is a part of Notepanda.
 *
 * @file configmanager.cpp
 * @brief This file implements the ConfigManager class.
 *
 */
#include "configmanager.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFontDatabase>
#include <QJsonDocument>
#include <QStandardPaths>

ConfigManager::ConfigManager(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_WIN
    if (QDir(QApplication::applicationDirPath() + "/config").exists())
    {
        configFile = QApplication::applicationDirPath() + "/config/notepanda.json";
    }
    else
    {
        QDir configDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation);
        configFile = configDir.absolutePath() + "/config.json";
    }
#else
    QDir configDir = QDir::homePath() + "/.config/notepanda";
    configFile = configDir.absolutePath() + "/config.json";
    if (!configDir.exists())
    {
        configDir.mkpath(configDir.absolutePath());
    }
#endif

    const QSettings::Format JsonFormat = QSettings::registerFormat("json", readJsonFile, writeJsonFile);
    settings = new QSettings(configFile, JsonFormat, this);

    readGeneralSettings();
}

bool ConfigManager::readJsonFile(QIODevice &device, QSettings::SettingsMap &map)
{
    QJsonParseError error;
    map = QJsonDocument::fromJson(device.readAll(), &error).toVariant().toMap();
    return error.error == QJsonParseError::NoError;
}

bool ConfigManager::writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    const auto json = QJsonDocument::fromVariant(map).toJson();
    return device.write(json) == json.size();
}

/**
 * @brief Save the settings.
 */
void ConfigManager::save()
{
    settings->beginGroup("Editor");
    settings->setValue("FontFamily", QVariant(m_editorFontFamily));
    settings->setValue("FontSize", QVariant(m_editorFontSize));
    settings->setValue("ColorTheme", QVariant(m_editorColorTheme));
    settings->setValue("TabSize", QVariant(m_editorTabSize));
    settings->setValue("IndentMode", QVariant(m_editorIndentMode));
}

/**
 * @brief Read general settings from `settings`.
 */
void ConfigManager::readGeneralSettings()
{
    if (settings->contains("Editor/FontFamily"))
    {
        m_editorFontFamily = settings->value("Editor/FontFamily").toString();
    }
    else
    {
        m_editorFontFamily = QFontDatabase::systemFont(QFontDatabase::FixedFont).family();
    }
    m_editorFontSize = settings->value("Editor/FontSize", 16).toInt();
    m_editorTabSize = settings->value("Editor/TabSize", 4).toInt();
    m_editorIndentMode = settings->value("Editor/IndentMode", "Spaces").toString();
    m_editorColorTheme = settings->value("Editor/ColorTheme", "Default").toString();
}

QString ConfigManager::editorFontFamily() const
{
    return m_editorFontFamily;
}
void ConfigManager::setEditorFontFamily(const QString &fontname)
{
    m_editorFontFamily = fontname;
}

int ConfigManager::editorFontSize() const
{
    return m_editorFontSize;
}
void ConfigManager::setEditorFontSize(const int &fontsize)
{
    m_editorFontSize = fontsize;
}

QString ConfigManager::editorColorTheme() const
{
    return m_editorColorTheme;
}
void ConfigManager::setEditorColorTheme(const QString &ctname)
{
    m_editorColorTheme = ctname;
}

int ConfigManager::editorTabSize() const
{
    return m_editorTabSize;
}
void ConfigManager::setEditorTabSize(const int &tabsize)
{
    m_editorTabSize = tabsize;
}

QString ConfigManager::editorIndentMode() const
{
    return m_editorIndentMode;
}
void ConfigManager::setEditorIndentMode(const QString &indentmode)
{
    m_editorIndentMode = indentmode;
}
