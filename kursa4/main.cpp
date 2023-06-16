#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QString>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Step 2: UI widgets
    QWidget *window = new QWidget();
    window->setWindowTitle("Hemoglobin Level Checker");

    QLabel *ageLabel = new QLabel("Age: ", window);
    ageLabel->setGeometry(10, 20, 80, 25);

    QLineEdit *ageLineEdit = new QLineEdit(window);
    ageLineEdit->setGeometry(100, 20, 80, 25);

    QLabel *genderLabel = new QLabel("Gender: ", window);
    genderLabel->setGeometry(10, 60, 80, 25);

    QComboBox *genderComboBox = new QComboBox(window);
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");
    genderComboBox->setGeometry(100,60, 80, 25);

    QLabel *hbLabel = new QLabel("Hemoglobin Level: ", window);
    hbLabel->setGeometry(10, 100, 120, 25);

    QLineEdit *hbLineEdit = new QLineEdit(window);
    hbLineEdit->setGeometry(140, 100, 80, 25);

    QPushButton *calculateButton = new QPushButton("Check", window);
    calculateButton->setGeometry(100, 140, 40, 25);

    QLabel *resultLabel = new QLabel(window);
    resultLabel->setGeometry(10, 180, 200, 25);

    // Step 4: Calculation Function
    QObject::connect(calculateButton, &QPushButton::clicked, [&](){
        int age = ageLineEdit->text().toInt();
        QString gender = genderComboBox->currentText();
        float hb = hbLineEdit->text().toFloat();

        if(gender == "Male") {
            if(age < 15) {
                if(hb < 115) {
                    resultLabel->setText("Hemoglobin level is low");
                } else if(hb > 155) {
                    resultLabel->setText("Hemoglobin level is high");
                } else {
                    resultLabel->setText("Hemoglobin level is normal");
                }
            } else {
                if(hb < 130) {
                    resultLabel->setText("Hemoglobin level is low");
                } else if(hb > 170) {
                    resultLabel->setText("Hemoglobin level is high");
                } else {
                    resultLabel->setText("Hemoglobin level is normal");
                }
            }
        } else {
            if(age < 15) {
                if(hb < 115) {
                    resultLabel->setText("Hemoglobin level is low");
                } else if(hb > 150) {
                    resultLabel->setText("Hemoglobin level is high");
                } else {
                    resultLabel->setText("Hemoglobin level is normal");
                }
            } else {
                if(hb < 120) {
                    resultLabel->setText("Hemoglobin level is low");
                } else if(hb > 160) {
                    resultLabel->setText("Hemoglobin level is high");
                } else {
                    resultLabel->setText("Hemoglobin level is normal");
                }
            }
        }
    });

    // Step 1: show window
    window->show();
    return app.exec();
}
