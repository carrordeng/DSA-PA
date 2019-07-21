/* Description
As shown in the following figure,
If another lighthouse is in gray area, they can beacon each other.

For example, in following figure,
(B, R) is a pair of lighthouse which can beacon each other,
while (B, G), (R, G) are NOT.

Input
1st line: N
2nd ~ (N + 1)th line: each line is X Y, means a lighthouse is on the point (X, Y).

Output
How many pairs of lighthourses can beacon each other
( For every lighthouses, X coordinates won't be the same,
Y coordinates won't be the same )

Example

Input
3
2 2
4 3
5 1

Output
1

Restrictions
For 90% test cases: 1 <= n <= 3 * 105
For 95% test cases: 1 <= n <= 106
For all test cases: 1 <= n <= 4 * 106
For every lighthouses, X coordinates won't be the same,
Y coordinates won't be the same.

1 <= x, y <= 10^8

Time: 2 sec

Memory: 256 MB

Hints
The range of int is usually [-231, 231 - 1],
it may be too small. */

#include <iostream>

void mergeSort(long *coordX, long *coordY, const long &lo, const long &hi);
void merge(long *coordX, long *coordY, const long &lo, const long &mid, const long &hi);
long pairInside(long *coordY, const long &lo, const long &hi);
long pairBetween(long *coordY, const long &lo, const long &mid, const long &hi);

int main()
{
    long N;
    scanf("%ld", &N);
    long *coordX = new long[N];
    long *coordY = new long[N];
    for (long i = 0; i != N; ++i)
        scanf("%ld %ld", &coordX[i], &coordY[i]);
    mergeSort(coordX, coordY, 0, N);
    printf("%ld", pairInside(coordY, 0, N));
    delete[] coordX;
    delete[] coordY;
    return 0;
}

void mergeSort(long *coordX, long *coordY, const long &lo, const long &hi)
{
    if (hi - lo < 2)
        return;
    long mid = (lo + hi) >> 1;
    mergeSort(coordX, coordY, lo, mid);
    mergeSort(coordX, coordY, mid, hi);
    merge(coordX, coordY, lo, mid, hi);
}

void merge(long *coordX, long *coordY, const long &lo, const long &mid, const long &hi)
{
    long lenB = mid - lo;
    long lenC = hi - mid;
    long *XB = new long[lenB];
    long *YB = new long[lenB];
    for (long i = 0; i != lenB; ++i)
    {
        XB[i] = coordX[lo + i];
        YB[i] = coordY[lo + i];
    }
    for (long itA = 0, itB = 0, itC = 0; itB != lenB;)
    {
        if (itC < lenC && coordX[mid + itC] < XB[itB])
        {
            coordX[lo + itA] = coordX[mid + itC];
            coordY[lo + itA++] = coordY[mid + itC++];
        }
        if (itC >= lenC || XB[itB] <= coordX[mid + itC])
        {
            coordX[lo + itA] = XB[itB];
            coordY[lo + itA++] = YB[itB++];
        }
    }
    delete[] XB;
    delete[] YB;
}

long pairInside(long *coordY, const long &lo, const long &hi)
{
    if (hi - lo < 2)
        return 0;
    long mid = (hi + lo) >> 1;
    long cntLeft = pairInside(coordY, lo, mid);
    long cntRight = pairInside(coordY, mid, hi);
    return cntLeft + cntRight + pairBetween(coordY, lo, mid, hi);
}

long pairBetween(long *coordY, const long &lo, const long &mid, const long &hi)
{
    long lenB = mid - lo;
    long lenC = hi - mid;
    long *YB = new long[lenB];
    long pairCnt = 0;
    for (long itB = 0; itB != lenB; ++itB)
        YB[itB] = coordY[lo + itB];
    for (long itA = 0, itB = 0, itC = 0; itB != lenB;)
    {
        if (itC < lenC && coordY[mid + itC] < YB[itB])
            coordY[lo + itA++] = coordY[mid + itC++];
        if (itC == lenC || YB[itB] <= coordY[mid + itC])
        {
            coordY[lo + itA++] = YB[itB++];
            pairCnt += lenC - itC;
        }
    }
    delete[] YB;
    return pairCnt;
}