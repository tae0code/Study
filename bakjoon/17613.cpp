#include<iostream>
#include<map>
#include<math.h>
using namespace std;
using Map = map<pair<int, int>, int>;
Map m;
int dp(int s, int e){
    if(s==0&&e==0) return 0;
    Map::iterator i = m.find({s,e});
    if(i!=m.end()) return i->second;
    int mm = 0;
    for(int i=1; i<=30; i++){
        int s_i = (1<<i)-1;
        if(s_i>e) break;
        int e_i = (s_i<<1);
        if(e_i<s) continue;
        int s_max = s_i>s ? s_i : s;
        int e_max = e_i>e ? e_i : e;
        mm = max(mm, dp(s_max-s_i, e_max-s_i)+i);
    }
    return m[{s,e}] = mm;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int x,y;
        cin>>x>>y;
        int ans = dp(x,y);
        m.clear();
        cout<<ans<<endl;
    }
    return 0;
}
