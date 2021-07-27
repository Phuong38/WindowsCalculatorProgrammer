import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: mainWindow
    visible: true
    width: 322*1.5
    height: 681
    title: qsTr("Windows Calculator")
    color: "lightgray"
//    signal qmlSignal(msg: string)
//    property string mainResultV: _calculator.exp

    ResultScreen{
        id: resultScreen
        anchors.top: parent.top
        anchors.bottom: fullKeypadFunctionButton.top
    }

    FunctionButton{
        id: fullKeypadFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: parent.left
        Image{
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
            source: "icon/full_keypad_icon.png"
        }
    }

    FunctionButton{
        id: bitTogglingKeypadFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: fullKeypadFunctionButton.right
        Image {
            id: bitTogglingKeypadFunctionButton_icon
            source: "icon/bit_toggling_keypad_icon.png"
            property real imageRatio: sourceSize.height/sourceSize.width
            height: parent.height - 10
            width: height/imageRatio
            anchors.centerIn: parent
        }
    }

    FunctionButton{
        id: changeTypeFunctionButton
        width: 150
        anchors.bottom: fullKeypadWindows.top
        anchors.left: bitTogglingKeypadFunctionButton.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "QWORD"
            color: "white"
        }
    }

    FunctionButton{
        id: msFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: changeTypeFunctionButton.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "MS"
            color: "white"
        }
    }

    FunctionButton{
        id: mListFunctionButton
        width: (parent.width-150)/4
        anchors.bottom: fullKeypadWindows.top
        anchors.left: msFunctionButton.right
        anchors.right: parent.right
        Text{
            anchors.centerIn: parent
            font.pixelSize: 20
            text: "M▾"
            color: "white"
        }
    }



    Rectangle{
        id: fullKeypadWindows
        width: mainWindow.width
        height: mainWindow.height/2
        color: "#494949"
        anchors.bottom: parent.bottom

        Repeater{
            id: digits
            model: ["Lsh", "Rsh", "Or", "Xor", "Not", "And", "↑", "Mod", "CE", "C", "⌫", "÷", "A", "B", "7", "8", "9", "X", "C", "D", "4", "5", "6", "-", "E", "F", "1", "2", "3", "+", "(", ")", "+/-", "0", ".", "="]
            KeypadButton {
                x: (index % 6) * width
                y: Math.floor(index / 6) * height
                width: parent.width / 6
                height: parent.height / 6
                color: (modelData=="=")?( containMouse?(pressed ? "#0178D7" : "#036FC4"): "#104066" ): containMouse?(pressed ? "#d6d6d6" : "#737373") : (pressed ? "#d6d6d6" : "#111111")
                text: modelData
                onClicked:_calculator.onDigitClick(eventName)

                property string eventName: {
                    switch (text) {
                    case "=": return "="
                    case "C": return "C"
                    case "X": return "*"
                    case "÷": return "/"
                    default: return text
                    }
                }
            }
        }
    }
}
