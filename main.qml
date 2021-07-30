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
                 height: 25
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
                 height: 25
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
                 height: 25
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
                 height: 25
                 anchors.top: octResult.bottom
                 color: 'lightgray'
                 Text {
                     anchors.leftMargin: 10
                     id: binResultValues
                     text: '  BIN      ' + binResultValue
                     font.pixelSize: 12
                     anchors.verticalCenter: parent.verticalCenter
                     anchors.margins: right
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
                border.color: 'black'
                Image{
                    property real imageRatio: sourceSize.height/sourceSize.width
                    height: parent.height - 10
                    width: height/imageRatio
                    anchors.centerIn: parent
                    source: "icon/full_keypad_icon.png"
                }
                MouseArea{
                    anchors.fill: parent
                }
            }
            Rectangle{
                id: bittogglingKeypad
                width: parent.width / 6
                height: parent.height
                anchors.left: fullKeypad.right
                anchors.leftMargin: 6
                border.color: 'black'
                Image{
                    property real imageRatio: sourceSize.height/sourceSize.width
                    height: parent.height - 10
                    width: height/imageRatio
                    anchors.centerIn: parent
                    source: "icon/bit_toggling_keypad_icon.png"
                }
                MouseArea{
                    anchors.fill: parent
                }
            }

            Rectangle{
                id: bittogglingOption
                width: parent.width / 6 * 2 - 2*13
                height: parent.height
                anchors.left: bittogglingKeypad.right
                anchors.leftMargin: 6
                border.color: 'black'
                Text {
                    text: 'QWORD'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    anchors.fill: parent
                }
            }

            Rectangle{
                id: memoryStore
                width: parent.width / 6
                height: parent.height
                anchors.left: bittogglingOption.right
                anchors.leftMargin: 6
                border.color: 'black'
                Text {
                    text: 'MS'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    anchors.fill: parent
                }
            }

            Rectangle{
                id: memory
                width: parent.width / 6
                height: parent.height
                anchors.left: memoryStore.right
                anchors.leftMargin: 6
                border.color: 'black'
                Text {
                    text: 'M▾'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    anchors.fill: parent
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
                border.color: 'black'
                Text {
                    text: 'Bitwise ▾'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
            }
            Rectangle{
                id: bitshift
                height: parent.height
                width: parent.width / 3
                anchors.left: bitwise.right
                anchors.leftMargin: 6
                border.color: 'black'
                border.width: 0.5
                Text {
                    text: 'Bitshift ▾'
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
                MouseArea{
                    anchors.fill: parent
                }
            }
        }
        Rectangle{
            id: keypad
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
                            onClicked: _calculator.onDigitClick(text)
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
                        onClicked: _calculator.onDigitClick(text)
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
                            onClicked: _calculator.onOperatorClick(eventName)
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
                        onClicked: _calculator.onDigitClick(text)
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
                        enabled: (modelData == '.')?false:true
                        text: modelData
                        onClicked: _calculator.onDigitClick(text)
                    }
                }
              }
            }
    }
}
