import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.3

import "./CodeEditor" 1.0

//import "./AboutWindow.qml"
ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 450
    font.family: "Microsoft YaHei"
    title: m_codeEditor.title

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

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
                onTriggered: m_codeEditor.clear()
                shortcut: StandardKey.New
            }

            Action {
                text: qsTr("&Open...")
                onTriggered: {
                    openDialog.open()
                }
                shortcut: StandardKey.Open
            }

            Action {
                text: qsTr("&Save...")
                onTriggered: {
                    m_codeEditor.save()
                }
                shortcut: StandardKey.Save
            }

            Action {
                text: qsTr("Save &As...")
                onTriggered: {
                    m_codeEditor.saveAs()
                }
                shortcut: StandardKey.SaveAs
            }

            MenuSeparator {}

            Action {
                text: qsTr("&Quit...")
                onTriggered: {
                    Qt.quit()
                }
            }
        }
        Menu {
            title: qsTr("&Edit")

            Action {
                text: qsTr("Undo")
                onTriggered: m_codeEditor.textArea.undo()
                shortcut: StandardKey.Undo
                enabled: m_codeEditor.textArea.canUndo
            }
            Action {
                text: qsTr("Redo")
                onTriggered: m_codeEditor.textArea.redo()
                shortcut: StandardKey.Redo
                enabled: m_codeEditor.textArea.canRedo
            }

            MenuSeparator {}

            Action {
                text: {

                    if (!m_codeEditor.textArea.readOnly)
                        qsTr("Turn on Read-Only mode")
                    else
                        qsTr("Turn off Read-Only mode")
                }
                onTriggered: {
                    m_codeEditor.setReadOnly(!m_codeEditor.textArea.readOnly)
                }
            }
        }
        Menu {
            title: qsTr("&Help")

            Action {
                text: "About"
                onTriggered: m_aboutWindow.show()
            }
        }
    }

    AboutWindow {
        id: m_aboutWindow
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
}
