import QtQuick 2.9
import QtQuick.Window 2.12

Window {
    id: view
    visible: true
    width: 600
    height: 380
    title: qsTr("Hello World")

    // Scene을 X Offset하면 하위 객체들도 한번에 움직인다.
    // 모든 것이 동일하게 움직이지 않고, 머~~얼리 있는 배경은 느리게,
    // 가까이에 있는 배경은 빠르게 움직이도록 상대 속도를 적용할 수가 있다.
    // 이를 담당하는게 Layer이다. Scene의 Offset 받아다가
    // 하위의 Layer도 같이 움직이되, 비율을 주면 얼마나 느리거나 빠르게 움직일지 지정할 수 있다.
    // Layer안에 속하지 않으면 Scene과 동일하게 움직인다.
    ParallaxScene {
        id: scene
        width: 1500
        height: 380
        anchors.bottom: parent.bottom
        currentPos: player.x
        //x : currentPos //player.x * (scene.width - view.width)/scene.width
        onXChanged: {
            console.log("x : " + scene.x)
        }
        ParallaxLayer {
            factor: 7.5
            width: sky.width; height: sky.height
            anchors.bottom: parent.bottom
            Image {
                id: sky
                property int dayLength: 60000 // 1 minute
                source: "images/sky.png"
                Item {
                    id: sun
                    x: 140
                    y: sky.height - 170
                    Rectangle {
                        id: sunVisual
                        width: 40
                        height: width
                        radius: width / 2
                        color: "yellow"
                        anchors.centerIn: parent
                        // sun 둘레에 태양 둘레를 그린다.
                        Item {
                            id: sunRays
                            property int count: 10
                            width: sunVisual.width
                            height: width
                            anchors.centerIn: parent
                            z : -1
                            Repeater{
                                model: sunRays.count
                                Rectangle{
                                    color: "red"
                                    rotation: index * 360 / sunRays.count
                                    anchors.fill: parent
                                }
                            }
                        }
                        //sun의 색상이 red->yellow->(Pause)->red 로 변한다.
                        SequentialAnimation on color {
                            ColorAnimation {
                                from: "red"
                                to: "yellow"
                                duration: 0.2 * sky.dayLength / 2
                            }
                            PauseAnimation { duration: 2 * 0.8 * sky.dayLength / 2 }
                            ColorAnimation {
                                to: "red"
                                duration: 0.2 * sky.dayLength / 2
                            }
                            running: true
                        }
                    }
                    //sun이 점점 작아졌다가 점점 커진다.
                    SequentialAnimation on scale {
                        NumberAnimation {
                            from: 1.6; to: 0.8
                            duration: sky.dayLength / 2
                            easing.type: Easing.OutCubic
                        }
                        NumberAnimation {
                            from: 0.8; to: 1.6
                            duration: sky.dayLength / 2
                            easing.type: Easing.InCubic
                        }
                    }
                }
            }

            NumberAnimation {
                target: sun
                property: "x"
                from: 0
                to: sky.width
                duration: sky.dayLength
                running: true
            }
            NumberAnimation{
                target: sun
                property: "rotation"
                from : 0
                to : 360
                duration: sky.dayLength
                running: true
            }
            SequentialAnimation {
                running: true
                NumberAnimation {
                    target: sun
                    property: "y"
                    from: sky.height + sunVisual.height
                    to: sky.height - 270
                    duration: sky.dayLength / 2
                    easing.type: Easing.OutCubic
                }
                NumberAnimation {
                    target: sun
                    property: "y"
                    to: sky.height + sunVisual.height
                    duration: sky.dayLength / 2
                    easing.type: Easing.InCubic
                }
            }
        }
        ParallaxLayer {
            factor: 2.5
            width: trees.width; height: trees.height
            anchors.bottom: parent.bottom
            Image { id: trees; source: "images/trees.png" }
        }
        ParallaxLayer {
            factor: 0
            width: grass.width; height: grass.height
            anchors.bottom: parent.bottom
            Image { id: grass; source: "images/grass.png" }
        }
        Player {
            id: player
            x: 40
        }
        Component {
            id: coinGenerator
            Coin {}
        }
        Timer {
            id: coinTimer
            interval: 1000
            repeat: true
            running: true

            onTriggered: {
                var cx = Math.floor(Math.random() * scene.width)
                var cy = Math.floor(Math.random() * scene.height / 3) + scene.height / 2
                coinGenerator.createObject(scene, { x: cx, y: cy});
            }
        }
    }
}












