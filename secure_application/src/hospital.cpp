#include "hospital.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

using namespace std;

Hospital::Hospital() {
    currentUser = "";
}

// --------------------------------------------------
// LOGIN
// --------------------------------------------------

void Hospital::login() {
    string username;
    string password;

    cout << "\n========== LOGIN ==========\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    // Intentionally hardcoded credentials
    // for demonstration purposes.
    if (username == "admin" && password == "admin123") {
        currentUser = username;
        cout << "\nLogin successful!\n";
    } else {
        cout << "\nInvalid username or password.\n";
    }
}

// --------------------------------------------------
// PATIENT REGISTRATION
// --------------------------------------------------

void Hospital::registerPatient() {

    Patient patient;

    cout << "\n========== PATIENT REGISTRATION ==========\n";

    cout << "Enter Patient ID: ";
    cin >> patient.id;

    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, patient.name);

    cout << "Enter Age: ";
    cin >> patient.age;

    cin.ignore();

    cout << "Enter Disease: ";
    getline(cin, patient.disease);

    savePatientRecord(patient);

    cout << "\nPatient registered successfully!\n";
}

// --------------------------------------------------
// SAVE PATIENT RECORD
// --------------------------------------------------

void Hospital::savePatientRecord(const Patient& patient) {

    string filename =
        "../records/patient" + to_string(patient.id) + ".txt";

    ofstream file(filename);

    if (!file) {
        cout << "Error: Could not create patient record.\n";
        return;
    }

    file << "Patient ID: " << patient.id << "\n";
    file << "Name: " << patient.name << "\n";
    file << "Age: " << patient.age << "\n";
    file << "Disease: " << patient.disease << "\n";

    file.close();
}

// --------------------------------------------------
// APPOINTMENT
// --------------------------------------------------

void Hospital::bookAppointment() {

    int patientId;
    string doctor;
    string date;

    cout << "\n========== APPOINTMENT ==========\n";

    cout << "Enter Patient ID: ";
    cin >> patientId;

    cin.ignore();

    cout << "Enter Doctor Name: ";
    getline(cin, doctor);

    cout << "Enter Appointment Date: ";
    getline(cin, date);

    cout << "\nAppointment booked successfully!\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor: " << doctor << "\n";
    cout << "Date: " << date << "\n";
}

// --------------------------------------------------
// PRESCRIPTION
// --------------------------------------------------

void Hospital::addPrescription() {

    int patientId;
    string medicine;
    string dosage;

    cout << "\n========== PRESCRIPTION ==========\n";

    cout << "Enter Patient ID: ";
    cin >> patientId;

    cin.ignore();

    cout << "Enter Medicine: ";
    getline(cin, medicine);

    cout << "Enter Dosage: ";
    getline(cin, dosage);

    cout << "\nPrescription added successfully!\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Medicine: " << medicine << "\n";
    cout << "Dosage: " << dosage << "\n";
}

// --------------------------------------------------
// BILLING
// --------------------------------------------------

void Hospital::generateBill() {

    int patientId;
    double consultationFee;
    double medicineCost;

    cout << "\n========== BILLING ==========\n";

    cout << "Enter Patient ID: ";
    cin >> patientId;

    cout << "Enter Consultation Fee: ";
    cin >> consultationFee;

    cout << "Enter Medicine Cost: ";
    cin >> medicineCost;

    double total = consultationFee + medicineCost;

    cout << "\n========== BILL ==========\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Consultation Fee: " << consultationFee << "\n";
    cout << "Medicine Cost: " << medicineCost << "\n";
    cout << "Total Bill: " << total << "\n";
}

// --------------------------------------------------
// MEDICAL RECORD
// --------------------------------------------------

void Hospital::viewMedicalRecord() {

    string patientInput;

    cout << "\n========== MEDICAL RECORD ==========\n";

    cout << "Enter Patient ID or record path: ";
    cin >> patientInput;

    /*
       INTENTIONAL VULNERABILITY #3
       PATH TRAVERSAL / INSECURE FILE HANDLING

       User input is directly used to construct
       a file path without proper validation.
    */

    string filename =
        "../records/patient" + patientInput + ".txt";

    ifstream file(filename);

    if (!file) {
        cout << "\nError: Medical record not found.\n";
        return;
    }

    cout << "\n----- MEDICAL RECORD -----\n";

    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// --------------------------------------------------
// PATIENT SEARCH
// --------------------------------------------------

void Hospital::searchPatient() {

    string patientId;

    cout << "\n========== PATIENT SEARCH ==========\n";

    cout << "Enter Patient ID: ";
    cin >> patientId;

    /*
       INTENTIONAL VULNERABILITY #1
       SQL INJECTION

       User input is directly inserted into an SQL
       query without validation or parameterization.

       This is included for security-lab demonstration.
    */

    string query =
        "SELECT * FROM patients WHERE id = '" +
        patientId + "';";

    cout << "\nGenerated SQL Query:\n";
    cout << query << "\n";

    cout << "\nPatient search completed.\n";
}

// --------------------------------------------------
// MENU
// --------------------------------------------------

void Hospital::showMenu() {

    int choice;

    while (true) {

        cout << "\n";
        cout << "============================================\n";
        cout << "       HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "Logged in user: " << currentUser << "\n";

        cout << "\n";
        cout << "1. Register Patient\n";
        cout << "2. Book Appointment\n";
        cout << "3. Add Prescription\n";
        cout << "4. Generate Bill\n";
        cout << "5. View Medical Record\n";
        cout << "6. Search Patient\n";
        cout << "7. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                registerPatient();
                break;

            case 2:
                bookAppointment();
                break;

            case 3:
                addPrescription();
                break;

            case 4:
                generateBill();
                break;

            case 5:
                /*
                   INTENTIONAL VULNERABILITY #2
                   BROKEN ACCESS CONTROL

                   The application does not check whether
                   the logged-in user is authorized to access
                   the requested patient's record.
                */
                viewMedicalRecord();
                break;

            case 6:
                searchPatient();
                break;

            case 7:
                cout << "\nExiting application...\n";
                return;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}

