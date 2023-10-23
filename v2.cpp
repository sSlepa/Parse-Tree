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

char arb[10000005];

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

    if(arb[nod * 2] == '\0' && arb[nod * 2 + 1] == '\0'){
        if(arb[nod / 2] == '!')
            cout << '!' << arb[nod];
        else
            cout << arb[nod];
    }

    if(arb[nod * 2] != '\0' && arb[nod * 2 + 1] != '\0'){
        
        cout << '(';
    
        inorder(nod * 2);
        cout << arb[nod];

        inorder(nod * 2 + 1);

        cout << ')';
    }

}

int main(){

    int n;
	char p[100005];
	char citire[100005];

    for(int i = 1 ; i <= 10000000 ; ++i)
        arb[i] = 0;

	cin >> n;
    cin.get();
    for(int i = 1 ; i <= n ; ++i){

        cin.getline(citire,100005);

        int j = 0;
        int k = -1;

        while(citire[j]){
            if(citire[j] != 32)
                p[++k] = citire[j];

            j++;
        }
        /// Sterg spatiile sa fie mai usor de lucrat

        p[++k] = 0;

        int nod = 1;

        for(int i = 0; p[i] ; ++i){

            //cout << nod << ' ';

            if(p[i] == '('){	/// Merg in adancime cu nodurile
                arb[nod] = '?';

                if((p[i + 1] >= 'a' && p[i + 1] <= 'z') || p[i + 1] == '('){ /// Marchez posibile "valori" in adancime
                    arb[nod * 2] = '?';
                    arb[nod * 2 + 1] = '?';
                    nod = nod * 2; /// Umplu ramura din stanga prima data
                    
                }
                else if (p[i + 1] == '!'){ /// Adaug nod de negatie
                    arb[nod * 2] = '!';
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
                
                else if (p[i] == '!'){ /// nod de negare;;
                    arb[nod] = '!';
                    nod = nod * 2;
                }
        }

        /// Daca apare ? in forma poloneza inseamna ca propozitia nu e bine formata ->
        /// Are paranteze in plus sau pozitionarea elementelor nu are sens in propozitie
        preorder(1);
        cout << '\n';
        inorder(1);

        cout << '\n' << '\n';

        exit(0);

    }


     
    return 0;
}
