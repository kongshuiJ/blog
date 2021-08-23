#include <iostream>
#include <vector>
#include <random>

template<typename T>
void quickSortRecursive(std::vector<T> &vec, size_t start, size_t end)
{
    if (start >= end)
        return;

    if (start > vec.size() || end > vec.size())
        return;

    if (vec.size() < 2)
        return;
    
    else if (vec.size() == 2)
    {
        if (vec[0] > vec[1])
            std::swap(vec[0], vec[1]);
    }

    T key     = vec[end];
    int left  = start;
    int right = end - 1;

    while (right > left)
    {
        while (left < right && vec[left]  <= key) ++left;
        while (left < right && vec[right] >= key) --right;

        std::swap(vec[left], vec[right]);
    }

    if (vec[left] > vec[end])
        std::swap(vec[left], vec[end]);
    else
        ++left;

    quickSortRecursive(vec, start,    left - 1);
    quickSortRecursive(vec, left + 1, end);
}

int main()
{
    std::vector<int> vec;
    vec.resize(10);

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

    quickSortRecursive(vec, 0, vec.size() - 1);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;
    return 0;
}
