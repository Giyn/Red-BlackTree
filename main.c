/**
 * @filename main.c
 * @description Red-Black Tree test
 * @author ���Ԫ
 * @date 2020/12/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "RedBlackTree.h"

_Noreturn void menu();

int InputInteger();

void main() {
    RBRoot *root = NULL;
    menu(root);
}

/**
 * �û������˵�
 *
 * @param[in]  root: the root of the red-black tree
 * @return  none
 */
_Noreturn void menu(RBRoot *root) {
    int exist_flag = 0;
    int delete_x;
    int insert_x;
    int search_x;
    while (true) {
        system("cls");
        printf("\n\n\n");
        printf("-------------------------------\n");
        printf(">>> 1.��ʼ�������\n");
        printf(">>> 2.��ӡ�����\n");
        printf(">>> 3.���ٺ����\n");
        printf(">>> 4.ɾ�����\n");
        printf(">>> 5.������\n");
        printf(">>> 6.����ָ�����������(1-100)���\n");
        printf(">>> 7.���ҽ��\n");
        printf(">>> 8.ǰ�����\n");
        printf(">>> 9.�������\n");
        printf(">>> 10.�������\n");
        printf(">>> 11.�˳�\n");
        printf("-------------------------------\n");
        if(exist_flag) {
            inorderRBTree(root); /* ʵʱ��������� */
            printf("\n");
        }
        else printf("�����ں����!\n");
        printf("-------------------------------\n");
        printf("----->>> ����������ִ�еĲ���:");

        switch (InputInteger()) {
            case 1:  /* ��ʼ�� */
                root = createRBTree();
                exist_flag = 1;
                printf("��ʼ��������ɹ�!\n");
                break;
            case 2:  /* ��ӡ */
                if (exist_flag) printRBTree(root);
                else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 3:  /* ���� */
                if (exist_flag) {
                    destroyRBTree(root);
                    exist_flag = 0;
                    printf("���ٺ�����ɹ�!\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 4:  /* ɾ�� */
                if (exist_flag) {
                    printf("����������ɾ���Ľ��:");
                    delete_x = InputInteger();
                    if ((deleteRBTree(root, delete_x)) == OK) printf("ɾ�����ɹ�!\n");
                    else printf("ɾ�����ʧ��, �����ڸý��!\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 5:  /* ���� */
                if (exist_flag){
                    printf("�������������Ľ��:");
                    insert_x = InputInteger();
                    insertRBTree(root, insert_x);
                    printf("������ɹ�!\n");
                }
                else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 6:  /* �������ָ�������Ľ�� */
                if (exist_flag) {
                    /* ������������� */
                    srand((unsigned int) time(NULL));
                    printf("�������������Ľ������:");
                    int i, length_of_array;
                    length_of_array = InputInteger();
                    /* �Ա�����ʾ���鳤�� */
                    int *const array = (int *) malloc(sizeof(int) * length_of_array);
                    /* ����Ԫ��λ��1~100������ */
                    for (i = 0; i < length_of_array; i++) array[i] = rand() % 100;
                    printf("����Ľ��Ϊ: ");
                    for (i = 0; i < length_of_array; i++) {
                        printf("%d ", array[i]);
                        insertRBTree(root, array[i]);
                    }
                    printf("\n������ɹ�!\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 7:  /* ���� */
                if (exist_flag) {
                    printf("������������ҵĽ��:");
                    search_x = InputInteger();
                    if ((recursiveSearchRBTree(root, search_x)) == OK) printf("���ҳɹ�, ���ڸý��!\n");
                    else printf("����ʧ��, �����ڸý��!\n");
                }
                break;
            case 8:  /* ǰ����� */
                if (exist_flag) {
                    preorderRBTree(root);
                    printf("\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 9:  /* ������� */
                if (exist_flag) {
                    inorderRBTree(root);
                    printf("\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 10:  /* ������� */
                if (exist_flag) {
                    postorderRBTree(root);
                    printf("\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 11:  /* �˳����� */
                printf("�ټ�!");
                exit(0);
            default:
                break;
        }
        system("pause");
    }
}

/**
 * ����û���������
 *
 * @param[in]  none
 * @return  legal integer
 */
int InputInteger() {
    /* store converted numbers */
    int integer = 0;
    /* flag status */
    Status status = FALSE;
    /* receive string */
    char str[100];

    do {
        scanf("%s", str);
        status = SUCCESS;
        int i;
        for (i = 0; str[i] != '\0'; i++) {
            /* check for illegal characters */
            if (i == 0) {
                if (str[i] == '-' || str[i] == '+') continue;
            } else {
                if (str[i] < '0' || str[i] > '9') status = FALSE;
            }
        }
        if (status == FALSE) {
            printf("����Ƿ�, ����������!\n");
            break;
        } else {
            /* Convert string to number */
            for (i = 0, integer = 0; str[i] != '\0'; i++) {
                if (i == 0) {
                    if (str[i] == '-' || str[i] == '+') continue;
                    else {
                        integer *= 10;
                        integer += (str[i] - 48);
                    }
                } else {
                    integer *= 10;
                    integer += (str[i] - 48);
                }
            }
            if (str[0] == '-') integer = -integer;

            /* check if the number entered is out of bounds */
            if (i >= 10) {
                printf("���, ����������:");
                status = FALSE;
            }
        }
    } while (status == FALSE);

    return integer;
}
