import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: mainWindow
    visible: true
    visibility: "Maximized"
    title: qsTr("Explorer")
    Rectangle{
        id: clientmMenu
        width: parent.width
        height: parent.height / 12
        color: "steelblue"
        ClientButton{
            id: homeButton
            anchors.left: parent.left
            Text{
                anchors.centerIn: parent
                color: "white"
                text: "Home"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: client.home()
            }
        }
        ClientButton{
            id: backButton
            width: clientmMenu.width / 15
            anchors.left: homeButton.right
            Text{
                anchors.centerIn: parent
                color: "white"
                text: "Back"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: client.back()
            }
        }
        Rectangle {
            id: currentDir
            width: clientmMenu.width / 8
            height: clientmMenu.height
            anchors.left: backButton.right;
            Text{
                anchors.centerIn: parent
                color: "white"
                text: client.currentDir
            }
            color: clientmMenu.color
            border.color: "gainsboro"
            radius: 4
            border.width: 5
        }
    }
    Rectangle{
        id: filesView
        border.color: "black"
        clip: true
        anchors.top: clientmMenu.bottom
        width: parent.width
        height: 11 * parent.height / 12
        ListView{
            anchors.fill: parent
            id: viewTimeStamps
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
            model: client.files
            delegate: Rectangle {
                id: filesDelegate
                width: filesView.width
                height:  filesView.height / 8
                border.color: "black"
                radius: 5
                function getImage(fl){
                    if(fl.fileType == "DIRECTORY"){
                        return fl.isReadable ? "qrc:/icons/directory.png" : "qrc:/icons/locked_directory.png"
                    } else {
                        return fl.isReadable ? "qrc:/icons/fs_file.png" : "qrc:/icons/locked_file.png"
                    }
                }
                Image {
                    id: imageFile
                    anchors.left: filesDelegate.left
                    width: filesDelegate.width /15
                    height: filesDelegate.height;
                    source: getImage(model.modelData)
                }
                Text {
                    anchors.left: imageFile.right
                    id: filesName
                    text: model.modelData.name
                    anchors.verticalCenter: filesDelegate.verticalCenter
                    anchors.leftMargin: 10
                }
                MouseArea{
                    anchors.fill: filesDelegate
                    onClicked: client.next(model.modelData.name)
                }
            }

        }
    }
}


