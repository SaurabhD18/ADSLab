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
    struct patient* temp = newPatient(id, priority);

    if (*head == NULL || (*head)->priority > priority) {
        temp->next = *head;
        *head = temp;
    } else {
        struct patient* start = *head;
        while (start->next != NULL && start->next->priority <= priority) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

// Function to remove a patient from the queue
void removePatient(struct patient** head) {
    if (*head == NULL) {
        printf("No patients in the queue.\n");
        return;
    }
    struct patient* temp = *head;
    printf("Patient ID %d with priority %d has been attended.\n", temp->id, temp->priority);
    *head = (*head)->next;
    free(temp);
}

// Function to display the queue
void displayQueue(struct patient* head) {
    if (!head) {
        printf("No patients in the queue.\n");
        return;
    }
    printf("Current patient queue:\n");
    while (head) {
        printf("Patient ID: %d, Priority: %d\n", head->id, head->priority);
        head = head->next;
    }
}

// Main function to drive the user interaction
int main() {
    struct patient* head = NULL;
    int choice, id, priority;

    while (1) {
        printf("\nHospital Emergency Queue System\n");
        printf("1. Add patient\n");
        printf("2. Attend a patient (Remove highest priority)\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                printf("Enter Priority (1-Serious, 2-Non serious, 3-General, 4-General Checkup): ");
                scanf("%d", &priority);
                insertPatient(&head, id, priority);
                break;
            case 2:
                removePatient(&head);
                break;
            case 3:
                displayQueue(head);
                break;
            case 4:
                printf("Exiting system.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
