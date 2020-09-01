import QtQuick 2.12

// 시계바늘은 원의 중심점을 기준으로 회전한다.
// 시침은 한번에 30도씩 움직인다.(property granularity : 12)
// 초침과 분침은 한번에 6도씩 움직인다.(property granularity : 60)
// 시침과 분침, 초침 모두 길이가 다르다. (property length)

// 시간이 바뀔 때마다 값을 받는다. (property value)
Rectangle {
    id : root
    property int value : 0
    property int granularity : 60
    property alias length : root.height
    // --> 외부에서 length로 들어온 값이 root.heigth가 된다.

    width: 2
    radius: width/2
    antialiasing: true
    anchors.bottom: parent.verticalCenter // 호출한 쪽의 가운데에 니들의 하단을 고정한다.
    anchors.horizontalCenter: parent.horizontalCenter //호출한 쪽의 가운데에 니들의 가운데에 고정한다.
    rotation: (value ) * (360 / granularity); // 외부로부터 값이 들어오면 rotation된다.
    transformOrigin: Rectangle.Bottom // 니들의 하단을 기준점으로 회전한다.
    //transformOrigin: Item.Bottom // 니들의 하단을 기준점으로 회전한다.
}
