import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.3
import QtQuick.Window 2.10

import AboutwindowBackend 1.0

Window {
    title: qsTr("About Notepanda")

    minimumWidth: 450
    minimumHeight: 500

    Column {
        id: column
        anchors.margins: 8
        spacing: 15
        anchors.fill: parent

        width: 413.6

        Image {
            id: image
            y: 23
            width: 413.6
            height: 153.6
            anchors.left: parent.left
            anchors.leftMargin: 0
            fillMode: Image.Stretch
            source: "qrc:/assets/horizontal-logo-text.png"
        }

        Grid {
            columns: 2
            spacing: 16
            Text {
                text: qsTr("Version")
                font.pointSize: 10
                font.family: {
                    if (Qt.platform.os == "windows")
                        "Microsoft YaHei"
                }
            }
            Text {
                text: Qt.application.version
                font.pointSize: 10
                font.family: {
                    if (Qt.platform.os == "windows")
                        "Microsoft YaHei"
                }
            }
            Text {
                text: "GitHub"
                font.pointSize: 10
                font.family: {
                    if (Qt.platform.os == "windows")
                        "Microsoft YaHei"
                }
            }
            Text {
                text: "[ChungZH/notepanda](https://github.com/ChungZH/notepanda)"
                textFormat: Text.MarkdownText
                onLinkActivated: Qt.openUrlExternally(link)
                font.pointSize: 10
                font.family: {
                    if (Qt.platform.os == "windows")
                        "Microsoft YaHei"
                }
            }
            Text {
                text: "License"
                font.pointSize: 10
                font.family: {
                    if (Qt.platform.os == "windows")
                        "Microsoft YaHei"
                }
            }
            Text {
                text: "MIT"
                font.pointSize: 10
                font.family: {
                    if (Qt.platform.os == "windows")
                        "Microsoft YaHei"
                }
            }
        }

        TextArea {
            id: creditArea
            width: 413.6
            wrapMode: TextArea.Wrap
            text: backend.creditText
            textFormat: TextArea.MarkdownText
        }
    }

    AboutwindowBackend {
        id: backend
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.8999999761581421;height:480;width:640}D{i:2;anchors_x:98}
}
##^##*/

