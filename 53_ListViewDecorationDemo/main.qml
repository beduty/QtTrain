import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window{
    visible : true
    width : 640
    height : 480
    title : qsTr("ListView-Decoration-Demo")
    ListView{
        id : mListViewId
        anchors.fill : parent
        model : ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"]
        delegate : delegateId
        highlight: Rectangle{
            width: parent.width
            color: "blue"
            opacity: 0.1
            radius: 14
            border.color: "yellowgreen"
            z : 3 // 이거를 안해주면 아래로 깔린다. 위로 올려주기 위해서 z값 설정한다.
        }
        header : Rectangle{
            id : headerRectId
            width : parent.width
            height : 50
            color: "yellowgreen"
            border {color : "#9EDDF2"; width :2}
            Text{
                anchors.centerIn : parent
                text : "English"
                font.pointSize : 20
            }
        }
//        footer : Rectangle{
//            width : parent.width
//            height : 50
//            color :  "dodgerblue"
//        }
        footer : Button{
            text: "Footer Button"
            width : parent.width
            height : 50
            onClicked: {footerDlgId.open()}
            Dialog{
               title : "Test Dlg"
               x : (parent.width - width)/2
               y : (parent.height - height)/2
               id : footerDlgId
               parent: Overlay.overlay
               modal: true
               Label {
                   text: "This is Footer Button"
               }
            }
        }
    }
    Component{
        id : delegateId
        Rectangle {
            width : parent.width
            height : 50
            color : "beige"
            border.color : "yellowgreen"
            radius : 10
            Text {
                anchors.centerIn : parent
                font.pointSize : 20
                text : modelData // ListView의 model에 직접 접근
            }
            MouseArea{
                anchors.fill : parent
                onClicked : {
                    console.log("Clicked on : " + modelData)
                    mListViewId.currentIndex = index
                }
            }
        }
    }
}



//import QtQuick 2.12
//import QtQuick.Window 2.12
//import QtQuick.Controls 2.12

//Window{
//    visible : true
//    width : 640
//    height : 480
//    title : qsTr("ListView-Decoration-Demo")
//    ListView{
//        id : mListViewId
//        anchors.fill : parent
//        model : ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"]
//        delegate : delegateId
//        highlight: Rectangle{
//            width: parent.width
//            color: "blue"
//            opacity: 0.1
//            radius: 14
//            border.color: "yellowgreen"
//            z : 3 // 이거를 안해주면 아래로 깔린다. 위로 올려주기 위해서 z값 설정한다.
//        }
//        header: Rectangle{
//            id : headerRectId
//            width: parent.width
//            height: 50
//            color: "yellowgreen"
//            border{color:"#9EDDF2"; width :2}
//            Text {
//                anchors.centerIn: parent
//                text : "English"
//                font.pointSize: 20
//            }
//        }
//        footer: Rectangle{
//            width: parent.width
//            height: 50
//            color: "dodgerblue"
//        }
//    }
//    Component{
//        id : delegateId
//        Rectangle {
//            width : parent.width
//            height : 50
//            color : "beige"
//            border.color : "yellowgreen"
//            radius : 10
//            Text {
//                anchors.centerIn : parent
//                font.pointSize : 20
//                text : modelData // ListView의 model에 직접 접근
//            }
//            MouseArea{
//                anchors.fill : parent
//                onClicked : {
//                    console.log("Clicked on : " + modelData)
//                    mListViewId.currentIndex = index
//                }
//            }
//        }
//    }
//}


////import QtQuick 2.12
////import QtQuick.Window 2.12
////import QtQuick.Controls 2.12

////Window {
////    visible: true
////    width: 640
////    height: 480
////    title: qsTr("ListView-Decoration-Demo")
////    Column{
////        Button{
////            onClicked: {}
////        }
////    }

////    ListView{
////        id : mListView
////        anchors.fill: parent
////        model : ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"]
////        delegate: Component{
////            id :delegateId
////            Rectangle{
////                //id : rectangleId
////                width: parent.width
////                height: 50
////                color: "beige"
////                border.color: "yellowgreen"
////                radius: 10
////                Text {
////                    id : textId
////                    anchors.centerIn: parent
////                    font.pointSize: 20
////                    text: modelData // default로 정의된 model을 이렇게 데이터 지정한다.
////                }
////                MouseArea{
////                    anchors.fill: parent
////                    onClicked: {
////                        //modelData = "Z"
////                        console.log("Clicked on : " + modelData)
////                        mListView.currentIndex = index //HighLight
////                    }
////                }
////            }
////        }
////        header: headerId
////        footer: Rectangle{
////            width: parent.width
////            height: 50
////            color: "dodgerblue"
////        }
////        highlight: Rectangle{
////            width: parent.width
////            color: "blue"
////            opacity: 0.1
////            radius: 14
////            border.color: "yellowgreen"
////            z : 3 // 이거를 안해주면 아래로 깔린다. 위로 올려주기 위해서 z값 설정한다.
////        }
////    }
////    Component{
////        id : headerId
////        Rectangle{
////            id : headerRectId
////            width: parent.width
////            height: 50
////            color: "yellowgreen"
////            border{color:"#9EDDF2"; width :2}
////            Text {
////                anchors.centerIn: parent
////                text : "English"
////                font.pointSize: 20
////            }
////        }
////    }
////}







//////
