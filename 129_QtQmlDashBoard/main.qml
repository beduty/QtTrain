import QtQuick 2.12
import QtQuick.Window 2.12
import CarInfo 1.0

Window {
    visible: true
    width: backgoundImage.width
    height: backgoundImage.height
    Image{
        id: backgoundImage
        source: "qrc:/dashboard.png"

        CarInfo {
            id: carData
            //visible: true
            engine.gear: 5
            speed: 200
        }

        // 왼쪽 계기판.
        Item{
            id : leftContainer
            property real value: carData.engine.rpm / 1000
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -550
            width: 400; height: width
            function calculatePosition(angle, radius){
                var a = angle * Math.PI / 180;
                var px = width/2 + radius * Math.cos(a);
                var py = width/2 + radius * Math.sin(a);
                return Qt.point(px,py);
            }
            // 숫자 기록한다.
            // scale(1,-1) 좌표계상에서 120도에 0을 기록하고, 숫자간 35간의 차이를 둔다.
            Repeater{
                model:7
                Item{
                    property point pt: leftContainer.calculatePosition(120+index*35, leftContainer.width * 0.4)
                    x: pt.x
                    y: pt.y
                    Label{
                        anchors.centerIn: parent
                        text : index
                    }
                }
            }

            // 계기침을 위치시킨다.
            // Needle의 0도는 12시를 가리키고 있는데, 이는 scale(1,-1) 좌표계상에서 -90도 이다.
            // scale(1,-1) 좌표계상에서 120도에 0을 기록하였으므로, 210(90 + 120)도 회전시킨다.
            Needle{
                color: "white"
                rotation: 210 + leftContainer.value * 35
                length: leftContainer.width*0.35
                anchors.centerIn: parent
                antialiasing: true
            }

            // 계기판 중앙에 기어 정보를 기록한다.
            Item{
                id:gearContainer
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 10 // 센터에서 오른쪽 방향으로 10px 이동
                anchors.verticalCenterOffset: -10  // 센터에서 윗방향으로 10px 이동
                Text{
                    id : gear
                    property int value: carData.engine.gear
                    property var gears: [
                        // <sup>를 쓰면, 작아지면서 앞 숫자 상단으로 올라간다.(제곱 처럼)
                        "R", "N", "1<sup>st</sup>","2<sup>nd</sup>",
                        "3<sup>rd</sup>","4<sup>rd</sup>","5<sup>rd</sup>"
                    ]
                    textFormat: Text.RichText // Richtext를 써줘야 제곱모양이 된다.
                    text: gears[value +1]
                    anchors.left: gearContainer.left
                    anchors.bottom: gearContainer.bottom
                    color:"yellow"
                    font.pixelSize: 32
                }
            }

            // 계기판의 단위를 기록한다.
            Text{
                text: "RPM\n[x1000]"
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 40  // 센터에서 아랫방향으로 40px 이동
                font.pixelSize: 16
                color: "#aaa"
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Item {
            id: middleContainer
            anchors.centerIn: parent
            width: 700; height: width

            // 원에 번호 배치하기 위해서 각도 계산한다.
            function calculatePosition(angle, radius){
                if(radius === undefined){
                    radius = 0.8 * width / 2;
                }
                var a = angle * Math.PI / 180;
                var px = width/2 + radius*Math.cos(a);
                var py = width/2 + radius*Math.sin(a);
                return Qt.point(px,py)
            }

            // 번호를 배치한다. (Repeater로 한번에 한다.)
            Repeater{
                model:12
                // delegate이다.
                Item{
                    // 0이 120도에 배치되고, 다음 항목은 24도 더 멀리 배치된다.
                    // 왜 120도 ? 좌상단이 0이고, 아래로 갈수록 y값이 커진다.
                    // index 0~11 로 가는 동안 기대했던, 반시계방향으로 기록되는게 아닌, 시계방향으로 기록될거다.
                    // 0우리가 좌측하단이라서 240도에 해당하는 곳에 기대되지만,
                    // scale(1,-1)이 되어있기 때문에 실제로는 120가 우리가 기대한 위치이다.
                    property point pt :
                        middleContainer.calculatePosition(120+ index * 12 * 2, 0.8 *middleContainer.width / 2)
                    x : pt.x
                    y : pt.y
                    Label{
                        anchors.centerIn: parent
                        text : index * 20
                    }
                }
            }
            Repeater{
                model: 120-4
                Item{
                    property point pt: middleContainer.calculatePosition(
                        120 + index * 1.2 * 2, middleContainer.width * 0.35)
                    x : pt.x
                    y : pt.y
                    Rectangle{
                        width: 2
                        height: index % 5 ? 5:10
                        color: "white"
                        rotation: 90 + 120 + index * 1.2 *2
                        anchors.centerIn: parent
                        antialiasing: true
                    }
                }
            }
            Text {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 40
                text: qsTr("SPEED\n[kph]")
                horizontalAlignment: Text.AlignHCenter
                color: "#aaa"
                font.pixelSize: 16
            }

            // 계기침을 배치한다.
            Needle{
                anchors.centerIn: parent
                length: parent.width * 0.35
                size: 4
                color: "yellow"
                // 0~230 까지 이루어져있고, 0~220까지 20간격으로 숫자기록되어있다.
                // 20간격은 index*12*2로 24도씩 가져간다.
                // 즉, 1 kph는 1.2도씩 가진다!
                // 210으로 시작된 이유는 Needle의 각도가 0일때 중점을 기준으로 수직, 위방향으로 세워져있다.
                // scale(1,-1)이 되어있는 좌표계에서는 수직, 윗방향이 -90도 이다.
                // 위에서 0kmh를 120도에 해당하는 위치에 기록했다. 따라서 계기침도 210도 (시계방향) 돌린다.
                rotation: 210 + (carData.speed * 1.2)
                Component.onCompleted: {
                    console.log("speed : " + carData.speed)
                }
            }

        }
        Item {
            id: rightContainer

            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 525
            width: 400
            height: 400

            // 그룹박스를 만들어준다.
            Rectangle {
                id: digitalDisplay
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                border.color: "white"
                border.width: 1
                radius: 10
                width: 350
                height: 300
                color: "transparent"

                // 그룹박스 안의 내용을 Item 하나로 묶어서 넣는다.
                Item {
                    anchors.fill: parent
                    anchors.margins: 10

                    // 날짜를 기록한다.
                    Label {
                        id: dateLabel
                        text: Qt.formatDate(new Date)
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    // 표 처럼 (1행의 1열에는 제목("Humidity"), 2열에는 내용(68.4%)
                    // 넣어야 할경우에는 Grid를 이용하면 좋다.
                    Grid {
                        id: topGrid
                        columns: 2  // 2열로 이루어져있고, 내부 객체들은 행을 추가해가며 이어 넣는다.
                        spacing: 5
                        anchors.top: dateLabel.bottom // dateLabel밑에 붙인다.
                        anchors.topMargin: 15 // 15px 여유를 둔다.
                        anchors.left: parent.left
                        anchors.right: parent.right
                        Label {
                            text: "Temperature:"
                            width: parent.width/2  // 공간 너비의 반씩 차지하도록 한다.
                        }
                        Label {
                            text: "+17°C"
                            horizontalAlignment: Text.AlignRight
                            width: parent.width / 2 - 5
                        }
                        Label {
                            text: "Humidity:"
                            width: parent.width / 2
                        }
                        Label {
                            text: "68.4%"
                            horizontalAlignment: Text.AlignRight
                            width: parent.width / 2 - 5
                        }
                    }

                    // 아래쪽에도 Distance : xxxx km를 그리드형태로 만든다.
                    Grid {
                        id: bottomGrid
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 15
                        Label {
                            text: "Distance:"
                            width: parent.width / 2
                        }
                        Label {
                            text: carData.distance+" km"
                            horizontalAlignment: Text.AlignRight
                            width: parent.width / 2 - 5
                        }
                    }
                }
            }
            // 그룹박스 아랫부분에 계기판의 일부 정보 추가해준다.
            Row {
                anchors.top: digitalDisplay.bottom
                anchors.topMargin: 10
                anchors.left: digitalDisplay.left
                anchors.right: digitalDisplay.right
                spacing: 10

                Label {
                    text: "ABS"
                    color: "#222"
                }
                Label {
                    text: "ESP"
                    color: "#da0"
                }
                Label {
                    text: "BRK"
                    color: "#222"
                }

                Label {
                    text: "CHECK"
                    color: "#222"
                }
            }
        }

    }


}
