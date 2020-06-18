import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Key Navigation Demo")

//    Row{
//        x : 100
//        anchors.centerIn: parent
//        Rectangle{
//            id : firstRectId
//            width: 100
//            height: width
//            border.color: "black"
//            color: "green"
//            focus: true
//            Keys.onDigit5Pressed: {
//                console.log("I am Rect1")
//            }
//            KeyNavigation.right: secondRectId
//            onFocusChanged: {
//                if(focus === true){
//                    color = "green"
//                }else{
//                    color = "grey"
//                }
//            }
//        }
//        Rectangle{
//            id : secondRectId
//            width: 100
//            height: width
//            border.color: "black"
//            color: "blue"
//            focus: true
//            Keys.onDigit5Pressed: {
//                console.log("I am Rect2")
//            }
//            KeyNavigation.left: firstRectId
//            onFocusChanged: {
//                if(focus === true){
//                    color = "blue"
//                }else{
//                    color = "grey"
//                }
//            }
//        }
//    }


    Grid {
          width: 100; height: 100
          columns: 2

          Rectangle {
              id: topLeft
              width: 50; height: 50
              color: focus ? "red" : "lightgray"
              focus: true

              KeyNavigation.right: topRight
              KeyNavigation.down: bottomLeft
          }

          Rectangle {
              id: topRight
              width: 50; height: 50
              color: focus ? "red" : "lightgray"

              KeyNavigation.left: topLeft
              KeyNavigation.down: bottomRight
          }

          Rectangle {
              id: bottomLeft
              width: 50; height: 50
              color: focus ? "red" : "lightgray"

              KeyNavigation.right: bottomRight
              KeyNavigation.up: topLeft
          }

          Rectangle {
              id: bottomRight
              width: 50; height: 50
              color: focus ? "red" : "lightgray"

              KeyNavigation.left: bottomLeft
              KeyNavigation.up: topRight
          }
      }
}












