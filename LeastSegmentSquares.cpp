#include <iostream>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

#define MAXN 16
#define INF numeric_limits<double>::infinity()
using namespace std;

struct Point {
    double x, y;
    bool operator < (const Point& that) const {
        return x < that.x;
    }
} points[MAXN + 1];

double err[MAXN][MAXN];

// OPT[0][j] is the optimal solution (minimum cost) for the points
double OPT[2][MAXN+1];


int GetInput(Point * A)
{
    string filename = "points.txt";
    ifstream myfile(filename);
    int index=0;
    if (myfile.is_open())
    {
        double next;
        while (myfile >> next)
        {
            Point p;
            p.x = next;
            myfile >> next;
            p.y = next;
            A[index] = p;
            index++;
        }
        myfile.close();
    }
    else{
        cout << "unable to find input file" <<endl;
        exit(1);
    }
return index;
}

double compute_a(int k, int n){

    double sum_xy = 0.0;
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_x_square = 0.0;

    for(int l=k; l<=n ;l++ ){
        sum_xy += (points[l].x * points[l].y);
        sum_x += points[l].x;
        sum_y += points[l].y;
        sum_x_square += (points[l].x * points[l].x);
    }

    double numerator = (n-k+1) * (sum_xy) - (sum_x*sum_y);
    double denominator =  ((n-k+1) * sum_x_square) - (sum_x * sum_x) ;
    //cout<< "numerator : " <<numerator <<endl;
    //cout<<"denominator: " <<denominator <<endl;

    return numerator / denominator;
}

double compute_b(int k, int n, double a){

    double  sum_y = 0.0;
    double sum_x = 0.0;
    for(int l=k; l<=n ;l++ ){
        sum_y += points[l].y;
        sum_x += points[l].x;
    }

    return (sum_y - a * sum_x)/(n-k+1);
}

double compute_error_values(int k, int n){

    double a = compute_a(k , n);
    double b = compute_b(k, n, a);
    double val = 0.0 ;
    for(int i = k ; i<=n ; i++){
        double res = points[i].y - (a * points[i].x + b);
        val += res * res;
    }

    return val;
}

//creating the err array
void createErrorArray( int n) {
    for (int l = 0; l < n; l++) {
        for (int m = 0; m < n; m++) {
            err[l][m] = 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || j == i + 1) err[i][j] = 0;
            else if (i > j) continue;
            else err[i][j] = compute_error_values(i, j);
        }
    }

}

//creating the OPT matrix based on the err array
void createOPT(int n){
    OPT[0][0] = OPT[0][1] = 0;
    OPT[1][0] = OPT[1][1] = INF;
    double min = INT_MAX;
    //using 1 as the segment penalty value
    int C = 1;
     for(int j=2 ; j <=n;j++){

         for(int i=1; i<j;i++){
             double val = err[i-1][j-1] + C + OPT[0][i];
             if(val < min){
                 min = val;
                 OPT[0][j] = min;
                 OPT[1][j] = i;
             }
         }
         min = INT_MAX;
     }

}

int main()	{

    int N = GetInput(points);

    createErrorArray(N);

    cout << "Error matrix :- "<<endl;
    for(int l = 0; l < N; l++)
    {
        for(int m = 0; m < N; m++)
        {
            cout << err[l][m] << " ";
        }
        cout << endl;
    }
    cout << endl;
    createOPT(N);

    cout << "OPT matrix :- "<<endl;
    for(int l = 0; l < 2; l++)
    {
        for(int m = 0; m <= N; m++)
        {
            cout << OPT[l][m] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout <<"Program Output :- " <<endl;
    cout << "j" << " " << "OPT(j)"<< " breakpoint (i)" <<endl;
    for(int m = 0; m <= N; m++)
    {
        for(int l = 0; l < 2; l++)
        {
            if (l == 0)
                cout << m << " " << OPT[l][m] << "      ";
            else cout << OPT[l][m];
        }
        cout << endl;
    }

    int max_val = OPT[1][N];
    double slope = compute_a(max_val-1, N-1);
    double intercept = compute_b(max_val-1, N-1, slope);
    cout << "line for segment " << max_val << " through " << N << " is y = " << slope<<"x + " << intercept<<endl;
    for(int j = N-1; j >= 2; j--){
        if(j == max_val) {
            max_val = OPT[1][j];
            slope = compute_a(max_val-1, j-1);
            intercept = compute_b(max_val-1, j-1, slope);
            cout << "line for segment " << max_val << " through " << j << " is y = " << slope<<"x + " << intercept<<endl;
        }
    }
    return 0;
}

