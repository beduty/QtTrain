import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Modify-Model-Dynamic")

    ListModel{
        id : mListModel
        ListElement{firstName : "John"; lastname : "Snow"}
        ListElement{firstName : "Nicholai"; lastname : "Itchenko"}
        ListElement{firstName : "Mitch"; lastname : "Mathson"}
        ListElement{firstName : "Ken"; lastname : "Kologorov"}
        ListElement{firstName : "Vince"; lastname : "LuvKyj"}
    }

    ColumnLayout{
        anchors.fill   : parent
        ListView{
            id : mListViewId
            model :mListModel
            delegate: delegateId
            Layout.fillWidth : true
            Layout.fillHeight: true
        }
        Button{
            text : "Add Item"
            Layout.fillWidth: true
            onClicked: {
                mListModel.append({"firstName" : "Daniel", "lastname" : "Gakwaya"})
            }
        }
        Button{
            text : "Clear"
            Layout.fillWidth: true
            onClicked: {
                mListModel.clear()
            }
        }
        Button{
            text : "Delete Item at index 2"
            Layout.fillWidth: true
            onClicked: {
                if(2 < mListViewId.model.count){
                    mListModel.remove(2)
                }else{
                    console.log("index is Invalid")
                }


            }
        }
        Button{
            text : "Set Item at index 2"
            Layout.fillWidth: true
            onClicked: {
                mListModel.set(2, {"firstName" : "John", "lastname" : "Doe"})
            }
        }
    }

    Component{
        id : delegateId
        Rectangle{
            id : rectangleILd
            width: parent.width
            height: 50
            color: "beige"
            border.color: "yellowgreen"
            radius: 14
            Text{
                id : textId
                anchors.centerIn : parent
                text : firstName + " " + lastname
                font.pointSize: 20
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked on : " + firstName + " " + lastname)
                }
            }
        }
    }
}








