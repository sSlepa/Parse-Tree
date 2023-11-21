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
#define lsb (i & -i)
#define pii pair<int,int>
#define tup tuple<int,int,int>
#define ll long long
///__builtin_popcount(x)

ifstream cin("date.in");
ofstream cout("date.out");

char arb[400005];
char verif[100005]; 
int l = -1;

map<char,int> mapa;

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

void verificareprop(){

    int Valida = 1,Nesatisfiabila,Satisfiabila = 0;

    int k = mapa.size();

    for(auto i : mapa)
        cout << i.first << ' ';
    
    cout << 'E';
    
    cout <<'\n';

    for(int msk = 0 ; msk < (1 << k) ; ++msk){

        int j = 0;

        for(auto i : mapa)
            mapa[i.first] = (bool)((1 << j) & msk),j++;

        
        for(auto i : mapa)
            cout << i.second << ' ';

        bool val = eval(1);

        cout << val << ' ';

        if(val == 0)
            Valida = 0;
        else if(val == 1)
            Satisfiabila = 1;

        cout <<'\n';
  
    }   
    cout <<'\n';
    if(Valida == 1)
        cout << "VALIDA\n";
    else if(Valida == 0 && Satisfiabila == 0)
        cout << "NESATISFIABILA\n";
    else if(Valida == 0 && Satisfiabila == 1)
        cout << "SATISFIABILA\n";

}
int main(){

    int n;
	char p[100005];
	char citire[100005];

    //srand(time(0)); 

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



*/
