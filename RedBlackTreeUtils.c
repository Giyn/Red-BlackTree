/**
 * @filename RedBlackTreeUtils.c
 * @description Red-Black tree utils interface implementation
 * @author ���Ԫ
 * @date 2020/12/18
 */

#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree.h"
#include "BinarySearchTree.h"
#include "BalancedBinaryTree.h"

/**
 * ������������
 *
 * @param[in]  x     : the data of the node
 * @param[in]  parent: its parent node
 * @param[in]  left  : its left child node
 * @param[in]  right : its right child node
 * @return  the new red-black tree node pointer
 */
RBTree createRBTreeNode(RBTreeElemType x, Node *parent, Node *left, Node *right)
{
    RBTree node = (Node *) malloc(sizeof(Node));
    if (!node) return NULL;

    node->data = x;
    node->left = left;
    node->right = right;
    node->parent = parent;
    node->color = BLACK;

    return node;
}

/**
 * ��������������ƽ��
 *
 * @param[in]  root: the root of the red-black tree
 * @param[in]  node: the inserted node
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status RBTreeInsertSelfBalancing(RBRoot *root, Node *node)
{
    Node *parent, *grandparent;

    /* �����Ϊ��ɫ��� */
    while ((parent = RBTreeParent(node)) && RBTreeIsRed(parent)) {
        grandparent = RBTreeParent(parent);

        /* ��������游�������ӽ�㡱 */
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;

            /* �������Ǻ�ɫ��� */
            if (uncle && RBTreeIsRed(uncle)) {
                RBTreeSetBlack(parent);
                RBTreeSetBlack(uncle);
                RBTreeSetRed(grandparent);
                node = grandparent;
                continue;
            }

            /* �����㲻����, �Ҳ��������丸�������ӽ�� */
            if (node == parent->left) {
                RBTreeSetBlack(parent);
                RBTreeSetRed(grandparent);
                RBTreeRightRotate(root, grandparent);
            }

            /* �����㲻����, �Ҳ��������丸�����Һ��ӽ�� */
            if (node == parent->right) {
                Node *temp;
                RBTreeLeftRotate(root, parent);
                temp = parent;
                parent = node;
                node = temp;
            }
        } else { /* ��������游�����Һ��ӽ�㡱 */
            Node *uncle = grandparent->left;

            /* �������Ǻ�ɫ��� */
            if (uncle && RBTreeIsRed(uncle)) {
                RBTreeSetBlack(uncle);
                RBTreeSetBlack(parent);
                RBTreeSetRed(grandparent);
                node = grandparent;
                continue;
            }

            /* �����㲻����, �Ҳ��������丸�����Һ��ӽ�� */
            if (node == parent->right) {
                RBTreeSetBlack(parent);
                RBTreeSetRed(grandparent);
                RBTreeLeftRotate(root, grandparent);
            }

            /* �����㲻����, �Ҳ��������丸�������ӽ�� */
            if (node == parent->left) {
                Node *temp;
                RBTreeRightRotate(root, parent);
                temp = parent;
                parent = node;
                node = temp;
            }
        }
    }

    RBTreeSetBlack(root->node);

    return SUCCESS;
}

/**
 * �����������С���
 *
 * @param[in]  root  : the root of the red-black tree
 * @param[in]  minVal: the minimum value of the red-black tree
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status minRBTreeNode(RBRoot *root, RBTreeElemType *minVal)
{
    Node *node = NULL;

    if (root) node = minBinarySearchTreeNode(root->node);
    if (!node) return FAILED;

    *minVal = node->data;

    return SUCCESS;
}

/**
 * ��������������
 *
 * @param[in]  root  : the root of the red-black tree
 * @param[in]  maxVal: the maximum value of the red-black tree
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status maxRBTreeNode(RBRoot *root, RBTreeElemType *maxVal)
{
    Node *node = NULL;

    if (root) node = maxBinarySearchTreeNode(root->node);
    if (!node) return FAILED;

    *maxVal = node->data;

    return SUCCESS;
}

/**
 * �����ɾ��������ƽ��
 *
 * @param[in]  root  : the root of the red-black tree
 * @param[in]  node  : the deleted node
 * @param[in]  parent: the deleted node
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status RBTreeDeleteSelfBalancing(RBRoot *root, Node *node, Node *parent)
{
    Node *sibling = NULL;

    while ((!node || RBTreeIsBlack(node)) && node != root->node) {
        if (node == parent->left) {
            sibling = parent->right;
            /* node���ֵܽ��sibling�Ǻ�ɫ��� */
            if (RBTreeIsRed(sibling)) {
                RBTreeSetBlack(sibling);
                RBTreeSetRed(parent);
                RBTreeLeftRotate(root, parent);
                sibling = parent->right;
            }
            /* node���ֵܽ��sibling�Ǻ�ɫ���, sibling��2�����ӽ�㶼�Ǻ�ɫ��� */
            if ((!sibling->left || RBTreeIsBlack(sibling->left)) &&
                (!sibling->right || RBTreeIsBlack(sibling->right))) {
                RBTreeSetRed(sibling);
                node = parent;
                parent = RBTreeParent(node);
            } else {
                /* node���ֵܽ��sibling�Ǻ�ɫ���, sibling�������Ǻ�ɫ, �Һ����Ǻ�ɫ */
                if (!sibling->right || RBTreeIsBlack(sibling->right)) {
                    RBTreeSetRed(sibling);
                    RBTreeSetBlack(sibling->left);
                    RBTreeRightRotate(root, sibling);
                    sibling = parent->right;
                }
                /* node���ֵܽ��sibling�Ǻ�ɫ���, sibling��������������ɫ, �Һ����Ǻ�ɫ */
                RBTreeSetColor(sibling, RBTreeColor(parent));
                RBTreeSetBlack(parent);
                RBTreeSetBlack(sibling->right);
                RBTreeLeftRotate(root, parent);
                node = root->node;
                break;
            }
        } else {
            sibling = parent->left;
            /* node���ֵܽ��sibling�Ǻ�ɫ��� */
            if (RBTreeIsRed(sibling)) {
                RBTreeSetBlack(sibling);
                RBTreeSetRed(parent);
                RBTreeRightRotate(root, parent);
                sibling = parent->left;
            }
            /* node���ֵܽ��sibling�Ǻ�ɫ���, sibling��2�����ӽ�㶼�Ǻ�ɫ��� */
            if ((!sibling->left || RBTreeIsBlack(sibling->left)) &&
                (!sibling->right || RBTreeIsBlack(sibling->right))) {
                RBTreeSetRed(sibling);
                node = parent;
                parent = RBTreeParent(node);
            } else {
                /* node���ֵܽ��sibling�Ǻ�ɫ���, sibling�������Ǻ�ɫ, �Һ����Ǻ�ɫ */
                if (!sibling->left || RBTreeIsBlack(sibling->left)) {
                    RBTreeSetBlack(sibling->right);
                    RBTreeSetRed(sibling);
                    RBTreeLeftRotate(root, sibling);
                    sibling = parent->left;
                }
                /* node���ֵܽ��sibling�Ǻ�ɫ���, sibling��������������ɫ, �Һ����Ǻ�ɫ */
                RBTreeSetColor(sibling, RBTreeColor(parent));
                RBTreeSetBlack(parent);
                RBTreeSetBlack(sibling->left);
                RBTreeRightRotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node) RBTreeSetBlack(node);

    return SUCCESS;
}

/**
 * �����ɾ�����ָ��
 *
 * @param[in]  root: the root of the red-black tree
 * @param[in]  node: the deleted node
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status deleteRBTreeNode(RBRoot *root, Node *node)
{
    Node *child = NULL, *parent = NULL;
    int color;

    /* ɾ���������Һ��ӽ�㶼���� */
    if (node->left && node->right) {
        Node *replace = node;
        /* ������, ����̽�� */
        replace = replace->right;
        /* ��ȡ��С�ĺ�̽�� */
        while (replace->left) replace = replace->left;

        /* node��㲻�Ǹ���� */
        if (RBTreeParent(node)) {
            if (node == RBTreeParent(node)->left) RBTreeParent(node)->left = replace;
            else RBTreeParent(node)->right = replace;
        } else root->node = replace;  /* node����Ǹ���� */

        /* child����������Һ���, ������Ҫ��������λ�� */
        child = replace->right;
        /* ����������ĸ���� */
        parent = RBTreeParent(replace);
        /* �������������ɫ */
        color = RBTreeColor(replace);

        /* ��������ɾ�������Һ��ӽ�� */
        if (parent == node) parent = replace;
        else {
            if (child) RBTreeSetParent(child, parent);
            /* ��������Һ��ӽ����������λ��(�����㲻���������ӽ��, ��������Ǻ�̽��) */
            parent->left = child;
            replace->right = node->right;
            RBTreeSetParent(node->right, replace);
        }

        /* ��������� */
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        /* ������Ϊ��ɫ, ��Ҫ��ƽ�� */
        if (color == BLACK) RBTreeDeleteSelfBalancing(root, child, parent);
        free(node);

        return SUCCESS;
    }

    /* ɾ�����ֻ����һ�����ӽ�����û�к��ӽ�� */
    if (node->left) child = node->left;
    else child = node->right;
    parent = node->parent;
    color = node->color;
    if (child) child->parent = parent;

    /* node��㲻�Ǹ���� */
    if (parent) {
        if (node == parent->left) parent->left = child;
        else parent->right = child;
    } else root->node = child;

    if (color == BLACK) RBTreeDeleteSelfBalancing(root, child, parent);
    free(node);

    return SUCCESS;
}

/**
 * �������Ϣ�Ĵ�ӡ
 *
 * @param[in]  tree    : the node of the red-black tree
 * @param[in]  data    : the data of the node
 * @param[in]  position: 0 - the current node is the root node
 *                      -1 - the current node is the left child node
 *                       1 - the current node is the right child node
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status PrintRBTreeInfo(RBTree tree, RBTreeElemType data, int position)
{
    if (tree) {
        if (position == 0) printf("[%d] (��) �Ǹ��ڵ�\n", tree->data);
        else printf("[%d] (%s) �� [%d] �� {%s} ���ӽ��\n", tree->data, RBTreeIsRed(tree) ? "��" : "��",
                    data, position == -1 ? "��" : "��");

        PrintRBTreeInfo(tree->left, tree->data, -1);
        PrintRBTreeInfo(tree->right, tree->data, 1);

        return SUCCESS;
    }

    return FAILED;
}

/**
 * ���뷨��ӡ�����
 *
 * @param[in]  tree : the node of the red-black tree
 * @param[in]  depth: the depth of the red-black tree node
 * @return  the operation status, SUCCESS is 0, FAILED is -1
 */
Status recessedPrintRBTree(RBTree tree, int depth)
{
    if (!tree) return FAILED;
    recessedPrintRBTree(tree->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("[%-d(%s)]\n", tree->data, RBTreeIsRed(tree) ? "��" : "��");
    recessedPrintRBTree(tree->left, depth + 1);

    return SUCCESS;
}
