/* Descriptioin
Let S be a set of n integral points on the x-axis. For each given interval [a, b], you are asked to count the points lying inside.

Input
The first line contains two integers: n (size of S) and m (the number of queries).
The second line enumerates all the n points in S.
Each of the following m lines consists of two integers a and b and defines an query interval [a, b].

Output
The number of points in S lying inside each of the m query intervals.

Example
Input
5 2
1 3 7 9 11
4 6
7 12

Output
0
3

Restrictions
0 <= n, m <= 5 * 10^5
For each query interval [a, b], it is guaranteed that a <= b.
Points in S are distinct from each other.
Coordinates of each point as well as the query interval boundaries a and b are non-negative integers not greater than 10^7.
Time: 2 sec
Memory: 256 MB */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void merge(vector<int> &iSeq, const int &lo, const int &mid, const int &hi)
{
    int LB = mid - lo;
    int LC = hi - mid;
    vector<int> B(LB);
    for (int i = 0; i < LB; ++i)
        B[i] = iSeq[lo + i];
    for (int i = 0, j = 0, k = 0; j < LB || k < LC;)
    {
        if (j < LB && (LC <= k || B[j] <= iSeq[mid + k]))
            iSeq[lo + i++] = B[j++];
        if (k < LC && (LB <= j || iSeq[mid + k] < B[j]))
            iSeq[lo + i++] = iSeq[mid + k++];
    }
}

void mergeSimplified(vector<int> &iSeq, const int &lo, const int &mid, const int &hi)
{
    int LB = mid - lo;
    int LC = hi - mid;
    vector<int> B(LB);
    for (int i = 0; i < LB; ++i)
        B[i] = iSeq[lo + i];
    for (int i = 0, j = 0, k = 0; j < LB;)
    {
        if (k < LC && iSeq[mid + k] < B[j])
            iSeq[lo + i++] = iSeq[mid + k++];
        if (LC <= k || B[j] <= iSeq[mid + k])
            iSeq[lo + i++] = B[j++];
    }
}

void mergeSort(vector<int> &iSeq, const int &lo, const int &hi)
{
    if (hi - lo < 2)
        return;
    int mid = (lo + hi) >> 1;
    mergeSort(iSeq, lo, mid);
    mergeSort(iSeq, mid, hi);
    mergeSimplified(iSeq, lo, mid, hi);
}

int main()
{
    int length, query, tmp;
    cin >> length >> query;
    vector<int> iSeq;
    vector<int> result;
    for (int cnt = 1; cnt <= length; ++cnt)
    {
        cin >> tmp;
        iSeq.push_back(tmp);
    }
    mergeSort(iSeq, 0, length);
    for (auto c : iSeq)
        cout << c << " ";
    cout << endl;
    return 0;
}