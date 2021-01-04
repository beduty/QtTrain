import QtQuick 2.0

Item {
    Canvas{
        id : root
        width: 300
        height: 300
        onPaint: {
//            var context = getContext("2d");
//            context.reset()

//            var centerX = width/2
//            var centerY = height/2

//            context.beginPath();
//            context.fillStyle = "yellowgreen"
//            context.moveTo(centerX, centerY);
//            context.arc(centerX, centerY, width/2, 0, Math.PI*1.5, false);
//            context.lineTo(centerX, centerY);
//            context.fill();

//            context.beginPath();
//            context.fillStyle = "red"
//            context.moveTo(centerX, centerY);
//            context.arc(centerX, centerY, width/4, Math.PI * 1.5, Math.PI, false);
//            context.lineTo(centerX, centerY)
//            context.fill()

            //var ctx = document.getElementById('canvas').getContext('2d');
             var ctx = getContext("2d");
              ctx.fillRect(0, 0, 150, 150);   // 기본 설정으로 사각형을 그리기
              ctx.save();                  // 기본 상태를 저장하기

              ctx.fillStyle = '#09F';      // 설정 변경하기
              ctx.fillRect(15, 15, 120, 120); // 새로운 설정으로 사각형 그리기

              ctx.save();                  // 현재 상태 저장하기
              ctx.fillStyle = '#FFF';      // 설정 변경하기
              ctx.globalAlpha = 0.5;
              ctx.fillRect(30, 30, 90, 90);   // 새로운 설정으로 사각형 그리기

              ctx.restore();               // 이전 상태 복원하기
              ctx.fillRect(45, 45, 60, 60);   // 복원된 설정으로 사각형 그리기

              ctx.restore();               // 초기 상태를 복원하기
              ctx.fillRect(60, 60, 30, 30);   // 복원된 설정으로 사각형 그리기
        }
    }
}
