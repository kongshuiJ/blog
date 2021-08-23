#include <iostream>
#include <vector>
#include <random>

//template<typename T>
//void mergeSortRecursive(std::vector<T> &vec, int start, int end)
//{
//    if (start >= end)
//        return;
//
//    int start_bak = start;
//
//    int len = end - start;
//    int mid = (len >> 1) + start;
//
//    int start1 = start;
//    int end1   = mid;
//
//    int start2 = mid + 1;
//    int end2   = end;
//
//    mergeSortRecursive(vec, start1, end1);
//    mergeSortRecursive(vec, start2, end2);
//
//    std::vector<T> reg(vec.size());
//
//    while (start1 <= end1 && start2 <= end2)
//        reg[start_bak++] = vec[start1] > vec[start2] ? vec[start2++] : vec[start1++];
//
//    while (start1 <= end1)
//        reg[start_bak++] = vec[start1++];
//
//    while (start2 <= end2)
//        reg[start_bak++] = vec[start2++];
//
//    for (int idx = start; idx <= end; ++idx)
//        vec[idx] = reg[idx];
//}


template <typename T>
void mergeSortRecursive(std::vector<T> &vec, int start, int end)
{
    if (start >= end)
        return;

    int len       = end - start;
    int start_bak = start;
    int mid       = (len >> 1) + start;

    int left_start = start;
    int left_end   = mid;

    int right_start = mid + 1;
    int right_end   = end;

    mergeSortRecursive(vec, left_start,  left_end);
    mergeSortRecursive(vec, right_start, right_end);

    std::vector<T> reg(vec.size());

    while (left_start <= left_end && right_start <= right_end)
        reg[start_bak++] = vec[left_start] > vec[right_start] ? vec[right_start++] : vec[left_start++];

    while (left_start <= left_end)
        reg[start_bak++] = vec[left_start++];

    while (right_start <= right_end)
        reg[start_bak++] = vec[right_start++];

    for (int idx = start; idx <= end; ++idx)
        vec[idx] = reg[idx];
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

    mergeSortRecursive(vec, 0, vec.size() - 1);

    std::cout << "new: ";
    for (auto tmp: vec)
    {
        std::cout << tmp << "     ";
    }
    std::cout << std::endl;

    return 0;
}
