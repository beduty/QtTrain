import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Text Area Demo")

    Column{
        spacing: 40
        width: parent.width
        Label{
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text : "TextArea is a multi-line text editor."
        }
        ScrollView{
            anchors.horizontalCenter: parent.horizontalCenter
            width: 600
            height: 150
            TextArea {
                id : textAreaId
                background: Rectangle{
                    width: parent.width
                    height: parent.height
                    color : "black"
                }
                color: "white"
                wrapMode: TextArea.Wrap
                placeholderText: "Type in your query"
                font.pointSize: 20
           }
        }
        Button{
           text : "Submit"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                console.log("The text inside the TextArea is : "
                                                + textAreaId.text)
            }
       }
    }

}
