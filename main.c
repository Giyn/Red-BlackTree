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
#include <Windows.h>
#include "HeaderFiles/RedBlackTree.h"
#include "HeaderFiles/RedBlackTreeUtils.h"

LARGE_INTEGER freq, begin, end;

void beginRecord();

double endRecord();

_Noreturn void menu();

int InputInteger();

void main()
{
    RBRoot *root = NULL;
    menu(root);
}

/**
 * �û������˵�
 *
 * @param[in]  root: the root of the red-black tree
 * @return  none
 */
_Noreturn void menu(RBRoot *root)
{
    int exist_flag = 0;  /* ��Ǻ�����Ƿ���� */
    while (true) {
        system("cls");
        printf("***********************************************************\n");
        printf("**                        �����                         **\n");
        printf("**                    ������: ���Ԫ                     **\n");
        printf("**                   ѧ��: 3119004757                    **\n");
        printf("**              �༶: �������ѧ�뼼��(1)��              **\n");
        printf("**              ��ϵ����: giyn.jy@gmail.com              **\n");
        printf("***********************************************************\n");
        printf("-----------------------------------------------------------\n");
        printf(">>> 1.��ʼ�������     7.����ָ�����������(1-2020)��� <<<\n");
        printf(">>> 2.��ӡ�������Ϣ   8.ǰ�����                       <<<\n");
        printf(">>> 3.���ٺ����       9.�������                       <<<\n");
        printf(">>> 4.ɾ�����        10.�������                       <<<\n");
        printf(">>> 5.������        11.����������С���             <<<\n");
        printf(">>> 6.���ҽ��        12.�˳�                           <<<\n");
        printf("-----------------------------------------------------------\n");
        if(exist_flag) {
            /* �԰��뷨�ķ�ʽʵʱ��ӡ����� */
            recessedPrintRBTree(root->node, 0);
            if (!root->node) printf("�����Ϊ��!\n");
        }
        else printf("�����ں����!\n");
        printf("-----------------------------------------------------------\n");
        printf(">>> ����������ִ�еĲ���:");

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
                    int delete_x;
                    printf("����������ɾ���Ľ��:");
                    delete_x = InputInteger();
                    if ((deleteRBTree(root, delete_x)) == SUCCESS) printf("ɾ�����ɹ�!\n");
                    else printf("ɾ�����ʧ��, �����ڸý��!\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 5:  /* ���� */
                if (exist_flag){
                    int insert_x;
                    Status insert_status;
                    double cost;
                    printf("�������������Ľ��:");
                    insert_x = InputInteger();
                    beginRecord();
                    insert_status = insertRBTree(root, insert_x);
                    cost = endRecord();
                    if (insert_status == SUCCESS) printf("������ɹ�!\n����ķ�ʱ��: %lf ms.\n", cost);
                    else printf("������ʧ��, �ý���Ѵ���!\n");
                }
                else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 6:  /* ���� */
                if (exist_flag) {
                    int search_x;
                    printf("������������ҵĽ��:");
                    search_x = InputInteger();
                    if ((recursiveSearchRBTree(root, search_x)) == SUCCESS) printf("���ҳɹ�, ���ڸý��!\n");
                    else printf("����ʧ��, �����ڸý��!\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 7:  /* �������ָ�������Ľ�� */
                if (exist_flag) {
                    /* ������������� */
                    srand((unsigned int) time(NULL));
                    printf("�������������Ľ������:");
                    int i, length_of_array;
                    length_of_array = InputInteger();
                    /* �Ա�����ʾ���鳤�� */
                    int *const array = (int *) malloc(sizeof(int) * length_of_array);
                    /* ����Ԫ��λ��1-2020������ */
                    for (i = 0; i < length_of_array; i++) array[i] = rand() % 2020;
                    printf("����Ľ��Ϊ: ");
                    for (i = 0; i < length_of_array; i++) {
                        printf("%d ", array[i]);
                        insertRBTree(root, array[i]);
                    }
                    printf("\n������ɹ�!\n");
                } else printf("�����ں����, ���ȳ�ʼ��!\n");
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
            case 11:
                if (exist_flag && root->node) {
                    RBTreeElemType *max = (RBTreeElemType *)malloc(sizeof(int));
                    RBTreeElemType *min = (RBTreeElemType *)malloc(sizeof(int));
                    maxRBTreeNode(root, max);
                    minRBTreeNode(root, min);
                    printf("����������Ϊ[%d], ��С���Ϊ[%d]!\n", *max, *min);
                } else if (!root->node) printf("�����Ϊ��!\n");
                else printf("�����ں����, ���ȳ�ʼ��!\n");
                break;
            case 12:  /* �˳����� */
                printf("Bye!");
                exit(0);
            default:
                printf("�����ڸ�ѡ��, ����������!\n");
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
int InputInteger()
{
    /* store converted numbers */
    int integer = 0;
    /* flag status */
    Status status = FALSE;
    /* receive string */
    char str[100];

    do {
        scanf("%s", str);
        status = TRUE;
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
            printf("����Ƿ�, ����������:");
            continue;
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

/**
 * ��ʼ��¼
 *
 * @param[in]  none
 * @return  none
 */
void beginRecord() {
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&begin);
}

/**
 * ֹͣ��¼
 *
 * @param[in]  none
 * @return  execution time of the program
 */
double endRecord() {
    QueryPerformanceCounter(&end);

    return (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart * 1000.0f;
}
