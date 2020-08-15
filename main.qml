import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 450
    font.family: "Microsoft YaHei"

    Flickable {
        id: flick
        TextEdit {
            objectName: "textEditor"
            id: edit
            width: flick.width
            focus: true
            font.pixelSize: 20
            font.family: "Cascadia Code"
            selectByMouse: true
            text: "#include <iostream>"
        }
    }
}
