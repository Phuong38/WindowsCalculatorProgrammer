import QtQuick 2.0
import QtQuick.Controls 2.12
Window{
    id: windowss
    visible: true
    width: 320
    height: 500

    property string hexResultValue : _calculator.hexResult
    property string decResultValue : _calculator.decResult
    property string octResultValue : _calculator.octResult
    property string binResultValue : _calculator.binResult
    property string mainResultValue: _calculator.mainResult
    property string expResultValue: _calculator.expResult

    Item{
        id: mainCalculator
        width: parent.width
        height: parent.height
        Rectangle{
             id:resultZone
             width: parent.width
             height: 190
             color: 'lightgray'
             Rectangle{
                 id: expResult
                 width: parent.width
                 height: 25
                 y:30
                 color: 'lightgray'
                 Text {
                     id: expResultValues
                     font.pixelSize: 20
                     anchors.rightMargin: 20
                     anchors.right: parent.right
                     anchors.verticalCenter: parent.verticalCenter
                     text: " " + expResultValue
                 }
             }

             Rectangle{
                 id: mainResult
                 width: parent.width
                 height: 35
                 anchors.top: expResult.bottom
                 border.color: 'black'
                 color: 'lightgray'
                 Text {
                     id: mainResultValues
                     text: "" + mainResultValue
                     font.pixelSize: 25
                     font.pointSize: 3
                     anchors.rightMargin: 15
                     anchors.right: parent.right
                     anchors.verticalCenter: parent.verticalCenter
                 }
             }

             Rectangle{
                 id: hexResult
                 width: parent.width
                 height: 23
                 anchors.top: mainResult.bottom
                 color: 'lightgray'
                 Text {
                     id: hexResultValues
                     text: '  HEX     ' + hexResultValue
                     font.pixelSize: 12
                     anchors.verticalCenter: parent.verticalCenter
                     MouseArea{
                         anchors.fill: parent
                         onClicked: {
                             hexKeyPad.opacity = 1
                             hexKeyPad.enabled = true
                         }
                     }
                 }
             }
             Rectangle{
                 id: decResult
                 width: parent.width
                 height: 23
                 anchors.top: hexResult.bottom
                 color: 'lightgray'
                 Text {
                     id: decResultValues
                     text: '  DEC     ' + decResultValue
                     font.pixelSize: 12
                     anchors.verticalCenter: parent.verticalCenter
                     MouseArea{
                         anchors.fill: parent
                         onClicked: {
                             hexKeyPad.opacity =  0.2
                             hexKeyPad.enabled = false
                         }
                     }
                 }
             }
             Rectangle{
                 id: octResult
                 width: parent.width
                 height: 23
                 anchors.top: decResult.bottom
                 color: 'lightgray'
                 Text {
                     id: octResultValues
                     text: '  OCT     ' + octResultValue
                     font.pixelSize: 12
                     anchors.verticalCenter: parent.verticalCenter
                 }
             }
             Rectangle{
                 id: binResult
                 width: parent.width
                 height: 41
                 anchors.top: octResult.bottom
                 color: 'lightgray'
                 Rectangle{
                     id: bin
                     color: parent.color
                     width: 36; height: parent.height
                     Text {
                         y:3; x: 7
                         text: 'BIN'
                         font.pixelSize: 12
                     }
                 }
                 Rectangle{
                     height: parent.height
                     width: parent.width - 36
                     anchors.left: bin.right
                     anchors.leftMargin: 10
                     color: parent.color
                     Text {
                         y: 3
                         text: binResultValue
                         font.pixelSize: 12
                     }
                 }
             }

        }
        Rectangle{
            id: menuZone
            width: parent.width
            height: 30
            anchors.top: resultZone.bottom
            color: 'lightgray'
            Rectangle{
                id: fullKeypad
                width: parent.width / 6
                height: parent.height
                color: parent.color
                border.color: fullKeypadMouse.containsMouse?"black":"lightgray"
                Image{
                    property real imageRatio: sourceSize.height/sourceSize.width
                    height: parent.height - 10
                    width: height/imageRatio
                    anchors.centerIn: parent
                    source: "icon/full_keypad_icon.png"
                }
                MouseArea{
                    id: fullKeypadMouse
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
            Rectangle{
                id: bittogglingKeypad
                width: parent.width / 6
                height: parent.height
                anchors.left: fullKeypad.right
                anchors.leftMargin: 6
                color: parent.color
                border.color: bittogglingKeypadmouse.containsMouse?"black":"lightgray"
                Image{
                    property real imageRatio: sourceSize.height/sourceSize.width
                    height: parent.height - 10
                    width: height/imageRatio
                    anchors.centerIn: parent
                    source: "icon/bit_toggling_keypad_icon.png"
                }
                MouseArea{
                    id:bittogglingKeypadmouse
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }

            Rectangle{
                id: bittogglingOption
                width: parent.width / 6 * 2 - 2*13
                height: parent.height
                anchors.left: bittogglingKeypad.right
                anchors.leftMargin: 6
                color: parent.color
                border.color: bittogglingOptionmouse.containsMouse?"black":"lightgray"
                Text {
                    text: 'QWORD'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    id:bittogglingOptionmouse
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }

            Rectangle{
                id: memoryStore
                width: parent.width / 6
                height: parent.height
                anchors.left: bittogglingOption.right
                anchors.leftMargin: 6
                color: parent.color
                border.color: memoryStoreMouse.containsMouse?"black":"lightgray"
                Text {
                    text: 'MS'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    id:memoryStoreMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        memory.enabled = true
                        memory.opacity = 1
                        _memoryModel.insertData(_calculator.mainResult)
                    }
                }
            }

            Rectangle{
                id: memory
                width: parent.width / 6
                height: parent.height
                anchors.left: memoryStore.right
                anchors.leftMargin: 6
                color: parent.color
                enabled: false
                opacity: 0.5
                Text {
                    text: 'M▾'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        memoryList.visible = !memoryList.visible
                        memoryListPopup.open()
                    }
                }
            }
        }
        Popup{
            id: memoryListPopup
            y: parent.height / 2 - 30
            height: parent.height / 2 + 30
            width: parent.width
            modal:true
            focus: true
            contentItem: Rectangle{
                id: memoryList
                color: "lightgray"
                anchors.top: menuZone.bottom
                visible: false
                z : 1
                Component {
                    id: memoryComponent
                    Rectangle {
                        width: memoryList.width ; height: 95
                        color: memoryComponentMouse.containsMouse?"darkgray":"lightgray"
                        MouseArea{
                            id: memoryComponentMouse
                            anchors.fill: parent
                            hoverEnabled: true
                        }

                        Rectangle{
                            id: memoryControl
                            width: 90
                            height: 20
                            color: "lightgray"
                            x: parent.width - 130
                            y: parent.height/6 + 30
                            visible: memoryComponentMouse.containsMouse?true:false
                            Rectangle{
                                id:mclear
                                width: 30
                                height: 20
                                color: mclearmouse.containsMouse?(mclearmouse.pressed ? "#d6d6d6" : "black") : (mclearmouse.pressed ? "#d6d6d6" : "white")
                                Text {
                                    text: "MC"
                                    anchors.centerIn: parent
                                    color: mclearmouse.containsMouse?(mclearmouse.pressed ? "black" : "white") : (mclearmouse.pressed ? "black" : "black")
                                }
                                MouseArea{
                                    id:mclearmouse
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked:
                                        _memoryModel.removeData(model.index)
                                }
                            }
                            Rectangle{
                                id: mplus
                                anchors.left: mclear.right
                                anchors.leftMargin: 2
                                width: 30
                                height: 20
                                color: mplusmouse.containsMouse?(mplusmouse.pressed ? "#d6d6d6" : "black") : (mplusmouse.pressed ? "#d6d6d6" : "white")
                                Text {
                                    text: "M+"
                                    anchors.centerIn: parent
                                    color: mplusmouse.containsMouse?(mplusmouse.pressed ? "black" : "white") : (mplusmouse.pressed ? "black" : "black")
                                }
                                MouseArea{
                                    id: mplusmouse
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked:
                                        _memoryModel.onMplusClick(model.index)
                                }
                            }
                            Rectangle{
                                id:mmine
                                anchors.left: mplus.right
                                anchors.leftMargin: 2
                                width: 30
                                height: 20
                                color: mminemouse.containsMouse?(mminemouse.pressed ? "#d6d6d6" : "black") : (mminemouse.pressed ? "#d6d6d6" : "white")
                                Text {
                                    text: "M-"
                                    anchors.centerIn: parent
                                    color: mminemouse.containsMouse?(mminemouse.pressed ? "black" : "white") : (mminemouse.pressed ? "black" : "black")
                                }
                                MouseArea{
                                    id:mminemouse
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked:
                                        _memoryModel.onMmineClick(model.index)
                                }
                            }
                        }

                        Text
                        {
                            x: parent.width - 50
                            y: parent.height/6
                            text: model.value;
                            font.pixelSize: 18
                        }
                    }
                }
                ListView {
                    anchors.fill: parent
                    model: _memoryModel
                    delegate: memoryComponent
                    clip: true
                }
                Rectangle{
                    width: 32
                    height: 32
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    color: parent.color
                    Image {
                        source: "icon/delete.png"
                        anchors.fill: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            _memoryModel.onClearDataClick()
                            memory.enabled = false
                            memory.opacity = 0.5
                        }
                    }
                }
            }
        }

        Rectangle{
            id:bitOptionZone
            width: parent.width
            height: 30
            anchors.top: menuZone.bottom
            color: 'lightgray'
            Rectangle{
                id: bitwise
                height: parent.height
                width: parent.width / 3
                color: parent.color
                border.color: bitOptionZoneMouse.containsMouse?"black":"lightgray"
                Text {
                    text: 'Bitwise ▾'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    id:bitOptionZoneMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        bitwiseOption.visible = !bitwiseOption.visible
                        keypad.focus = false
                        bitwiseOption.focus = true
                        popupBitwiseOption.open()
                    }
                }
            }
            Rectangle{
                id: bitshift
                height: parent.height
                width: parent.width / 3
                anchors.left: bitwise.right
                anchors.leftMargin: 6
                color: parent.color
                border.color: bitshiftMouse.containsMouse?"black":"lightgray"
                Text {
                    text: 'Bitshift ▾'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    id: bitshiftMouse
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }
        Popup{
            id: popupBitwiseOption
            height: 90
            width: parent.width * 3/5
            y: parent.height /2
            contentItem:  Rectangle{
                id: bitwiseOption
                color: 'lightgray'
                opacity: 0.8
                Repeater{
                    model: ["AND", "OR", "NOT", "NAND", "NOR", "XOR"]
                    KeypadButton{
                        x: (index % 3) * width
                        y: Math.floor(index / 3) * height
                        width: bitwiseOption.width / 3
                        height: bitwiseOption.height / 2
                        color: containMouse?(pressed ? "#d6d6d6" : "lightgray") : (pressed ? "#d6d6d6" : "white")
                        text: modelData
                        onClicked: _calculator.onOperatorClick(eventName)
                        property string eventName: {
                            switch (text) {
                            case "AND": return "&"
                            case "OR": return "|"
                            case "XOR": return "^"
                            case "NAND": return "$"
                            case "NOR": return "#"
                            case "NOT": return "~"
                            default: return text
                            }
                        }
                    }
                }
            }
        }

        Rectangle{
            id: keypad
            enabled: true
            width: parent.width
            height: parent.height / 2
            anchors.top: bitOptionZone.bottom
            color:'lightgray'
            Rectangle{
                id: hexKeyPad
                width: parent.width / 5
                height: parent.height
                opacity: 0.3
                enabled: false
                Column{
                    Repeater{
                        id: hexKeyPadValues
                        model: ["A", "B", "C", "D", "E", "F"]
                        KeypadButton{
                            y: index *(hexKeyPad.height / 6)
                            width: hexKeyPad.width
                            height: hexKeyPad.height / 6
                            color: containMouse?(pressed ? "#d6d6d6" : "lightgray") : (pressed ? "#d6d6d6" : "white")
                            text: modelData
                            onClicked:{
                                bitwiseOption.visible = false
                                 _calculator.onDigitClick(text)
                            }

                            property string eventName: {
                                switch (text) {
                                case ".": return "POINT"
                                case "C": return "C"
                                default: return "DIGIT." + text
                                }
                            }
                        }
                    }
                }
            }
            Rectangle{
                id: functionKeypad
                width: parent.width * 3/5
                height: parent.height * 1/3
                anchors.top: parent.top
                anchors.left: hexKeyPad.right
                opacity: 0.6
                color: 'lightgray'
                Repeater{
                    id: functionKeypadValues
                    model: ["<<", ">>", "C", "(", ")", "%"]
                    KeypadButton{
                        x: (index % 3) * width
                        y: Math.floor(index / 3) * height
                        width: functionKeypad.width / 3
                        height: functionKeypad.height / 2
                        color: containMouse?(pressed ? "#d6d6d6" : "lightgray") : (pressed ? "#d6d6d6" : "white")
                        text: modelData
                        onClicked:{
                            bitwiseOption.visible = false
                            _calculator.onOperatorClick(eventName)
                        }

                        property string eventName: {
                            switch (text) {
                            case "<<": return "<"
                            case ">>": return ">"
                            default: return text
                            }
                        }
                    }
                }
            }
            Rectangle{
                id: operatorKeypad
                width: parent.width / 5
                height: parent.height
                anchors.top: parent.top
                anchors.left: functionKeypad.right
                opacity: 0.6
                color: 'lightgray'
                Column{
                    Repeater{
                        id: operatorKeypadValues
                        model: ["⌫", "÷", "×", "-","+", "="]
                        KeypadButton{
                            y: index *(operatorKeypad.height / 6)
                            width: operatorKeypad.width
                            height: operatorKeypad.height / 6
                            color: (modelData == "=")?( containMouse?(pressed ? "lightgray" : "darkgray"): "#9a9a9a" ): containMouse?(pressed ? "#d6d6d6" : "lightgray") : (pressed ? "#d6d6d6" : "white")
                            text: modelData
                            onClicked: {
                                bitwiseOption.visible = false
                                _calculator.onOperatorClick(eventName)
                            }

                            property string eventName: {
                                switch (text) {
                                case "⌫": return "del"
                                case "×": return "x"
                                default: return text
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                id: numberKeypad
                width: parent.width *  3/5
                height: parent.height * 2/3
                anchors.top: functionKeypad.bottom
                anchors.right: operatorKeypad.left
                color: 'black'
                Repeater{
                    model: ["7", "8", "9", "4", "5", "6", "1", "2", "3"]
                    KeypadButton{
                        x: (index % 3) * width
                        y: Math.floor(index / 3) * height
                        width: numberKeypad.width / 3
                        height: numberKeypad.height / 4
                        color: containMouse?(pressed ? "#d6d6d6" : "lightgray") : (pressed ? "#d6d6d6" : "white")
                        text: modelData
                        onClicked: {
                            bitwiseOption.visible = false
                            _calculator.onDigitClick(text)
                        }
                        }
                    }
                Repeater{
                    model: ["+/-", "0", "."]
                    KeypadButton{
                        x: (index % 3) * width
                        y:parent.height * 3/4
                        width: numberKeypad.width / 3
                        height: numberKeypad.height / 4
                        color: containMouse?(pressed ? "#d6d6d6" : "lightgray") : (pressed ? "#d6d6d6" : "white")
                        text: modelData
                        onClicked: {
                            bitwiseOption.visible = false
                            _calculator.onDigitClick(eventName)
                        }
                        property string eventName: {
                            switch (text) {
                            case "0": return "0"
                            default: return
                            }
                        }
                    }
                }
              }
            }
    }
}
