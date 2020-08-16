import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.3

import "./CodeEditor" 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 450
    font.family: "Microsoft YaHei"
    title: m_codeEditor.title

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&New...")
                onTriggered: m_codeEditor.clear()
            }

            MenuItem {
                text: qsTr("&Open...")
                onTriggered: {
                    openDialog.open()
                }
            }

            MenuItem {
                text: qsTr("&Save...")
                onTriggered: {
                    m_codeEditor.save()
                }
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
}
