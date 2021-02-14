import QtQuick 2.12

Rectangle{
    width: clientmMenu.width / 10
    height: clientmMenu.height
    Text{
        anchors.centerIn: parent
        color: "white"
    }
    color: clientmMenu.color
    border.color: "gainsboro"
    radius: 4
    border.width: 5
    MouseArea{
        anchors.fill: parent
        onClicked: {
        }
    }
}

