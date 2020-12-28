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

int InputInteger();

void main() {
    RBRoot *root = NULL;
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
        for (int i = 0; str[i] != '\0'; i++) {
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
            int i = 0;
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
