import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480

    title: qsTr("Hello World")
    property real defaultSize: 200

    Rectangle{
        id : circle
        width: 60
        height: width
        radius: width/2
        color: "red"
        onXChanged: {
            if(circle.x>parent.width || circle.x < 0)
                circle.x = 30
        }
        onYChanged: {
            if(circle.y>parent.height|| circle.y < 0)
                circle.y = 30
        }
        MouseArea{
            anchors.fill: parent
            drag.target: circle
        }
    }

    Rectangle{
        id : circle2
        width: 60
        x: 150
        height: width
        radius: width/2
        color: "blue"
        onXChanged: {
            if(circle2.x>parent.width || circle2.x < 0)
                circle2.x = 30
        }
        onYChanged: {
            if(circle2.y>parent.height|| circle2.y < 0)
                circle2.y = 30
        }
        MouseArea{
            anchors.fill: parent
            drag.target: circle2
        }
    }
    Image {
        id: photo
        y : 100
        width: 200
        height:  150
        source: "qrc:/wilanow.jpg"
        MouseArea{
            anchors.fill: parent
            drag.target: photo
            onPressed: {
                photo.z =5;
            }
        }
    }

    // Rectangle 위에 이미지를 붙인다. 이미지보다 5% 크게 Rectangle의 크기를
    // 설정하여 색상 프레임을 만든다. Rectangle의 색상을 바꾸어 프레임 색상이 변경된다.

    Rectangle{
        id: photoFrame
        width: image.width *(1+ 0.05 * image.height/image.width)
        height: image.height * 1.05
        scale: defaultSize / Math.max(image.sourceSize.width, image.sourceSize.height)
        color: "black"
        smooth: true
        antialiasing: true
        Component.onCompleted: { // 만들어지고 바로 호출된다.
            x = Math.random()* root.width-width/2
            y = Math.random()* root.height-height/2
            rotation = Math.random() * 13 - 6
        }
        Image {
            id: image
            antialiasing: true
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: "qrc:/wilanow.jpg"
        }
        MouseArea{
            id: dragArea
            drag.target: photoFrame // 드래그 할 수 있다.
            anchors.fill: parent
            hoverEnabled: true // 마우스가 Area로 들어오거나 나가는 이벤트 알아차린다.
            onContainsMouseChanged: {
                if(containsMouse)
                    parent.color = "red" // 마우스가 Area로 들어오면 프레임색상을 빨간색으로.
                else
                    parent.color = "black"
            }
            onPressed: {
                // photo를 아래로 내려서 클릭했을 때 photoFrame이 위로 올라오게 한다.
                photo.z = 0;
            }
            onWheel: {
                if(wheel.modifiers & Qt.ControlModifier){
                    // 컨트롤 키 + 휠을 하면 rotation을 증가시킨다.
                    photoFrame.rotation += wheel.angleDelta.y / 120 *5;
                    if(Math.abs(photoFrame.rotation)<4)
                        photoFrame.rotation = 0;
                }else{
                    // 휠을 하면 스케일을 변경한다.
                    var scaleBefore = photoFrame.scale;
                    photoFrame.scale += photoFrame.scale * wheel.angleDelta.y/120/10;
                }
            }
        }

        // 키보드 입력 받으려면 focus : true 가 되어야 한다.
        focus: true
        Keys.onPressed: {
            if(event.key === Qt.Key_B){
                photoFrame.color = "blue" // B키를 누르면 파란색으로 프레임 색상 바꾼다.
            }else if(event.key === Qt.Key_G){
                photoFrame.color = "green"
            }else if(event.key === Qt.Key_P){
                photoFrame.color = "purple"
            }else if(event.key === Qt.Key_Y){
                photoFrame.color = "yellow"
            }else if(event.key === Qt.Key_Down){
                photoFrame.y += 5;
            }else if(event.key === Qt.Key_Up){
                photoFrame.y -= 5;
            }else if(event.key === Qt.Key_Right){
                photoFrame.x += 5;
            }else if(event.key === Qt.Key_Left){
                photoFrame.x -= 5;
            }
        }
    }
}






