import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    TextArea {
        objectName: "textEditor"
        id: edit
        height: 500
        width: 450

        focus: true
        font.pixelSize: 20
        font.family: "Cascadia Code"
        selectByMouse: true
        text: "#include <iostream>"
        wrapMode: TextEdit.Wrap
    }
}
