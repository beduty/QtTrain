import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML Basic Elements Demo")
    Item{
        id : containerItemId
        x:50; y:50
        width: 600
        height: 300

        Rectangle{
            anchors.fill: parent
            color: "beige"
            border.color: "black"
        }

        Rectangle{
            x:0
            y:10
            width : 50
            height: 50
            color: "red"
            MouseArea{
                anchors.fill : parent
                onClicked: {

                }
            }
        }
        Rectangle{
            x:60
            y:10
            width : 50
            height: 50
            color: "green"
            MouseArea{
                anchors.fill : parent
                onClicked: {

                }
            }
        }
        Rectangle{
            x:120
            y:10
            width : 50
            height: 50
            color: "blue"
            MouseArea{
                anchors.fill : parent
                onClicked: {

                }
            }
        }
        Rectangle{
            x:180
            y:10
            width : 50
            height: 50
            color: "dodgerblue"
            MouseArea{
                anchors.fill : parent
                onClicked: {

                }
            }
        }
        Text{
            x : 100
            y : 80
            id : mTextId
            text : "정태영"
//            font.pointSize: 20
//            font.family: "맑은 고딕"
//            font.underline: true
//            font.bold: true
//            font.italic: true
            font{
                pointSize: 13
                family: "맑은 고딕"
                underline: true
                bold: true
                italic: true
            }
        }
        Image {
            x : 10
            y : 150
            width: 100
            height: 100
            source: "file:AlignR.bmp"  // 빌드 파일에 있는 이미지를 연다.
        }
        Image {
            x : 160
            y : 150
            width: 100
            height: 100
            source: "images/111.PNG" // resource로 등록한 이미지를 넣는다.
        }
        Image {
            x : 320
            y : 150
            width: 100
            height: 100
            source: "file:///C:/Users/jungt/Desktop/AIK-SKC_TestIMG/Stack.bmp" // 지정한 Full Path로 연다.
        }
        Image {
            x : 450
            y : 150
            width: 100
            height: 100
            source: "https://mir-s3-cdn-cf.behance.net/project_modules/1400_opt_1/d9837a98524075.5ee7c9920469c.png" // 웹 상의 이미지도 열 수 있다.
        }

        //
    }
}
