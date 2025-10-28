#include<bits/stdc++.h>
using namespace std;
const int INF=1e8;



int main(){
     vector<vector<int>> dist = {
        {0, 4, INF, 5, INF},
        {INF, 0, 1, INF, 6},
        {2, INF, 0, 3, INF},
        {INF, INF, 1, 0, 2},
        {1, INF, INF, 4, 0}
    };

    int v = dist.size();

      for(int k = 0; k < v ; k++){
        for(int i = 0; i < v ; i++){
            for(int j = 0; j < v ; j++){

                if(dist[i][j] != INF && dist[j][k] != INF){
                    dist[i][j] = min(dist[i][j], dist[i][k]+ dist[j][k]);
                }
            }
        }
    } 

     
    for(int i = 0; i<dist.size(); i++) {
        for(int j = 0; j<dist.size(); j++) {
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;

}