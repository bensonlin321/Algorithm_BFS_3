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

    // calculate how many connected component
    int number_of_island(std::vector< std::vector<int> > space) {

        // get the size of the room
        int m = space.size();
        if(m < 1) return -1; 
        int n = space[0].size();
        if(n < 1) return -1;

        int islands = 0, offsets[] = {0, 1, 0, -1, 0};

        // print the space
        for(int i = 0 ; i < m ; i++) {
            for(int j = 0 ; j < n ; j++) {
                printf("%d\t",space[i][j]);
            }
            printf("\n");
        }

        printf("===================================\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (space[i][j] == 1) {
                    islands++;
                    space[i][j] = 0;

                    // push the new postion
                    std::queue<std::pair<int, int>> todo;
                    todo.push({i, j});

                    // go through the neighbor position
                    while (!todo.empty()) {
                        std::pair<int, int> p = todo.front();
                        todo.pop();

                        // check the neighbor
                        for (int k = 0 ; k < 4 ; k++) {
                            int new_y = p.first + offsets[k];
                            int new_x = p.second + offsets[k + 1];
                            if (is_valid(space, new_y, new_x)) {
                                space[new_y][new_x] = 0;
                                // re-push the position into the queue
                                todo.push({new_y, new_x});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }

    bool is_valid(std::vector< std::vector<int> >& space, int& new_y, int& new_x) {
        int m = space.size();
        if(m < 1) return false; 
        int n = space[0].size();
        if(n < 1) return false;
        // not out of the space
        return new_y >= 0 && new_y < m && new_x >= 0 && new_x < n && space[new_y][new_x] == 1;
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