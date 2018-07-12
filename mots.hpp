// mots.hpp

#include <iostream>
using namespace std;

#include <vector>

#ifndef MOTS_HPP
#define MOTS_HPP



#define NB_LETTRES 38



// 2
struct caractere{
	char n;
	char s;
};
typedef struct caractere caractere;

// 76
struct slettres{
	caractere c[38];
};
typedef struct slettres slettres;

// sur le long terme cette structure de données ne sera probablement plus nécessaire
// les fonctions retournant un «mot» retourneront un void et prendrons le mot en référence…
//… et ce sera sans doute juste le contenu du mot
struct mot{
	char c[30];
};
typedef struct mot mot;

struct windex{
	unsigned char n[256];
	unsigned char s[256];
};
typedef struct windex windex;



void caractere_zero(caractere &c_out);
void caractere_copie(caractere &c_in, caractere &c_out);
void mot_zero(char* m_out);
void mot_copie(char* m_in, char* m_out);
void mot_to_caractere(char* m_in, caractere &c_out);
int mot_to_int(char* m_in);
void mot_int_to_caractere(char* m_in, int i_in, caractere &c_out);
bool caractere_2_to_bool(caractere &c1_in, caractere &c2_in);
void l_init(caractere* l);
void l_to_w(caractere* l, windex &w);
char w_caractere_to_char(windex &w, caractere &c);
void mot_int_to_mot(char *m_in, int i_in, char *m_out);
int mot_2_to_int(char* m1, char* m2);













#endif
