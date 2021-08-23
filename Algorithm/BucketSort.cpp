#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <forward_list>

struct ListNode
{
    ListNode() :              value(0),         next_node(nullptr){}
    ListNode(int tmp_value) : value(tmp_value), next_node(nullptr){}

    ListNode(struct ListNode *node)
    {
        if (node != nullptr)
        {
            value     = node->value;
            next_node = node;
        }
    }

    int             value;
    struct ListNode *next_node;
};

constexpr int bucket_num = 10;

struct ListNode *insertNodeToList(struct ListNode *head, int value)
{
    struct ListNode *new_node = new struct ListNode(value);

    if (head == nullptr)
        return new_node;

    struct ListNode dummy_node(0);
    dummy_node.next_node      = head;
    struct ListNode *pre_node = &dummy_node;
    struct ListNode *cur_node = head;

    while (cur_node != nullptr && cur_node->value <= value)
    {
        pre_node = cur_node;
        cur_node = cur_node->next_node;
    }

    pre_node->next_node = new_node;
    new_node->next_node = cur_node;

    return dummy_node.next_node;
}

void mergeLists(std::vector<int> &vec, const std::vector<struct ListNode *> vec_nodes)
{
    vec.clear();

    for (size_t idx = 0; idx < vec_nodes.size(); ++idx)
    {
        struct ListNode *tmp = vec_nodes[idx];

        while (tmp != nullptr)
        {
            vec.emplace_back(tmp->value);
            tmp = tmp->next_node;
        }
    }
}

void BucketSort(std::vector<int> &vec)
{
    std::vector<struct ListNode *> vec_nodes(bucket_num, (struct ListNode *) (0));

    for(size_t idx = 0; idx < vec.size(); ++ idx)
    {
        int bucket_idx = vec[idx] / bucket_num;
        vec_nodes[bucket_idx] = insertNodeToList(vec_nodes[bucket_idx], vec[idx]);
    }

    std::cout << std::endl << "=====Bucket Sort List=====" << std::endl;
    for (size_t idx = 0; idx < vec_nodes.size(); ++idx)
    {
        struct ListNode *tmp = vec_nodes[idx];
        std::cout << "List " << idx << ": ";
        while (tmp != nullptr)
        {
            std::cout << tmp->value << "    ";
            tmp = tmp->next_node;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "=====Bucket Sort List=====" << std::endl;

    mergeLists(vec, vec_nodes);
}

int main()
{
    std::vector<int> vec;
    vec.resize(15);

    std::random_device rd;

    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = rd() % 99;
    }

    std::cout << "old: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    BucketSort(vec);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}
