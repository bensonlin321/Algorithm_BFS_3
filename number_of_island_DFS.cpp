#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#define LAND 1
#define WATER 0
#define NOT_CLASSIFY 0

class Solution {
public:

    void show_group_map(int m, int n, std::vector<int> group_map) {
        int maximum_group_value = 0;
        for (int i = 0 ; i < m; i++) {
            for(int j = 0 ; j < n; j++) {
                int group_value = group_map[i*n + j];
                printf("%d\t", group_value);
                if(maximum_group_value < group_value){
                    maximum_group_value = group_value;
                }
                if(j == n - 1){
                    printf("\n");
                }
            }
        }
        printf("number of island: %d\n",maximum_group_value);
    }

    int number_of_island(std::vector< std::vector<int> > space) {
        // get the size of the room
        int m = space.size();
        if(m < 1) return -1; 
        int n = space[0].size();
        if(n < 1) return -1;

        int islands = 0;
        // Go through all column and row. When meet the island, set the island to 0
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (space[i][j] == 1) {
                    islands++;
                    dfs(space, m, n, i, j);
                }
            }
        }
        
        return islands;
    }

    void dfs(std::vector< std::vector<int> >& space, const int& m, const int& n, const int& i, const int& j) {
        if(space[i][j] == 0)
            return;

        // set the island to 0 and check if the neighbor is 1
        space[i][j] = 0;
        if(i - 1 >= 0) { dfs(space, m, n, i-1, j); } // up
        if(i + 1 < m)  { dfs(space, m, n, i+1, j); } // down
        if(j - 1 >= 0) { dfs(space, m, n, i, j-1); } // left
        if(j + 1 < n)  { dfs(space, m, n, i, j+1); } // right
    }
};

int main(int argc, char *argv[]) {
    //int m = atoi(argv[1]);
    //int n = atoi(argv[2]);
    Solution *s = new Solution();
    std::vector< std::vector<int> > input;
    std::vector<int> a = {1,1,0,0,0};
    input.push_back(a);
    std::vector<int> b = {0,0,0,1,1};
    input.push_back(b);
    std::vector<int> c = {1,1,0,0,1};
    input.push_back(c);
    std::vector<int> d = {0,0,1,1,1};
    input.push_back(d);
    int islands = s -> number_of_island(input);
    printf("islands:%d\n", islands);
}