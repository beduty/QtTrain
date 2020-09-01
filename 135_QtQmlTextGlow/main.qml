import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Badge{
        id : importantBadge
        anchors.centerIn: parent
    }

    // 소스 뒤에 배치되어 오브젝트 주변에 후광을 만든다.!
    // radius로 후광의 크기를 제어한다.
    // samples로 품질을 제어한다.클수록 렌더링 속도가 느리다.
    Glow{
        source: importantBadge
        anchors.fill: source
        samples: 64
        color: "red"
        SequentialAnimation on radius {
            loops: Animation.Infinite
            running: true

            NumberAnimation{from : 0; to :30; duration: 500}
            PauseAnimation {duration: 100}
            NumberAnimation{from : 30; to :0; duration: 500}
            PauseAnimation {duration: 100}
        }
    }
}
