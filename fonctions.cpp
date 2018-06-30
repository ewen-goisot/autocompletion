// ne va pas avec CE main

#include <iostream>
#include <vector>
//#include <string.h>

using namespace std;

#include "fonctions.hpp"
//#include "lettres.hpp"


// 2
struct caractere{
	char normal;
	char special;
};
typedef struct caractere caractere;

// 210
struct noeud{
	char mot_actuel[30];
	unsigned char nb_historique;
	unsigned char taille; // taille mot actuel (évite de devoir la recalculer)
	unsigned char info; // 87654321 ... 1: noeud vrai? 2: racine? 3: +1 car exactement 4: premier car normal
	caractere c_pere;
	int pere;
	int fils[NB_LETTRES];
	int historique[20];
};
typedef struct noeud noeud;

// 76
struct slettres{
	caractere c[38];
};
typedef struct slettres slettres;

struct mot{
	char c[30];
};
typedef struct mot mot;

struct arbre{
	int taille; // different de size
	int nb_mots; // different de taille et size
	vector <noeud> v;
};
typedef struct arbre arbre;

struct numlettre{
	unsigned char normal[256];
	unsigned char special[256];
};
typedef struct numlettre numlettre;



void carnull(caractere &c){
	c.normal = 0;
	c.special = 0;
}

void cacopie(caractere &cain, caractere &caout){
	caout.normal = cain.normal;
	caout.special = cain.special;
}

/*
// TODO : la refaire
char * catoch(caractere c){
	char resultat[4];
	resultat[0] = c.normal;
	if(c.normal == -61){
		resultat[1] = c.special;
		resultat[2] = 0;
	}
	else{
		resultat[1] = 0;
	}
	return resultat;
}
*/

caractere chtoca(char * c){
	caractere resultat;
	resultat.normal = c[0];
	if(c[0] == -61){
		resultat.special = c[1];
	}
	return resultat;
}

//une racine par lettre
void racine(noeud &n, caractere &c){
	n.mot_actuel[0] = c.normal;
	if(c.normal == -61){
		n.mot_actuel[1] = c.special;
		n.mot_actuel[2] = 0; // \0
		n.info = 0b00000110; // special, un car, racine, non utilisable
	}
	else{
		n.mot_actuel[1] = 0; // \0
		n.info = 0b00001110; // normal, un car, racine, non utilisable
	}
	n.pere = -1;
	cacopie(c, n.c_pere);
	int i;
	for(i=0; i<NB_LETTRES; ++i){
		n.fils[i] = -1;
	}
	for(i=0; i<20; ++i){
		n.historique[i] = -1;
	}
	n.nb_historique = 0;
	n.taille = 1;
}

void initial(noeud &n){
	n.mot_actuel[0] = 0;
	n.pere = -1;
	carnull(n.c_pere);
	int i;
	for(i=0; i<NB_LETTRES; ++i){
		n.fils[i] = -1;
	}
	for(i=0; i<20; ++i){
		n.historique[i] = -1;
	}
	n.nb_historique = 0;
	n.taille = 0;
	n.info = 0;
}

void ninfos(noeud &n){
	printf("mot : %s\ncpere (d) : %d %d\nhistorique : %d\n\n", n.mot_actuel, n.c_pere.normal, n.c_pere.special, n.nb_historique);
}


// TODO : perfectionner
int len_mot(char* s){
	int fausse_taille=0;
	int vraie_taille=0;
	char lecture;
	do{
		lecture = s[fausse_taille];
		if( (int)lecture != 0 && (int)lecture != -61){
			++ vraie_taille;
		}
		++ fausse_taille;
	}while((int)lecture != 0 && fausse_taille < 100);
	return vraie_taille;
}

// TODO : retourner \0 si on dépasse la taille limite
caractere trouve_caractere_position( int i, char* s ){
	//cout << "\n\n\n";
	caractere carac;
	int fausse_taille=0;
	int vraie_taille=0;
	char lecture;
	while(vraie_taille < i){
		lecture = s[fausse_taille];
		//cout << (int)lecture << endl;
		if( (int)lecture != 0 && (int)lecture != -61){
			++ vraie_taille;
		}
		++ fausse_taille;
	}
	carac.normal = s[fausse_taille];
	if(carac.normal == -61){
		carac.special = s[fausse_taille+1];
	}
	else{
		carac.special = 0;
	}
	//cout << "\n\n";
	//cout << "caractere:" << (int)caractere.normal << " et " << (int)caractere.special << endl;
	return carac;
}

bool compare(caractere &a, caractere &b){
	if( (int)a.normal == -61 xor (int)b.normal == -61 ){
		return false;
	}
	else if( (int)a.normal == -61 && (int)b.normal == -61){
		return ((int)a.special == (int)b.special);
	}
	else{
		return ((int)a.normal == (int)b.normal);
	}
}



void initialise(slettres &c){
	c.c[0] = chtoca("a");
	c.c[1] = chtoca("b");
	c.c[2] = chtoca("c");
	c.c[3] = chtoca("d");
	c.c[4] = chtoca("e");
	c.c[5] = chtoca("f");
	c.c[6] = chtoca("g");
	c.c[7] = chtoca("h");
	c.c[8] = chtoca("i");
	c.c[9] = chtoca("j");
	c.c[10] = chtoca("k");
	c.c[11] = chtoca("l");
	c.c[12] = chtoca("m");
	c.c[13] = chtoca("n");
	c.c[14] = chtoca("o");
	c.c[15] = chtoca("p");
	c.c[16] = chtoca("q");
	c.c[17] = chtoca("r");
	c.c[18] = chtoca("s");
	c.c[19] = chtoca("t");
	c.c[20] = chtoca("u");
	c.c[21] = chtoca("v");
	c.c[22] = chtoca("w");
	c.c[23] = chtoca("x");
	c.c[24] = chtoca("y");
	c.c[25] = chtoca("z");
	c.c[26] = chtoca("à");
	c.c[27] = chtoca("â");
	c.c[28] = chtoca("é");
	c.c[29] = chtoca("è");
	c.c[30] = chtoca("ê");
	c.c[31] = chtoca("ë");
	c.c[32] = chtoca("î");
	c.c[33] = chtoca("ï");
	c.c[34] = chtoca("ô");
	c.c[35] = chtoca("ù");
	c.c[36] = chtoca("ü");
	c.c[37] = chtoca("ç");
}

void inverse(slettres &c, numlettre &n){
	unsigned char i;
	for(i=0; i<38; ++i){
		if(c.c[i].normal == -61){
			n.special[c.c[i].special] = i;
		}
		else{
			n.normal[c.c[i].normal] = i;
		}
	}
}

unsigned char trouve_lettre(caractere &c, numlettre &n){
	if(c.normal == -61){
		return n.special[c.special];
	}
	else{
		return n.normal[c.normal];
	}
}

void init_arbre(arbre &a, slettres l){
	int i;
	a.taille = 38;
	a.nb_mots = 0;
	a.v.resize(38);
	for(i=0; i<38; ++i){
		racine(a.v[i], l.c[i]);
	}
}

// TODO : déplacer et améliorer
mot extrait(char* m, int i){
	mot resultat;
	int fausse_taille=0;
	int vraie_taille=0;
	char lecture;
	while(vraie_taille < i){
		lecture = m[fausse_taille];
		resultat.c[fausse_taille] = m[fausse_taille];
		if( (int)lecture != 0 && (int)lecture != -61){
			++ vraie_taille;
		}
		++ fausse_taille;
	}
	return resultat;
}


// TODO : améliorer ... et mettre toutes les fonctions de "char" ensemble
int commun(char* m1, char* m2){
	int fausse_taille=0;
	int vraie_taille=0;
	char lecture1, lecture2;
	bool continuer = true;
	while(continuer){
		lecture1 = m1[fausse_taille];
		lecture2 = m2[fausse_taille];
		if( (int)lecture1 == 0 || (int)lecture2 == 0 || (int)lecture1 != (int)lecture2){
			continuer = false; // break serait mieux
		}
		else if( (int)lecture1 != 0 && (int)lecture1 != -61){
			++ vraie_taille;
		}
		++ fausse_taille;
	}
	return vraie_taille;
}

void ajoute_mot(noeud &n, mot &m, numlettre &nl){
	int t = len_mot(m.c);
	caractere c = trouve_caractere_position(0, m.c);
	int p;
	p = trouve_lettre(c, nl);
}

