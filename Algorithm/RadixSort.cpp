#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

constexpr int bucket_num = 10;

void radixSort(std::vector<int> &vec)
{
    int exp = 1;
    int max = *max_element(vec.begin(), vec.end());

    while (max / exp > 0)
    {
        std::vector<std::vector<int>> bucket(10);

        for (size_t idx = 0; idx < vec.size(); ++idx)
            bucket[(vec[idx] / exp) % 10].push_back(vec[idx]);

        vec.clear();

        for (auto tmp_vec: bucket)
            for (auto tmp: tmp_vec)
                vec.push_back(tmp);

        exp *= 10;
    }
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

    radixSort(vec);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}
