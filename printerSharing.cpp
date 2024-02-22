// Simulation of printer sharing among a group of students, using circular linked list

#include <iostream>
using namespace std;

class Node{
    public:
        int roll;
        int time;
        Node * next;

        Node(int roll, int time){
            this->roll = roll; 
            this->time = time;
            next=NULL;
        }

        ~Node(){
            delete next;
        }
};

void insertAtTail(Node*& head, int roll, int time) {
    Node* n = new Node(roll, time);

    if (head == NULL) {
        n->next = n;
        head = n;
        return;
    }

    Node* ptr = head;
    while (ptr->next != head) {
        ptr = ptr->next;
    }

    ptr->next = n;
    n->next = head;
}

void display(Node * head){
    Node * ptr = head;
    do{
        cout <<  ptr->roll << "-" << ptr->time << "-> "; 
        ptr=ptr->next;
    }while(ptr != head);
    cout<<endl;
}


void deleteNode(Node*& head, int val) {
    if (head == NULL) {
        return;
    }

    if (head->roll == val) {
        Node* deletedNode = head;
        head = head->next;
        delete deletedNode;
        return;
    }

    Node* ptr = head;
    while (ptr->next != NULL && ptr->next->roll != val) {
        ptr = ptr->next;
    }

    if (ptr->next == NULL) {
        cout << val << " not found in the list." << endl;
        return;
    }

    Node* deletedNode = ptr->next;
    ptr->next = ptr->next->next;

    delete deletedNode;
    cout << val << " deleted from the list." << endl;
}

int main() {
    Node *head = NULL;
    int numberOfStudents; 
    float totalTime, allottedTime;
    int roll, studentTime;

    // Input total time, number of students, and time allotted to each student
    cout << "Enter total time (in hours): ";
    cin >> totalTime;
    totalTime *= 60; // converting to minutes

    cout << "How many students are there? ";
    cin >> numberOfStudents;

    cout << "Enter time allotted to each student (in mins.): ";
    cin >> allottedTime;

    // Input student details and insert them into the linked list
    for (int i = 0; i < numberOfStudents; i++) {
        cout << "Enter student roll number: ";
        cin >> roll;
        cout << "Enter student's allotted time (in minutes): ";
        cin >> studentTime;
        insertAtTail(head, roll, studentTime);
    }

    cout << "Sending printer to class...\n";

    Node *student = head;
    int rotations = 0;

    // Simulate printing tasks
    while (totalTime >= 0 && head != NULL) {
        cout << "\n\nRotation " << rotations + 1 << ":\n";
        Node* currentStudent = head;  // Store the current student

        do {
            totalTime -= allottedTime;
            cout << "Student " << currentStudent->roll << ": ";
            currentStudent->time -= allottedTime;
            cout << "Time up!\n";
            cout << "Task time left - " << currentStudent->time << " minutes\n";

            Node* nextStudent = currentStudent->next;
            if (currentStudent->time == 0) {
                // If student's task is completed, remove them from the list
                int studentRoll = currentStudent->roll; // Store roll before potential deletion
                currentStudent = nextStudent; // Move to the next student before deletion
                deleteNode(head, studentRoll);
                cout << "Student " << studentRoll << "\'s task is completed. Removed from the list\n";
            }
            else{
                currentStudent = nextStudent; // Move to the next student
            }

        } while (currentStudent != head);

        // Display remaining students and their times after each rotation
        display(head);
        cout << "Total time left - " << totalTime << " minutes\n";
        rotations++;
    }

    return 0;
}