#include <iostream>
#include <algorithm>
using namespace std;

class PatientNode {
private:
    string name;
    int arrivalNumber;
    string condition;
    int priority;
    PatientNode* next;

public:
    PatientNode(string patientName, int arrivalNum, string patientCondition, int patientPriority)
        : name(patientName),
          arrivalNumber(arrivalNum),
          condition(patientCondition),
          priority(patientPriority),
          next(nullptr) {}

    friend class PriorityQueue; // Allow PriorityQueue to access private members
};

class PriorityQueue {
private:
    PatientNode* front;
    PatientNode* rear;

    // Helper function to clear the queue
    void clearQueue() {
        while (front != nullptr) {
            PatientNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }

public:
    PriorityQueue() : front(nullptr), rear(nullptr) {}

    ~PriorityQueue() {
        clearQueue();
    }

    void addPatient(string name, int arrivalNumber, string condition, int priority) {
        PatientNode* newPatient = new PatientNode(name, arrivalNumber, condition, priority);

        if (!front) {
            front = rear = newPatient;
            return;
        }

        if (priority < front->priority) {
            newPatient->next = front;
            front = newPatient;
            return;
        }

        PatientNode* current = front;
        PatientNode* previous = nullptr;

        while (current && current->priority <= priority) {
            previous = current;
            current = current->next;
        }

        previous->next = newPatient;
        newPatient->next = current;
        if (!current) {
            rear = newPatient;
        }
    }

    void displayPatients() const {
        cout << "=============== Patient List ===============" << endl;
        if (!front) {
            cout << "No patients in the queue.\n";
            return;
        }

        PatientNode* current = front;
        while (current) {
            cout << "Name: " << current->name
                 << " Arrival: " << current->arrivalNumber
                 << " Condition: " << current->condition
                 << " Priority: " << current->priority << endl;
            current = current->next;
        }
    }
};

int main() {
    PriorityQueue emergencyRoom;
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "\n========= Emergency Room Menu =========" << endl;
        cout << "1. Register New Patient" << endl;
        cout << "2. Show All Patients" << endl;
        cout << "3. Exit Program" << endl;
        cout << "=========================================" << endl;

        int choice;
        cout << "Choose an option: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string name, condition;
                int arrival, priority;

                cout << "Enter Patient Name: ";
                cin >> name;

                cout << "Enter Arrival Number: ";
                if (!(cin >> arrival)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid arrival number.\n";
                    continue;
                }

                cout << "Enter Emergency Condition: ";
                cin.ignore();
                getline(cin, condition);

                // Convert condition to lowercase for case-insensitive comparison
                string conditionLower = condition;
                transform(conditionLower.begin(), conditionLower.end(), conditionLower.begin(), ::tolower);

                if (conditionLower == "heart attack" || conditionLower == "stroke")
                    priority = 1;
                else if (conditionLower == "broken leg" || conditionLower == "severe burn" || conditionLower == "fractured arm")
                    priority = 2;
                else if (conditionLower == "fever" || conditionLower == "food poisoning" || conditionLower == "migraine")
                    priority = 3;
                else if (conditionLower == "mild cold" || conditionLower == "small cut")
                    priority = 4;
                else {
                    cout << "Unknown condition. Cannot assign priority.\n";
                    continue;
                }

                emergencyRoom.addPatient(name, arrival, condition, priority);
                break;
            }
            case 2:
                emergencyRoom.displayPatients();
                break;
            case 3:
                exitFlag = true;
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
