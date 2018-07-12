// fonctions.hpp

#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <iostream>
using namespace std;
#include <vector>

#include "mots.hpp"

typedef int pointeur;

struct noeud{
// TODO RÉPARER CE STOCKAGE MÉMOIRE FOIREUX
	char m[30];             // mot représenté
	char nh;                // taille de l'historique ( <= 20 )
	pointeur p;             // pointeur vers le père
	char d;                 // 87654321 ... 1: noeud vrai? 2: racine? 3: +1 car exactement 4: premier car normal
	char t;                 // taille mot actuel en caractères
	caractere cp;           // caractère du père allant à THIS
	pointeur h[20];         // liste des pointeurs vers les historiques
	pointeur f[NB_LETTRES]; // liste des pointeurs vers les fils
};
typedef struct noeud noeud;

struct arbre{
	int n;            // nombre total de noeuds utilisés (racineS et feuilles incluses)
	int m;            // nombre de noeuds représentant des mots
	int z;            // size du vector v
	vector <noeud> v; // dictionnaire-arbre-historique 
	caractere l[38];  // fils_to_caractere
	windex w;         // caractere_to_fils
};
typedef struct arbre arbre;

void caractere_to_noeud(caractere &c_in, noeud &n_out);
void noeud_init(noeud &n_out);
void int_to_arbre_icz(int i_in, arbre &a_out);
bool noeud_mg(noeud &n_out);
void arbre_noeud_ms(arbre &a_out, noeud &n_out);
void arbre_noeud_mu(arbre &a_out, noeud &n_out);
void ninfos(noeud &n);
void arbre_init(arbre &a);
void mot_to_arbre_add(char* m_in, arbre &a_out);
void mot_arbre_to_pointeur(char* c_in, arbre &a_in, pointeur &p_out);
void pointeur_arbre_to_mot(pointeur &p_in, arbre &a_in, char* m_out);

#endif
