// Implement the hospital emergency queueu to cate service to patients based on 
// Serious (top priority), Non serious (Medium priority and General (Low priority)
// General checkup (least priority)

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a patient
struct patient {
    int id;
    int priority;
    struct patient* next;
};

// Function to create a new patient
struct patient* newPatient(int id, int priority) {
    struct patient* temp = (struct patient*)malloc(sizeof(struct patient));
    temp->id = id;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

// Function to insert a patient into the queue
void insertPatient(struct patient** head, int id, int priority) {
    struct patient* start = (*head);
    struct patient* temp = newPatient(id, priority);

    if ((*head)->priority > priority) {
        temp->next = *head;
        (*head) = temp;
    } else {
        while (start->next != NULL && start->next->priority < priority) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

// Function to remove a patient from the queue
void removePatient(struct patient** head) {
    struct patient* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// Function to display the queue
void displayQueue(struct patient* head) {
    while (head) {
        printf("Patient ID: %d, Priority: %d\n", head->id, head->priority);
        head = head->next;
    }
}

int main() {
    struct patient* head = newPatient(1, 2);
    insertPatient(&head, 2, 1);
    insertPatient(&head, 3, 3);
    insertPatient(&head, 4, 2);
    insertPatient(&head, 5, 1);
    insertPatient(&head, 6, 3);

    printf("Queue before removing a patient:\n");
    displayQueue(head);

    removePatient(&head);

    printf("\nQueue after removing a patient:\n");
    displayQueue(head);

    return 0;
}
