import QtQuick 2.12

Item {
    width: receiverRectId.width
    height: receiverRectId.height

    // main에서 색상 변경할 수 있도록 property 열어둔다
    property alias rectColor : receiverRectId.color

    // 들어오는 시그널 받아서 처리하는 부분이 필요하다.
    function receiveInfo(count) {
        // 데이터 받아와서 text갱신하면 해당 부분이 업데이트된다.
        displayTextId.text = count
        console.log("Receiver received number : " + count)
    }

    Rectangle{
        id : receiverRectId
        width: 200
        height: 200
        color : "red"
        Text{
            id :  displayTextId
            anchors.centerIn: parent
            font.pointSize: 20
            text : "0"
        }
    }
}
