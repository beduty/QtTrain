import QtQuick 2.12

Item {
    width: receiverRectId.width
    height: receiverRectId.height
    property alias rectColor : receiverRectId.color
    function receiveInfo(count) {
        // 구독하는 개념이다.
        // signal.connect(receiveInfo)로 연결되어 있어서,
        // signal에서 보내면 receiveInfo에서 데이터 받아 처리한다.
        receiverdisplayTextId.text = count
        console.log("Receiver received number : " + count)
    }

    Rectangle{
        id : receiverRectId
        width: 200
        height: 200
        color : "red"
        Text{
            id :  receiverdisplayTextId
            anchors.centerIn: parent
            font.pointSize: 20
            text : "0"
        }
    }
}
