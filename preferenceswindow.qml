import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1

Window {
    title: qsTr("Preferences")

    Column {
        anchors.fill: parent
        spacing: 20

        TabBar {
            id: bar
            width: parent.width
            TabButton {
                text: qsTr("General")
            }
            TabButton {
                text: qsTr("Text Editor")
            }
        }

        StackLayout {
            anchors.top: bar.bottom
            width: parent.width
            currentIndex: bar.currentIndex
            Item {
                id: generalTab
            }
            Item {
                id: textEditorTab

                GroupBox {
                    id: fontGroup
                    title: qsTr("Font")

                    Text {
                        id: fontFamily
                        text: qsTr("Font Family")
                    }
                }
            }
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

