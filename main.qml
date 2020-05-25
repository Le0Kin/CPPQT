import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.qmlmodels 1.0

ApplicationWindow {
    id: _root
    visible: true
    width: 1300
    height: 480
    minimumWidth: 1300
    minimumHeight: 240
    title: qsTr("\"Огранайзер\"")

    TableView {
        id: _mainLayout
        width: parent.width
        height: parent.height - _addTaskButton.height
        Component.onCompleted: {
            name.width = parent.width / 5
            desc.width = parent.width / 5
            ds.width = parent.width / 5
            de.width = parent.width / 5
            prog.width = parent.width / 5
        }

        TableViewColumn {
            id: name
            role: "name"
            title: "Название"
        }
        TableViewColumn {
            id: desc
            role: "description"
            title: "Описание"
        }
        TableViewColumn {
            id: ds
            role: "dateStart"
            title: "Дата начала"
        }
        TableViewColumn {
            id: de
            role: "dateEnd"
            title: "Дата окончания"
        }
        TableViewColumn {
            id: prog
            role: "progress"
            title: "Прогресс"
        }

        model: mymodel

        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
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
