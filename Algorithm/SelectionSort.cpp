#include <iostream>
#include <vector>

/*
    选择排序思路：
    1. 在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
    2. 从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾
    3. 以此类推，直到所有元素均排序完毕
*/

template<typename T>
void SelectionSort(std::vector <T> &vec)
{
    size_t len = vec.size();

    for (size_t left_idx = 0; left_idx < len - 1; ++left_idx)
    {
        size_t min_idx = left_idx;

        for (size_t right_idx = left_idx + 1; right_idx < len; ++right_idx)
        {
            if (vec[min_idx] > vec[right_idx])
            {
                min_idx = right_idx;
            }
        }

        if (min_idx != left_idx)
        {
            std::swap(vec[min_idx], vec[left_idx]);
        }
    }
}

int main()
{
    std::vector<float> vec{4.1, 3.2, 1.2, 12.3, 5.4, 7, 23, 0.53, 5.2, 2, 6, 7, 4};

    SelectionSort<float>(vec);

    std::cout << "vec: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}