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

struct nod{

	nod *st, *dr, *parinte;
	char val;
};

nod* radacina = NULL;

void adauga_st(nod*& poz, char val){

	nod* nou = new nod();

	nou->st = nou->dr = NULL;
	nou->val = '?';
	nou->parinte = poz;

	poz->st = nou;

}

void adauga_dr(nod* &poz, char val){

	nod* nou2 = new nod();

	nou2->st = nou2->dr = NULL;
	nou2->val = '?';
	nou2->parinte = poz;

	poz->dr = nou2;

}
void preorder(struct nod* node){

	if (node == NULL)
		return;

	cout << node->val << " ";

	preorder(node->st);
	preorder(node->dr);
}
void inorder(struct nod* node){

    if(node == nullptr)
        return;

    if(node->st == NULL && node->dr == NULL){
        cout << node->val;
        return;
    }    
    cout << '(';

    inorder(node->st);

    cout << node->val;

    inorder(node->dr);

    cout << ')';

}
// Crearea radacinii
void root(nod*& poz){

	nod* nou = new nod();
	nou->dr = nou->st = NULL;
	nou->val = '?';

	poz = radacina = nou;

}
// Functie pentru adaugarea nodului de negatie
void adauga_neg(nod*& poz){

	nod* nou = new nod();

	nou->st = NULL;
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

        p[++k] = 0;

        for(int i = 0; p[i] ; ++i){
            if(p[i] == '('){	
                if(radacina == NULL)
                    root(poz);

                if((p[i + 1] >= 'a' && p[i + 1] <= 'z') || p[i + 1] == '('){
                    adauga_st(poz, '?');
                    adauga_dr(poz, '?');
                    poz = poz->st;
                    
                }
                else if (p[i + 1] == '!'){
                    adauga_neg(poz);
                    poz->val = '!';
                    poz = poz->st;

                }
            }
            if(p[i] >= 'a' && p[i] <= 'z'){
                poz->val = p[i];
                // Daca introduc un literal, urc in sus
                poz = poz->parinte;
                
            }
            else if (p[i] == '=' || p[i] == '|' || p[i] == '&' || p[i] == '~'){
                poz->val = p[i];
                // Daca introduc un conector merg e celalalt fiu
                poz = poz->dr;
                
            }
            else if (p[i] == ')')
                if (poz->parinte != NULL){
                    //Daca dau de paranteza inchisa, urc in sus o pozitie
                    poz = poz->parinte;
                }
                else if (p[i] == '!'){
                    adauga_neg(poz);
                    poz->val = '!';
                    // Daca introduc o negatie, inserez un singur nod si ma plasez o pozitie in jos
                    poz = poz->st;
                }
        }
        preorder(radacina);
        cout << '\n';
        inorder(radacina);

        cout << '\n' << '\n';
        
    }

    
    
    
    

    return 0;
}


/*
! - negatie
& - si
| - sau
~ - implica
= - echivalent

*/
