// là ça arche, ça trie les caracteres selon la *** ème lettre au choix

#include <iostream>
using namespace std;

#include <fstream>


#include <sys/types.h>
#include <sys/stat.h>
	//status = mkdir("/home/ewen-goisot/aprog/023_sinapt", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

int len_mot(string s){
	cout << "\n\n\n";
	int fausse_taille=0;
	int vraie_taille=0;
	char lecture;
	do{
		lecture = s[fausse_taille];
		cout << (int)lecture << endl;
		if( (int)lecture != 0 && (int)lecture != -61){
			++ vraie_taille;
		}
		++ fausse_taille;
	}while((int)lecture != 0 && fausse_taille < 100);
	cout << "\n\n";
	cout << "taille:" << vraie_taille << "\n\n" << endl;
	return vraie_taille;
}

struct car_fra{
	char normal;
	char special;
};
typedef struct car_fra car_fra;

car_fra trouve_caractere_position( int i, string s ){
	cout << "\n\n\n";
	car_fra caractere;
	int fausse_taille=0;
	int vraie_taille=0;
	char lecture;
	while(vraie_taille < i){
		lecture = s[fausse_taille];
		cout << (int)lecture << endl;
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
	cout << "\n\n";
	cout << "caractere:" << (int)caractere.normal << " et " << (int)caractere.special << endl;
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
	int position = 0;
	if(argc >= 0){
		position = stoi( string(argv[1]) );
	}

	int i, j;
	int status;
	string francais[100] = {
	"a","b","c","d","e","f","g","h","i","j",
	"k","l","m","n","o","p","q","r","s","t",
	"u","v","w","x","y","z","à","â","é","è",
	"ê","î","ï","ô","ö","ù","û","ç"};
	bool lettre_presente[38];
	for(i=0; i<38; ++i){
		lettre_presente[i] = false;
	}
	
	ifstream fichier("undone.txt", ios::in);
	if( ! fichier ){
		//cout << "ouverture impossible";
		return 0;
	}
	
	typedef string chp;	
	chp dictionnaire[38];
	string mot;

	
	for(i=0; i<38; ++i){
		dictionnaire[i] = "";
	}
	while( getline(fichier,mot) ){
		for(j=0;j<38;++j){
			if(	compare( trouve_caractere_position(0,francais[j])  , trouve_caractere_position(position, mot) ) ){
				dictionnaire[j] += mot;
				dictionnaire[j] += "\n";
				lettre_presente[j] = true;
			}
		}
		
	}
	fichier.close();
	
	string nom;	
	for(i=0; i<38; ++i){
		if(lettre_presente[i]){
			cout << francais[i] << endl;
			nom = "";
			nom += francais[i];
			nom += "/undone.txt";
			ofstream fichier2(nom);
			if( ! fichier2 ){
				return 0;
			}
			fichier2 << dictionnaire[i];
			fichier2.close();
		}
	}



	return 0;


}

// -61 c'est la mort!
