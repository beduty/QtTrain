import QtQuick 2.12

Item {
    id: clock
    property color color : "lightgray"
    property date currentDate : new Date()
    property int hours :currentDate.getHours()
    property int minutes :currentDate.getMinutes()
    property int seconds :currentDate.getSeconds()
    property alias running : timer.running

    Timer{
        id : timer
        repeat: true
        interval: 500
        running: true // 타이머가 시작된다.
        onTriggered: clock.currentDate  = new Date()
        // timer가 interval(500)마다 콜백된다.(onTriggered)
        // clock.currentDate가 갱신되면, 이와 같이 묶여있는,
        // property int hours, minutes, seconds 도 갱신된다.
    }

    Rectangle{
        id : plate
        anchors.centerIn: parent // 부른 쪽(main)의 화면크기의 센터가 된다.
        width: Math.min(clock.width, clock.height)
        height: width
        radius: width/2   // 시계의 배경 형태를 만든다.
        color: clock.color
        border.color: Qt.darker(color)
        border.width: 2

        // 열두번 반복한다!!
        Repeater{
            model: 12
            // Repeater로 반복되어 생성되는 아이템으로 Delegate이다.
            // 기본적으로 색상속성이 없다. 투명이다.
            //Rectangle{
            Item{
                id : hourContainer
                property int hour :index  // index가 0~11로 바뀌면서 반복된다.

                // 시계를 12섹션으로 나누는 마크를 그린다.
                // Item으로는 공간을 만들고, 그 위에 Rectangle을 그린다.
                // Item공간은 시계의 절반 크기의 높이를 가지고, x를 시계 중간에 위치시킨다.
                // 30도씩 공간을 돌리면 그위의 Rectangle도 같이 돌아간다!
                x : plate.width/2
                y : 0
                height:  plate.height/2
                width: 2
                rotation: index * 30


                // Repeater로 생성하는 아이템에는 이름이 없지만,
                // 임시로 생성된 아이템의 속성에 접근하고자 할때 Item을 사용한다.
                transformOrigin: Item.Bottom // 아이템공간의 하단이 회전 중심점이 된다.

                // Item위에 색상 Retangle을 그린다. 시계의 섹션 마크가 그려진다.
                Rectangle{
                    width: 2
                    height: (hour %3 ==0) ? plate.height*0.1 : plate.height * 0.05
                    color: plate.border.color
                    antialiasing: true
                    anchors.horizontalCenter: hourContainer.horizontalCenter
                    anchors.top:  hourContainer.top
                    anchors.topMargin: 4
                }
            }
        }

        // 시침, 분침, 초침을 만든다!
        Needle{
            length: plate.height*0.3
            color: "blue"
            value: clock.hours // hours 가 바뀌면, 이에 맞게 Needle이 갱신된다.
            granularity: 12  // 360/12 인 30도씩 움직인다.
        }
        Needle{
            length: plate.height*0.4
            color: "darkgreen"
            value: clock.minutes
            granularity: 60  // 360/60 인 6도씩 움직인다.
        }
        Needle{
            length: plate.height*0.45
            color: "red"
            value: clock.seconds
            granularity: 60
        }
    }
}
