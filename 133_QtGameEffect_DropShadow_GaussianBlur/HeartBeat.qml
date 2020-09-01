import QtQuick 2.12
import QtQuick.Window 2.12

Canvas {
    id : canvas
    property int lineWidth: 2
    property color color : "black"
    property color topColor : "red"
    property color bottomColor : "blue"
    implicitHeight: 300
    implicitWidth: 600

    // 속성등을 저장하는 구조체이다.
    QtObject{
        id : d
        // point 컨테이너이다.
        property var points: []
        property real arg : -Math.PI
        function func(argument) {
            var a = (2*Math.PI/10);
            var b = 4 * Math.PI / 5;
            return Math.sin(20*argument) * (
                        Math.exp(-Math.pow(argument/a,2)) +
                        Math.exp(-Math.pow((argument-b)/a,2)) +
                        Math.exp(-Math.pow((argument+b)/a,2))
                   );
        }
        onArgChanged: {
            points.push(func(arg)); // 값을 point컨테이너에 넣는다.
            points = points.slice(-canvas.width); // 최근 canvas.width개수만 추리고 나머지는 버린다.
            canvas.requestPaint(); // redraw이다.
        }
    }
    Timer{
        interval: 10
        repeat: true
        running: true
        onTriggered: {
            d.arg += Math.PI / 180; //10ms마다 d.arg가 업데이트 되고, onArgChanged가 호출된다.
            while(d.arg >= Math.PI){
                d.arg -= 2*Math.PI;
            }
        }
    }

    onPaint: {
        var ctx = canvas.getContext("2d");
        ctx.reset();
        ctx.clearRect(0,0,canvas.width, canvas.height)
        var pointsToDraw = d.points.slice(-canvas.width);
        ctx.translate(0, canvas.height/2); // 원점을 옮긴다.

        // fill
        ctx.beginPath();
        ctx.moveTo(0,0);
        var i ;
        for(i = 0; i < pointsToDraw.length; i ++){
            ctx.lineTo(i, -pointsToDraw[i] * canvas.height/2);
        }
        ctx.lineTo(i,0);

        var gradient = ctx.createLinearGradient(
                    0, -canvas.height /2, 0, canvas.height/2);
        gradient.addColorStop(0.1, canvas.topColor);
        gradient.addColorStop(0.5, Qt.rgba(1,1,1,0));
        gradient.addColorStop(0.9, canvas.bottomColor);
        ctx.fillStyle = gradient;
        ctx.fill();

//        ctx.beginPath();
//        ctx.moveTo(0, -pointsToDraw[0]*canvas.height/2);
//        for(i = 1; i< pointsToDraw.length; i ++){
//            ctx.lineTo(i, -pointsToDraw[i] * canvas.height /2);
//        }
//        ctx.lineWidth = canvas.lineWidth;
//        ctx.strokeStyle = canvas.color;
        ctx.stroke();
    }
}





















