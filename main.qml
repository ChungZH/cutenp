import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 450
    font.family: "Microsoft YaHei"

    ScrollView {
        anchors.fill: parent
        id: control
        TextArea {
            font.pixelSize: 20
            selectByMouse: true
        }
    }
}
