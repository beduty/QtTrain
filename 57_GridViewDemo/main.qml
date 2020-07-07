import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("GridView Demo")
    property int nNum : 9
    ColumnLayout{
        anchors.fill: parent
        RowLayout{
            spacing: 10
            Button{
                Layout.fillWidth: true
                text : "add"
                onClicked: {
                    modelId.append({"mNumger" : ++nNum, mColor :"gold"});
                }
            }
            Button{
                Layout.fillWidth: true
                text : "Edit"
                onClicked: {
                    modelId.set(0,{"mNumger" : ++nNum, mColor :"gold"});
                }
            }
            Button{
                Layout.fillWidth: true
                text : "delete "
                onClicked: {
                    modelId.remove(0)
                }
            }
        }
        GridView{
            id : mGridViewId
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: modelId
            delegate: delegateId
        }
        Button{
            Layout.fillWidth: true
            text : "clear"
            onClicked: {
                modelId.clear()
            }
        }
    }
    Component{
        id : delegateId
        Rectangle{
            property string imgName : "images/" + mNumger + ".png"
            width: 100
            height: width
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0)
            Image{
                width: 100
                height: width
                source: imgName
            }
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    messageDialog.open()
                    console.log(imgName)
                }
            }
            Dialog{
                id : messageDialog
                x : (parent.width -width)/2
                y : (parent.height -height)/2
                parent : Overlay.overlay
                modal : true
                title : "Image Info"
                Label {
                    text : imgName
                }
            }
        }
    }
    ListModel{
        id : modelId
        ListElement{mNumger:1; mColor : "red"}
        ListElement{mNumger:2; mColor : "green"}
        ListElement{mNumger:3; mColor : "beige"}
        ListElement{mNumger:4; mColor : "yellowgreen"}
        ListElement{mNumger:5; mColor : "dodgerblue"}
        ListElement{mNumger:6; mColor : "lightyellow"}
        ListElement{mNumger:7; mColor : "pink"}
        ListElement{mNumger:8; mColor : "magenta"}
        ListElement{mNumger:9; mColor : "silver"}
    }
}
