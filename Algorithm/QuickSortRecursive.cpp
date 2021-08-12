#include <iostream>
#include <vector>
#include <random>

/*
    （小数，基准元素，大数）。在区间中随机挑选一个元素作基准，将小于基准的元素放在基准之前，大于基准的元素放在基准之后，再分别对小数区与大数区进行排序。
    快速排序思路：
    1. 选取第一个数为基准
    2. 将比基准小的数交换到前面，比基准大的数交换到后面
    3. 对左右区间重复第二步，直到各区间只有一个数
*/

template<typename T>
void quickSortRecursive(std::vector <T> &vec, int start, int end)
{
    if (end <= start)
        return;

    T key = vec[end];
    int left = start;
    int right = end - 1;

    while (right > left)
    {
        while (right > left && vec[left] <= key) ++left;
        while (right > left && vec[right] >= key) --right;

        std::swap(vec[left], vec[right]);
    }

    if (vec[left] > vec[end])
        std::swap(vec[left], vec[end]);
    else
        ++left;

    quickSortRecursive(vec, start, left - 1);
    quickSortRecursive(vec, left + 1, end);
}

int main()
{
    std::vector<float> vec{1.1, 3.2, 1.2, 23, 3.2, 12.3, 3.2, 5.4, 7, 3.2, 3.2, 3.2};

    std::default_random_engine e;
    std::uniform_real_distribution<float> u(0, 100);
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = u(e);
    }

    std::cout << "old: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    int len = vec.size() - 1;
    quickSortRecursive(vec, 0, len);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}