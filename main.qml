import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: _root
    visible: true
    width: 1300
    height: 480
    minimumWidth: 1300
    minimumHeight: 240
    title: qsTr("\"Огранайзер\"")

    ColumnLayout {
        id: _mainLayout
        width: parent.width
        // Table header
        Task {
            id: _Header
            Layout.fillWidth: true
            height: 35

            idColor: "#A0A0A0"
            nameColor: "#A0A0A0"
            descriptionColor: "#A0A0A0"
            startColor: "#A0A0A0"
            endColor: "#A0A0A0"
            progColor: "#A0A0A0"
        }
    }

    Button {
        id: _addTaskButton
        text: "Добавить задачу"
        width: parent.width
        anchors.bottom: parent.bottom
        onClicked: {
            _formAddTask.show()
        }
    }

    FormAddTask {
        id: _formAddTask
        title: qsTr("Добавить задачу")
    }
}
