#include "hospital.h"

#include <iostream>

using namespace std;

int main() {

    cout << "============================================\n";
    cout << "       HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "             LAB ASSIGNMENT 3\n";
    cout << "============================================\n";

    Hospital hospital;

    hospital.login();

    hospital.showMenu();

    cout << "\nThank you for using the Hospital Management System.\n";

    return 0;
}
