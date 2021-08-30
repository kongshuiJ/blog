//
// Created by kongshui on 8/24/21.
//

#include <iostream>
#include <vector>

typedef struct Node
{
    Node(int value) : key(value)
    {}

    bool operator=(const struct Node &tmp)
    {
        key = tmp.key;
        left_child = tmp.left_child;
        right_child = tmp.right_child;
    }


    int key;
    struct Node *left_child;
    struct Node *right_child;
} BSTNode;

bool searchBST(BSTNode *T, int key, BSTNode **pre_node, BSTNode **result_node)
{
    if (!T)
    {
        *result_node = *pre_node;
        return false;
    } else if (T->key == key)
    {
        *result_node = T;
        return true;
    } else if (T->key > key)
    {
        *pre_node = T;
        return searchBST(T->left_child, key, pre_node, result_node);
    } else if (T->key < key)
    {
        *pre_node = T;
        return searchBST(T->right_child, key, pre_node, result_node);
    }

    return true;
}

BSTNode *generateBST(const std::vector<int> &vec)
{
    if (vec.empty())
        return nullptr;

    BSTNode *root_node = new BSTNode(vec[0]);

    for (size_t idx = 1; idx < vec.size(); ++idx)
    {
        BSTNode *cur_node = new BSTNode(vec[idx]);
        BSTNode *pre_node = root_node;

        while (true)
        {
            if (cur_node->key <= pre_node->key)
            {
                if (!pre_node->left_child)
                {
                    pre_node->left_child = cur_node;
                    break;
                } else
                    pre_node = pre_node->left_child;
            } else if (cur_node->key > pre_node->key)
            {
                if (!pre_node->right_child)
                {
                    pre_node->right_child = cur_node;
                    break;
                } else
                    pre_node = pre_node->right_child;
            }
        }
    }

    return root_node;
}

void insertBST(BSTNode **root_node, int key)
{
    BSTNode *pre_node = nullptr;
    BSTNode *result_node = nullptr;

    if (searchBST(*root_node, key, &pre_node, &result_node))
        return;
    else
    {
        BSTNode *cur_node = new BSTNode(key);
        if (result_node && result_node->key <= key)
            result_node->right_child = cur_node;
        else if (result_node && result_node->key > key)
            result_node->left_child = cur_node;
    }
}

bool isLeftChild(BSTNode *parent_node, BSTNode *cur_node)
{
    if (parent_node->left_child && parent_node->left_child->key == cur_node->key)
        return true;
    return false;
}

bool isRightChild(BSTNode *parent_node, BSTNode *cur_node)
{
    if (parent_node->right_child && parent_node->right_child->key == cur_node->key)
        return true;
    return false;
}

//第三种情况:删除有两棵子树的节点
//思路:
//    需要先找到待删除的节点 targetNode
//    找到targetNode的父节点 parent
//    从targetNode的右子树中找到最小的节点
//    用一个临时变量,将最小的节点值保存在temp中
//    删除该最小的节点
//    targetNode.val = temp

bool deleteBST(BSTNode **root_node, int key)
{
    BSTNode *cur_node = nullptr;
    BSTNode *pre_node = nullptr;

    // not found key
    if (!searchBST(*root_node, key, &pre_node, &cur_node))
        return false;

    // not child
    if (!cur_node->left_child && !cur_node->right_child)
    {
        delete cur_node;
        cur_node = nullptr;
        return true;
    }
        // only have left child tree
    else if (!cur_node->right_child && cur_node->left_child)
    {
        if (isLeftChild(pre_node, cur_node))
            pre_node->left_child = cur_node->left_child;
        else
            pre_node->right_child = cur_node->left_child;

        delete cur_node;
        cur_node = nullptr;
        return true;
    }
        // only have right child tree
    else if (!cur_node->left_child && cur_node->right_child)
    {
        if (isLeftChild(pre_node, cur_node))
            pre_node->left_child = cur_node->left_child;
        else
            pre_node->right_child = cur_node->left_child;

        delete cur_node;
        cur_node = nullptr;
        return true;
    }


}

void clearBST(BSTNode **root_node)
{
    if (*root_node == nullptr)
        return;

    BSTNode *left_child = (*root_node)->left_child;
    BSTNode *right_child = (*root_node)->right_child;

    if (left_child)
        clearBST(&left_child);
    if (right_child)
        clearBST(&right_child);

    if (!left_child && !right_child)
    {
        delete *root_node;
        *root_node = nullptr;
    }
}

int main()
{
    std::vector<int> vec = {61, 87, 59, 47, 35, 73, 51, 98, 37, 93};

    BSTNode *root_node = generateBST(vec);
    BSTNode *pre_node = nullptr;
    BSTNode *tmp_node = nullptr;

    std::cout << searchBST(root_node, 93, &pre_node, &tmp_node) << std::endl;
    std::cout << tmp_node->key << std::endl;

//    int insert_key = 95;
//    insertBST(&root_node, insert_key);

    deleteBST(&root_node, 59);

    clearBST(&root_node);

    return 0;
}