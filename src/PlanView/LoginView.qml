import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import QGroundControl.Login 1.0

Item {
    id : dialog_item
    property var _login: Login
    focus: true

    signal connect_signal()

//    Component {
//        id: myComponent

//    }

//    Component.onCompleted: {
//        myComponent.createObject(dialog_item)
//        myComponent.createObject(dialog_item, {"x": 200})
//    }

    Rectangle {

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 3
            spacing: 3

            TextField {
                id: login
                Layout.fillWidth: true
                placeholderText: "Username"
                text: _login.userName
                onTextChanged: _login.userName = login.text
            }

            TextField {
                id: password
                Layout.fillWidth: true
                placeholderText: "Password"

                text: _login.pass
                echoMode: TextInput.PasswordEchoOnEdit
                onTextChanged: _login.pass = password.text
            }

            Button {
                id: loginButton
                text: "Login"
                onClicked: {
                    dialog_item.connect_signal()
                }
            }
        }
    }

}

