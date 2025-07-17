#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 100

typedef struct Node {
    char url[MAX_URL];
    struct Node* next;
} Node;

Node* createNode(char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        strcpy(newNode->url, url);
        newNode->next = NULL;
    }
    return newNode;
}

void push(Node** top, char* url) {
    Node* newNode = createNode(url);
    if (newNode == NULL) {
        printf("khing the cap phat bo nho\n");
        return;
    }
    newNode->next = *top;
    *top = newNode;
}

char* top(Node* stack) {
    if (stack == NULL) return NULL;
    return stack->url;
}

char* pop(Node** top) {
    if (*top == NULL) return NULL;
    Node* temp = *top;
    char* url = (char*)malloc(MAX_URL * sizeof(char));
    strcpy(url, temp->url);
    *top = (*top)->next;
    free(temp);
    return url;
}

int isEmpty(Node* stack) {
    return stack == NULL;
}

void clearStack(Node** top) {
    while (!isEmpty(*top)) {
        Node* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

int main() {
    Node* backStack = NULL;
    Node* forwardStack = NULL;
    char current[MAX_URL] = "Trang chu";

    int choice;
    char url[MAX_URL];

    do {
        printf("\n----HISTORY WEB -----\n");
        printf("1. Truy cap trang mOi\n");
        printf("2. Quay lai (Back)\n");
        printf("3. Di toi (Forward)\n");
        printf("4. Hien thi trang hien tai\n");
        printf("5. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap URL trang moi: ");
                fgets(url, MAX_URL, stdin);
                url[strcspn(url, "\n")] = '\0';
                push(&backStack, current);
                strcpy(current, url);
                clearStack(&forwardStack);
                printf("Da chuyen den: %s\n", current);
                break;

            case 2:
                if (!isEmpty(backStack)) {
                    push(&forwardStack, current);
                    char* backURL = pop(&backStack);
                    strcpy(current, backURL);
                    free(backURL);
                    printf("da quay lai trang: %s\n", current);
                } else {
                    printf("khong the quay lai.\n");
                }
                break;

            case 3:
                if (!isEmpty(forwardStack)) {
                    push(&backStack, current);
                    char* forwardURL = pop(&forwardStack);
                    strcpy(current, forwardURL);
                    free(forwardURL);
                    printf("da di toi trang: %s\n", current);
                } else {
                    printf("khong the di toi trang.\n");
                }
                break;

            case 4:
                printf("Trang hien tai: %s\n", current);
                break;

            case 5:
                printf("Thoat\n");
                break;

            default:
                printf("Lua chon khong hop le\n");
                break;
        }
    } while (choice != 5);

    clearStack(&backStack);
    clearStack(&forwardStack);

    return 0;
}
