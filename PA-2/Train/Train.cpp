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

#include <iostream>

int main()
{
    long N, M;
    scanf("%ld %ld", &N, &M);
    long *inputOrder = new long[N];
    for (long i = 0; i != N; ++i)
        scanf("%ld", &inputOrder[i]);
    return 0;
}