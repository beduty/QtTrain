import QtQuick 2.0

// ParallaxScene은 움직이는 평면이다.
// 캐릭터가 이동할 때 화면을 스크롤(오프셋)하는 값을 계산한다.
//      Window {
//          width: 600;
//          ParallaxScene {
//              width: 1500;
//              currentPos: player.x
// 으로 설정되어, 코끼리가 움직일 수 있는 총거리(width : 1500)을 지정한다.
//
Item {
    id : root
    property int currentPos
    x : -currentPos * (root.width - root.parent.width)/root.width
}
