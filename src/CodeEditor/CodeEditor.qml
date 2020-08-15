import QtQuick 2.9
import QtQuick.Controls 2.5
import CodeEditorBackend 1.0

Item {
    width: parent.width
    height: parent.height

    ScrollView {
        id: view
        anchors.fill: parent

        TextArea {
            objectName: "textEditor"
            id: edit

            focus: true
            font.pixelSize: 20
            font.family: "Cascadia Code"
            selectByMouse: true
            text: "#include <iostream>"
            wrapMode: TextEdit.Wrap
        }
    }
    CodeEditorBackend {
        id: backend
    }
}
