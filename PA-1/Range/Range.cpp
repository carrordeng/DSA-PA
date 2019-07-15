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

//using std::cin;
//using std::cout;
//using std::endl;

void merge(int *iSeq, const int &lo, const int &mid, const int &hi)
{
    int LB = mid - lo;
    int LC = hi - mid;
    int B[LB];
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

void mergeSimplified(int *iSeq, const int &lo, const int &mid, const int &hi)
{
    int LB = mid - lo;
    int LC = hi - mid;
    int B[LB];
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

void mergeSort(int *iSeq, const int &lo, const int &hi)
{
    if (hi - lo < 2)
        return;
    int mid = (lo + hi) >> 1;
    mergeSort(iSeq, lo, mid);
    mergeSort(iSeq, mid, hi);
    mergeSimplified(iSeq, lo, mid, hi);
}

int binSearch(const int *iSeq, const int &num, int lo, int hi)
{
    while (lo < hi)
    {
        int mid = (lo + hi) >> 1;
        num < iSeq[mid] ? hi = mid : lo = mid + 1;
    }
    return --lo;
}

int main()
{
    int length, query;
    scanf("%d %d", &length, &query);
    //cin >> length >> query;
    int iSeq[length], result[query];
    for (int cnt = 0; cnt != length; ++cnt)
        scanf("%d", &iSeq[cnt]);
        //cin >> iSeq[cnt];
    mergeSort(iSeq, 0, length);

    int lo, hi;
    for (int cnt = 0; cnt != query; ++cnt)
    {
        scanf("%d %d", &lo, &hi);
        //cin >> lo >> hi;
        int lo_rank = binSearch(iSeq, lo, 0, length);
        int hi_rank = binSearch(iSeq, hi, 0, length);
        if (lo_rank == -1)
            result[cnt] = hi_rank + 1;
        else
            result[cnt] = hi_rank - lo_rank + (lo == iSeq[lo_rank]);
    }
    for (auto c : result)
        printf("%d\n", c);
        //cout << c << endl;
    return 0;
}