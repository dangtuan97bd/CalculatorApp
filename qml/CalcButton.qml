import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    property alias text: label.text
    property bool accent: false
    signal clicked()

    implicitWidth: 64
    implicitHeight: 56
    Layout.fillWidth: true
    Layout.fillHeight: true

    radius: 6
    color: accent ?  "#3b82f6" : "#2a2a2a"

    Text{
        id: label
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 18
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: root.clicked()

        onEntered: root.color = accent ? "#2563eb" : "#3a3a3a"
        onExited:  root.color = accent ? "#3b82f6" : "#2a2a2a"
        onPressed: root.color = accent ? "#1d4ed8" : "#444444"
        onReleased:root.color = accent ? "#2563eb" : "#3a3a3a"

    }
}
