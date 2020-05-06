#include<stdlib.h>
#include<iostream>
#include<queue>
using namespace std;
static int N;
const int MAX = 16;
int MAP[MAX][MAX];
static int cnt = 0;
bool rangeChk(int r, int c){
    return r>=0&&c>=0&&r<N&&c<N;
}
int main(){
    cin >> N;
    vector<vector<int> > v;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> MAP[i][j];
        }
    }
    //초기 map에서 (1,1), (1,2)는 가로 형태의 파이프가 존재
    MAP[0][0] = 1;
    MAP[0][1] = 1;
    // 0 가로
    // 1 세로
    // 2 대각선
    int dr[] = {0,1,1};
    int dc[] = {1,0,1};
    queue<pair<pair<int, int>, int > > q;
    q.push(make_pair(make_pair(0,1),0));
    while(!q.empty()){
        int r = q.front().first.first;
        int c = q.front().first.second;
        int d = q.front().second;
        q.pop();
        if(r==N-1 && c==N-1){
            cnt++;
            continue;
        }
        for(int i=0; i<3; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(i==0 && d==1) continue;
            if(i==1 && d==0) continue;
            if(!rangeChk(nr, nc) || MAP[nr][nc]==1) continue;
            if(i==2 && (MAP[nr-1][nc]==1 || MAP[nr][nc-1]==1)) continue;
            q.push(make_pair(make_pair(nr, nc), i));
        }
    }
    cout<<cnt<<endl;
    return 0;
}
/*
void loopFunc(vector<vector<int> > v, int x, int y, char flag){
    if(x==N-1 && y==N-1){
        cnt++;
        return;
    }else if(x > N-1 && y > N-1){
        return;
    }
    // 가로
    if(y+1!=N && v.at(x).at(y+1)!=1 && flag != 'y'){
        //벡터 복사
        loopFunc(v, x, y+1, 'x');
    }
    // 세로
    if(x+1!=N && v.at(x+1).at(y)!=1 && flag != 'x'){
        //벡터 복사
        loopFunc(v, x+1, y, 'y');
    }
    // 대각선 
    if((x!=N-1 && y!=N-1) && (v.at(x).at(y+1) | v.at(x+1).at(y) | v.at(x+1).at(y+1))!=1){
        //벡터 복사
        loopFunc(v, x+1, y+1, 'c');
    }
}
*/