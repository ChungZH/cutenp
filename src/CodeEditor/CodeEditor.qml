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

    function openFile(fileUrl) {
        backend.fileUrl = fileUrl
        backend.load()
        textArea.text = backend.text
        isUnsavedFile = false
        changedSinceLastSave = false
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
        textArea.text = ""
        backend.fileUrl = ""
        backend.fileName = "Untitled"
        changedSinceLastSave = false
    }

    function setReadOnly(bl) {
        textArea.readOnly = bl
    }

    width: parent.width
    height: parent.height

    ScrollView {
        id: view
        anchors.fill: parent

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
            width: parent.width - lineNumbers.width
            anchors.left: lineNumbers.right
            anchors.leftMargin: 5

            function update() {
                var lineHeight = contentHeight / lineCount
                // var lineHeight = fontMetrics.height
                lineNumbers.lineCount = lineCount
                // lineNumbers.scrollY = flickableItem.contentY
                lineNumbers.lineHeight = lineHeight
                lineNumbers.cursorPosition = cursorPosition
                lineNumbers.selectionStart = selectionStart
                lineNumbers.selectionEnd = selectionEnd
                lineNumbers.text = text
                lineNumbers.update()
            }

            onLineCountChanged: update()
            onHeightChanged: update()
            onCursorPositionChanged: update()

            focus: true
            font.pointSize: configManager.editorFontSize
            font.family: configManager.editorFontFamily
            selectByMouse: true
            onTextChanged: changedSinceLastSave = true
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
