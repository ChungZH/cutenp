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

    Flickable {
        id: view
        anchors.fill: parent

        contentWidth: textArea.paintedWidth
        contentHeight: textArea.paintedHeight
        clip: true

        ScrollBar.vertical: ScrollBar {
            id: control
            policy: ScrollBar.AlwaysOn
            size: 0.3
            active: true
            position: 0.2
            orientation: Qt.Vertical
            width: 10

            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 100
                radius: width / 2
                color: control.pressed ? "#81e889" : "#c2f4c6"
            }
        }

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

        function ensureVisible(r) {
            if (contentX >= r.x)
                contentX = r.x
            else if (contentX + width <= r.x + r.width)
                contentX = r.x + r.width - width
            if (contentY >= r.y)
                contentY = r.y
            else if (contentY + height <= r.y + r.height)
                contentY = r.y + r.height - height
        }

        TextEdit {
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
                // lineNumbers.scrollY = view.flickableItem.contentY
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
            onCursorRectangleChanged: view.ensureVisible(cursorRectangle)
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
