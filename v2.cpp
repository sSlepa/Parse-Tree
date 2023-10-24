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

int main(){

    int n;
	char p[100005];
	char citire[100005];

	cin >> n;
    cin.get();
    for(int i = 1 ; i <= n ; ++i){

        for(int j = 1 ; j <= 400000 ; ++j)
            arb[j] = 0;

        verif[0] = 0;
        l = -1;

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

            //cout << nod << ' ';

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
                nod = nod / 2; /// Urc inapoi in radacina subarborelui curent
                
            }
            else if (p[i] == '=' || p[i] == '|' || p[i] == '&' || p[i] == '~'){
                arb[nod] = p[i];
                // Merg dreapta ca sa completez (stanga am pus deja)
                nod = nod * 2 + 1;
                
            }
            else if (p[i] == ')')
                if(nod / 2 != 0)
                    nod = nod / 2; /// Recursie spre radacina
                
            else if(p[i] == '!'){ /// nod de negare;;
                arb[nod] = '!';
                nod = nod * 2;
            }
        }

        /// Daca apare ? in forma poloneza inseamna ca propozitia nu e bine formata ->
        /// Are paranteze in plus/minus sau pozitionarea elementelor nu are sens in propozitie

        cout << i << '\n';
        preorder(1);
        cout << '\n';
        inorder(1);

        verif[++l] = 0;

        cout << verif << '\n';

        if(strcmp(verif,p) == 0)
            cout << "BINE FORMATA";
        else
            cout << "NU ESTE BINE FORMATA";

        cout << '\n' << '\n';
        
        //exit(0);

    }


     
    return 0;
}

/*
! - negatie
& - si
| - sau
~ - implica
= - echivalent

10
(((p ~ q) | s) = t)
(p ~ ((! q) & (s ~ t)))
(p ~ (q & (s ~ t)))
((p ~ ( q & (s ~ t))))
(!(b(!q)) & r) 
(p & ((!q) ^ (!(!(q = (!r))))))
((p | q) ~ !(p | q)) & (p | (!(!q)))
(((p | q) ~ !(p | q)) & (p | (!(!q))))
((p & q) | (p & (!q)) = p)


*/
