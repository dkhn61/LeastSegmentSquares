Implemented the Least Square Curve-fitting algorithm in c++.
The program reads the input from the file called as the points.txt
and prints the segments in the optimal solution at console.

E.g. for points P consists of 6 points, as follows:
1.4 2.3
1.5 2.6
1.7 3.1
2.2 3.5
2.7 2.8
2.84 2.2

The actual program output is :-

j OPT(j) breakpoint i
0 0 -858993460
1 0 -858993460
2 1 1
3 1.00071 1
4 1.08013 1
5 1.65675 1
6 2.14021 4
line for segment 4 through 6 is y = -1.86396x + 7.64234
line for segment 1 through 4 is y = 1.42105x + 0.459211
