import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.3
import QtQuick.Window 2.10

import AboutwindowBackend 1.0

Window {
    title: qsTr("About Notepanda")

    minimumWidth: 450
    minimumHeight: 200

    Flow {
        id: aboutFlow
        flow: Flow.TopToBottom
        anchors.margins: 8
        spacing: 10
        anchors.fill: parent

        Image {
            id: image
            x: 98
            y: 23
            width: 413.6
            height: 153.6
            source: "qrc:/assets/horizontal-logo-text.png"
        }

        Text {
            text: qsTr("Version: ") + Qt.application.version
            font.pointSize: 10
            font.family: {
                if (Qt.platform.os == "windows")
                    "Microsoft YaHei"
            }
        }

        TextArea {
            id: creditArea
            text: backend.creditText
        }
    }

    //AboutwindowBackend {
    //id: backend
    //}
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.8999999761581421;height:480;width:640}
}
##^##*/

