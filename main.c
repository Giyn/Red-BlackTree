/**
 * @filename main.c
 * @description Red-Black Tree test
 * @author ���Ԫ
 * @date 2020/12/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RedBlackTree.h"

void main() {
    int length_of_array, i;
    /* ������������� */
    srand((unsigned int)time(NULL));

    printf("������һ��������:");
    scanf("%d", &length_of_array);

    /* �Ա�����ʾ���鳤�� */
    int* const array = (int*)malloc(sizeof(int)*length_of_array);
    /* ����Ԫ��λ��1~100������ */
    for (i = 0; i < length_of_array; i++) array[i] = rand() % 100;

    RBRoot *root = createRBTree();
    printf("���ɵ�����Ϊ: ");
    for (i = 0; i < length_of_array; i++) {
        printf("%d ", array[i]);
        insertRBTree(root, array[i]);
    }

    printf("\nǰ������Ľ��: ");
    preorderRBTree(root);
    printf("\n��������Ľ��: ");
    inorderRBTree(root);
    printf("\n��������Ľ��: ");
    postorderRBTree(root);

    printf("\nɾ�����: [%d], [%d].", array[length_of_array / 2], array[length_of_array / 3]);
    deleteRBTree(root, array[length_of_array / 2]);
    deleteRBTree(root, array[length_of_array / 3]);

    printf("\nǰ������Ľ��: ");
    preorderRBTree(root);
    printf("\n��������Ľ��: ");
    inorderRBTree(root);
    printf("\n��������Ľ��: ");
    postorderRBTree(root);
}
