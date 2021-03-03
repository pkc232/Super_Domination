# Super_Domination

The dynamic programming algorithm for finding Super Domination number of a tree is implemented in super_domination_dp.cpp.


The first line contains the number of vertices (n), followed by n-1 edges representing the tree.

Eg.
Sample Input:

    4
    1 2 
    1 3 
    3 4

Sample Output:

    Calling function for 1

    Calling function for 2

    After finishing function call for 2:
    Vertex  0U      0S      1F      1R      1B
    1       NULL    NULL    NULL    NULL    NULL
    2       0       INF     1       INF     INF
    3       NULL    NULL    NULL    NULL    NULL
    4       NULL    NULL    NULL    NULL    NULL

    Calling function for 3

    Calling function for 4

    After finishing function call for 4:
    Vertex  0U      0S      1F      1R      1B
    1       NULL    NULL    NULL    NULL    NULL
    2       0       INF     1       INF     INF
    3       NULL    NULL    NULL    NULL    NULL
    4       0       INF     1       INF     INF

    After finishing function call for 3:
    Vertex  0U      0S      1F      1R      1B
    1       NULL    NULL    NULL    NULL    NULL
    2       0       INF     1       INF     INF
    3       INF     1       2       1       INF
    4       0       INF     1       INF     INF

    After finishing function call for 1:
    Vertex  0U      0S      1F      1R      1B
    1       INF     2       3       2       3
    2       0       INF     1       INF     INF
    3       INF     1       2       1       INF
    4       0       INF     1       INF     INF

    Time taken by function: 22015 microseconds
    Super domination number = 2
