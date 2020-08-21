import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.3
import ConfigManager 1.0

import "./CodeEditor" 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumWidth: 550
    minimumHeight: 500
    font.family: "Microsoft YaHei"
    title: m_codeEditor.title

    opacity: cfManager.opacity

    // Actions
    Action {
        id: newAct
        onTriggered: m_codeEditor.clear()
        shortcut: StandardKey.New
        icon.source: "qrc:/i/add.svg"
    }
    Action {
        id: openAct
        onTriggered: openDialog.open()
        shortcut: StandardKey.Open
        icon.source: "qrc:/i/open.svg"
    }
    Action {
        id: saveAct
        onTriggered: m_codeEditor.save()
        shortcut: StandardKey.Save
        icon.source: "qrc:/i/save.svg"
    }
    Action {
        id: saveAsAct
        onTriggered: m_codeEditor.saveAs()
        shortcut: StandardKey.SaveAs
        icon.source: "qrc:/i/save_as.svg"
    }
    Action {
        id: preferencesAct
        onTriggered: m_preferencesWindow.open()
        shortcut: StandardKey.Preferences
        icon.source: "qrc:/i/settings.svg"
    }
    Action {
        id: quitAct
        onTriggered: Qt.quit()
        shortcut: StandardKey.Quit
        icon.source: "qrc:/i/calendar_cancel.svg"
    }
    // Copy Paste and Cut cannot be in Menu.
    // Because when the MenuBar is clicked,
    // the active focus item is not in the textArea.
    // Then the selection will disappear!
    Action {
        text: qsTr("Copy")
        onTriggered: m_codeEditor.textArea.copy()
        shortcut: StandardKey.Copy
    }
    Action {
        text: qsTr("Paste")
        onTriggered: m_codeEditor.textArea.paste()
        shortcut: StandardKey.Paste
    }
    Action {
        text: qsTr("Cut")
        onTriggered: m_codeEditor.textArea.cut()
        shortcut: StandardKey.Cut
    }
    Action {
        id: undoAct
        onTriggered: m_codeEditor.textArea.undo()
        shortcut: StandardKey.Undo
        enabled: m_codeEditor.textArea.canUndo
        icon.source: "qrc:/i/undo.svg"
    }
    Action {
        id: redoAct
        onTriggered: m_codeEditor.textArea.redo()
        shortcut: StandardKey.Redo
        enabled: m_codeEditor.textArea.canRedo
        icon.source: "qrc:/i/redo.svg"
    }
    Action {
        id: readOnlyAct

        onTriggered: m_codeEditor.setReadOnly(!m_codeEditor.textArea.readOnly)

        icon.source: "qrc:/i/read_only.svg"
    }
    Action {
        id: aboutAct
        onTriggered: m_aboutWindow.show()
        icon.source: "qrc:/i/info.svg"
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                action: newAct
                text: qsTr("&New")
                ToolTip.text: qsTr("New file")
                ToolTip.visible: hovered
            }
            MenuItem {
                action: openAct
                text: qsTr("&Open")
                ToolTip.text: qsTr("Open file")
                ToolTip.visible: hovered
            }
            MenuItem {
                action: saveAct
                text: qsTr("&Save")
                ToolTip.text: qsTr("Save file")
                ToolTip.visible: hovered
            }
            MenuItem {
                action: saveAsAct
                text: qsTr("Save &As")
                ToolTip.text: qsTr("Save file as")
                ToolTip.visible: hovered
            }

            MenuSeparator {}

            MenuItem {
                action: preferencesAct
                text: qsTr("Preferences")
                ToolTip.text: qsTr("Open preferences window")
                ToolTip.visible: hovered
            }

            MenuSeparator {}

            MenuItem {
                action: quitAct
                text: qsTr("&Quit")
                ToolTip.text: qsTr("Quit")
                ToolTip.visible: hovered
            }
        }
        Menu {
            title: qsTr("&Edit")

            MenuItem {
                text: qsTr("Undo")
                action: undoAct
            }
            MenuItem {
                text: qsTr("Redo")
                action: redoAct
            }

            MenuSeparator {}

            MenuItem {
                text: {
                    if (!m_codeEditor.textArea.readOnly)
                        qsTr("Turn on Read-Only mode")
                    else
                        qsTr("Turn off Read-Only mode")
                }
                action: readOnlyAct
            }
        }
        Menu {
            title: qsTr("&Help")

            MenuItem {
                text: "&About"
                action: aboutAct
            }
        }
    }

    header: ToolBar {
        background: Rectangle {
            implicitHeight: 40
            color: Material.color(Material.Grey)
        }
        Row {
            spacing: 2
            ToolButton {
                action: newAct
                ToolTip.text: qsTr("New file")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: openAct
                ToolTip.text: qsTr("Open file")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: saveAct
                ToolTip.text: qsTr("Save file")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: saveAsAct
                ToolTip.text: qsTr("Save file as")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: preferencesAct
                ToolTip.text: qsTr("Open preferences window")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: quitAct
                ToolTip.text: qsTr("Quit")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: undoAct
            }
            ToolButton {
                action: redoAct
            }
            ToolButton {
                action: readOnlyAct
                ToolTip.text: qsTr("Read-Only")
                ToolTip.visible: hovered
            }
            ToolButton {
                action: aboutAct
            }
        }
    }

    AboutWindow {
        id: m_aboutWindow
    }

    PreferencesWindow {
        id: m_preferencesWindow

        onVisibleChanged: {
            if (result === Dialog.Accepted) {
                m_codeEditor.configChanged()
                cfManager.readGeneralSettings()
            }
        }
    }

    CodeEditor {
        id: m_codeEditor
    }

    FileDialog {
        id: openDialog
        title: "Open file"
        folder: shortcuts.documents
        onAccepted: {
            m_codeEditor.openFile(openDialog.fileUrl)
        }
    }

    ConfigManager {
        id: cfManager
    }
}
