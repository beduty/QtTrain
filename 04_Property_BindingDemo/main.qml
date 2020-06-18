import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")    
    Rectangle {
        id : rectId
        width: 50
        height: width * 2
        color: "blue"
        focus: true
        Keys.onSpacePressed: {
            height = Qt.binding(function(){return (width / 2)})
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                rectId.width += 20
            }
        }
    }

//    Rectangle {
//        width: 100
//        height: width * 2
//        color: "blue"
//        focus: true
//        Keys.onSpacePressed: {
//            height = Qt.binding(function() { return width * 3 })
//        }
//    }


//    Column{
//        id : column
//        width  : 200
//        height: 200
//        Rectangle{
//            id: topRect
//            height: (parent.height/3)+10
//            TextInput{
//                id : myTextInput
//                text: "Hello QML"
//            }
//        }
//    }
//    Rectangle{
//        y : 50
//        id : bottomRect
//        width: height*2
//        height: 50
//        color: myTextInput.text.length <= 10? "red" : "blue"
//    }




//    Rectangle{
//        id : redRectId
//        width: 50
//        height: width*1.5
//        color: "red"
//    }

//    Rectangle{
//        id : blueRectId
//        color: "blue"
//        width: 100
//        height: 100
//        anchors.bottom: parent.bottom

//        MouseArea{
//            anchors.fill: parent
//            onClicked: {
//                redRectId.width += 10
//            }
//        }
//    }

//    Rectangle{
//        id: greenRectId
//        color: "green"
//        width: 100
//        height: 100
//        anchors.bottom: parent.bottom
//        anchors.left: blueRectId.right
//        MouseArea{
//            anchors.fill: parent
//            onClicked: {
//                redRectId.height -= 10 //이렇게 하니까 파란색 버튼을 눌렀을 때 Height가 변경되지 않았다.
////                redRectId.height = Qt.binding(function(){
////                    return redRectId.width *2.0
////                })
//            }
//        }
//    }
}










