#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student {
    char name[50];
    int score;
    struct Student* next;
} Student;

typedef struct list {
    Student* head;
    int size;
} list;

void init(list* lst) {
    lst->head = NULL;
    lst->size = 0;
}

void add(list* lst, const char* name, int score) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    strncpy(new_student->name, name, sizeof(new_student->name) - 1);
    new_student->name[sizeof(new_student->name) - 1] = '\0';
    new_student->score = score;
    new_student->next = NULL;

    if (lst->head == NULL) {
        lst->head = new_student;
    } else {
        Student* current = lst->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_student;
    }
    lst->size++;
}


void delete(list* lst, const char* name) {
    Student* current = lst->head;
    Student* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (previous == NULL) {
                lst->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            lst->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

void print(const list* lst) {
    Student* current = lst->head;
    while (current != NULL) {
        printf("%s %d\n", current->name, current->score);
        current = current->next;
    }
}

int main() {
    char name[50];
    int score;
    char action[10];
    list student_list;
    init(&student_list);
    
    while (1) {
        scanf("%s", action);
        
        if (strcmp(action, "add") == 0) {
            scanf("%s %d", name, &score);
            add(&student_list, name, score);
        } else if (strcmp(action, "delete") == 0) {
            scanf("%s", name);
            Student* current = student_list.head;
            while (current != NULL) {
                if (strcmp(current->name, name) == 0) {
                    delete(&student_list, name);
                    break;
                }
                current = current->next;
            }
        } else if (strcmp(action, "print") == 0) {
            print(&student_list);
        }
        else if (strcmp(action, "quit") == 0) {
            Student* current = student_list.head;
            while (current != NULL) {
                Student* temp = current;
                current = current->next;
                free(temp);
            }
            break;
        }
        else {
            printf("Invalid action. Please try again.\n");
        }
    }


    return 0;
}
