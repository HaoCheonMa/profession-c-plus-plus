import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: "Перемещение круга"

    Rectangle {
        id: leftRectangle
        width: 100
        height: 100
        color: "lightblue"
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        radius: 10
        border.color: "blue"
        border.width: 2

        Text {
            anchors.centerIn: parent
            text: "move"
            font.bold: true
            font.pointSize: 14
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (ball.x >= rightRectangle.x) {
                    ball.state = "InitialState";
                } else {
                    ball.x += 30;
                    ball.state = "OtherState";
                }
            }
        }
    }

    Rectangle {
        id: rightRectangle
        width: 100
        height: 100
        color: "lightcoral"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        radius: 10
        border.color: "red"
        border.width: 2

        Text {
            anchors.centerIn: parent
            text: "return"
            font.bold: true
            font.pointSize: 14
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.state = "InitialState";
            }
        }
    }

    Rectangle {
        id: ball
        width: 40
        height: 40
        radius: 20
        color: "gold"
        anchors.verticalCenter: leftRectangle.verticalCenter
        x: leftRectangle.x + (leftRectangle.width - width)/2

        states: [
            State {
                name: "InitialState"
                PropertyChanges {
                    target: ball
                    x: leftRectangle.x + (leftRectangle.width - ball.width)/2
                }
            },
            State {
                name: "OtherState"
                PropertyChanges {
                    target: ball
                    x: ball.x
                }
            }
        ]

        transitions: [
            Transition {
                from: "OtherState"
                to: "InitialState"
                NumberAnimation {
                    properties: "x,y"
                    duration: 1000
                    easing.type: Easing.OutBounce
                }
            }
        ]
    }
}
