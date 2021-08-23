#include <iostream>
#include <vector>
#include <random>

template<typename T>
void shellSort(std::vector<T> &vec)
{
    int len  = vec.size();
    int step = (vec.size() >> 1) + 1;

    while (step >= 1)
    {
        for (int idx = step; idx < len; ++idx)
        {
            for (int sub_idx = idx; sub_idx >= step; sub_idx -= step)
            {
                if (vec[sub_idx] < vec[sub_idx - step])
                    std::swap(vec[sub_idx], vec[sub_idx - step]);
            }
        }

        step = step >> 1;
    }
}

int main()
{
    std::vector<int> vec;
    vec.resize(9);

    std::random_device rd;

    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = rd() % 50;
    }

    std::cout << "old: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    shellSort(vec);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}
