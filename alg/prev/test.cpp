#include<stdio.h>
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;


int maxs = 0;
void dfs(vector<int>& heights, int bricks, int ladders, int cur) {
    if (bricks==0 && ladders==0 && heights[cur+1] > heights[cur]) {
        maxs = max(maxs, cur);
        return;
    }
    for (int i = cur; i < heights.size(); ++i) {
        if (bricks<=0 && ladders<=0 && heights[i+1] > heights[i]) {
            maxs = max(maxs, i);
            return;
        } 
        cout<<i<<" "<<ladders<<" "<<bricks<<" "<<heights[i+1] <<" "<<heights[i]<<endl;
        if (heights[i+1] > heights[i]) {
            cout<<"choose one"<<endl;

            if (ladders > 0) {
                cout<<"use lander "<<ladders<<" "<<ladders-1<<endl;
                dfs(heights, bricks, ladders-1, i+1);
            }
            if (bricks >= (heights[i+1]- heights[i])) {
                cout<<"use brick"<<endl;
                dfs(heights, bricks - (heights[i+1]- heights[i]), ladders, i+1);   
            }
            if (ladders == 0 && bricks<(heights[i+1]- heights[i])) {
                maxs = max(maxs, i);
                cout<<"return"<<endl;
                return;
            }
                
        } else cur = i+1;
    }
    cout<<cur<<endl;
}

int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    dfs(heights, bricks, ladders, 0);
    return maxs;
}
int main() {
    int a[] = {4,2,7,6,9,14,12};
    vector<int> heights(a, a+7);
    int bricks=5, ladders=1;
    furthestBuilding(heights, bricks, ladders);
}