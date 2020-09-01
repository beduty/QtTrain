import QtQuick 2.0

Item {
    id : player
    y : parent.height
    focus: true

    // 코끼리가 가지는 속성은 다음과 같다.
    // 이동중(walking), 왼쪽방향(facinLeft), 점프(jumping) 여부
    property bool walking: flags.rightPressed || flags.leftPressed
    property bool facinLeft : false
    readonly property bool jumping: jumpAnim.running

    // 시스템 속성도 캐싱한다.( 이동속도, Key값 눌렸는지 여부(Right, Left, Up))
    QtObject{
        // QtObject : QML의 속성만 가지는 비시각적 요소이다.( 구조체 느낌)
        id : flags
        readonly property int speed : 100
        property  bool rightPressed : false
        property  bool leftPressed : false
        property  bool upPressed : false
        onUpPressedChanged: {
            if(upPressed && !jumping) {jumpAnim.start()}
        }
        onRightPressedChanged: {
             recalculateDuration()
            if(rightPressed){ console.log("right press"); facinLeft = false;}
        }
        onLeftPressedChanged:{
            recalculateDuration()
           if(leftPressed && !rightPressed){console.log("left press"); facinLeft = true;}
        }
    }

    // 키보드 눌리면 시스템 속성값을 업데이트한다.
    Keys.onRightPressed: {
        if(event.isAutoRepeat) // 꾹 눌려있는 경우를 의미(isAutoRepeat)
            return;
        flags.rightPressed = true // 속성값 바뀌면, NOTIFY()가 호출된다.(onRightPressedChanged)
    }
    Keys.onLeftPressed: {
        if(event.isAutoRepeat)
            return;
        flags.leftPressed = true
    }
    Keys.onUpPressed: {
        if(event.isAutoRepeat)
            return;
        flags.upPressed = true
    }
    Keys.onReleased: {
        if(event.isAutoRepeat){return}
        if(event.key === Qt.Key_Right) { console.log("Right Key Release"); flags.rightPressed = false}
        if(event.key === Qt.Key_Left) { console.log("Left Key Release"); flags.leftPressed = false}
        if(event.key === Qt.Key_Up) { console.log("Up Key Release"); flags.upPressed = false}
    }

    // 코끼리를 움직일 때 계산된 픽셀수만큼 이동하는 것이 아닌,
    // 애니메이션을 만들고, 총실행 시간을 정의한 뒤, QML에서 알아서 개체 업데이트를 처리하도록 한다.
    // Key-State에 연동시켜 애니메이션을 동작시킨다.
    // 총 실행시간(duration)은 코끼리의 X위치에 따라서 다르게 한다. (--> 속도를 맞춰줘야 하기 때문!)
    function recalculateDuration() {
        // (xAnimRight.to - x)가 아닌 x로 고정된 경우, 코끼리 위치에 따라서 이동속도가 휙휙 바뀐다.
        xAnimRight.duration = (xAnimRight.to - x)* 1000 / flags.speed
        xAnimLeft.duration = (x - xAnimLeft.to)* 1000/flags.speed
    }
    NumberAnimation on x {
        // 정의해둔 애니메이션은 running 상태에 따라서 알아서 동작된다.
        // facinLeft가 아니고,walking true 즉, 오른쪽 키 눌리면 동작한다.
        id : xAnimRight
        running: walking && !facinLeft//flags.rightPressed
        to : parent.width
    }
    NumberAnimation on x {
        id : xAnimLeft
        running: walking && facinLeft ;//flags.leftPressed && !flags.rightPressed
        to : 0
    }

    // [Sprite]
    //   - 캐릭터 움직임 표현을 위해서 이미지의 교체가 반복되어야 한다.
    //   - NumberAnimation 을 사용하여 walking 컨디션에 따라서 running을 결정하고,
    //     반복적으로 이미지를 Loading하는 것도 가능하지만, 더 좋은 방법이 있다.(walking_1.png ~ walking_7.png)
    // -> Sprite는 작은 이미지세트를 하나의 큰 이미지로 결합한 이미지 시트를 의미한다.
    //   - 단일 이미지를 로드하고, 애니메이션을 적용하여 작은이미지간 전환을 처리할 수 있다!
    //   - 스프라이트에서 시작 프레임을 지정할 수 있다.(맨왼쪽 상단이 시작위치가 아니다!)
    //       -> 첫번째 프레임은 frameX 와 frameY로 지정한 위치에서 시작하고,
    //       -> frameWidth와 frameHeight로 프레임 크기를 정한다.
    //       -> frameCount는 시작프레임에서 몇개까지를 연속적으로 이미지 업데이트 할지 지정한다.
    //       -> frameX + frameWidth * count(1~7) 의 값이 이미지소스 의  Width보다 크다면??
    //             - QML은 알아서 다음행의 이미지를 가져온다!! (Good~!)
    //   - 스프라이트의 프레임간 전환은 알아서 작동하지만, 다음 속성은 직접 지정해줘야한다. (둘 중 하나만)
    //       -> 애니메이션 속도 결정 1 : frameRate (초당 순환할 프레임 수)
    //       -> 애니메이션 속도 결정 2 : frameDuration (프레임을 표시할 기간.)


    SpriteSequence{
        // 다양한 동작(Sprite)을 하나의 묶음으로 넣을 수 있다!!!
        // Sprite간 전환을 쉽게수행할 수 있다.(전환이루어질때는 동작중인 Sprite가 끝나고 다른 Sprite로 전환된다.)
        id : sprite
        width: 80
        height: jumping ? 70 : 52
        interpolate: true // 보간을 사용하면, QML에서 프레임간 부드러운 전환을 계산한다.
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        running: true
        Sprite{
            name : "still"
            source: "images/sprite.png"
            frameCount:  6
            frameWidth: 80; frameHeight: 52
            frameDuration: 100
            // 동작중인 Sprite가 끝나면, 그다음 동작할 Sprite를 지정한다. (확률값이다.)
            // 확률값이 1,0,0이므로 still Sprite 이후에는 still이 동작한다.!
            to : {"still" : 1, "walking" : 0, "jumping" : 0}
        }
        Sprite{
            name: "walking"
            source: "images/sprite.png"
            frameX: 560; frameY: 0
            frameCount: 7
            frameWidth: 80;frameHeight: 52
            frameRate: 20
            to : {"still" : 0, "walking" : 1, "jumping" : 0}
        }
        Sprite{
            name : "jumping"
            source: "images/sprite.png"
            frameX:480; frameY: 52
            frameCount: 11
            frameWidth: 80; frameHeight: 70
            frameDuration: 50
            to : { "still" : 0, "walking": 0, "jumping" : 1}
        }
        transform:  Scale{
            origin.x : sprite.width/2
            xScale: player.facinLeft? -1 : 1
        }
    }
    onWalkingChanged: {
        // SpriteSequence에서는 동작중인 Sprite가 끝나면, to:로 지정한 goalSprite로 자동 전환되는데,
        // .jumpTo("walking")을 쓰면, 동작중이던 Sprite가 뭐던 간에 바로 "walking"으로 Sprite가 변경된다.
        // "walking"동작이 끝나면??? to:로 지정한 goalSprite로 순환된다.
        if(jumping) return
        if(walking) sprite.jumpTo("walking")
        else sprite.jumpTo("still");
    }

    SequentialAnimation on y {
        id : jumpAnim
        running: true
        loops: Animation.Infinite
        ScriptAction{script : sprite.jumpTo("jumping")} // jumping 스프라이트가 재생된다.
        // 코끼리를 위로 띄운다.
        NumberAnimation{
            to : player.parent.height-50; easing.type: Easing.OutQuad; duration: 275
        }
         // 코끼리를 아래로 끌어내린다.
        NumberAnimation{
            to : player.parent.height; easing.type: Easing.OutQuad; duration: 275
        }
        // 스프라이트 Status를 결정한다.
        // Up 키가 안눌려 있는 경우에는 jumpAnim을 계속 반복한다.
        ScriptAction{
            script: if(!flags.upPressed){
                        sprite.jumpTo(player.walking? "walking" : "still")
                        jumpAnim.stop()
                    }
        }
    }
}



////    Image {
////        id : elephantImage
////        property int currentFrame : 1
////        property int frameCount : 7
////        source: "images/walking_"+currentFrame + ".png"
////        mirror: player.facinLeft // 이미지가 반전된다!

////        anchors.bottom: parent.bottom
////        anchors.horizontalCenter: parent.horizontalCenter
////        NumberAnimation on currentFrame {
////            from : 1
////            to : elephantImage.frameCount
////            loops:Animation.Infinite
////            duration: elephantImage.frameCount * 40
////            running: player.walking
////        }
////    }
//    AnimatedSprite{
//        id : sprite
//        source: "images/sprite.png"
//        frameX: 560
//        frameY: 0
//        frameWidth: 80
//        frameHeight: 52
//        frameCount: 7
//        frameRate: 14
//        interpolate: true
//        width: frameWidth
//        height: frameHeight
//        running: player.walking
//        anchors.bottom: parent.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//        transform: Scale{
//            origin.x : sprite.width/2
//            xScale: player.facinLeft ? -1 : 1
//        }
//    }
//    // X가 변화하면 즉시변경되지 않고, Animation으로 실행된다.
//    Behavior on x {
//        NumberAnimation{
//            duration: 500
//        }
//    }

//    SequentialAnimation on y {
//        id : jumpAnim
//        running: flags.upPressed
//        loops:Animation.Infinite
//        alwaysRunToEnd: true
//        NumberAnimation{
//            to : player.parent.height - 80
//            easing.type: Easing.OutQuad
//            duration: 300
//        }
//        NumberAnimation{
//            to : player.parent.height
//            easing.type: Easing.InQuad
//            duration: 300
//        }
//    }
