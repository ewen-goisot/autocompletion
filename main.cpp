#include <iostream>
using namespace std;

#include <fstream>
#include <string>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
	//status = mkdir("/home/ewen-goisot/aprog/023_sinapt", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

int len_mot(string s){
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

struct car_fra{
	char normal;
	char special;
};
typedef struct car_fra car_fra;

struct instruction{
	char chemin[200];
	int position;
};
typedef struct instruction instruction;

car_fra trouve_caractere_position( int i, string s ){
	//cout << "\n\n\n";
	car_fra caractere;
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
	caractere.normal = s[fausse_taille];
	if(caractere.normal == -61){
		caractere.special = s[fausse_taille+1];
	}
	else{
		caractere.special = 0;
	}
	//cout << "\n\n";
	//cout << "caractere:" << (int)caractere.normal << " et " << (int)caractere.special << endl;
	return caractere;
}

bool compare(car_fra a, car_fra b){
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

int main(int argc, char *argv[]){

	instruction liste_instructions[12*38];
	instruction liste_instructions_nettoyage[38];
	sprintf(liste_instructions[0].chemin, "%s", "/home/ewen-goisot/aprog/023_sinapt/data");
	char nom_fichier[20];
	sprintf(nom_fichier, "/undone.txt");
	char chemin_fichier[200];
	liste_instructions[0].position = 0;
	int actuelle = 0;
	int actuelle_nettoyage;
	
	int i, j;
	int status;
	string francais[100] = {
	"a","b","c","d","e","f","g","h","i","j",
	"k","l","m","n","o","p","q","r","s","t",
	"u","v","w","x","y","z","à","â","é","è",
	"ê","î","ï","ô","ö","ù","û","ç"};
	char dossier_fr[38][4];
	sprintf(dossier_fr[0],"/%s","a");
	sprintf(dossier_fr[1],"/%s","b");
	sprintf(dossier_fr[2],"/%s","c");
	sprintf(dossier_fr[3],"/%s","d");
	sprintf(dossier_fr[4],"/%s","e");
	sprintf(dossier_fr[5],"/%s","f");
	sprintf(dossier_fr[6],"/%s","g");
	sprintf(dossier_fr[7],"/%s","h");
	sprintf(dossier_fr[8],"/%s","i");
	sprintf(dossier_fr[9],"/%s","j");
	sprintf(dossier_fr[10],"/%s","k");
	sprintf(dossier_fr[11],"/%s","l");
	sprintf(dossier_fr[12],"/%s","m");
	sprintf(dossier_fr[13],"/%s","n");
	sprintf(dossier_fr[14],"/%s","o");
	sprintf(dossier_fr[15],"/%s","p");
	sprintf(dossier_fr[16],"/%s","q");
	sprintf(dossier_fr[17],"/%s","r");
	sprintf(dossier_fr[18],"/%s","s");
	sprintf(dossier_fr[19],"/%s","t");
	sprintf(dossier_fr[20],"/%s","u");
	sprintf(dossier_fr[21],"/%s","v");
	sprintf(dossier_fr[22],"/%s","w");
	sprintf(dossier_fr[23],"/%s","x");
	sprintf(dossier_fr[24],"/%s","y");
	sprintf(dossier_fr[25],"/%s","z");
	sprintf(dossier_fr[26],"/%s","à");
	sprintf(dossier_fr[27],"/%s","â");
	sprintf(dossier_fr[28],"/%s","é");
	sprintf(dossier_fr[29],"/%s","è");
	sprintf(dossier_fr[30],"/%s","ê");
	sprintf(dossier_fr[31],"/%s","î");
	sprintf(dossier_fr[32],"/%s","ï");
	sprintf(dossier_fr[33],"/%s","ô");
	sprintf(dossier_fr[34],"/%s","ö");
	sprintf(dossier_fr[35],"/%s","ù");
	sprintf(dossier_fr[36],"/%s","û");
	sprintf(dossier_fr[37],"/%s","ç");
	
	int position;
	char chemin[200];
	char chemin_aux[200];
	
	typedef string chp;
	
/*
	for(int i=0; i<38; ++i){
		sprintf(chemin_aux, "%s%s",liste_instructions[0].chemin, dossier_fr[i]);
		status = rmdir(chemin_aux);
	}
*/	
	
	
	bool lettre_presente[38];

	for(int k=0; k<10000; ++k){
		// se placer dans le bon dossier
		position = liste_instructions[actuelle].position;
		sprintf(chemin, "%s", liste_instructions[actuelle].chemin);
		
		// creer des sous dossiers, initialiser
		for(int i=0; i<38; ++i){
			sprintf(chemin_aux, "%s%s", chemin, dossier_fr[i]);
			status = mkdir(chemin_aux, S_IRWXU | S_IRWXG);
		}
		for(i=0; i<38; ++i){
			lettre_presente[i] = false;
		}
		
		// ouvrir la liste de mots actuelle et la séparer selon une certaine lettre
		sprintf(chemin_fichier, "%s%s", chemin, nom_fichier);
		ifstream fichier(chemin_fichier, ios::in);
		if( ! fichier ){
			return 0;
		}
		chp dictionnaire[38];
		string mot;
		for(i=0; i<38; ++i){
			dictionnaire[i] = "";
		}
		while( getline(fichier,mot) ){
			for(j=0;j<38;++j){
				if(	len_mot(mot) > position &&
				compare( trouve_caractere_position(0,francais[j])  , trouve_caractere_position(position, mot) ) ){
					dictionnaire[j] += mot;
					dictionnaire[j] += "\n";
					lettre_presente[j] = true;
				}
			}
			
		}
		fichier.close();
		
		
		
		// réécrire le fichier séparé en 38 dans les sous dossiers, supprimer les dossiers inutiles
		string nom;	
		for(i=0; i<38; ++i){
			if(lettre_presente[i]){
				sprintf(chemin_aux, "%s%s", chemin, dossier_fr[i]);
				status = mkdir(chemin_aux, S_IRWXU | S_IRWXG);
				sprintf(chemin_fichier, "%s%s%s", chemin, dossier_fr[i], nom_fichier);
				nom = "";
				nom += francais[i];
				nom += "/undone.txt";
				ofstream fichier2(chemin_fichier);
				if( ! fichier2 ){
					return 0;
				}
				fichier2 << dictionnaire[i];
				fichier2.close();
				liste_instructions[actuelle].position = position+1;
				sprintf(liste_instructions[actuelle].chemin, "%s%s", chemin, dossier_fr[i]);
				++actuelle;
			}
			else{
				// si le dossier avait été créé à une époque lointaine
				//sprintf(chemin_aux, "%s%s", chemin, dossier_fr[i]);
				//status = rmdir(chemin_aux);
			}
		}
		
		--actuelle;
		if(actuelle == -1){
			break;
		}
		
	}





	return 0;


}

// -61 c'est la mort!
