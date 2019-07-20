/* Description
Let's play the game Zuma!

There are a sequence of beads on a track at the right beginning.
All the beads are colored but no three adjacent ones are allowed to be with a same color.
You can then insert beads one by one into the sequence.
Once three (or more) beads with a same color become adjacent due to an insertion, they will vanish immediately.

Note that it is possible for such a case to happen for more than once for a single insertion.
You can't insert the next bead until all the eliminations have been done.

Given both the initial sequence and the insertion series,
you are now asked by the fans to provide a playback tool for replaying their games.
In other words, the sequence of beads after all possible eliminations as a result of each insertion should be calculated.


Input
The first line gives the initial bead sequence.
Namely, it is a string of capital letters from 'A' to 'Z',
where different letters correspond to beads with different colors.

The second line just consists of a single interger n,
i.e., the number of insertions.

The following n lines tell all the insertions in turn.
Each contains an integer k and a capital letter Σ,
giving the rank and the color of the next bead to be inserted respectively.
Specifically, k ranges from 0 to m when there are currently m beads on the track.


Output
n lines of capital letters, i.e., the evolutionary history of the bead sequence.

Specially, "-" stands for an empty sequence.


Example

Input
ACCBA
5
1 B
0 A
2 B
4 C
0 A

Output
ABCCBA
AABCCBA
AABBCCBA
-
A


Restrictions

0 <= n <= 10^4
0 <= length of the initial sequence <= 10^4
Time: 2 sec
Memory: 256 MB 

Hints
List*/

#include "ZumaList.h"
#include <iostream>
#include <string>

using std::string;

int main()
{
    string sequence;
    getline(std::cin, sequence);
    int loopNum;
    scanf("%d", &loopNum);
    ZumaList zuma = ZumaList(sequence);
    int pos;
    char colorCode;
    for (int cnt = 1; cnt <= loopNum; ++cnt)
    {
        scanf("%d %c", &pos, &colorCode);
        ListNode *currNode = zuma.insertAt(pos, colorCode);
        zuma.zumaDelete(currNode);
        zuma.print();
    }
    return 0;
}