import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
Window{
    visible : true
    width : 640
    height : 480
    title : qsTr("List Model View")
    ColumnLayout{
        anchors.fill: parent
        Row{
            spacing: 10
            Button {
                text: "add Korea"
                onClicked: {
                    mModelId.append({"country" : "Korea", "capital" : "Seoul", "mycolor" : "magenta"})
                }
            }
            Button {
                text: "delete Idx 0"
                onClicked: {
                    mModelId.remove(0)
                }
            }
            Button {
                text: "Change Idx 1"
                onClicked: {
                    mModelId.set(1, {"country" : "조선", "capital" : "한양", "mycolor" : "gold"})
                }
            }
        }

        ListView{
            id : mListViewId
            Layout.fillWidth : true
            Layout.fillHeight: true
            model : mModelId
            delegate : delegateId
        }
        Button {
            Layout.fillWidth : true
            text: "All Clear"
            onClicked: {
                mModelId.clear()
            }
        }
    }

    ListModel{
        id : mModelId
        ListElement{country : "Rwanda"; capital : "Kigali";mycolor : "red"}
        ListElement{country : "China"; capital : "Beijing";mycolor : "green" }
        ListElement{country : "Japan"; capital : "Tokyo" ;mycolor : "blue"}
        ListElement{country : "Nigeria"; capital : "Dakar" ;mycolor : "yellowgreen"}
        ListElement{country : "Ghana"; capital : "Accra" ;mycolor : "orange"}
        ListElement{country : "France"; capital : "Paris" ;mycolor : "pink"}
        ListElement{country : "India"; capital : "New Delhi" ;mycolor : "beige"}
        ListElement{country : "Uganda"; capital : "Kampala" ;mycolor : "dodgerblue"}
    }
    Component {
        id : delegateId
        Rectangle{
            width : parent.width
            height : 50
            color : mycolor
            border.color : "yellowgreen"
            radius : 10
            Text {
                id : textId
                anchors.centerIn : parent
                font.pointSize : 20
                text : country + " : " + capital
            }
            MouseArea{
                anchors.fill : parent
                onClicked : {
                    console.log("Clicked on : " + capital + " :  " + country)
                }
            }
        }
    }
}


//import QtQuick 2.12
//import QtQuick.Window 2.12
//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("List Model View")

//    ListView{
//        id : mListView
//        anchors.fill: parent
//        model : mModelId
//        //delegate :delegateId
//        delegate: Component{
//            id :delegateId
//            Rectangle{
//                id : rectangleId
//                width: parent.width
//                height: 50
//                color: "beige"
//                border.color: "yellowgreen"
//                radius: 10
//                Text {
//                    id : textId
//                    anchors.centerIn: parent
//                    font.pointSize: 20
//                    text: country + " : " + capital
//                }
//                MouseArea{
//                    anchors.fill: parent
//                    onClicked: {
//                        //capital = "testLog"
//                        console.log("Clicked on : " + capital + " : " + country)
//                    }
//                }
//            }
//        }
//    }
//    ListModel{
//        id : mModelId
//        ListElement{country : "RWanda"; capital : "Kigali" }
//        ListElement{country : "China"; capital : "Beijing" }
//        ListElement{country : "Japan"; capital : "Tokyo" }
//        ListElement{country : "Nigeria"; capital : "Dakar" }
//        ListElement{country : "Ghana"; capital : "Accra" }
//        ListElement{country : "France"; capital : "Paris" }
//        ListElement{country : "India"; capital : "New Delhi" }
//        ListElement{country : "Uganda"; capital : "Kampala" }
//    }
////    Component{
////        id :delegateId
////        Rectangle{
////            id : rectangleId
////            width: parent.width
////            height: 50
////            color: "beige"
////            border.color: "yellowgreen"
////            radius: 10
////            Text {
////                id : textId
////                anchors.centerIn: parent
////                font.pointSize: 20
////                text: country + " : " + capital
////            }
////            MouseArea{
////                anchors.fill: parent
////                onClicked: {
////                    //capital = "testLog"
////                    console.log("Clicked on : " + capital + " : " + country)
////                }
////            }
////        }
////    }
//}
