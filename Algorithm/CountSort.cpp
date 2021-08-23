#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

void countSort(std::vector<int> &vec)
{
    if (vec.size() <= 1)
        return;

    int max_value = *max_element(vec.begin(), vec.end());

    std::vector<int> tmp_vec(max_value + 1);

    for (auto tmp : vec)
        ++tmp_vec[tmp];

    int orderly_idx = 0;
    for (size_t idx = 0; idx < tmp_vec.size(); ++idx)
    {
        while (tmp_vec[idx]-- > 0)
            vec[orderly_idx++] = idx;
    }
}

int main()
{
    std::vector<int> vec;
    vec.resize(15);

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

    countSort(vec);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}
