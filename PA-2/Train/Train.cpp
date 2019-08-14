/* judged regarding the feasibility.

Output
If the sequence is feasible, output the sequence.
“Push” means one compartment goes from A to S,
while “pop” means one compartment goes from S to B.
Each operation takes up one line.

If the sequence is infeasible, output a “no”.

Example 1

Input
5 2
1 2 3 5 4

Output
push
pop
push
pop
push
pop
push
push
pop
pop

Example 2

Input
5 5
3 1 2 4 5

Output
No

Restrictions
1 <= n <= 1,600,000
0 <= m <= 1,600,000
Time: 2 sec
Memory: 256 MB */

#include "Stack.h"
#include <iostream>

bool shuffleStack(const long &N, long const *B, Stack &A, Stack &station, int *&opCode);

int main()
{
    long N, M;
    scanf("%ld %ld", &N, &M);
    long *B = new long[N];
    int *opCode = new int[2 * N]; //0:push, 1:pop
    Stack A = Stack(N);
    Stack station = Stack(M);
    for (long i = 0; i != N; ++i)
    {
        scanf("%ld", &B[i]);
        A.push(N - i);
    }
    if (shuffleStack(N, B, A, station, opCode))
    {
        for (long i = 0; i != 2 * N; ++i)
            opCode[i] ? printf("pop\n") : printf("push\n");
    }
    else
        printf("No\n");
    return 0;
}

bool shuffleStack(const long &N, long const *B, Stack &A, Stack &station, int *&opCode)
{
    bool isFeasible = true;
    long opCnt = 0;
    long BCnt = 0;
    station.push(A.pop());
    opCode[opCnt++] = 0;
    while (isFeasible && BCnt < N)
    {
        if (B[BCnt] < A.top() || A.isEmpty())
        {
            if (B[BCnt] == station.top())
            {
                station.pop();
                opCode[opCnt++] = 1;
                BCnt++;
            }
            else
                isFeasible = false;
        }
        else if(B[BCnt] == A.top())
        {
            if (station.push(A.pop()))
            {
                opCode[opCnt++] = 0;
                station.pop();
                opCode[opCnt++] = 1;
                BCnt++;
            }
            else
                isFeasible = false;
        }
        else
        {
            if (station.push(A.pop()))
                opCode[opCnt++] = 0;
            else
                isFeasible = false;
        }
    }
    return isFeasible;
}