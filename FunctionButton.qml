import QtQuick 2.0

Rectangle{
    property bool containMouse: mouse.containsMouse
    property bool pressed: mouse.pressed
    id: functionButton
    signal functionButtonClicked
    height: 40
    border.color: containMouse? "white" : "#4F4F4F"
    border.width: 1
    color: containMouse?(pressed ? "#d6d6d6" : "#737373") : (pressed ? "#d6d6d6" : "#525353")
    MouseArea{
        id: mouse
        anchors.fill: parent
        onClicked: functionButton.functionButtonClicked()
        hoverEnabled: true
    }
}
