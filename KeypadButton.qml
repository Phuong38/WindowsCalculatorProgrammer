import QtQuick 2.0

Rectangle {
    id: keypadButton
    signal clicked
    property alias text: text.text
    border.color: mouse.containsMouse?"white":"lightgray"
    border.width: 0.5
    property real textHeight: height - 2
    property real fontHeight: 0.5
    property bool pressed: mouse.pressed
    property bool containMouse: mouse.containsMouse

    Text {
        id: text
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.textHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: height * fontHeight
        font.family: "Open Sans Regular"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: keypadButton.clicked()
        hoverEnabled: true
    }
}
