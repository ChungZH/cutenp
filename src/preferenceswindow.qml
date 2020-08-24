import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import ConfigManager 1.0
import QtQuick.Dialogs 1.2 as Dialogs
import PreferencesWindowBackend 1.0

Dialog {
    title: qsTr("Preferences")
    width: parent.width
    height: parent.height
    standardButtons: Dialog.Ok | Dialog.Cancel

    TabBar {
        id: bar
        width: parent.width

        Material.accent: Material.LightBlue

        TabButton {
            text: qsTr("General")
        }
        TabButton {
            text: qsTr("Text Editor")
        }
    }

    StackLayout {
        anchors.topMargin: 6
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        currentIndex: bar.currentIndex

        Item {
            id: generalTab
            ScrollView {
                anchors.fill: parent
                Grid {
                    spacing: 2
                    columns: 2
                    GroupBox {
                        id: appearanceGroup
                        title: qsTr("Appearance")
                        font.pointSize: 13

                        Grid {
                            spacing: 5
                            columns: 2
                            Text {
                                id: opacity
                                text: qsTr("Opacity: ")
                                font.pointSize: 10
                            }
                            Slider {
                                from: 0
                                value: 1
                                to: 1
                                onValueChanged: cfManager.setOpacity(value)
                            }
                        }
                    }
                }
            }
        }

        Item {
            id: textEditorTab
            ScrollView {
                anchors.fill: parent
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

                                onTextChanged: cfManager.setEditorFontFamily(
                                                   text)
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

                                onValueChanged: cfManager.editorFontSize = value
                            }

                            Button {
                                icon.source: "qrc:/i/text_font.svg"
                                onClicked: {
                                    fontDialog.open()
                                    width: 58
                                    height: 58
                                }
                                highlighted: true
                                Material.accent: Material.Orange
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
                                currentIndex: {
                                    backend.setCurrentName(
                                                cfManager.editorColorTheme)
                                    backend.currentIndex
                                }
                                onCurrentTextChanged: cfManager.setEditorColorTheme(
                                                          currentText)
                            }
                        }
                    }

                    GroupBox {
                        id: behaviorGroup
                        title: qsTr("Behavior")
                        font.pointSize: 13

                        Grid {
                            columns: 2
                            spacing: 5

                            Text {
                                id: tabPolicy
                                text: qsTr("Tab Policy: ")
                                font.pointSize: 10
                            }
                            ComboBox {
                                model: ["Spaces", "Tabs"]
                                font.pointSize: 10
                                currentIndex: {
                                    if (cfManager.editorIndentMode == "Spaces")
                                        0
                                    else
                                        1
                                }

                                onCurrentTextChanged: cfManager.setEditorIndentMode(
                                                          currentText)
                            }

                            Text {
                                id: tabSize
                                text: qsTr("Tab Size: ")
                                font.pointSize: 10
                            }
                            SpinBox {
                                value: cfManager.editorTabSize
                                font.pointSize: 10
                                editable: true
                                width: 130

                                onValueChanged: cfManager.editorTabSize = value
                            }
                        }
                    }

                    GroupBox {
                        id: displayGroup
                        title: qsTr("Display")
                        font.pointSize: 13

                        Grid {
                            columns: 2
                            spacing: 5

                            CheckBox {
                                id: showLineNumbers
                                text: qsTr("Show Linenumbers: ")
                                checked: cfManager.showLineNumbers
                                font.pointSize: 10
                                onCheckedChanged: cfManager.setShowLineNumbers(
                                                      checked)
                            }
                        }
                    }
                }
            }
        }
    }

    ConfigManager {
        id: cfManager
    }

    PreferencesWindowBackend {
        id: backend
    }

    Dialogs.FontDialog {
        id: fontDialog
        monospacedFonts: true
        font: Qt.font({
                          "family": cfManager.editorFontFamily,
                          "pointSize": cfManager.editorFontSize
                      })
        onAccepted: {
            cfManager.setEditorFontFamily(font.family)
            cfManager.setEditorFontSize(font.pointSize)
        }
    }

    onAccepted: {
        cfManager.save()
    }
    onRejected: {
        cfManager.readGeneralSettings()
    }
}
