#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Order {
    int id;
    char customer[100];
    int status;
    char total[50];
    struct Order *next;
    struct Order *prev;
} Order;

Order *head = NULL, *tail = NULL;

typedef struct DeliveredOrder {
    int id;
    char customer[100];
    char total[50];
    struct DeliveredOrder *next;
} DeliveredOrder;

DeliveredOrder *deliveredHead = NULL;

Order* createOrder() {
    Order *newOrder = (Order*)malloc(sizeof(Order));
    printf("Nhap ID: ");
    scanf("%d", &newOrder->id);
    getchar();
    printf("Nhap ten khach hang: ");
    fgets(newOrder->customer, 100, stdin);
    newOrder->customer[strcspn(newOrder->customer, "\n")] = '\0';
    printf("Nhap tong tien: ");
    fgets(newOrder->total, 50, stdin);
    newOrder->total[strcspn(newOrder->total, "\n")] = '\0';
    newOrder->status = 0;
    newOrder->next = newOrder->prev = NULL;
    return newOrder;
}
//Them don hang
void addOrder() {
    Order* newOrder = createOrder();
    if (!head) {
        head = tail = newOrder;

    }else {
        tail->next = newOrder;
        newOrder->prev = tail;
        tail = newOrder;
    }
    printf("Da them don hang \n ");
}
//Hien thi don hang
void displayOrders() {
    printf("\n---- Don hang CHUA GIAO ----\n");
    Order *cur = head;
    if (!cur) printf("Khong co don hang chua giao.\n");
    while (cur) {
        printf("ID: %d | Ten KH: %s | Tien: %s\n", cur->id, cur->customer, cur->total);
        cur = cur->next;
    }

    printf("\n---- Don hang DA GIAO ----\n");
    DeliveredOrder *d = deliveredHead;
    if (!d) printf("khong co don hang da giao.\n");
    while (d) {
        printf("ID: %d | Ten KH: %s | Tien: %s\n", d->id, d->customer, d->total);
        d = d->next;
    }
}
//Xoa don hang theo Id
void deleteOrder() {
    int id;
    printf("Nhap ID: ");
    scanf("%d", &id);
    Order *cur = head;
    while (cur && cur->id != id)
        cur = cur->next;
    if (!cur) {
        printf("Khong co don hang chua giao.\n");
        return;
    }
    if (cur->prev) cur->prev->next = cur->next;
    else head = cur->next;
    if (cur->next) cur->next->prev = cur->prev;
    else tail = cur->prev;

    free(cur);
    printf("da xoa don hang\n ");

}
//cap nhat thong tin ngan hang
void updateOrder() {
    int id;
    printf("nhap ID don hang can cap nhat: ");
    scanf("%d", &id);
    getchar();
    Order *cur = head;
    while (cur && cur->id != id)
        cur = cur->next;

    if (!cur) {
        printf("khong tim thay don hang.\n");
        return;
    }

    printf("Nhap ten moi: ");
    fgets(cur->customer, 100, stdin);
    cur->customer[strcspn(cur->customer, "\n")] = '\0';

    printf("Nhap tong tien moi: ");
    fgets(cur->total, 50, stdin);
    cur->total[strcspn(cur->total, "\n")] = '\0';

    printf(" Cap nhat thanh cong don hang\n");
}
//danh dau da giao
void markAsDelivered() {
    int id;
    printf("Nhap ID can danh dau da giao: ");
    scanf("%d", &id);
    Order *cur = head;

    while (cur && cur->id != id)
        cur = cur->next;

    if (!cur) {
        printf("khong tim thay don hang.\n");
        return;
    }

    DeliveredOrder *d = (DeliveredOrder*)malloc(sizeof(DeliveredOrder));
    d->id = cur->id;
    strcpy(d->customer, cur->customer);
    strcpy(d->total, cur->total);
    d->next = deliveredHead;
    deliveredHead = d;

    if (cur->prev) cur->prev->next = cur->next;
    else head = cur->next;
    if (cur->next) cur->next->prev = cur->prev;
    else tail = cur->prev;

    free(cur);
    printf(" Don hang da duoc danh dau la da giao\n");
}
//sap xep domn hang chua giao
int parseMoney(char *total) {
    return atoi(total);
}
void sortOrders() {
    if (!head) return;
    Order *i, *j;
    for (i = head; i->next; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (parseMoney(i->total) > parseMoney(j->total)) {
                int tmpID = i->id;
                char tmpCus[100], tmpTotal[50];
                strcpy(tmpCus, i->customer);
                strcpy(tmpTotal, i->total);

                i->id = j->id;
                strcpy(i->customer, j->customer);
                strcpy(i->total, j->total);

                j->id = tmpID;
                strcpy(j->customer, tmpCus);
                strcpy(j->total, tmpTotal);
            }
        }
    }
    printf(" Da sap xep theo tong tien tang dan\n");
}
//tim kiem don hang
    void searchOrder() {
        char name[100];
        getchar();
        printf("Nhap ten khach hang can tim: ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = '\0';

        int found = 0;
        Order *cur = head;
        while (cur) {
            if (strcasecmp(cur->customer, name) == 0) {
                printf("CHUA GIAO: ID: %d | Ten: %s | Tien: %s\n", cur->id, cur->customer, cur->total);
                found = 1;
            }
            cur = cur->next;
        }

        DeliveredOrder *d = deliveredHead;
        while (d) {
            if (strcasecmp(d->customer, name) == 0) {
                printf("DA GIAO: ID: %d | Ten: %s | Tien: %s\n", d->id, d->customer, d->total);
                found = 1;
            }
            d = d->next;
        }

        if (!found)
            printf("Khong tim thay don hang!\n");
    }

int main() {
    int choice;
    do {
        printf("\n ---- ORDER MANAGER ---- \n");
        printf("1. Them don hang\n");
        printf("2. Hien thi danh sach don hang\n");
        printf("3. Xoa don hang\n");
        printf("4. Cap nhat don hang\n");
        printf("5. Danh dau da giao\n");
        printf("6. Sap xep theo tong tien\n");
        printf("7. Tim kiem theo ten\n");
        printf("8. Thoat\n");
        printf("Lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addOrder();
                break;
            case 2:
                displayOrders();
                break;
            case 3:
                deleteOrder();
                break;
            case 4:
                updateOrder();
                break;
            case 5:
                markAsDelivered();
                break;
            case 6:
                sortOrders();
                break;
            case 7:
                searchOrder();
                break;
            case 8:
                printf("Thoat\n");
                break;
            default:
                printf(" Lua chon khong hop le\n");
        }

    } while (choice != 8);
    return 0;
}

