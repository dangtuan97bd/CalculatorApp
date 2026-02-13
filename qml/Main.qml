import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Calculator"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        // DISPLAY
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            radius: 8
            color: "#1f1f1f"

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 4

                // Expression (nhỏ phía trên)
                Text {
                    text: calculator ? calculator.expression : ""
                    font.pixelSize: 14
                    color: "#888"
                    horizontalAlignment: Text.AlignRight
                    width: parent.width
                    elide: Text.ElideLeft
                }

                // Display (kết quả lớn)
                Text {
                    text: calculator ? calculator.display : ""
                    font.pixelSize: 32
                    color: "white"
                    horizontalAlignment: Text.AlignRight
                    width: parent.width
                    elide: Text.ElideLeft
                }
            }
        }


        // ================= BUTTON GRID =================
        GridLayout {
            columns: 4
            rowSpacing: 10
            columnSpacing: 10
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Row 1
            CalcButton {
                text: "C"
                onClicked: calculator.clear()
            }

            CalcButton {
                text: "CE"
                onClicked: calculator.clearEntry()
            }


            CalcButton {
                text: "⌫"
                onClicked: calculator.backspace()
            }


            CalcButton {
                text: "÷"
                accent: true
                onClicked: calculator.inputOperator("÷")
            }

            // Row 2
            CalcButton { text: "7"; onClicked: calculator.inputNumber("7") }
            CalcButton { text: "8"; onClicked: calculator.inputNumber("8") }
            CalcButton { text: "9"; onClicked: calculator.inputNumber("9") }

            CalcButton {
                text: "×"
                accent: true
                onClicked: calculator.inputOperator("×")
            }

            // Row 3
            CalcButton { text: "4"; onClicked: calculator.inputNumber("4") }
            CalcButton { text: "5"; onClicked: calculator.inputNumber("5") }
            CalcButton { text: "6"; onClicked: calculator.inputNumber("6") }

            CalcButton {
                text: "-"
                accent: true
                onClicked: calculator.inputOperator("-")
            }

            // Row 4
            CalcButton { text: "1"; onClicked: calculator.inputNumber("1") }
            CalcButton { text: "2"; onClicked: calculator.inputNumber("2") }
            CalcButton { text: "3"; onClicked: calculator.inputNumber("3") }

            CalcButton {
                text: "+"
                accent: true
                onClicked: calculator.inputOperator("+")
            }

            // Row 5
            CalcButton {
                text: "±"
                onClicked: calculator.toggleSign()
            }


            CalcButton { text: "0"; onClicked: calculator.inputNumber("0") }

            CalcButton {
                text: "="
                accent: true
                Layout.columnSpan: 2
                Layout.fillWidth: true
                onClicked: calculator.calculate()
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            model: historyManager ? historyManager.history : []

            delegate: Text {
                text: modelData
                color: "black"
            }
        }
    }
}
