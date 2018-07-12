// main.cpp

#include <iostream>
using namespace std;

#include <vector>

#include "fonctions.cpp"
#include "mots.cpp"


int main(){

	char mot6[30];
	char mot4[30];
	char mot7[30];
	char mot3[30];
	char mot9[30];
	char mot0[30];
	char mot2[30];
	char mot5[30];
	char mot8[30];
	int i1, i2, i3;
	i1=sprintf(mot9,"%s","alléé");
	i1=sprintf(mot4,"%s","atotou");
	i1=sprintf(mot7,"%s","alùre");
	i1=sprintf(mot5,"%s","aaa");
	i1=sprintf(mot3,"%s","attirancer");
	i1=sprintf(mot6,"%s","aaaas");
	i1=sprintf(mot2,"%s","attoancer");
	i1=sprintf(mot0,"%s","aaaaaaab");
	i1=sprintf(mot8,"%s","allér");
	arbre a1;
	arbre_init(a1);
	mot_to_arbre_add(mot7, a1);
	mot_to_arbre_add(mot0, a1);
	mot_to_arbre_add(mot6, a1);
	mot_to_arbre_add(mot9, a1);
	mot_to_arbre_add(mot4, a1);
	mot_to_arbre_add(mot8, a1);
	mot_to_arbre_add(mot5, a1);
	mot_to_arbre_add(mot3, a1);
	mot_to_arbre_add(mot2, a1);
	mot_to_arbre_add(mot9, a1);
	mot_to_arbre_add(mot9, a1);
	mot_to_arbre_add(mot4, a1);
	mot_to_arbre_add(mot9, a1);
	ainfos(a1);
	return 0;
}



