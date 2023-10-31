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

int level = 0;

void preorder(int nod,int niv){

    if(arb[nod] == '\0')
        return;

    level = max(level,niv);

    cout << arb[nod] << ' ';

    preorder(nod * 2,niv + 1);
    preorder(nod * 2 + 1,niv + 1);

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

    if(arb[nod * 2] == 0 && arb[nod * 2 + 1] == 0) /// Nod frunza, adica intoarcem interpretarea atomului
        return mapa[arb[nod]];
    
    int valst;
    int valdr;

    if(arb[nod] != '!'){

        int valst = eval(nod * 2);
        int valdr = eval(nod * 2 + 1);

        if(arb[nod] == '&'){
            if(valst && valdr)
                return 1;
            else
                return 0;
        }
        else if(arb[nod] == '|'){
            if(valst || valdr)
                return 1;
            else
                return 0;
        }
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
int main(){

    int n;
	char p[100005];
	char citire[100005];

    srand(time(0)); 

    /// Generez random 0 si 1 pentru interpretare
    /// Testez mai usor asa decat sa primesc input arbore, interpretare etc.
    /// Pun propozitia in arbore, de preferat una bine formata
    /// Si apoi evaluez expresia daca e bine formata

    cin.getline(citire,100005);

    int j = 0;
    int k = -1;

    while(citire[j]){
        if(citire[j] != 32)
            p[++k] = citire[j];

        j++;
    }
    /// Sterg spatiile sa fie mai usor de lucrat
    /// Problema are nevoie de parantezare corecta pentru a crea arborele corect
    /// Lipsa parantezarii sau parantezele in plus duc la crearea / lipsa nivelelor in arbore

    p[++k] = 0;

    int nod = 1;

    for(int i = 0; p[i] ; ++i){
        if(p[i] == '('){/// Merg in adancime cu nodurile
            if(nod == 1)
                arb[nod] = '?';

            if((p[i + 1] >= 'a' && p[i + 1] <= 'z') || p[i + 1] == '('){ /// Marchez posibile "valori" in adancime
                arb[nod * 2] = '?';
                arb[nod * 2 + 1] = '?';
                nod = nod * 2; /// Umplu ramura din stanga prima data
                    
            }
            else if (p[i + 1] == '!'){ /// Adaug nod de negatie
                arb[nod] = '!';
                nod = nod * 2;
            }
        }
        if(p[i] >= 'a' && p[i] <= 'z'){ /// Pun "valoarea propozitionala" in nod
            arb[nod] = p[i];
            mapa[arb[nod]] = rand() % 2;
            /// Aici generez 0 sau 1 random pentru prop atomice
        
            nod = nod / 2; /// Urc inapoi in radacina subarborelui curent
                
        }
        else if (p[i] == '=' || p[i] == '|' || p[i] == '&' || p[i] == '~'){
            arb[nod] = p[i];
            // Merg dreapta ca sa completez (stanga am pus deja)
            nod = nod * 2 + 1;
        }
        else if (p[i] == ')')
            if(nod / 2 != 0) /// Sa nu iesim din arbore
                nod = nod / 2; /// Recursie spre radacina
                
        else if(p[i] == '!'){ /// nod de negare;;
            arb[nod] = '!';
            nod = nod * 2;
        }
    }
    /// Daca apare ? in forma poloneza inseamna ca propozitia nu e bine formata ->
    /// Are paranteze in plus/minus sau pozitionarea elementelor nu are sens in propozitie
    preorder(1,0);
    inorder(1);
    cout << '\n';

    verif[++l] = 0;

    cout << p << '\n';
    cout << verif << '\n';

    if(strcmp(verif,p) == 0){
        cout << "BINE FORMATA\n";
    
        cout << '\n';   

        cout << "VALOAREA PROPOZITIEI : ";
        cout << eval(1);
        cout << '\n';
        cout << "INTERPRETAREA :\n";
        for(auto i : mapa)
            cout << i.first << ' ' << i.second << '\n';

        cout << '\n';
        cout << "ARBORELE CULCAT\n";
        afisare("",1,false);
        
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

14
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


*/
