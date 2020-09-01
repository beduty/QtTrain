import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Particles 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    ParticleSystem{
        id : particleSystem
        anchors.fill: parent
        Emitter{
            anchors.centerIn: parent
            width: 50; height: 50
            emitRate: 50
            velocity: AngleDirection{
                angleVariation: 45
                angle: 180
                magnitude: 200
            }
        }
        ImageParticle{
            source: "star_white.png"
            colorVariation: 1
        }
    }
}
