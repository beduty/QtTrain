import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Canvas{
        id : canvas
        property int lineWidth : 2
        property color color : "black"
        property color topColor : "red"
        property color bottomColor : "blue"

//        property var points : []
//        property real arg : -Math.PI
//        function func(argument){
//            var a = (2*Math.PI/10)
//            var b = (4 * Math.PI/5)
//            return Math.sin(20 * argument) * (
//                Math.exp(-Math.pow(argument / a, 2)) +
//                Math.exp(-Math.pow((argument - b) / a, 2)) +
//                Math.exp(-Math.pow((argument + b) / a, 2))
//            );
//        }
//        onArgChanged: {
//            points.push(func(arg))
//            points = points.slice(-canvas.width)
//            canvas.requestPaint();
//        }
        // Cavas의 속성으로 points와 arg를 쓰게되면, 외부에서 변경을 할 수 있게된다.
        // Timer에서 접근해야 됐기때문에, 전역 속성변수로 썼지만, 이는 여러모로 위험하다.
        // 이를 위해서 QtObject가 있다. QObject의 QML표현으로써 특정기능은 없지만,
        // 속성을 따로 정의 할 수가 있다. 이제 타이머에서는 d.points 등으로 접근해야 한다.
        // 이로써 내부에서만 쓸 수 있고, 외부에서는 접근못하게 만들 수 있다.
        // arg가  QtObject의 속성이므로 onArgChanged도 QtObject내부에 정의되어야 한다.
        QtObject{
            id : d
            property var points: []
            property real arg : -Math.PI
            function func(argument){
                var a = (2*Math.PI/10)
                var b = (4 * Math.PI/5)
                return Math.sin(20 * argument) * (
                    Math.exp(-Math.pow(argument / a, 2)) +
                    Math.exp(-Math.pow((argument - b) / a, 2)) +
                    Math.exp(-Math.pow((argument + b) / a, 2))
                );
            }
            // 타이머에서 arg를 바꿀 때마다 호출된다.
            onArgChanged: {
                points.push(func(arg)) // 값을 추가한다.
                points = points.slice(-canvas.width)
                // 맨마지막을 기준으로 canvas.width의 개수(600)개만 빼고 지운다.
                // 즉, 최근 600개만 챙기고 나머지는 버린다.
                // 캔버스에 그릴부분만 챙기기 위해서이다@
                canvas.requestPaint();// redraw!
            }
        }

        Timer{
            interval: 10
            repeat: true
            running: true
            onTriggered: {
                d.arg += Math.PI/180
                // -Pi ~ +Pi 의 범위에 있도록 수정한다.
                while(d.arg>Math.PI){
                    d.arg -= 2* Math.PI;
                }
            }
        }

        x : 20
        y : 20
        implicitWidth: 600
        implicitHeight: 300
        onPaint: {
            var ctx = canvas.getContext("2d");
            ctx.reset();
            ctx.clearRect(0,0,canvas.width, canvas.height);
            ctx.strokeRect(0,0,canvas.width, canvas.height);
            var pointsToDraw = d.points ;//points.slice(-canvas.width)
            ctx.translate(0,canvas.height/2)
            // fill
            ctx.beginPath()
            ctx.moveTo(0,0);// translate되었기 떄문에 0,0이지만, 사실은 0, canvas.height/2이다.
            var i;
            for(i = 0; i < pointsToDraw.length; i++)
            {
                ctx.lineTo(i, -pointsToDraw[i]*canvas.height/2);
            }
            ctx.lineTo(i,0);
            var gradient = ctx.createLinearGradient(
                        0, -canvas.height/2, 0, canvas.height/2);
            gradient.addColorStop(0.1, canvas.topColor);
            gradient.addColorStop(0.5, Qt.rgba(1,1,1,0));
            gradient.addColorStop(0.9, canvas.bottomColor);
            ctx.fillStyle = gradient
            ctx.fill();

            // 선
            ctx.beginPath()
            ctx.moveTo(0,-pointsToDraw[0]*canvas.height/2);
            for(var i = 1; i < pointsToDraw.length; i++){
                ctx.lineTo(i, -pointsToDraw[i]*canvas.height/2);
            }
            ctx.lineWidth = canvas.lineWidth
            ctx.stroke(); // 만들어놓은 경로를 그린다.
        }
    }

    Canvas{
        id : smallCanvas
        Timer{
            interval: 10
            repeat: true
            running: true
            onTriggered: {
                smallCanvas.requestPaint();
            }
        }
        x : 20
        y : 350
        implicitWidth: 105
        implicitHeight: 105
        onPaint: {
            var ctx = smallCanvas.getContext("2d");
            ctx.reset();
            ctx.clearRect(0,0,smallCanvas.width, smallCanvas.height);
            ctx.strokeRect(0,0,smallCanvas.width, smallCanvas.height);

            var offset =d.arg*10
            ctx.strokeRect(0,0,100,100);
            ctx.fillStyle = Qt.rgba(1,0,0,1)
            ctx.fillRect(25+offset,25,50,50)
            var text =  Number(offset).toLocaleString(Qt.locale("de_DE"));
            ctx.fillText(text, 50,15)
        }
    }
}

