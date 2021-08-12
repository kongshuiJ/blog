#include <iostream>
#include <vector>
#include <random>

/*
    （有序区，无序区）。把无序区的第一个元素插入到有序区的合适的位置。对数组：比较得少，换得多。

    插入排序思路：
    1. 从第一个元素开始，该元素可以认为已经被排序
    2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
    3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
    4. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
    5. 将新元素插入到该位置后
    6. 重复步骤2~5
*/

template<typename T>
void insertSort(std::vector <T> &vec)
{
    if (vec.size() <= 1)
        return;

    for (size_t idx = 1; idx < vec.size(); ++idx)
    {
        T temp = vec[idx];

        for (size_t orderly_idx = idx - 1; orderly_idx >= 0; --orderly_idx)
        {
            if (vec[orderly_idx] > temp)
            {
                vec[orderly_idx + 1] = vec[orderly_idx];
                vec[orderly_idx] = temp;
            } else
                break;
        }
    }
}

int main()
{
    std::vector<float> vec{1.1, 3.2, 1.2, 23, 3.2, 12.3, 3.2, 5.4, 7, 3.2, 3.2, 3.2};

    std::default_random_engine e;
    std::uniform_real_distribution<float> u(0, 30);
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
    insertSort(vec);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}