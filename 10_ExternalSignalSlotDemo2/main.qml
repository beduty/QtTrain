import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("External Components with signals ans slots")

    Notifier{
        id : notifierId
        rectColor: "yellowgreen"
        target: receiverId
    }

    Receiver{
        id : receiverId
        rectColor: "dodgerblue"
        anchors.right: parent.right
    }
//    Component.onCompleted: {
//        // signal인 notify에 connect를 붙이면,
//        // notify호출할 때 데이터를 connect내부의 인자로 전달한다.
//        notifierId.notify.connect(receiverId.receiveInfo)
//    }
}
