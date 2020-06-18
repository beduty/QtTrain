import QtQuick 2.12

Item {
    width: notifierRectId.width
    height: notifierRectId.height

    // main에서 색상 변경할 수 있도록 property 열어둔다
    property alias rectColor : notifierRectId.color

    // 시그널 정의한다.
    signal notify(string count)

    // 외부 모듈을 등록해야 하므로 property로 만든다.
    property Receiver target : null

    // 시그널 과 슬롯(타겟)을 연결한다.
    onTargetChanged: {
        notify.connect(target.receiveInfo)
    }

    // 상태 관리 멤버 이다.
    property int count : 0

    Rectangle{
        id : notifierRectId
        width: 200
        height: 200
        color : "red"

        Text{
            id : displayTextId
            anchors.centerIn: parent
            font.pointSize: 20
            text : count
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                count ++
                notify(count)
            }
        }
    }
}


