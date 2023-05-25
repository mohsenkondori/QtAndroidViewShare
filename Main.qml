import QtQuick
import QtQuick.Window
import QtQuick.Controls

import QtAndroidViewShare

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QtAndroidViewShare")

    Label {
        id: title

        text: "QtAndroidViewShare Example"
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: imgView
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.margins: 10
        width: 150
        height: 40
        text: "View image"
        onClicked: {

            ShareUtils.viewFile(ResourceCreator.imgPath(), "View File",
                                "image/png", 1)
        }
    }

    Button {
        id: imgShare
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.margins: 10
        width: 150
        height: 40
        text: "Share image"
        onClicked: {

            ShareUtils.sendFile(ResourceCreator.imgPath(), "View File",
                                "image/png", 2)
        }
    }

    Button {
        anchors.left: parent.left
        anchors.top: imgView.bottom
        anchors.margins: 10
        width: 150
        height: 40
        text: "View PDF"
        onClicked: {

            ShareUtils.viewFile(ResourceCreator.pdfPath(), "View File",
                                "application/pdf", 3)
        }
    }

    Button {
        anchors.right: parent.right
        anchors.top: imgShare.bottom
        anchors.margins: 10
        width: 150
        height: 40
        text: "Share PDF"
        onClicked: {

            ShareUtils.sendFile(ResourceCreator.pdfPath(), "View File",
                                "application/pdf", 4)
        }
    }
}
