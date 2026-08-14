#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>

using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
};

class Hospital {
private:
    string currentUser;

public:
    Hospital();

    void login();
    void registerPatient();
    void bookAppointment();
    void addPrescription();
    void generateBill();
    void viewMedicalRecord();
    void searchPatient();
    void showMenu();

    void savePatientRecord(const Patient& patient);
};

#endif
