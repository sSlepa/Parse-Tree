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
#include <iomanip>
#include <list>
#include <sstream>
#include <functional>
#include <numeric>
#include <string>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace chrono;
using namespace __gnu_pbds;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define MOD 1000000007
#define MODC 984162946217979097
#define lsb(i) (i & -i)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define tup tuple<int,int,int>
#define ll long long
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> ost;

///__builtin_popcount(x)

ifstream cin("date.in");
ofstream cout("date.out");

char arb[400005];
char verif[100005]; 
int l = -1;

map<char,int> mapa;

vector<pair<char,int> > FND[1005],FNC[1005];
int pasFND = -1,pasFNC = -1;

void preorder(int nod){

    if(arb[nod] == '\0')
        return;

    cout << arb[nod] << ' ';

    preorder(nod * 2);
    preorder(nod * 2 + 1);

}
void inorder(int nod){

    if(arb[nod] == '\0')
        return;

    if(arb[nod * 2] == '\0' && arb[nod * 2 + 1] == '\0')
        verif[++l] = arb[nod];
    
    if(arb[nod] == '!'){

        verif[++l] = '(';
        verif[++l] = arb[nod];
        inorder(nod * 2);

        verif[++l] = ')';
    }

    else if(arb[nod * 2] != '\0' && arb[nod * 2 + 1] != '\0'){

        verif[++l] = '(';
    
        inorder(nod * 2);
        
        verif[++l] = arb[nod];

        inorder(nod * 2 + 1);

        verif[++l] = ')';

    }
}
int eval(int nod){

    if(arb[nod * 2] == 0 && arb[nod * 2 + 1] == 0)
        return mapa[arb[nod]];
    
    int valst;
    int valdr;

    if(arb[nod] != '!'){

        
        int valst = eval(nod * 2);
        int valdr = eval(nod * 2 + 1);

        if(arb[nod] == '&')
            return valst && valdr;
        
        else if(arb[nod] == '|')
            return valst || valdr;
        
        else if(arb[nod] == '=')
            return valst == valdr;

        else if(arb[nod] == '~'){
            if(valst == 1 && valdr == 0)
                return 0;
            else
                return 1;
        }
    }
    else{
    
        valst = eval(nod * 2);
        return !valst;  
    }
}

void afisare(const string &prefix, int nod, bool isLeft){
    
    if(arb[nod] != 0){
        if(nod != 1){
            cout << prefix << (isLeft ? "L|─── " : "R└── ");
            if(arb[nod] != '|')
                cout << arb[nod] << '\n';
            else
                cout << '/' << '\n';
                
        }
        else{
            cout << arb[nod];
            cout << " ───╷\n";
        }
    afisare(prefix + (isLeft ? " │   " : "    "),nod * 2, true);
    afisare(prefix + (isLeft ? " │   " : "    "),nod * 2 + 1, false);

    }
}

void FND_FNC(){

    cout <<'\n';
    cout << "Formula in FND : \n";
    for(int i = 0 ; i <= pasFND ; ++i){
        cout << "(";
        
        for(int j = 0 ; j < FND[i].size() ; ++j){
            if(FND[i][j].second == 1)
                cout << FND[i][j].first;
            else
                cout << "!" << FND[i][j].first;
            
            if(j != FND[i].size() - 1)
                cout << " & ";
        }

        cout << ")";
        if(i != pasFND)
            cout << " | ";
    } 

    cout << '\n' << '\n';
    cout << "Formula in FNC : \n";
    for(int i = 0 ; i <= pasFNC ; ++i){
        cout << "(";
        
        for(int j = 0 ; j < FNC[i].size() ; ++j){
            if(FNC[i][j].second == 1)
                cout << FNC[i][j].first;
            else
                cout << "!" << FNC[i][j].first;
            
            if(j != FNC[i].size() - 1)
                cout << " | ";
        }

        cout << ")";
        if(i != pasFNC)
            cout << " & ";
    }     
}

void verificareprop(){

    int Valida = 1,Nesatisfiabila,Satisfiabila = 0;

    int k = mapa.size();

    for(auto i : mapa)
        cout << i.first << ' ';
    
    cout << 'E';
    
    cout <<'\n';

    for(int msk = (1 << k) - 1 ; msk >= 0 ; --msk){

        int j = mapa.size() - 1;

        for(auto i : mapa)
            mapa[i.first] = (bool)((1 << j) & msk),j--;

        for(auto i : mapa)
            cout << i.second << ' ';

        bool val = eval(1);

        cout << val;

        if(val == 0)
            Valida = 0;
        else if(val == 1)
            Satisfiabila = 1;

        cout <<'\n';

        if(val){
            pasFND++;
            for(auto i : mapa)
                FND[pasFND].push_back({i.first,i.second});
        }
        else if(!val){
            pasFNC++;
            for(auto i : mapa)
                FNC[pasFNC].push_back({i.first,!i.second});
        }
    }   
    cout <<'\n';

    if(Valida == 1)
        cout << "VALIDA\n";
    else if(Valida == 0 && Satisfiabila == 0)
        cout << "NESATISFIABILA\n";
    else if(Valida == 0 && Satisfiabila == 1)
        cout << "SATISFIABILA\n";

    FND_FNC();

}
int main(){

    int n;
	char p[100005];
	char citire[100005];

    cin.getline(citire,100005);

    int j = 0;
    int k = -1;

    while(citire[j]){
        if(citire[j] != 32)
            p[++k] = citire[j];

        j++;
    }
    
    /// Problema are nevoie de parantezare corecta pentru a crea arborele corect
    
    p[++k] = 0;

    int nod = 1; 

    for(int i = 0; p[i] ; ++i){
        
        if(p[i] == '('){
            if(nod == 1)
                arb[nod] = '?';

            if((p[i + 1] >= 'a' && p[i + 1] <= 'z') || p[i + 1] == '('){ 
                arb[nod * 2] = '?';
                arb[nod * 2 + 1] = '?';
                nod = nod * 2; 
                    
            }
            else if (p[i + 1] == '!'){
                arb[nod] = '!';
                nod = nod * 2;
            }
        }
        if(p[i] >= 'a' && p[i] <= 'z'){ 
            arb[nod] = p[i];
            mapa[arb[nod]] = 1;
            nod = nod / 2;
                
        }
        else if (p[i] == '=' || p[i] == '|' || p[i] == '&' || p[i] == '~'){
            arb[nod] = p[i];
            
            nod = nod * 2 + 1;
        }
        else if (p[i] == ')')
            if(nod / 2 != 0) 
                nod = nod / 2; 
                
        else if(p[i] == '!'){ 
            arb[nod] = '!';
            nod = nod * 2;
        }
        
    }
    preorder(1);
    inorder(1);
    cout << '\n';

    verif[++l] = 0;

    cout << p << '\n';
    cout << verif << '\n'; 

    if(strcmp(verif,p) == 0){
        cout << "BINE FORMATA\n";
    
        cout << '\n';   

        afisare("",1,false);

        cout << '\n';

        verificareprop();
    }
    else
        cout << "NU ESTE BINE FORMATA";


    
    
    return 0;
}

/*

! - negatie
& - si
| - sau
~ - implica
= - echivalent


(((p ~ q) | s) = t)
((p ~ ( q & (s ~ t))))
(!(b(!q)) & r)
(p & ((!q) & (!(!(q = (!r))))))
((p | q) ~ !(p | q)) & (p | (!(!q)))
(((p | q) ~ (!(p | q))) & (p | (!(!q))))
(p ~ ((! q) & (s ~ t)))
(p ~ (q & (s ~ t)))
(((p | q) ~ !(p | q)) & (p | (!(!q))))
(((p & q) | (p & (!q))) = p)
((p & q) | (p & (!q)) = p)
((p=q)=(!(p~(!q))))
(!(p ~ (q & p)))
((p&(!q)) | (q ~ r))
((p & (!p)) ~ q)

((p~q) & ((!q) & (!p)))
((p ~ q) ~ ((q ~ s) ~ ((p | q) ~ r)))
((!(p~q)) = ((p | q) & ((!p) ~ q)))
((p = q) = (!(p ~ (!q))))

(((!r) | s) & ((!s) | r))
(((p & (!q)) & (!r)) | (!q))
(((p | q) & ((!p) | r)) ~ (q | r))
(((a & b) & (c & d)) & (e & f))

((!((!((r | (!q)) = (r ~ q))) & (q & (!r))) ) ~ q)

(((((p | q) | (!r)) & ((!p) | r)) & ((p | (!q)) | s)) & ((((!p) | (!q)) | (!r)) & (p | (!s))))

((((((!a) | (!b)) | c) & (a | d)) & (b | e)) & ((!f) & (((!g) | (!d)) | (!e))))

*/
