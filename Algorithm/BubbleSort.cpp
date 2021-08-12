#include <iostream>
#include <vector>

template<typename T>
void BubbleSort(std::vector <T> &vec)
{
    size_t len = vec.size();
    bool orderly = false;

    for (size_t head_idx = 0; (head_idx < len - 1) && !orderly; ++head_idx)
    {
        orderly = true;
        for (size_t idx = 0; idx < len - 1 - head_idx; ++idx)
        {
            if (vec[idx] > vec[idx + 1])
            {
                orderly = false;
                std::swap(vec[idx], vec[idx + 1]);
            }
        }
    }
}

int main()
{
    std::vector<float> vec{4.1, 3.2, 1.2, 12.3, 5.4, 7, 23, 0.53, 5.2, 2, 6, 7, 4};

    BubbleSort<float>(vec);

    std::cout << "vec: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << ",";
    }
    std::cout << std::endl;

    return 0;
}