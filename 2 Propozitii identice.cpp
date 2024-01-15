#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <stack>
#include <unordered_map>
#include <map>
#include <cmath>
#include <chrono>
#include <set>

using namespace std;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define mod 1000000007
#define lsb(i) (i & -i)
#define pii pair<int,int>
#define tup tuple<int,int,int>
#define ll long long
///__builtin_popcount(x)

ifstream cin("date.in");
ofstream cout("date.out");

int n;
string a,b;
int p;
map<char,int> m;

int check(string a,string b, map<char,int>& m){

    for(auto i : a)
        if(isalpha(i))
            m[i] = 1;

    for(auto i : b)
        if(isalpha(i))
            if(m.find(i) == m.end())
                return 0;
        else
            m[i] = 0;

    for(auto i : m)
        if(i.second != 0)
            return 0;

    return m.size();

}

int eval(string s);
int termen(string s);
int xr(string s);
int AND(string s);

int eval(string s){

    int ans = xr(s),t;

    while(s[p] == '|'){
        p++;
        t = xr(s);
        ans = (ans | t);
    }
    return ans;

}
int xr(string s){

    int ans = AND(s),t;

    while(s[p] == '^'){

        p++;
        t = AND(s);
        ans = (ans ^ t);

    }
    return ans;

}
int AND(string s){

    int ans = termen(s),t;
    while(s[p] == '&'){
        p++;
        t = termen(s);
        ans = (ans & t);
    }
    return ans;

}
int termen(string s){

    int semn = 0;
    int ans = 0;
    while(s[p] == '~'){
        semn = !semn;
        p++;
    }
    
    if(s[p] == '('){
        p++;
        ans += eval(s);
        p++;
        if(semn)
            return !ans;
        
        return ans;
    }
    ans = m[s[p]];
    p++;

    if(semn)
        return !ans;

    return ans;

}

int main(){

    cin >> n;
    for(int i = 1 ; i <= n ; ++i){
        cin >> a >> b;
        m.clear();
        int k = check(a,b,m);
        if(k){
            int ok = 1;        
            for(int j = 0 ; j < (1 << k) ; ++j){
                int poz = 0;
                for(auto it : m)
                    m[it.first] = (bool)((1 << poz) & j),poz++;

                p = 0;
                int val1 = eval(a);

                p = 0;
                int val2 = eval(b);
                
                if(val1 != val2){
                    ok = 0;
                    break;
                }
                
            }
            if(ok)
                cout << "egale\n";
            else
                cout << "diferite\n";
            
        }
        else
            cout << "diferite\n";
        
        
    }
 
 
 
    return 0;
}
