import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Material 2.3
import ConfigManager 1.0
import PreferencesWindowBackend 1.0

Window {
    title: qsTr("Preferences")
    height: 400
    width: 500

    Column {
        id: column
        anchors.fill: parent
        spacing: 20

        TabBar {
            id: bar
            width: parent.width
            currentIndex: 1
            TabButton {
                text: qsTr("General")
            }
            TabButton {
                text: qsTr("Text Editor")
            }
        }

        StackLayout {
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: bar.bottom
            currentIndex: bar.currentIndex
            Item {
                id: generalTab
            }
            Item {
                id: textEditorTab

                Grid {
                    spacing: 5
                    columns: 2

                    GroupBox {
                        id: fontGroup
                        title: qsTr("Font")
                        font.pointSize: 13

                        Grid {
                            spacing: 5
                            columns: 2
                            Text {
                                id: fontFamily
                                text: qsTr("Font Family: ")
                                font.pointSize: 10
                            }
                            TextField {
                                text: cfManager.editorFontFamily
                                font.pointSize: 10

                                onTextChanged: {
                                    cfManager.setEditorFontFamily(text)
                                }
                            }

                            Text {
                                id: fontSize
                                text: qsTr("Font Size: ")
                                font.pointSize: 10
                            }
                            SpinBox {
                                value: cfManager.editorFontSize
                                font.pointSize: 10
                                inputMethodHints: Qt.ImhFormattedNumbersOnly
                                editable: true
                                width: 130

                                onValueChanged: {
                                    cfManager.editorFontSize = value
                                }
                            }
                        }
                    }

                    GroupBox {
                        id: shGroup // Syntax Highlighting
                        title: qsTr("Syntax Highlighting")
                        font.pointSize: 13
                        Grid {
                            columns: 2
                            spacing: 5

                            Text {
                                id: shTheme
                                text: qsTr("Theme")
                                font.pointSize: 10
                            }

                            ComboBox {
                                model: backend.shThemeList
                                font.pointSize: 10
                                editable: true
                                currentIndex: {
                                    backend.setCurrentName(
                                                cfManager.editorColorTheme)
                                    backend.currentIndex
                                }
                                onCurrentTextChanged: {
                                    cfManager.setEditorColorTheme(currentText)
                                }
                            }
                        }
                    }
                    GroupBox {
                        id: behaviorGroup
                        title: qsTr("Behavior")
                        font.pointSize: 13
                    }
                }
            }
        }
    }


    /**
 Button {
icon.source: "qrc:/i/text_fields-24px.svg"
 onClicked: {
 fontDialog.open()
   width: 58
  height: 58
 highlighted: true
 Material.accent: Material.Orange
                        }
                        */
    ConfigManager {
        id: cfManager
    }

    PreferencesWindowBackend {
        id: backend
    }

    FontDialog {
        id: fontDialog
        monospacedFonts: true
        onVisibleChanged: {
            if (visible == false) {
                cfManager.setEditorFontFamily(font.family)
            }
        }
    }

    onVisibleChanged: {
        if (visible == false) // closed
        {
            cfManager.save()
        }
    }
}
