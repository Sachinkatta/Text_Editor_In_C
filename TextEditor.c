#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWNODE (struct node*) malloc(sizeof(struct node))

struct node {
    char data[500];
    struct node *next;
    struct node *prev;
};

struct node *createDLL(int n) {
    struct node *t = NULL, *f = NULL, *l = NULL;

    getchar();
    f = NEWNODE;
    printf("Enter data: ");
    fgets(f->data, sizeof(f->data), stdin);
    f->prev = NULL;
    f->next = NULL;
    l = f;

    for (int i = 2; i <= n; i++) {
        t = NEWNODE;
        printf("Enter data: ");
        fgets(t->data, sizeof(t->data), stdin);
        t->data[strcspn(t->data, "\n")] = '\0';
        l->next = t;
        t->prev = l;
        l = l->next;
    }
    l->next = NULL;
    return f;
}

void display(struct node *f) {
    struct node *t;

    if (f == NULL) {
        printf("\nNo Data is available");
        return;
    }

    printf("Entered data:\n");
    for (t = f; t != NULL; t = t->next) {
        printf("\n%s ", t->data);
    }
    printf("\n");
}

void find(struct node *f, char data[]) {
    struct node *t;
    int cnt = 0, i = 0;

    printf("'%s' is repeated at line no: ", data);

    for (t = f; t != NULL; t = t->next) {
        i++;

        if (strcmp(t->data, data) == 0) {
            cnt++;
            printf("%d ", i);
        }
    }

    if (cnt == 0) {
        printf("Not found in the list.\n");
    } else {
        printf("\nTotal occurrences of '%s': %d\n", data, cnt);
    }
}

int replace(struct node *f, char rd[], char tord[]) {
    struct node *t;
    int cnt = 0;

    for (t = f; t != NULL; t = t->next) {
        if (strcmp(t->data, tord) == 0) {
            strcpy(t->data, rd);
            cnt++;
        }
    }

    if (cnt == 0) {
        return -1;
    }
    return 0;
}

void count(struct node *f) {
    struct node *t;
    int cnt = 0;

    for (t = f; t != NULL; t = t->next) {
        cnt++;
    }
    printf("Number of Lines are %d\n", cnt);
}

struct node *eraseDLL(struct node *f) {
    struct node *t;

    t = f;
    while (f != NULL) {
        f = f->next;
        free(t);
        t = f;
    }
    return f;
}

struct node *insertDLL(struct node *f, int pos) {
    struct node *t, *s;

    t = NEWNODE;
    printf("\nEnter data you want to Insert: ");
    getchar(); // Consume the newline character from previous input
    fgets(t->data, sizeof(t->data), stdin);
    t->data[strcspn(t->data, "\n")] = '\0';
    t->prev = NULL;
    t->next = NULL;

    if (pos == 1) {
        t->next = f;
        f->prev = t;
        f = t;
        printf("\nData inserted\n");
        return f;
    } else {
        s = f;
        for (int i = 1; s != NULL && i <= pos - 2; i++) {
            s = s->next;
        }
        if (s == NULL) {
            printf("\nINVALID POS\n");
            return f;
        } else {
            t->next = s->next;
            t->prev = s;
            if (s->next != NULL)
                s->next->prev = t;
            s->next = t;
            printf("\nData Inserted successfully\n");
            return f;
        }
    }
}

struct node *deleteDLL(struct node *f, int loc) {
    struct node *t, *s;

    if (loc == 1) {
        t = f;
        f = f->next;
        free(t);
        if (f != NULL)
            f->prev = NULL;
        printf("\nData DELETED successfully\n");
        return f;
    } else {
        s = f;
        for (int i = 1; i <= loc - 2 && s != NULL; i++) {
            s = s->next;
        }
        if (s == NULL || s->next == NULL) {
            printf("\nInvalid location\n");
            return f;
        } else {
            t = s->next;
            s->next = t->next;
            if (t->next != NULL) {
                t->next->prev = s;
            }
            free(t);
            printf("\nData DELETED successfully\n");
            return f;
        }
    }
}

int main() {
    struct node *head = NULL;
    int n, pos, loc, choice;
    char data[100];
    char replaceData[100], toBeReplace[100];

    printf("Enter how many String data you want to store: ");
    scanf("%d", &n);

    while (1) {
        printf("\nPress 1 to ENTER data\nPress 2 to DISPLAY data\nPress 3 to INSERT data\nPress 4 to DELETE data\nPress 5 to FIND data\nPress 6 to REPLACE data\nPress 7 to LINE COUNT\nPress 0 to EXIT\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = createDLL(n);
                printf("\nData created successfully..!!!");
                break;

            case 2:
                display(head);
                break;

            case 3:
                if (head == NULL) {
                    printf("\nNo Data is available");
                    break;
                }
                printf("\nEnter position where you want to insert: ");
                scanf("%d", &pos);
                head = insertDLL(head, pos);
                break;

            case 4:
                if (head == NULL) {
                    printf("\nNo Data is available");
                    break;
                }
                printf("\nEnter position where you want to delete: ");
                scanf("%d", &loc);
                head = deleteDLL(head, loc);
                break;

            case 5:
                printf("\nEnter data to find: ");
                getchar(); // Consume the newline character from previous input
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                find(head, data);
                break;

            case 6:
                if (head == NULL) {
                    printf("\nNo data available..");
                    break;
                }
                printf("\nEnter data to add: ");
                getchar(); // Consume the newline character from previous input
                fgets(replaceData, sizeof(replaceData), stdin);
                replaceData[strcspn(replaceData, "\n")] = '\0';
                printf("\nEnter data you want to replace: ");
                fgets(toBeReplace, sizeof(toBeReplace), stdin);
                toBeReplace[strcspn(toBeReplace, "\n")] = '\0';
                int output = replace(head, replaceData, toBeReplace);
                if (output == -1) {
                    printf("\nData which has to be replaced NOT found...!!!");
                } else {
                    printf("\nData replaced successfully");
                }
                break;

            case 7:
                if (head == NULL) {
                    printf("\nNo data available..!!");
                    break;
                }
                count(head);
                break;

            case 0:
                head = eraseDLL(head);
                exit(0);

            default:
                printf("Invalid operation...!!!\n");
        }
    }

    return 0;
}
