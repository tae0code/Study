#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

int main(){
    int N;
    cin >> N;

    for(int i=0; i<N; i++){
        vector<vector<char> > v;
        v.push_back(vector<char>());
        v.push_back(vector<char>());
        v.push_back(vector<char>());
        int O=0;
        int X=0;
        for(int j=0; j<3; j++){
            for(int k=0; k<3; k++){
                char c;
                cin >> c;
                v.at(j).push_back(c);
                if(c=='O') O++;
                if(c=='X') X++;
            }
        }
        int BingoO = 0;
        int BingoX = 0;
        string msg;
        for(int j=0; j<3; j++){
            if(v.at(j).at(0)=='O' && v.at(j).at(1)=='O' && v.at(j).at(2)=='O') BingoO++;
            else if(v.at(j).at(0)=='X' && v.at(j).at(1)=='X' && v.at(j).at(2)=='X') BingoX++;
            for(int k=0; k<3; k++){
                if(v.at(0).at(k)=='O' && v.at(1).at(k)=='O' && v.at(2).at(k)=='O') BingoO++;
                else if(v.at(0).at(k)=='X' && v.at(1).at(k)=='X' && v.at(2).at(k)=='X') BingoX++;
            }
        }
        if(v.at(0).at(0)=='X'&&v.at(1).at(1)=='X'&&v.at(2).at(2)=='X') BingoX++;
        else if(v.at(0).at(0)=='O'&&v.at(1).at(1)=='O'&&v.at(2).at(2)=='O') BingoO++;
        if(v.at(0).at(2)=='X'&&v.at(1).at(1)=='X'&&v.at(2).at(0)=='X') BingoX++;
        else if(v.at(0).at(2)=='O'&&v.at(1).at(1)=='O'&&v.at(2).at(0)=='O') BingoO++;
        if(X-1==O){
            bool rule = (BingoO==0&&BingoX==0)||(BingoX>=1&&BingoO==0)||(X==5&&O==4&&BingoX==0&&BingoO==0);
            msg = rule ? "yes" : "no";
        } 
        else if(O==X){
            bool rule = (BingoO==0&&BingoX==0)||(BingoO>=1&&BingoX==0);
            msg = rule ? "yes" : "no";
        } 
        else msg = "no";
        cout<<msg<<endl;
    }
    return 0;
}