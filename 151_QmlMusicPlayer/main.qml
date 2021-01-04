import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow{
    id : window
    width: 1280
    height: 720
    visible: true
    title: "Qt Quick Controls - Imagine Style Example: Musicplayer"

    Component.onCompleted: {
        x = Screen.width/2 - width/2
        y = Screen.height/2 - height/2
    }
    Shortcut{
        sequence : "Ctrl+Q"
        onActivated: Qt.quit()
    }
    header: ToolBar{
        RowLayout{
            id : headerRowLayout
            anchors.fill: parent
            spacing: 0
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/grid.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/settings.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/filter.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/message.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/music.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/cloud.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/bluetooth.png"
            }
            ToolButton{
                icon.source : "/icons/musicplayer/32x32@2/cart.png"
            }
            Item{
                Layout.fillWidth: true
            }
            ToolButton{
                icon.source: "/icons/musicplayer/32x32@2/power.png"
                onClicked: Qt.quit()
            }
        }
    }

    Label{
        text: "Qtify"
        font.pixelSize: Qt.application.font.pixelSize * 1.3
        anchors.centerIn: header
        z: header.z + 1
    }

    RowLayout{
        spacing: 115
        anchors.fill: parent
        anchors.margins: 70
        ColumnLayout{
            spacing: 0
            Layout.preferredWidth: 230
            RowLayout{
                Layout.maximumHeight: 170
                ColumnLayout{
                    Label{
                        text: "12 dB"
                        Layout.fillHeight: true
                    }
                    Label{
                        text: "6 dB"
                        Layout.fillHeight: true
                    }
                    Label{
                        text: "0 dB"
                        Layout.fillHeight: true
                    }
                    Label{
                        text: "-6 dB"
                        Layout.fillHeight: true
                    }
                    Label{
                        text: "-12 dB"
                        Layout.fillHeight: true
                    }
                }
                Repeater{
                    model: 7
                    Slider{
                        value: Math.random()
                        orientation: Qt.Vertical
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }

            RowLayout{
                spacing: 10
                Layout.topMargin: 23
                ComboBox{
                    currentIndex: 1
                    model : ["Blues", "Classical", "Jazz", "Metal"]
                    Layout.fillWidth: true
                }
                Button{
                    icon.source: "/icons/musicplayer/32x32/folder.png"
                    //icon.name: "folder"
                }
                Button{
                    icon.source: "/icons/musicplayer/32x32/save.png"
                    enabled: false
                }
            }

            Dial{
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 50
            }
            Label{
                text:"Volume"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 12
            }
        }
        ColumnLayout{
            spacing: 26
            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Image{
                    anchors.fill: parent
                    fillMode:Image.PreserveAspectCrop
                    source: "images/album-cover.jpg" // .pro에 이미지경로를 직접 추가했다.
                }
            }
            Item {
                id: songLabelContainer
                clip: true
                Layout.fillWidth:  true
                Layout.preferredHeight: songNameLabel.implicitHeight

                Label {
                    id:songNameLabel
                    text : "Edvard Grieg - In the Hall of the Mountain King"
                    font.pixelSize: Qt.application.font.pixelSize * 1.4
                }

                Rectangle {
                    id: leftGradient
                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#dfe4ea"
                        }
                        GradientStop {
                            position: 1
                            color: "#00dfe4ea"
                        }
                    }

                    width: height
                    height: parent.height
                    anchors.left: parent.left
                    z: 1
                    rotation: -90
                    opacity: 0
                }

                Rectangle{
                    id : rightGradient
                    gradient: Gradient{
                        GradientStop{
                            position: 0
                            color: "#00dfe4ea"
                        }
                        GradientStop{
                            position: 1
                            color : "#dfe4ea"
                        }
                    }
                    width: height
                    height: parent.height
                    anchors.right: parent.right
                    rotation: -90
                    color: "red"
                }

                SequentialAnimation{
                    running: true
                    loops : Animation.Infinite

                    PauseAnimation {
                        duration: 2000
                    }
                    ParallelAnimation{
                        XAnimator{
                            target: songNameLabel
                            from: 0
                            to : songLabelContainer.width - songNameLabel.implicitWidth
                            duration: 5000
                        }
                        OpacityAnimator{
                            target: leftGradient
                            from: 0
                            to : 1
                        }
                    }
                    OpacityAnimator{
                        target: rightGradient
                        from: 1
                        to : 0
                    }
                    PauseAnimation {
                        duration: 1000
                    }
                    OpacityAnimator{
                        target: rightGradient
                        from: 0
                        to : 1
                    }
                    ParallelAnimation{
                        XAnimator{
                            target: songNameLabel
                            from: songLabelContainer.width-songNameLabel.implicitWidth
                            to : 0
                            duration: 5000
                        }
                        OpacityAnimator{
                            target: leftGradient
                            from: 0
                            to : 1
                        }
                    }
                    OpacityAnimator{
                        target: leftGradient
                        from: 1
                        to : 0
                    }
                }
            }

            RowLayout{
                spacing: 8
                Layout.alignment: Qt.AlignHCenter
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/favorite.png"
                }
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/stop.png"
                }
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/previous.png"
                }
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/pause.png"
                }
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/next.png"
                }
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/repeat.png"
                }
                RoundButton{
                    icon.source: "/icons/musicplayer/32x32/shuffle.png"
                }
            }
            Slider{
                id : seekSlider
                value : 113
                to : 261
                Layout.fillWidth: true
                ToolTip{
                    parent : seekSlider.handle
                    visible: seekSlider.pressed
                    text: pad(Math.floor(value / 60)) + ":" + pad(Math.floor(value % 60))
                    y : parent.height
                    readonly property int value: seekSlider.valueAt(seekSlider.position)
                    function pad(number){
                        if(number<=9)
                            return "0" + number;
                        return   number;
                    }
                }
            }
        }
        ColumnLayout {
            spacing: 16
            Layout.preferredWidth: 230
            ButtonGroup{
                buttons: libraryRowLayout.chidren
            }

            RowLayout{
                id : libraryRowLayout
                Layout.alignment: Qt.AlignHCenter
                Button{
                    text : "Files"
                    checked : true
                }
                Button {
                    text : "Playlists"
                    checkable: true
                }
                Button {
                    text : "Favourites"
                    checkable: true
                }
            }
            RowLayout{
                TextField{
                    Layout.fillWidth: true
                }
                Button{
                    icon.source: "/icons/musicplayer/32x32/folder.png"
                }
            }
            Frame{
                id : filedFrame
                leftPadding: 1
                rightPadding: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
                ListView{
                    clip: true
                    anchors.fill: parent
                    model: ListModel{
                        Component.onCompleted: {
                            for(var i = 0; i < 100; ++i)
                            {
                                append({author : "Author", album : "Album", track : "Track 0" + (i%9+1)});
                            }
                        }
                    }
                    delegate: ItemDelegate{
                        text : model.author + "-" + model.album + "-"+ model.track
                        width: parent.width
                    }
                    ScrollBar.vertical: ScrollBar{
                        parent: filedFrame
                        policy: ScrollBar.AlwaysOn
                        anchors.top: parent.top
                        anchors.topMargin: filedFrame.topPadding
                        anchors.right: parent.right
                        anchors.rightMargin: 1
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: filedFrame.bottomPadding
                    }
                }
            }
        }


    }
}































