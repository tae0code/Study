#include<iostream>

using namespace std;
int map[10][10];
int paper[6] ={0,0,0,0,0,0};
int ans = 1e5;
bool checkMap(int x, int y, int c){
    if(x+c>10 || y+c>10) return false;
    for(int i=x; i<x+c; i++){
        for(int j=y; j<y+c; j++){
            if(map[i][j]==0) return false;
        }
    }
    return true;
}
void fillMap(int x, int y, int c, int v){
    for(int i=x; i<x+c; i++){
        for(int j=y; j<y+c; j++){
            map[i][j]=v;
        }
    }
}
void dfs(int x, int cnt){
    //입구 컷
    if(ans!=1e5 && cnt>=ans) return;
    for(int i=x; i<10; i++){
        for(int j=0; j<10; j++){
            //map탐색
            if(map[i][j]==1){
                int c=5;
                while(c!=0){
                    if(checkMap(i,j,c) && paper[c]!=5){ // 색종이 c*c로 채울 수 있다면, c사이즈 색종이의 여유가 있다면
                        fillMap(i,j,c,0); // 일단 채운다.
                        paper[c]++; // 해당 색종이 사용 count 올려주고
                        dfs(i, cnt+1); // 지금 위치에서 사용된 종이의 개수를 저장하고 탐색 시작
                        fillMap(i,j,c,1); // Map을 채우기 전으로 돌린다.
                        paper[c]--; // 사용한 색종이도 돌려놓고
                        // 다음으로 낮은 사이즈의 색종이로 채우는걸 생각해본다.
                    }
                    c--;
                }
                return;
            }
            if(i==j && i==9){ ans = cnt>=ans ? ans : cnt;}
        }
    }
}
int main(){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cin>>map[i][j];
        }
    }
    dfs(0,0);
    cout<<(ans==1e5?-1:ans)<<endl;
    return 0;
}
