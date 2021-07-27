import QtQuick 2.0

Window{
    id: windowss
    visible: true
    width: 322*1.5
    height: 681
    Item{
        id: mainCal
        height: parent.height
        width: parent.width
        Item{
            id: resultZone
            height: parent.height - 20
            width: parent.width
            Rectangle{
                id: expResult
                height: 30
                width: parent.width
                anchors.left: parent.right
                anchors.bottom: inputResult.top
                anchors.topMargin: 20
            }
            Rectangle{
                id: inputResult
                height: 40
                width: parent.width
                anchors.left: parent.right
                anchors.bottom: hexResult.top
                anchors.bottomMargin: 40
                Text {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 30
                    id: inputResultValue
                    text: '0'
                }
            }
            Rectangle{
                id: hexResult
                width: parent.width
                height: 25
                anchors.left: parent.left
                anchors.bottom: decResult
                Text {
                    id: hexResultValue
                    font.pixelSize: 20
                    text: " HEX  " + "0"
                }
            }
            Rectangle{
                id: decResult
                width: parent.width
                height: 25
                anchors.left: parent.left
                anchors.bottom: octResult
                Text {
                    id: decResultValue
                    font.pixelSize: 20
                    text: " DEC  " + "0"
                }
            }
            Rectangle{
                id: octResult
                width: parent.width
                height: 25
                anchors.left: parent.left
                anchors.bottom: binResult
                Text {
                    id: octResultValue
                    font.pixelSize: 20
                    text: " OCT  " + "0"
                }
            }
            Rectangle{
                id: binResult
                width: parent.width
                height: 25
                anchors.left: parent.left
                Text {
                    id: binResultValue
                    font.pixelSize: 20
                    text: " BIN  " + "0"
                }
            }
        }
    }

    Item{
        id: menuLayout
        height: 30
        width: parent.width
        anchors.top: mainCal.bottom
        Rectangle{
            id: fullKeyPad
            height: parent.height
            width: parent.width / 6
            Image {
                id: fullKeyPad_icon
                source: "icon/full_keypad_icon.png"
                property real imageRatio: sourceSize.height/sourceSize.width
                height: parent.height - 10
                width: height/imageRatio
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
            }
        }

        Rectangle{
            id: bittogglingKeyPad
            height: parent.height
            width: parent.width / 6
            Image {
                id: bittogglingKeyPad_icon
                source: "icon/bit_toggling_keypad_icon.png"
                property real imageRatio: sourceSize.height/sourceSize.width
                height: parent.height - 10
                width: height/imageRatio
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
            }
        }
    }
}
