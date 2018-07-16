// main.cpp

#include <iostream>
using namespace std;

#include <vector>

#include "fonctions.cpp"
#include "mots.cpp"


int main(){
	struct mot{
		char m[30];
	};
	typedef struct mot mot;
	vector <mot> mmm;
	mmm.resize(40);

	int i1, i2, i3;
	i2 = 0;
	arbre a1;
	i1=sprintf(mmm[i2].m,"%s","aulér"); ++i2;
	i1=sprintf(mmm[i2].m,"%s","axlér"); ++i2;
	i1=sprintf(mmm[i2].m,"%s","axléa"); ++i2;
	i1=sprintf(mmm[i2].m,"%s","aulér"); ++i2;
	//i1=sprintf(mmm[i2].m,"%s","axlér"); ++i2;
	//i1=sprintf(mmm[i2].m,"%s","axléa"); ++i2;
	arbre_init(a1);
	for(i3=0; i3<i2; ++i3){
		mot_to_arbre_add(mmm[i3].m, a1);
	}
	ainfos(a1);
	return 0;
}



