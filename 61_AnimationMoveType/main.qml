//import QtQuick 2.12
//import QtQuick.Window 2.12
//import QtQuick.Layouts 1.12

//Window {
//    id : rootId
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Animation Move Type_Easing")

//    property int animationDuration : 500
//    Flickable{
//        anchors.fill: parent
//        contentHeight: mColumnId.implicitHeight
//        ColumnLayout{
//            id : mColumnId
//            width: parent.width
//            spacing: 2
//            MovingRectangle{
//                backgroundColor: "gray"
//                startColor: "beige"
//                endColor: "blue"
//                animDuration:  animationDuration
//                easingText: "Linear"
//                easingType: Easing.Linear
//                trackWidth: rootId.width
//            }
//            MovingRectangle{
//                backgroundColor: "gray"
//                startColor: "beige"
//                endColor: "green"
//                animDuration:  animationDuration
//                easingText: "InQuad"
//                easingType: Easing.InQuad
//                trackWidth: rootId.width
//            }

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "salmon";
//                animDuration: animationDuration;easingText: "OutQuad";easingType: Easing.OutQuad;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "tomato";
//                animDuration: animationDuration;easingText: "InOutQuad";easingType: Easing.InOutQuad;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkorange"
//                animDuration: animationDuration;easingText: "OutInQuad";easingType: Easing.OutInQuad;
//                trackWidth: rootId.width}

//            //Cubic
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "gold"
//                animDuration: animationDuration;easingText: "InCubic";easingType: Easing.InCubic;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "yellow"
//                animDuration: animationDuration;easingText: "OutCubic";easingType: Easing.OutCubic;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "peachpuff"
//                animDuration: animationDuration;easingText: "InOutCubic";easingType: Easing.InOutCubic;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "thistle"
//                animDuration: animationDuration;easingText: "OutInCubic";easingType: Easing.OutInCubic;
//                trackWidth: rootId.width}

//            //Quart
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "orchid"
//                animDuration: animationDuration;easingText: "InQuart";easingType: Easing.InQuart;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "purple"
//                animDuration: animationDuration;easingText: "OutQuart";easingType: Easing.OutQuart;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "slateblue"
//                animDuration: animationDuration;easingText: "InOutQuart";easingType: Easing.InOutQuart;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "chartreuse"
//                animDuration: animationDuration;easingText: "OutInQuart";easingType: Easing.OutInQuart;
//                trackWidth: rootId.width}

//            //Quint
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "limegreen"
//                animDuration: animationDuration;easingText: "InQuint";easingType: Easing.InQuint;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "seagreen"
//                animDuration: animationDuration;easingText: "OutQuint";easingType: Easing.OutQuint;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkgreen"
//                animDuration: animationDuration;easingText: "InOutQuint";easingType: Easing.InOutQuint;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "olive"
//                animDuration: animationDuration;easingText: "OutInQuint";easingType: Easing.OutInQuint;
//                trackWidth: rootId.width}

//            //Sine
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkseagreen"
//                animDuration: animationDuration;easingText: "InSine";easingType: Easing.InSine;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "teal"
//                animDuration: animationDuration;easingText: "OutSine";easingType: Easing.OutSine;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "turquoise"
//                animDuration: animationDuration;easingText: "InOutSine";easingType: Easing.InOutSine;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "steelblue"
//                animDuration: animationDuration;easingText: "OutInSine";easingType: Easing.OutInSine;
//                trackWidth: rootId.width}

//            //Expo
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "skyblue"
//                animDuration: animationDuration;easingText: "InExpo";easingType: Easing.InExpo;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "royalblue"
//                animDuration: animationDuration;easingText: "OutExpo";easingType: Easing.OutExpo;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "mediumblue"
//                animDuration: animationDuration;easingText: "InOutExpo";easingType: Easing.InOutExpo;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "midnightblue"
//                animDuration: animationDuration;easingText: "OutInExpo";easingType: Easing.OutInExpo;
//                trackWidth: rootId.width}

//            //Circ
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "cornsilk"
//                animDuration: animationDuration;easingText: "InCirc";easingType: Easing.InCirc;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "bisque"
//                animDuration: animationDuration;easingText: "OutCirc";easingType: Easing.OutCirc;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "rosybrown"
//                animDuration: animationDuration;easingText: "InOutCirc";easingType: Easing.InOutCirc;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "sandybrown"
//                animDuration: animationDuration;easingText: "OutInCirc";easingType: Easing.OutInCirc;
//                trackWidth: rootId.width}


//            //Elastic
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "cornsilk"
//                animDuration: animationDuration;easingText: "InElastic";easingType: Easing.InElastic;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "bisque"
//                animDuration: animationDuration;easingText: "OutElastic";easingType: Easing.OutElastic;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "rosybrown"
//                animDuration: animationDuration;easingText: "InOutElastic";easingType: Easing.InOutElastic;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "sandybrown"
//                animDuration: animationDuration;easingText: "OutInElastic";easingType: Easing.OutInElastic;
//                trackWidth: rootId.width}


//            //Black
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "maroon"
//                animDuration: animationDuration;easingText: "InBack";easingType: Easing.InBack;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "lavenderblush"
//                animDuration: animationDuration;easingText: "OutBack";easingType: Easing.OutBack;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "mistyrose"
//                animDuration: animationDuration;easingText: "InOutBack";easingType: Easing.InOutBack;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "gainsboro"
//                animDuration: animationDuration;easingText: "OutInBack";easingType: Easing.OutInBack;
//                trackWidth: rootId.width}


//            //Bounce
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "silver"
//                animDuration: animationDuration;easingText: "InBounce";easingType: Easing.InBounce;
//                trackWidth: rootId.width }

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "dimgray"
//                animDuration: animationDuration;easingText: "OutBounce";easingType: Easing.OutBounce;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "slategray"
//                animDuration: animationDuration;easingText: "InOutBounce";easingType: Easing.InOutBounce;
//                trackWidth: rootId.width}

//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkslategray"
//                animDuration: animationDuration;easingText: "OutInBounce";easingType: Easing.OutInBounce;
//                trackWidth: rootId.width}

//            //Bezier
//            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkslategray"
//                animDuration: animationDuration;easingText: "Bezier";easingType: Easing.Bezier;
//                trackWidth: rootId.width}

//        }
//    }
//}



import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
Window {
    id : rootId
    visible : true
    width : 640
    height : 480
    title : qsTr("Animation Move Type")
    property int animationDuration : 500

    Flickable{
        anchors.fill : parent
        contentHeight : mColumnId.implicitHeight
        ColumnLayout{
            id : mColumnId
            width : parent.width
            spacing : 2
            MovingRectangle{
                backgroundColor: "gray"
                startColor : "beige"
                endColor : "blue"
                animDuration : animationDuration
                easingText : "Linear"
                easingType : Easing.Linear
                trackWidth : rootId.width
            }
            MovingRectangle{
                backgroundColor: "gray"
                startColor: "beige"
                endColor: "green"
                animDuration:  animationDuration
                easingText: "InQuad"
                easingType: Easing.InQuad
                trackWidth: rootId.width
            }

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "salmon";
                animDuration: animationDuration;easingText: "OutQuad";easingType: Easing.OutQuad;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "tomato";
                animDuration: animationDuration;easingText: "InOutQuad";easingType: Easing.InOutQuad;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkorange"
                animDuration: animationDuration;easingText: "OutInQuad";easingType: Easing.OutInQuad;
                trackWidth: rootId.width}

            //Cubic
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "gold"
                animDuration: animationDuration;easingText: "InCubic";easingType: Easing.InCubic;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "yellow"
                animDuration: animationDuration;easingText: "OutCubic";easingType: Easing.OutCubic;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "peachpuff"
                animDuration: animationDuration;easingText: "InOutCubic";easingType: Easing.InOutCubic;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "thistle"
                animDuration: animationDuration;easingText: "OutInCubic";easingType: Easing.OutInCubic;
                trackWidth: rootId.width}

            //Quart
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "orchid"
                animDuration: animationDuration;easingText: "InQuart";easingType: Easing.InQuart;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "purple"
                animDuration: animationDuration;easingText: "OutQuart";easingType: Easing.OutQuart;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "slateblue"
                animDuration: animationDuration;easingText: "InOutQuart";easingType: Easing.InOutQuart;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "chartreuse"
                animDuration: animationDuration;easingText: "OutInQuart";easingType: Easing.OutInQuart;
                trackWidth: rootId.width}

            //Quint
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "limegreen"
                animDuration: animationDuration;easingText: "InQuint";easingType: Easing.InQuint;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "seagreen"
                animDuration: animationDuration;easingText: "OutQuint";easingType: Easing.OutQuint;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkgreen"
                animDuration: animationDuration;easingText: "InOutQuint";easingType: Easing.InOutQuint;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "olive"
                animDuration: animationDuration;easingText: "OutInQuint";easingType: Easing.OutInQuint;
                trackWidth: rootId.width}

            //Sine
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkseagreen"
                animDuration: animationDuration;easingText: "InSine";easingType: Easing.InSine;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "teal"
                animDuration: animationDuration;easingText: "OutSine";easingType: Easing.OutSine;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "turquoise"
                animDuration: animationDuration;easingText: "InOutSine";easingType: Easing.InOutSine;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "steelblue"
                animDuration: animationDuration;easingText: "OutInSine";easingType: Easing.OutInSine;
                trackWidth: rootId.width}

            //Expo
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "skyblue"
                animDuration: animationDuration;easingText: "InExpo";easingType: Easing.InExpo;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "royalblue"
                animDuration: animationDuration;easingText: "OutExpo";easingType: Easing.OutExpo;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "mediumblue"
                animDuration: animationDuration;easingText: "InOutExpo";easingType: Easing.InOutExpo;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "midnightblue"
                animDuration: animationDuration;easingText: "OutInExpo";easingType: Easing.OutInExpo;
                trackWidth: rootId.width}

            //Circ
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "cornsilk"
                animDuration: animationDuration;easingText: "InCirc";easingType: Easing.InCirc;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "bisque"
                animDuration: animationDuration;easingText: "OutCirc";easingType: Easing.OutCirc;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "rosybrown"
                animDuration: animationDuration;easingText: "InOutCirc";easingType: Easing.InOutCirc;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "sandybrown"
                animDuration: animationDuration;easingText: "OutInCirc";easingType: Easing.OutInCirc;
                trackWidth: rootId.width}


            //Elastic
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "cornsilk"
                animDuration: animationDuration;easingText: "InElastic";easingType: Easing.InElastic;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "bisque"
                animDuration: animationDuration;easingText: "OutElastic";easingType: Easing.OutElastic;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "rosybrown"
                animDuration: animationDuration;easingText: "InOutElastic";easingType: Easing.InOutElastic;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "sandybrown"
                animDuration: animationDuration;easingText: "OutInElastic";easingType: Easing.OutInElastic;
                trackWidth: rootId.width}


            //Black
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "maroon"
                animDuration: animationDuration;easingText: "InBack";easingType: Easing.InBack;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "lavenderblush"
                animDuration: animationDuration;easingText: "OutBack";easingType: Easing.OutBack;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "mistyrose"
                animDuration: animationDuration;easingText: "InOutBack";easingType: Easing.InOutBack;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "gainsboro"
                animDuration: animationDuration;easingText: "OutInBack";easingType: Easing.OutInBack;
                trackWidth: rootId.width}


            //Bounce
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "silver"
                animDuration: animationDuration;easingText: "InBounce";easingType: Easing.InBounce;
                trackWidth: rootId.width }

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "dimgray"
                animDuration: animationDuration;easingText: "OutBounce";easingType: Easing.OutBounce;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "slategray"
                animDuration: animationDuration;easingText: "InOutBounce";easingType: Easing.InOutBounce;
                trackWidth: rootId.width}

            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkslategray"
                animDuration: animationDuration;easingText: "OutInBounce";easingType: Easing.OutInBounce;
                trackWidth: rootId.width}

            //Bezier
            MovingRectangle {backgroundColor: "gray";startColor: "beige";endColor: "darkslategray"
                animDuration: animationDuration;easingText: "Bezier";easingType: Easing.Bezier;
                trackWidth: rootId.width}
        }
    }
}
