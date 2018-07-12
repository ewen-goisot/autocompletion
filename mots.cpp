// mots.cpp // {{{
// toutes les fonctions sur les char / caracteres
// suppose que les mots sont au format standard, optimal en lecture mais pas en stockage
#include <iostream>
using namespace std;
#include <vector>
#include "mots.hpp" // }}}
void caractere_zero(caractere &c_out){ //{{{
	c_out.n = 0;
	c_out.s = 0;
} //}}}
void caractere_copie(caractere &c_in, caractere &c_out){ //{{{
	c_out.n = c_in.n;
	c_out.s = c_in.s;
} //}}}
void mot_zero(char* m_out){ //{{{
	int i1;
	for(i1=0; i1<=30; ++i1){
		m_out[i1] = 0;
	}
} //}}}
void mot_copie(char* m_in, char* m_out){ //{{{
	char u1;
	int i1;
	for(i1=0; i1<=30; ++i1){
		u1 = m_in[i1];
		m_out[i1] = u1;
	}
} //}}}
void mot_to_caractere(char* m_in, caractere &c_out){ // enregiste le premier caractere du mot //{{{
	c_out.n = m_in[0];
	if(m_in[0] == -61){
		c_out.s = m_in[1];
	}
} //}}}
int mot_to_int(char* m_in){ // taille du mot //{{{
	int i1, i2;
	char u1, u2;
	i1 = 0; i2 = 0;
	while(true){
		if(i2 >= 28){
			cout << "bug" << endl;
			break;
		}
		u1 = m_in[i2];
		if(u1 == -61){
			++i2;
			++i2; // nombre de char
			++i1; // nombre de caracteres
		}
		else if(u1 == 0){
			break;
		}
		else{
			++i2;
			++i1;
		}
	}
	return i1;
} //}}}
void mot_int_to_caractere(char* m_in, int i_in, caractere &c_out){ // i_in eme caractere du mot //{{{
	int i1, i2;
	char u1, u2;
	i1 = 0; i2 = 0;
	while(i1 < i_in){
		if(i2 >= 28){
			cout << "bug" << endl;
			return;
		}
		u1 = m_in[i2];
		if(u1 == -61){
			++i2;
			++i2;
			++i1;
		}
		else{
			++i2;
			++i1;
		}
	}
	u1 = m_in[i2];
	if(u1 == -61){
		c_out.n = -61;
		++i2;
		u2 = m_in[i2];
		c_out.s = u2;
	}
	else{
		c_out.n = u1;
	}
	return ;
} //}}}
bool caractere_2_to_bool(caractere &c1_in, caractere &c2_in){ // teste si les caracteres sont identiques //{{{
	if( c1_in.n == -61 xor c2_in.n == -61 ){
		return false;
	}
	else if( c1_in.n == -61 && c2_in.n == -61){
		return (c1_in.s == c2_in.s);
	}
	else{
		return (c1_in.n == c2_in.n);
	}
} //}}}
void l_init(caractere* l){ //{{{
	mot_to_caractere("a",l[0]);
	mot_to_caractere("b",l[1]);
	mot_to_caractere("c",l[2]);
	mot_to_caractere("d",l[3]);
	mot_to_caractere("e",l[4]);
	mot_to_caractere("f",l[5]);
	mot_to_caractere("g",l[6]);
	mot_to_caractere("h",l[7]);
	mot_to_caractere("i",l[8]);
	mot_to_caractere("j",l[9]);
	mot_to_caractere("k",l[10]);
	mot_to_caractere("l",l[11]);
	mot_to_caractere("m",l[12]);
	mot_to_caractere("n",l[13]);
	mot_to_caractere("o",l[14]);
	mot_to_caractere("p",l[15]);
	mot_to_caractere("q",l[16]);
	mot_to_caractere("r",l[17]);
	mot_to_caractere("s",l[18]);
	mot_to_caractere("t",l[19]);
	mot_to_caractere("u",l[20]);
	mot_to_caractere("v",l[21]);
	mot_to_caractere("w",l[22]);
	mot_to_caractere("x",l[23]);
	mot_to_caractere("y",l[24]);
	mot_to_caractere("z",l[25]);
	mot_to_caractere("à",l[26]);
	mot_to_caractere("â",l[27]);
	mot_to_caractere("é",l[28]);
	mot_to_caractere("è",l[29]);
	mot_to_caractere("ê",l[30]);
	mot_to_caractere("ë",l[31]);
	mot_to_caractere("î",l[32]);
	mot_to_caractere("ï",l[33]);
	mot_to_caractere("ô",l[34]);
	mot_to_caractere("ù",l[35]);
	mot_to_caractere("ü",l[36]);
	mot_to_caractere("ç",l[37]);
} //}}}
void l_to_w(caractere* l, windex &w){ //{{{
	char u;
	for(u=0; u<38; ++u){
		if(l[u].n == -61){
			w.s[l[u].s] = u;
		}
		else{
			w.n[l[u].n] = u;
		}
	}
} //}}}
char w_caractere_to_char(windex &w, caractere &c){ // dans le tableau //{{{
	if(c.n == -61){
		return w.s[c.s];
	}
	else{
		return w.n[c.n];
	}
} //}}}
void mot_int_to_mot(char *m_in, int i_in, char *m_out){ // sous mot d'une taille choisie //{{{
	int i1, i2;
	char u1, u2;
	i1 = 0; i2 = 0;
	while(i1 < i_in){
		if(i2 >= 28){
			cout << "bug" << endl;
			return;
		}
		u1 = m_in[i2];
		if(u1 == -61){
			m_out[i2] = -61;
			++i2;
			m_out[i2] = m_in[i2];
			++i2; // nombre de char
			++i1; // nombre de caracteres
		}
		else{
			m_out[i2] = m_in[i2];
			++i2;
			++i1;
		}
	}
	m_out[i2] = 0; // \0 ou fin de chaine
	return ;
} //}}}
int mot_2_to_int(char* m1, char* m2){ // plus long préfixe commun //{{{
	int i1, i2;
	char u1, u2;
	i1 = 0; i2 = 0;
	while(true){
		if(i2 >= 28){
			cout << "bug" << endl;
			break;
		}
		u1 = m1[i2];
		u2 = m2[i2];
		if(u1 == -61 && u2 == -61){ // caracteres spéciaux à comparer
			++i2;
			u1 = m1[i2];
			u2 = m2[i2];
			if(u1 == u2){ // deux caractères spéciaux identiques
				++i2;
				++i1;
			}
			else{ // deux caractères spéciaux différents
				break;
			}
		}
		else if(u1 == 0 && u2 == 0){ // les deux mots terminent
			break;
		}
		else if(u1 == u2){ // deux caractères normaux identiques
			++i2;
			++i1;
		}
		else{ // deux caractères normaux différents
			break;
		}
	}
	return i1;
} //}}}
// {{{
// }}}
