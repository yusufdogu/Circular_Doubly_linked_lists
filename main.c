#include <stdio.h>
#include <stdlib.h>

typedef struct doubly_circ {
    int data;
    struct doubly_circ *next;
    struct doubly_circ *prev;
} doubly_circ_list;

// Function prototypes
void insert_at_start_end(doubly_circ_list**);
void insert_at_position(doubly_circ_list**);
void delete_at_position(doubly_circ_list**);
void reverse_list(doubly_circ_list**);
void display_list(doubly_circ_list**);

int main() {
    int num, choice = 10;
    doubly_circ_list *tail = NULL;

    while (choice > 0) {
        printf("Enter a number to choose an action (1-5):\n");
        printf("1. Insert at start/end\n");
        printf("2. Insert at position\n");
        printf("3. Delete at position\n");
        printf("4. Reverse list\n");
        printf("5. Display list\n");
        scanf("%d", &num);

        switch (num) {
            case 1:
                insert_at_start_end(&tail);
                break;
            case 2:
                insert_at_position(&tail);
                break;
            case 3:
                delete_at_position(&tail);
                break;
            case 4:
                reverse_list(&tail);
                break;
            case 5:
                display_list(&tail);
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
        choice--;
    }
}

void insert_at_start_end(doubly_circ_list **tail) {
    int num;
    printf("Enter the number to insert: ");
    scanf("%d", &num);

    doubly_circ_list *new_node = malloc(sizeof(doubly_circ_list));
    new_node->data = num;

    if (*tail == NULL) {  // If the list is empty
        *tail = new_node;
        (*tail)->next = *tail;
        (*tail)->prev = *tail;
    } else {
        doubly_circ_list *head = (*tail)->next;
        new_node->next = head;
        new_node->prev = *tail;
        (*tail)->next = new_node;
        head->prev = new_node;
        *tail = new_node;  // Update tail to the new node
    }

    printf("Inserted: %d\n", (*tail)->data);
}

void insert_at_position(doubly_circ_list **tail) {
    if (*tail == NULL) {
        printf("The list is empty. Add at the start/end first.\n");
        return;
    }
    int pos, num;
    doubly_circ_list *new_node = malloc(sizeof(doubly_circ_list));
    doubly_circ_list *temp = (*tail)->next;

    printf("Enter the position and number to insert: ");
    scanf("%d %d", &pos, &num);
    if (pos == 1) {
        insert_at_start_end(tail);
        return;
    }
    new_node->data = num;
    // Move to the correct position
    while (pos > 2) {
        temp = temp->next;
        pos--;
    }
    // Insert at the correct position
    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next->prev = new_node;
    temp->next = new_node;
    if (new_node->next == (*tail)->next) {
        *tail = new_node;  // Update tail if inserted at the end}
    }
}

void delete_at_position(doubly_circ_list **tail) {
    if (*tail == NULL) {
        printf("The list is empty.\n");
        return;}
    int pos;
    doubly_circ_list *temp = (*tail)->next;
    doubly_circ_list *remove = NULL;
    printf("Enter the position to delete: ");
    scanf("%d", &pos);
    if (pos == 1) {
        (*tail)->next = temp->next;
        temp->next->prev = *tail;
        remove = temp;
        free(remove);
        return;
    }
    // Move to the correct position
    while (pos > 1) {
        temp = temp->next;
        pos--;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    if (temp == *tail) {
        *tail = temp->prev;  // Update tail if deleting the tail node
    }
    remove = temp;
    free(remove);
}

void reverse_list(doubly_circ_list **tail) {
    if (*tail == NULL) {
        printf("The list is empty. Nothing to reverse.\n");
        return;
    }

    doubly_circ_list *move = (*tail)->next;
    doubly_circ_list *prev = *tail;
    doubly_circ_list *next = NULL;
    doubly_circ_list *head = move;

    do {
        next = move->next;
        move->next = prev;
        move->prev = next;
        prev = move;
        move = next;
    } while (move != head);

    *tail = head;
}

void display_list(doubly_circ_list **tail){
    if (*tail == NULL) {
        printf("The list is empty.\n");
        return;
    }

    doubly_circ_list *temp = (*tail)->next;
    int count = 5;  // Limit to 5 nodes for now

    while (count-- > 0) {
        printf("Data: %d\n", temp->data);
        temp = temp->next;
    }
}
