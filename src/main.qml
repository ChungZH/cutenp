import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import "./CodeEditor" 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 450
    font.family: "Microsoft YaHei"

    ScrollView {
        id: view
        anchors.fill: parent

        CodeEditor {}
    }
}
