import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "VideoPlayer"
    color: "#121212"

    Rectangle {
        id: videoScreen
        width: parent.width - 40
        height: parent.height * 0.65
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#1e1e1e"
        radius: 8
        border.color: "#444444"
        border.width: 1
        anchors.topMargin: 20
    }

    Rectangle {
        width: parent.width - 40
        height: parent.height * 0.29
        anchors.top: videoScreen.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#222222"
        radius: 12
        border.color: "#333333"
        border.width: 1
        anchors.topMargin: 10

        Column {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 12

            Row {
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Repeater {
                    model: [
                        {text:"▶️", tooltip:"Play"},
                        {text:"⏸️", tooltip:"Pause"},
                        {text:"⏹", tooltip:"Stop"},
                        {text:"⏪️", tooltip:"Rewind"},
                        {text:"⏩️", tooltip:"Forward"}
                    ]
                    delegate: Button {
                        text: modelData.text
                        width: 44
                        height: 44
                        font.pixelSize: 22
                        ToolTip.visible: hovered
                        ToolTip.text: modelData.tooltip
                    }
                }
            }

            Rectangle {
                id: customProgressBar
                width: parent.width - 20
                height: 14
                radius: 7
                color: "#444444"
                anchors.horizontalCenter: parent.horizontalCenter
                property real progressValue: 0

                Rectangle {
                    id: fillBar
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height
                    width: 0
                    radius: 7
                    color: "#00aaff"
                }

                onProgressValueChanged: {
                    fillBar.width = width * (progressValue / 100)
                }
            }

        }
    }
}
