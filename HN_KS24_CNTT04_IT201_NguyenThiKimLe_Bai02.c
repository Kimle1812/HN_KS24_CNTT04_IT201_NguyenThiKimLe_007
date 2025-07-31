#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    char english[100];
    char vietnamese[100];
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char vietnamese[], char english[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode -> vietnamese, vietnamese);
    strcpy(newNode -> english, english);
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

//Hàm thêm từ mới vào cây
Node* addNode(Node* root, char vietnamese[], char english[]) {
    Node* newNode = createNode(vietnamese,english);
    if ( root == NULL) {
        return newNode;
    }else if (strcmp(vietnamese, root -> vietnamese) < 0) {
        root -> left = addNode(root -> left, vietnamese, english);

    }else if (strcmp(vietnamese, root -> vietnamese) > 0) {
        root -> right = addNode(root -> right, vietnamese, english);
    } else {
        printf("Tu da ton tai\n");
        return root;
    }
    return root;
}
void printPostOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    printPostOrder(root -> left);
    printPostOrder(root -> right);
    printf("Vietnamese: %s\n", root -> vietnamese);
    printf("English: %s\n", root -> english);
}
//hàm tra nghĩa tiếng anh sang tiếng việt
 void translate(Node* root, char english[]) {
    if (root == NULL) {
        return;
    }
    if (strcmp (english, root -> english) == 0) {
        printf("Nghia Tieng Viet: %s\n", root ->vietnamese);
        return;
    }else {
        translate(root->left, english);
        translate(root->right, english);
    }
    printf("Khong co tu muon tim\n");
    return;
}
//Hàm cập nhập từ tiếng anh cũ
void update(Node* root, char english[]) {
    if (root == NULL) {
        return;
    }
    if (strcmp(english, root -> english) == 0) {
        printf("Nhap nghia Tieng  Viet moi: ");
        scanf("%s", root -> vietnamese);
        return;
    }
    update(root -> left, english);
    update(root -> right, english);
}
int main() {
    Node* root = NULL;
    int choice;
    do {
        printf("=====MENU=====\n");
        printf("1. Them tu\n");
        printf("2. Tra nghia\n");
        printf("3. Hien thi\n");
        printf("4. Cap nhap\n");
        printf("5. Thoat\n");
        printf("Moi nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                char vietnamese[100];
                char english[100];
                printf("Nhap Tieng Viet: ");
                scanf("%s", vietnamese);
                printf("Nhap Tieng Anh: ");
                scanf("%s", english);
                root = addNode(root, vietnamese, english);
                break;
            case 2:
                char search[100];
                fflush(stdin);
                printf("Nhap tu Tieng Anh muon tra nghia: ");
                scanf("%s", search);
                translate(root, search);
                break;
            case 3:
                printPostOrder(root);
                break;
            case 4:
                char updateWord[100];
                printf("Nhap tu tieng Anh muon cap nhap: ");
                scanf("%s", updateWord);
                update(root, updateWord);
                break;
            case 5:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }while (choice != 5);
}