#include <iostream>
#include <vector>
#include <random>


template<typename T>
void adjust(std::vector<T> &vec, size_t vec_len, size_t max_idx)
{
    if (vec.size() < vec_len)
    {
        return;
    }

    if (vec_len <= 1)
    {
        return;
    }

    if (vec_len == 2)
    {
        if (vec[0] < vec[1]) std::swap(vec[0], vec[1]);
        return;
    }

    size_t left        = 2 * max_idx + 1;
    size_t right       = 2 * max_idx + 2;
    size_t old_max_idx = max_idx;

    if (left > vec_len && right > vec_len)
    {
        return;
    }

    if (left  < vec_len && vec[left]  > vec[max_idx]) max_idx = left;
    if (right < vec_len && vec[right] > vec[max_idx]) max_idx = right;

    if (old_max_idx != max_idx)
    {
        std::swap(vec[old_max_idx], vec[max_idx]);
        adjust(vec, vec_len, max_idx);
    }
}

template<typename T>
void heapSort(std::vector<T> &vec)
{
    for (int idx = vec.size() / 2 - 1; idx >= 0; --idx)
    {
        adjust(vec, vec.size(), idx);
    }

    std::cout << "adjust: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    for (int idx = vec.size() - 1; idx >= 0; --idx)
    {
        std::swap(vec[idx], vec[0]);
        adjust(vec, idx, 0);
    }
}

int main()
{
    std::vector<int> vec = {8, 1, 14, 3, 21, 5, 7, 10};

    std::uniform_int_distribution<int> u(0, 20);
    std::default_random_engine e;

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

    heapSort<int>(vec);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;
    return 0;
}