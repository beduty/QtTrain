import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QProperty_Automatic_Connet_Demo")
    Column{
        spacing: 20
        Text {
            id: titleId
            width: 500
            text: Movie.title  // change 시그널 받아서 업데이트 된다. Binding 되었기 떄문!
            font.pointSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: mainCharId
            width: 500
            text: Movie.mainCharcter  // change 시그널 받아서 업데이트 된다. Binding 되었기 떄문!
            font.pointSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Row{
            anchors.horizontalCenter:  parent.horizontalCenter
            TextField{
                id : titleTextFeildId
                width: 300
            }
            Button{
                width: 200
                id : button1Id
                text: "Change Title"
                onClicked: {
                    Movie.title = titleTextFeildId.text
                    //Movie.settitle(titleTextFeildId.text)
                }
            }
        }
        Row{
            anchors.horizontalCenter:  parent.horizontalCenter
            TextField{
                id : mainCharacterTextFeildId
                width: 300
            }
            Button{
                width: 200
                id : button2Id
                text: "Change Main Character"
                onClicked: {
                    //Movie.mainCharcter = mainCharacterTextFeildId.text
                    Movie.setmainCharcter(mainCharacterTextFeildId.text)
                }
            }
        }
    }

}
