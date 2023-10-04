#include <iostream>
#include <algorithm>
using namespace std;

const int rows=5;
const int cols=6;
string path[rows][cols]; 

int cost(int i,int j){
    static int weight[rows][cols]={
        {3,4,1,2,8,6},
        {6,1,8,2,7,4},
        {5,9,3,9,9,5},
        {8,4,1,3,2,6},
        {3,7,2,8,6,4}};
    //memo
    static int memo[rows][cols]; 
    if (memo[i][j] > 0) return memo[i][j]; 
    if(j == 0) { 
        path[i][j]= to_string(i); 
        return weight[i][0]; 
    }
    //recursion calls
    int left = cost(i , j - 1); 
    int up = cost( (rows + i - 1) % rows, j - 1); 
    int down = cost( (i + 1) % rows, j - 1);  
	//finding the minumum
    int minCost = min( min(left, up), down); 

    //place values in path based off of minCost value
    if(left == minCost) { 
        path[i][j]= path[i][j - 1] + to_string(i);  
    }
    else if(up == minCost) {
        path[i][j] = path[ (rows + (i - 1) ) % rows ][j - 1] + to_string(i);
    }
    else if(down == minCost){
        path[i][j] = path[ (i + 1) % rows ][j - 1] + to_string(i);
    }
    //add value to memo then return
    memo[i][j]= weight[i][j] + minCost; 
    return memo[i][j];
}

int main() {
    int ex[rows], minRow = 0;
    for(int i = 1; i < rows; i++){
        ex[i]=cost(i, cols - 1); 
        if(ex[i]< cost(minRow, cols - 1)) { 
            minRow = i; 
        }
    }
    cout<< "The shortest path is of the length: " << cost(minRow, cols - 1) << endl; 
    cout<< "The path of the shortest length is: "<< path[minRow][cols - 1];
    return 0; 
}