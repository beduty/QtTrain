import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("GridView Demo")
    ListModel{
        id : modelId
        ListElement{
            mNumger:1
            mColor : "red"
        }
        ListElement{
            mNumger:2
            mColor : "green"
        }
        ListElement{
            mNumger:3
            mColor : "beige"
        }
        ListElement{
            mNumger:4
            mColor : "yellowgreen"
        }
        ListElement{
            mNumger:5
            mColor : "dodgerblue"
        }
        ListElement{
            mNumger:6
            mColor : "lightyellow"
        }
        ListElement{
            mNumger:7
            mColor : "pink"
        }
        ListElement{
            mNumger:8
            mColor : "magenta"
        }
        ListElement{
            mNumger:9
            mColor : "silver"
        }
    }
    GridView{
        id : mGridViewId
        anchors.fill: parent
        model: modelId
        flow: GridView.TopToBottom
        delegate: Rectangle{
            width: 100
            height: width
            color: mColor
            Text{
                text: mNumger
                anchors.centerIn: parent
                font.pointSize: 10
            }
        }
    }




}
