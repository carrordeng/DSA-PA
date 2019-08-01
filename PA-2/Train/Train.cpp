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

bool shuffleStack(const long &N, long const *targetOrder, Stack &stackOrigin, Stack &stackM, int *&opCode);

int main()
{
    long N, M;
    scanf("%ld %ld", &N, &M);
    long *targetOrder = new long[N];
    int *opCode = new int[2 * N]; //0:push, 1:pop
    Stack stackOrigin = Stack(N);
    Stack stackM = Stack(M);
    for (long i = 0; i != N; ++i)
    {
        scanf("%ld", &targetOrder[i]);
        stackOrigin.push(N - i);
    }
    if (shuffleStack(N, targetOrder, stackOrigin, stackM, opCode))
    {
        for (long i = 0; i != 2 * N; ++i)
            opCode ? printf("pop\n") : printf("push\n");
    }
    else
        printf("no\n");
    return 0;
}

bool shuffleStack(const long &N, long const *targetOrder, Stack &stackOrigin, Stack &stackM, int *&opCode)
{
    bool isFeasible = true;
    long opCnt = 0;
    long targetCnt = 0;
    stackM.push(stackOrigin.pop());
    opCode[opCnt++] = 0;
    while (isFeasible && !stackOrigin.isEmpty() && targetCnt < N)
    {
        if (targetOrder[targetCnt] < stackOrigin.top())
        {
            if (targetOrder[targetCnt] != stackM.top() || stackM.isEmpty())
                isFeasible = false;
            else
            {
                stackM.pop();
                opCode[opCnt++] = 1;
                targetCnt++;
            }
        }
        else
        {
            if (stackM.push(stackOrigin.pop()))
                opCode[opCnt++] = 0;
            else
                isFeasible = false;
        }
    }
    if (isFeasible && stackOrigin.isEmpty() && targetCnt == N - 1)
        return true;
    else
        return false;
}