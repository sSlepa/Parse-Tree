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

using namespace std;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define mod 1000000007
#define lsb (i & -i)
///__builtin_popcount(x)

ifstream cin("date.in");
ofstream cout("date.out");

struct nod{

	nod *st, *dr, *parinte;
	char val;
};

nod* radacina = nullptr;

void adauga_st(nod*& poz, char val){

	nod* nou = new nod();

	nou->st = nou->dr = nullptr;
	nou->val = '?';
	nou->parinte = poz;

	poz->st = nou;

}

void adauga_dr(nod* &poz, char val){

	nod* nou2 = new nod();

	nou2->st = nou2->dr = nullptr;
	nou2->val = '?';
	nou2->parinte = poz;

	poz->dr = nou2;

}
void preorder(struct nod* node){

	if (node == nullptr)
		return;

	cout << node->val << " ";

	preorder(node->st);
	preorder(node->dr);
    
}
void inorder(struct nod* node){

    if(node == nullptr)
        return;

    if(node->st == nullptr && node->dr == nullptr){
        if(node->parinte->val == '!')
            cout << '!' << node->val; 
        else
            cout << node->val;
        return;
    }    
    /// Afisare custom pentru negare ->
    /// Ar afisa p! in loc de !p daca nu se verifica

    cout << '(';

    inorder(node->st);

    if(node->val != '!')
        cout << node->val;

    inorder(node->dr);

    cout << ')';

}
void root(nod*& poz){

	nod* nou = new nod();
	nou->dr = nou->st = nullptr;
	nou->val = '?';

	poz = radacina = nou;

}
void adauga_neg(nod*& poz){

	nod* nou = new nod();

	nou->st = nullptr;
	poz->st = nou;
	nou->parinte = poz;
    
}

int main(){

    int n;
	char p[100005];
	char citire[100005];

	nod* poz = NULL;
	
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

        for(int i = 0; p[i] ; ++i){

            if(p[i] == '('){	/// Merg in adancime cu nodurile
                if(radacina == NULL)
                    root(poz);

                if((p[i + 1] >= 'a' && p[i + 1] <= 'z') || p[i + 1] == '('){ /// Marchez posibile "valori" in adancime
                    adauga_st(poz, '?');
                    adauga_dr(poz, '?');
                    poz = poz->st; /// Umplu ramura din stanga prima data
                    
                }
                else if (p[i + 1] == '!'){ /// Adaug nod de negatie
                    adauga_neg(poz);
                    poz->val = '!';
                    poz = poz->st; 

                }
            }
            if(p[i] >= 'a' && p[i] <= 'z'){ /// Pun "valoarea propozitionala" in nod
                poz->val = p[i];
                poz = poz->parinte; /// Urc inapoi in radacina subarborelui curent
                
            }
            else if (p[i] == '=' || p[i] == '|' || p[i] == '&' || p[i] == '~'){
                poz->val = p[i];
                // Merg dreapta ca sa completez (stanga am pus deja)
                poz = poz->dr;
                
            }
            else if (p[i] == ')')
                if(poz->parinte != NULL)
                    poz = poz->parinte; /// Recursie spre radacina
                
            else if (p[i] == '!'){ /// nod de negare;;
                adauga_neg(poz);
                poz->val = '!'; 
                poz = poz->st;
            }
        }

        /// Daca apare ? in forma poloneza inseamna ca propozitia nu e bine formata ->
        /// Are paranteze in plus sau pozitionarea elementelor nu are sens in propozitie
        cout << i << '\n';
        preorder(radacina);
        cout << '\n';
        inorder(radacina);

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

