#include <iostream>
#include <vector>
using namespace std;
 
int N;
vector<int> v;
vector<int> visited;
vector<int> ans;
void dfs(int s,int c){
    
    if(visited[c]){
        if(c==s)
            ans.push_back(s);
    }else{
        visited[c]++;
        dfs(s,v[c]);
    }
    
}
int main(){
    
    cin>>N;
    cout<<(1?"A":"B")<<endl;
    v = vector<int> (N+1,0);
    visited = vector<int> (N+1,0);
 
    for(int i=1;i<=N;i++){
        int t;
        cin >> t;
        v[i] = t;
    }
    
    for(int i=1;i<=N;i++){
        dfs(i,i);
        visited = vector<int> (N+1,0);
    }
    
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
 
