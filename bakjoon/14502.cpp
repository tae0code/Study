#include<iostream>
#include<queue>

using namespace std;

int ans=0, N=0, M=0;
int MAP[10][10], COPY_MAP[10][10];
queue<pair<int, int> > virus_pos;
int N_MOVE[4] = {1,-1,0,0};
int M_MOVE[4] = {0,0,-1,1};
bool chkMapRange(int n, int m){
    return (n>=0 && n<N) &&(m>=0 && m<M);
}
void simulation(){
    int TEMP[10][10];
    memcpy(TEMP, COPY_MAP, sizeof(COPY_MAP));
    queue<pair<int, int> > virus_hist = virus_pos;
    while(!virus_hist.empty()){
        int n = virus_hist.front().first;
        int m = virus_hist.front().second;
        virus_hist.pop();
        for(int i=0; i<4; i++){
            n += N_MOVE[i];
            m += M_MOVE[i];
            if(chkMapRange(n,m) && TEMP[n][m]==0){
                TEMP[n][m] = 2;
                pair<int,int> p = make_pair(n,m);
                virus_hist.push(p);
            }
            n -= N_MOVE[i];
            m -= M_MOVE[i];
        }
    }
    int s = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(TEMP[i][j]==0) s++;
        }
    }
    ans = ans<s?s:ans;
}
void dfs(int wall){
    if(wall==3){
        simulation();
        return;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(COPY_MAP[i][j]==0){
                COPY_MAP[i][j]=1;
                dfs(wall+1);
                COPY_MAP[i][j]=0;
            }
        }
    }
}
int main(){
    cin>> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> MAP[i][j];
            pair<int,int> p = make_pair(i,j);
            if(MAP[i][j]==2) virus_pos.push(p) ;
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(MAP[i][j]==0){
                memcpy(COPY_MAP, MAP, sizeof(MAP));
                COPY_MAP[i][j]=1;
                dfs(1);
                COPY_MAP[i][j]=0;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}