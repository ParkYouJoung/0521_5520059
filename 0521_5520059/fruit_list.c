#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����
typedef struct FruitNode {
    char name[50];
    struct FruitNode* next;
} FruitNode;

// ������ ���� ���
typedef struct DeletedFruitNode {
    char name[50];
    struct DeletedFruitNode* next;
} DeletedFruitNode;

// �� ���� �߰�
FruitNode* createFruitNode(const char* name) {
    FruitNode* newNode = (FruitNode*)malloc(sizeof(FruitNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// ������ ���� �߰�
DeletedFruitNode* createDeletedFruitNode(const char* name) {
    DeletedFruitNode* newNode = (DeletedFruitNode*)malloc(sizeof(DeletedFruitNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// �������� ���ο� ���� �߰�
void appendFruit(FruitNode** head, const char* name) {
    FruitNode* newNode = createFruitNode(name);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    FruitNode* temp = *head;
    while (temp->next != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("%s �̹� �ֽ��ϴ�.\n", name);
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    if (strcmp(temp->name, name) == 0) {
        printf("%s �̹� �ֽ��ϴ�.\n", name);
        free(newNode);
    }
    else {
        temp->next = newNode;
        printf("%s �߰��Ǿ����ϴ�.\n", name);
    }
}

// ����Ʈ�� �ִ� ������ ����
void deleteFruit(FruitNode** head, DeletedFruitNode** deletedHead, const char* name) {
    if (*head == NULL) {
        printf("%s ��Ͽ� �����ϴ�.\n", name);
        return;
    }

    FruitNode* temp = *head;
    FruitNode* prev = NULL;


    if (strcmp(temp->name, name) == 0) {
        *head = temp->next;
        DeletedFruitNode* deletedNode = createDeletedFruitNode(name);
        deletedNode->next = *deletedHead;
        *deletedHead = deletedNode;
        free(temp);
        printf("%s �߰��Ǿ����ϴ�.\n", name);
        return;
    }

    // ����Ʈ ���鼭 ������ ��� ã��
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // ��� ã��
    if (temp == NULL) {
        printf("%s ��Ͽ� �����ϴ�.\n", name);
        return;
    }

    // ��� ��ã��
    prev->next = temp->next;
    DeletedFruitNode* deletedNode = createDeletedFruitNode(name);
    deletedNode->next = *deletedHead;
    *deletedHead = deletedNode;
    free(temp);
    printf("%s �����Ǿ����ϴ�.\n", name);
}

// ������ ���� ��� ���
void printDeletedFruits(DeletedFruitNode* head) {
    if (head == NULL) {
        printf("������ ������ �����ϴ�.\n");
        return;
    }

    DeletedFruitNode* temp = head;
    printf("������ ����: ");
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

// ���� ���� ����Ʈ ���
void printFruitList(FruitNode* head) {
    if (head == NULL) {
        printf("���� ����� ����ֽ��ϴ�.\n");
        return;
    }

    FruitNode* temp = head;
    printf("���� ���� ���: ");
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

// �޸𸮸� ����
void freeFruitList(FruitNode* head) {
    FruitNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeDeletedFruitList(DeletedFruitNode* head) {
    DeletedFruitNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FruitNode* fruitList = NULL;
    DeletedFruitNode* deletedFruitList = NULL;

    // �ʱ� ���� ����Ʈ �߰�
    char* initialFruits[] = {
        "����", "������", "���", "����", "ü��",
        "�÷�", "���ƹ�", "�����", "�ٳ���", "������"
    };

    for (int i = 0; i < 10; i++) {
        appendFruit(&fruitList, initialFruits[i]);
    }

    int choice;
    char fruitName[50];

    do {
        printf("�޴�\n");
        printf("1. ����Ʈ �������� ���ο� ���� �߰��ϱ�\n");
        printf("2. ���� ����\n");
        printf("3. ������ ���� ��� ���\n");
        printf("4. ����\n");
        printf("�޴��� �����Ͻÿ�: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("�߰��� ������ �Է��ϼ���: ");
            scanf("%s", fruitName);
            appendFruit(&fruitList, fruitName);
            printFruitList(fruitList);
            break;
        case 2:
            printf("������ ������ �Է��ϼ���: ");
            scanf("%s", fruitName);
            deleteFruit(&fruitList, &deletedFruitList, fruitName);
            printFruitList(fruitList);
            break;
        case 3:
            printDeletedFruits(deletedFruitList);
            break;
        case 4:
            printf("����\n");
            break;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    } while (choice != 4);

    // �޸� ����
    freeFruitList(fruitList);
    freeDeletedFruitList(deletedFruitList);

    return 0;
}