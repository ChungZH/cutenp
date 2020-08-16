import QtQuick 2.9
import QtQuick.Controls 2.5
import CodeEditorBackend 1.0

Item {
    property alias textArea: textArea
    property alias text: textArea.text
    property string title: changedSinceLastSave ? fileName + "*" : fileName
    property alias fileName: backend.fileName
    property bool changedSinceLastSave: false
    property bool isUnsavedFile: true

    function openFile(fileUrl) {
        backend.fileUrl = fileUrl
        backend.load()
        textArea.text = backend.text
        isUnsavedFile = false
        changedSinceLastSave = false
    }

    width: parent.width
    height: parent.height

    ScrollView {
        id: view
        anchors.fill: parent

        TextArea {
            objectName: "textEditor"
            id: textArea

            focus: true
            font.pixelSize: 20
            font.family: {
                "Cascadia Code"
                "JetBrainsMono Nerd Font"
            }
            selectByMouse: true
            text: "#include <iostream>"
            wrapMode: TextEdit.Wrap
        }
    }
    CodeEditorBackend {
        id: backend
    }
}
