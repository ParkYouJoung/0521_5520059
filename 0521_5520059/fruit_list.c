#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 과일
typedef struct FruitNode {
    char name[50];
    struct FruitNode* next;
} FruitNode;

// 삭제된 과일 목록
typedef struct DeletedFruitNode {
    char name[50];
    struct DeletedFruitNode* next;
} DeletedFruitNode;

// 새 과일 추가
FruitNode* createFruitNode(const char* name) {
    FruitNode* newNode = (FruitNode*)malloc(sizeof(FruitNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// 삭제된 과일 추가
DeletedFruitNode* createDeletedFruitNode(const char* name) {
    DeletedFruitNode* newNode = (DeletedFruitNode*)malloc(sizeof(DeletedFruitNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// 마지막에 새로운 과일 추가
void appendFruit(FruitNode** head, const char* name) {
    FruitNode* newNode = createFruitNode(name);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    FruitNode* temp = *head;
    while (temp->next != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("%s 이미 있습니다.\n", name);
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    if (strcmp(temp->name, name) == 0) {
        printf("%s 이미 있습니다.\n", name);
        free(newNode);
    }
    else {
        temp->next = newNode;
        printf("%s 추가되었습니다.\n", name);
    }
}

// 리스트에 있는 과일을 삭제
void deleteFruit(FruitNode** head, DeletedFruitNode** deletedHead, const char* name) {
    if (*head == NULL) {
        printf("%s 목록에 없습니다.\n", name);
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
        printf("%s 추가되었습니다.\n", name);
        return;
    }

    // 리스트 돌면서 삭제할 노드 찾기
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // 노드 찾음
    if (temp == NULL) {
        printf("%s 목록에 없습니다.\n", name);
        return;
    }

    // 노드 못찾음
    prev->next = temp->next;
    DeletedFruitNode* deletedNode = createDeletedFruitNode(name);
    deletedNode->next = *deletedHead;
    *deletedHead = deletedNode;
    free(temp);
    printf("%s 삭제되었습니다.\n", name);
}

// 삭제된 과일 목록 출력
void printDeletedFruits(DeletedFruitNode* head) {
    if (head == NULL) {
        printf("삭제된 과일이 없습니다.\n");
        return;
    }

    DeletedFruitNode* temp = head;
    printf("삭제할 과일: ");
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 현재 과일 리스트 출력
void printFruitList(FruitNode* head) {
    if (head == NULL) {
        printf("과일 목록이 비어있습니다.\n");
        return;
    }

    FruitNode* temp = head;
    printf("현재 과일 목록: ");
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 메모리를 해제
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

    // 초기 과일 리스트 추가
    char* initialFruits[] = {
        "망고", "오렌지", "사과", "포도", "체리",
        "플럼", "구아바", "라즈베리", "바나나", "복숭아"
    };

    for (int i = 0; i < 10; i++) {
        appendFruit(&fruitList, initialFruits[i]);
    }

    int choice;
    char fruitName[50];

    do {
        printf("메뉴\n");
        printf("1. 리스트 마지막에 새로운 과일 추가하기\n");
        printf("2. 과일 삭제\n");
        printf("3. 삭제된 과일 목록 출력\n");
        printf("4. 종료\n");
        printf("메뉴를 선택하시오: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 과일을 입력하세요: ");
            scanf("%s", fruitName);
            appendFruit(&fruitList, fruitName);
            printFruitList(fruitList);
            break;
        case 2:
            printf("삭제할 과일을 입력하세요: ");
            scanf("%s", fruitName);
            deleteFruit(&fruitList, &deletedFruitList, fruitName);
            printFruitList(fruitList);
            break;
        case 3:
            printDeletedFruits(deletedFruitList);
            break;
        case 4:
            printf("종료\n");
            break;
        default:
            printf("잘못된 선택입니다.\n");
        }
    } while (choice != 4);

    // 메모리 해제
    freeFruitList(fruitList);
    freeDeletedFruitList(deletedFruitList);

    return 0;
}