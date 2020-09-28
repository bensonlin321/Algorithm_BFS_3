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

class Solution1 {
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
    void number_of_island(std::vector< std::vector<int> > space) {

        // get the size of the room
        int m = space.size();
        if(m < 1) return; 
        int n = space[0].size();
        if(n < 1) return;

        // print the space
        std::vector<int> group_map;
        for(int i = 0 ; i < m ; i++) {
            for(int j = 0 ; j < n ; j++) {
                printf("%d\t",space[i][j]);
                group_map.push_back(NOT_CLASSIFY);
            }
            printf("\n");
        }

        // find all lands
        std::vector< std::pair<int, int> > lands_pos;
        for (int i = 0 ; i < m ; i++) {
            for (int j = 0 ; j < n ; j++){
                if (space[i][j] == LAND){
                    std::pair<int, int> pos;
                    pos.first  = i;
                    pos.second = j;
                    lands_pos.push_back(pos);
                }
            }
        }
        std::vector< std::pair<int, int> > neighbor_pair;
        // neighbor: up, down, left, right
        std::pair<int, int> up, down, left, right;
        up.first     =-1;
        up.second    = 0;
        down.first   = 1;
        down.second  = 0;
        left.first   = 0;
        left.second  =-1;
        right.first  = 0;
        right.second = 1;
        neighbor_pair.push_back(up);
        neighbor_pair.push_back(down);
        neighbor_pair.push_back(left);
        neighbor_pair.push_back(right);

        printf("===================================\n");
        int group = 1;
        std::vector<int> tmp_array;
        for (int l = 0 ; l < lands_pos.size() ; l++) {

            std::pair<int, int> candicate = lands_pos[l];
            int candicate_y = candicate.first;
            int candicate_x = candicate.second;
            int candicate_group = group_map[candicate_y*n + candicate_x];
            printf("current: [%d][%d], candicate_group:%d\n", candicate_y, candicate_x, candicate_group);

            if (candicate_group == NOT_CLASSIFY) {
                //printf("add new group \n");
                candicate_group = group;
                group_map[candicate_y*n + candicate_x] = candicate_group;
                group++;
            }

            // deal with up, down, lef, right
            // check if neighbor has group
            for (int k = 0 ; k < neighbor_pair.size(); k++) {
                int neighbor_y = neighbor_pair[k].first;
                int neighbor_x = neighbor_pair[k].second;
                int new_y = candicate_y + neighbor_y;
                int new_x = candicate_x + neighbor_x;
                std::pair<int, int> test_pair = {new_y, new_x};

                if(is_valid(test_pair, m, n)) {
                    if(space[new_y][new_x] == 1) {
                        printf("check neighbor:\n");
                        if(group_map[new_y*n + new_x] == NOT_CLASSIFY) {
                            group_map[new_y*n + new_x] = candicate_group;
                        }

                        if (candicate_group > group_map[new_y*n + new_x]) {
                            candicate_group = group_map[new_y*n + new_x];
                            group_map[candicate_y*n + candicate_x] = candicate_group;
                            printf("re-push {%d, %d}\n", candicate_y, candicate_x);
                            lands_pos.push_back({candicate_y, candicate_x});
                        }

                        if (candicate_group < group_map[new_y*n + new_x]) {
                            group_map[new_y*n + new_x] = candicate_group;
                            printf("re-push {%d, %d}\n", new_y, new_x);
                            lands_pos.push_back({new_y, new_x});
                        }
                        printf("[%d][%d] and [%d][%d] are the same group:%d\n",candicate_y, candicate_x, new_y, new_x, candicate_group);
                    }
                }
            }
        }
        show_group_map(m, n, group_map);
    }

    bool is_valid(std::pair<int, int>& cur, int& m, int& n) {
        // not out of the space
        return cur.first >= 0 && cur.first < m && cur.second >= 0 && cur.second < n;
    }
};

int main(int argc, char *argv[]) {
    //int m = atoi(argv[1]);
    //int n = atoi(argv[2]);
    Solution1 *s1 = new Solution1();
    std::vector< std::vector<int> > input;
    std::vector<int> a = {1,1,0,0,0};
    input.push_back(a);
    std::vector<int> b = {0,0,0,1,1};
    input.push_back(b);
    std::vector<int> c = {1,1,0,0,1};
    input.push_back(c);
    std::vector<int> d = {0,0,1,1,1};
    input.push_back(d);
    s1 -> number_of_island(input);
}