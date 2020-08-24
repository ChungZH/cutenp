import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import CodeEditorBackend 1.0
import LineNumbers 1.0
import ConfigManager 1.0

Item {
    property alias textArea: textArea
    property alias text: textArea.text
    property string title: if (changedSinceLastSave) {
                               fileName + "*"
                           } else {
                               fileName
                           }
    property alias fileName: backend.fileName
    property bool changedSinceLastSave: false
    property bool isUnsavedFile: true
    property var isStarted: false
    property string tabText: {
        for (var i = 0; i < configManager.editorTabSize; i++)
            " "
    }

    function openFile(fileUrl) {
        backend.fileUrl = fileUrl
        backend.load()
        textArea.clear()
        textArea.text = backend.text
        isUnsavedFile = false
        changedSinceLastSave = false
        configChanged()
    }

    function save() {
        backend.text = textArea.text
        backend.save()
        backend.load()
        changedSinceLastSave = false
    }

    function saveAs() {
        backend.text = textArea.text
        backend.saveAs()
        backend.load()
        changedSinceLastSave = false
    }

    function clear() {
        textArea.clear()
        backend.fileUrl = ""
        backend.fileName = "Untitled"
        changedSinceLastSave = false
    }

    function setReadOnly(bl) {
        textArea.readOnly = bl
    }

    function configChanged() {
        configManager.readGeneralSettings()
        lineNumbers.updateConfigs()
        lineNumbers.update()
        backend.updateShTheme(configManager.editorColorTheme)
        tabText = ""
        for (var i = 0; i < configManager.editorTabSize; i++)
            tabText += "1"
        console.log(tabText)
    }

    width: parent.width
    height: parent.height

    ScrollView {
        id: view
        anchors.fill: parent

        contentWidth: textArea.paintedWidth
        contentHeight: textArea.paintedHeight

        LineNumbers {
            id: lineNumbers
            height: {
                if (window.height > textArea.contentHeight)
                    window.height
                else
                    textArea.contentHeight
            }
            width: fontMetrics.advanceWidth(textArea.lineCount.toString()) + 10
        }

        TextArea {
            objectName: "textEditor"
            id: textArea

            height: parent.height
            width: if (configManager.showLineNumbers)
                       parent.width - lineNumbers.width
                   else
                       parent.width
            anchors.left: if (configManager.showLineNumbers)
                              lineNumbers.right
                          else
                              parent.left
            anchors.leftMargin: 5

            function update() {
                if (!configManager.showLineNumbers)
                    return
                var lineHeight = contentHeight / lineCount
                // var lineHeight = fontMetrics.height
                lineNumbers.lineCount = lineCount
                // lineNumbers.scrollY = view.flickableItem.contentY
                lineNumbers.lineHeight = lineHeight
                lineNumbers.cursorPosition = cursorPosition
                lineNumbers.selectionStart = selectionStart
                lineNumbers.selectionEnd = selectionEnd
                lineNumbers.text = text
                lineNumbers.update()
            }

            onTextChanged: changedSinceLastSave = true
            onLineCountChanged: update()
            onHeightChanged: update()
            onCursorPositionChanged: update()
            onPressed: {
                if (event.modifiers === Qt.Key_Tab) {
                    console.log("tabed")
                }
                console.log(tabText)
                //console.log(tabText)
                //console.log(fontMetrics.advanceWidth(tabText))
            }

            textFormat: "PlainText"
            focus: true
            font.pointSize: configManager.editorFontSize
            font.family: configManager.editorFontFamily
            selectByMouse: true
            tabStopDistance: fontMetrics.advanceWidth(tabText)

            background: Rectangle {
                color: backend.bgColor
            }
            selectionColor: backend.selectColor
        }
    }

    CodeEditorBackend {
        id: backend
    }

    ConfigManager {
        id: configManager
    }

    FontMetrics {
        id: fontMetrics
        font: textArea.font
    }
}
