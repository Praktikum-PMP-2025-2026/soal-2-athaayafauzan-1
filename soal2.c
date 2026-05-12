/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
 *   Modul               : Foundation of Algorithm
 *   Hari dan Tanggal    : Selasa, 12 Mei 2026
 *   Nama (NIM)          : Abdullah Athaaya Fauzan
 *   Nama File           : soal2.c
 *   Deskripsi           : Parade Istana ZigZag untuk cetak node per level dengan zigzag
 *   Menggunakan referensi dari geeksforgeeks (Level Order Transversal in C)
 */

#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* level(int arr[], struct Node* root, int i, int n){
    if (i<n){
        struct Node* temp = newNode(arr[i]);
        root = temp;
        root->left = level(arr, root->left, 2*i+1, n);
        root->right = level(arr, root->right, 2*i+2, n);
    }
    return root;
}

int height(struct Node* node){
    if (node == NULL) return 0;
    int leftheight = height(node->left);
    int rightheight = height(node->right);
    return (leftheight > rightheight)? (leftheight + 1) : (rightheight + 1);
}

void printGivenLevel(struct Node* root, int level, int direction, int* first){
    if (root == NULL) return;
    if (level == 0){
        if (!*first){
            printf(" ");
        }
        printf("%d", root->data);
        *first = 0;
    } else if (level > 0){
        if (direction == 0){ 
            printGivenLevel(root->left, level - 1, direction, first);
            printGivenLevel(root->right, level - 1, direction, first);
        } else{ 
            printGivenLevel(root->right, level - 1, direction, first);
            printGivenLevel(root->left, level - 1, direction, first);
        }
    }
}

void zigzag(struct Node* root){
    int h = height(root);
    for (int i = 0; i < h; i++){
        printf("LEVEL %d: ", i);
        int first = 1;
        printGivenLevel(root, i, i % 2, &first);
        printf("\n");
    }
}

int main(void){
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    struct Node* root = level(arr, NULL, 0, n);
    zigzag(root);

    return 0;
}
