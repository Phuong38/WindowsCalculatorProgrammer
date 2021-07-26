import QtQuick 2.0

Rectangle {
    width: parent.width
    property int subResultHeight: 30
    property int hexResultValue : 0
    property int decResultValue : 0
    property int octResultValue : 0
    property int binResultValue : 1011
    property string mainResultValue: "0"
    id: resultScreen
    color:"#525353"

    Rectangle{
        id: mainResult
        width: parent.width
        height: 40
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: hexResult.top
        anchors.bottomMargin: 40
        Text{
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
            text: "" + mainResultValue
            color: "white"
        }
    }

    Rectangle{
        id: hexResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: decResult.top
        Text{
            font.pixelSize: 20
            text: "  HEX    " + hexResultValue
            color: "white"
        }
    }

    Rectangle{
        id: decResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: octResult.top
        Text{
            font.pixelSize: 20
            text: "  DEC    " + decResultValue
            color: "white"
        }
    }

    Rectangle{
        id: octResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: binResult.top
        Text{
            font.pixelSize: 20
            text: "  OCT    " + octResultValue
            color: "white"
        }
    }

    Rectangle{
        id: binResult
        width: parent.width
        height: subResultHeight
        color: parent.color
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Text{
            font.pixelSize: 20
            text: "  BIN    " + binResultValue
            color: "white"
        }
    }

}
