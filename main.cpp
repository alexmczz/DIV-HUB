#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>


using namespace std;


// Function to calculate atmospheric pressure
double calc_pressure(double atmospressure, double density, double accgravity, double depth)
{
    return atmospressure + (density * accgravity * depth);
}

// Function to display pressure and distance
void display_hud(double dispA_depth, double dispB_pressure, double dispC_pressureLbs)
{
    cout << "Meters: " << dispA_depth << endl;
    cout << "Total Pressure: " << dispB_pressure << " Pa" << endl;
    cout << dispC_pressureLbs << " lbs " << endl;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create a QWidget as the main window
    QWidget window;
    window.setWindowTitle("Diving Pressure Calculator");

    // Create input fields
    QLabel depthLabel("Depth (meters):");
    QLineEdit depthLineEdit;
    QPushButton calculateButton("Calculate");

    // Create layout and add widgets
    QFormLayout layout(&window);
    layout.addRow(&depthLabel, &depthLineEdit);
    layout.addRow(&calculateButton);

    // Connect the calculateButton click event to calculate the pressure
    QObject::connect(&calculateButton, &QPushButton::clicked, [&](){
        bool conversionOk;
        double depth = depthLineEdit.text().toDouble(&conversionOk);
        if (conversionOk) {
            // Perform pressure calculation
            double totalPressure = calc_pressure(101325, 1000, 9.8, depth);
            double pressure_pounds = totalPressure / 6894.76;
            QMessageBox::information(&window, "Pressure Calculation", QString("Total Pressure: %1 Pa").arg(totalPressure));
            display_hud(depth, totalPressure, pressure_pounds);

            if (depth > 30) {
                QMessageBox::warning(&window, "Danger", "DANGER! Depth exceeds 30 meters.");
            } else if (depth >= 18) {
                QMessageBox::warning(&window, "Warning", "WARNING! Depth exceeds 18 meters.");
            }
        } else {
            QMessageBox::warning(&window, "Input Error", "Invalid depth value!");
        }
    });

    // Show the window
    window.show();

    // Execute the application event loop
    return app.exec();
}
