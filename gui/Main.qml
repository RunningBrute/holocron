import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: "Holocron"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            text: "Nodes: " + nodeCount.value
        }

        SpinBox {
            id: nodeCount
            from: 1
            to: 100
            value: 5
        }

        Button {
            text: "Start"

            onClicked: {
                nodeManager.start(nodeCount.value)
            }
        }
    }

    Connections {
        target: nodeManager

        function onNodeStarted(count) {
            console.log("QML: nodes started:", count)
    }
}
}