import QtQuick 2.0

//Rectangle {
//    id : myrect
//    // Rectangle자체의 프로터피와 동일한
//    // 프로퍼티(x,y,color등)을 선언하면 에러가 난다~
//    //property int x: myrect.x
//    //property color color: myrect.color
//    width: 10
//    height: width
//    radius: width/2
//}


Item{
    // property 로 속성을 노출할 구성요소를 선언한다.
    property int diameter: 20

    // Item에는 color, border 속성이 없으므로 만들어줄 수 있다.
    property alias color : rect.color
    property alias border: rect.border

    implicitHeight: diameter
    implicitWidth: diameter
    Rectangle{
        id : rect
        radius: diameter/2
        width: radius
        height: radius
        anchors.centerIn: parent
    }
}
