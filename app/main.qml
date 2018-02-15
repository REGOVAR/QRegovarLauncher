import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Window 2.10

Window
{
    id: splash
    color: "transparent"
    title: qsTr("Regovar")
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
//    x: (Screen.width - splashImage.width) / 2
//    y: (Screen.height - splashImage.height) / 2
    width: 800
    height: 500

//    property int timeoutInterval: 5000
//    signal timeout

//    SplashScreen
//    {
//        id: splashImage
//        width: 100
//        height: 100
//        barCount: 10


//        MouseArea
//        {
//            anchors.fill: parent
//            onClicked: Qt.quit()
//        }
//    }
//    Timer {
//        interval: timeoutInterval; running: true; repeat: false
//        onTriggered: {
//            visible = false
//            splash.timeout()
//        }
//    }
//    Component.onCompleted: visible = true




    Button
    {
        anchors.centerIn: parent
        text: "Launch"
        onClicked: regovar.start()
    }
}
