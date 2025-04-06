#include <iostream>
using namespace std;

class PatientNode
{
public:
  string name;
  int arrivalNumber;
  string condition;
  int priority;
  PatientNode *next;

  PatientNode(string name, int arrivalNumber, string condition, int priority)
  {
    this->name = name;
    this->arrivalNumber = arrivalNumber;
    this->condition = condition;
    this->priority = priority;
    next = NULL;
  }
};

class PriorityQueue
{
public:
  PatientNode *front;
  PatientNode *rear;

  PriorityQueue()
  {
    front = rear = NULL;
  }

  void addPatient(string name, int arrivalNumber, string condition, int priority)
  {
    PatientNode *newPatient = new PatientNode(name, arrivalNumber, condition, priority);

    // If queue is empty
    if (front == NULL)
    {
      front = rear = newPatient;
      return;
    }

    // If new patient has highest priority
    if (priority < front->priority)
    {
      newPatient->next = front;
      front = newPatient;
      return;
    }

    // Insert based on priority
    PatientNode *current = front;
    PatientNode *previous = NULL;

    while (current != NULL && current->priority <= priority)
    {
      previous = current;
      current = current->next;
    }

    previous->next = newPatient;
    newPatient->next = current;

    // If inserted at the end
    if (current == NULL)
    {
      rear = newPatient;
    }
  }

  void displayPatients()
  {
    cout << "=============== Patient List ===============" << endl;
    if (front == NULL)
    {
      cout << "No patients in the queue.\n";
      return;
    }

    PatientNode *current = front;
    while (current != NULL)
    {
      cout << "Name: " << current->name
           << " Arrival : " << current->arrivalNumber
           << " Condition: " << current->condition
           << " Priority: " << current->priority << endl;
      current = current->next;
    }
  }
};

int main()
{
  PriorityQueue emergencyRoom;
  int exitFlag = 0;

  while (!exitFlag)
  {
    cout << "\n========= Emergency Room Menu =========" << endl;
    cout << "1. Register New Patient" << endl;
    cout << "2. Show All Patients" << endl;
    cout << "3. Exit Program" << endl;
    cout << "=========================================" << endl;

    int choice;
    cout << "Choose an option: ";
    cin >> choice;

    if (choice == 1)
    {
      string name, condition;
      int arrival, priority;

      cout << "Enter Patient Name: ";
      cin >> name;

      cout << "Enter Arrival Number: ";
      cin >> arrival;

      cout << "Enter Emergency Condition: ";
      cin.ignore();
      getline(cin, condition);

      // Assign priority level based on condition
      if (condition == "Heart Attack" || condition == "Stroke")
        priority = 1;
      else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm")
        priority = 2;
      else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine")
        priority = 3;
      else if (condition == "Mild Cold" || condition == "Small Cut")
        priority = 4;
      else
      {
        cout << "Unknown condition. Cannot assign priority.\n";
        continue;
      }

      emergencyRoom.addPatient(name, arrival, condition, priority);
    }
    else if (choice == 2)
    {
      emergencyRoom.displayPatients();
    }
    else if (choice == 3)
    {
      exitFlag = 1;
      cout << "Exiting the program. Goodbye!" << endl;
    }
    else
    {
      cout << "Invalid option. Please try again." << endl;
    }
  }

  return 0;
}
