// fonctions.cpp {{{
#include <iostream>
using namespace std;
#include <vector>
#include "fonctions.hpp"
// }}}
void caractere_to_noeud(caractere &c_in, noeud &n_out){ //{{{
	n_out.m[0] = c_in.n;
	if(c_in.n == -61){
		n_out.m[1] = c_in.s;
		n_out.m[2] = 0; // \0
		n_out.d = 0b00000110; // special, un car, racine, non utilisable
	}
	else{
		n_out.m[1] = 0; // \0
		n_out.d = 0b00001110; // n, un car, racine, non utilisable
	}
	n_out.p = -1; // -1 signifie NULL
	caractere_copie(c_in, n_out.cp);
	int i;
	for(i=0; i<NB_LETTRES; ++i){
		n_out.f[i] = -1;
	}
	for(i=0; i<20; ++i){
		n_out.h[i] = -1;
	}
	n_out.nh = 0;
	n_out.t = 1;
} //}}}
void noeud_init(noeud &n_out){ //{{{
	n_out.m[0] = 0;
	n_out.p = -1;
	caractere_zero(n_out.cp);
	int i;
	for(i=0; i<NB_LETTRES; ++i){
		n_out.f[i] = -1;
	}
	for(i=0; i<20; ++i){
		n_out.h[i] = -1;
	}
	n_out.nh = 0;
	n_out.t = 0;
	n_out.d = 0;
} //}}}
void int_to_arbre_icz(int i_in, arbre &a_out){ //{{{
	int i1, i2, i3;
	i1 = a_out.n;
	a_out.n += i_in;
	i2 = a_out.n;
	if(i2 > a_out.z){
		a_out.v.resize(i2); // optimal? tableau vs vector?
		a_out.z = i2;
	}
	for(i3=i1; i3<i2; ++i3){
		noeud_init(a_out.v[i3]);
		cout << "ici" << i3 << "\t";
	}
} //}}}
bool noeud_mg(noeud &n_out){ // est-ce un mot? //{{{
	return (n_out.d & 0b00000001);
} //}}}
void arbre_noeud_ms(arbre &a_out, noeud &n_out){ // devient un mot //{{{
	if( !(n_out.d & 0b00000001) ){
		++a_out.m;
		n_out.d += 1;
	}
} //}}}
void arbre_noeud_mu(arbre &a_out, noeud &n_out){ // devient un non-mot //{{{
	if( n_out.d & 0b00000001 ){
		--a_out.m;
		n_out.d -= 1;
	}
} //}}}
void ninfos(noeud &n){ //{{{
	// fonction non réglementaire
	printf("mot : %s\tpere : %d\thistorique : %d\n", n.m, n.p, n.nh);
} //}}}
void ainfos(arbre &a){ //{{{
	// fonction non réglementaire
	int i;
	for(i=0; i<a.n; ++i){
		cout << "noeud: " << i << ", ";
		ninfos(a.v[i]);
	}
} //}}}
void arbre_init(arbre &a_out){ //{{{
	int i;
	a_out.n = 38;
	a_out.m = 0;
	a_out.z = 38;
	a_out.v.resize(38);
	l_init(a_out.l);
	l_to_w(a_out.l, a_out.w);
	for(i=0; i<38; ++i){
		caractere_to_noeud(a_out.l[i], a_out.v[i]);
	}
} //}}}
void int_2_to_historique(int i1_in, int i2_in, noeud &n_out){ //{{{
	pointeur      p1, p2, p3, p4;
	int           i1, i2, i3, i4;
	for(i1=i2_in; i1>i1_in; --i1){
		n_out.h[i1] = n_out.h[i1-1];
	}
} //}}}
void pointeur_to_noeud_hist(pointeur &p_in, noeud &n_out){ //{{{
	pointeur      p1, p2, p3, p4;
	int           i1, i2, i3, i4;
	i1 = n_out.nh;
	if(n_out.nh < 20){
		for(i2=0; i2<i1; ++i2){
			if(n_out.h[i2] == p_in){
				i1 = (2*i2)/3;
				int_2_to_historique(i1, i2, n_out);
				n_out.h[(2*i2)/3] = p_in;
				return;
			}
		}
		cout << "là" << p_in << "\t";
		++n_out.nh;
		n_out.h[i1] = p_in;
		return;
	}
	for(i2=0; i2<20; ++i2){
		if(n_out.h[i2] == p_in){
			i1 = (2*i2)/3;
			int_2_to_historique(i1, i2, n_out);
			n_out.h[i1] = p_in;
			if(i2<19){
				++n_out.nh;
			}
			cout << "làlllà" << p_in << "\t";
			return;
		}
	}
	int_2_to_historique(13, 20, n_out);
	n_out.h[13] = p_in;
} //}}}
void pointeur_to_arbre_hist(pointeur &p_in, arbre &a_out){ //{{{
	pointeur_to_noeud_hist(p_in, a_out.v[p_in]); // si le mot a des descendants
	caractere     c1, c2, c3, c4;
	pointeur      p1, p2, p3, p4;
	int           i1, i2, i3, i4;
	char          u1, u2, u3, u4;
	p1 = p_in;
	while(p1 >= 38){ // while not root
		p1 = a_out.v[p1].p;
		pointeur_to_noeud_hist(p_in, a_out.v[p1]);
	}
} //}}}
// TODO actualiser les historiques des noeuds permutés //{{{
void mot_to_arbre_add(char* m_in, arbre &a_out){
	caractere     c1, c2, c3, c4;
	pointeur      p1, p2, p3, p4;
	int           i1, i2, i3, i4; // peuvent etre des char
	char          u1, u2, u3, u4;
	i1 = mot_to_int(m_in);
	if(i1 == 0){
		return;
	}
	if(i1 == 1){
		mot_int_to_caractere(m_in, 0, c1);
		p2 = w_caractere_to_char(a_out.w, c1);
		if( not noeud_mg(a_out.v[p2]) ){
			arbre_noeud_ms(a_out, a_out.v[p2]);
			++ a_out.m;
			pointeur_to_noeud_hist(p2, a_out.v[p2]);
		}
		return;
	}
	mot_int_to_caractere(m_in, 0, c1);
	p2 = w_caractere_to_char(a_out.w, c1); // une racine
	i2 = 1;
	mot_int_to_caractere(m_in, i2, c1);
	u1 = w_caractere_to_char(a_out.w, c1);
	p3 = a_out.v[p2].f[u1];
	while(true){
		if(p3 == -1){ // le fils est innexistant
			cout << "mode1 " << i1 << " " << i2 << " " << i3 << " " << i4 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << endl;
			p3 = a_out.n;
			++a_out.m;
			int_to_arbre_icz(1, a_out);
			noeud_init(a_out.v[p3]);
			mot_copie(m_in, a_out.v[p3].m);
			a_out.v[p2].f[u1] = p3;
			a_out.v[p3].p = p2;
			pointeur_to_arbre_hist(p3, a_out);
			return;
		}
		i3 = mot_to_int(a_out.v[p3].m);
		i4 = mot_2_to_int(m_in, a_out.v[p3].m);
		// i2 < i1 , i4 <= i1 , i4 <= i3
		if( i4 == i1 && i4 == i3){ // m == a_out.v[p3].mot
			cout << "mode2 " << i1 << " " << i2 << " " << i3 << " " << i4 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << endl;
			if( not noeud_mg(a_out.v[p2]) ){
				arbre_noeud_ms(a_out, a_out.v[p2]);
				++ a_out.m;
				pointeur_to_arbre_hist(p2, a_out);
			}
			return;
		}
		if( i4 != i1 && i4 == i3 ){ // appel récursif (le seul)
			cout << "mode3 " << i1 << " " << i2 << " " << i3 << " " << i4 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << endl;
			p2 = p3;
			i2 = i3;
			mot_int_to_caractere(m_in, i2, c1);
			u1 = w_caractere_to_char(a_out.w, c1);
			p3 = a_out.v[p2].f[u1];
			continue; // retourne au début du while
		}
		if( i4 == i1 && i4 != i3 ){ // mot= noeud intermédiaire
			cout << "mode4 " << i1 << " " << i2 << " " << i3 << " " << i4 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << endl;
			p1 = a_out.n;
			++a_out.m; // TODO vérifier
			int_to_arbre_icz(1, a_out); // ajoute UN noeud
			a_out.v[p2].f[u1] = p1;
			a_out.v[p1].p = p2;
			noeud_init(a_out.v[p1]);
			mot_copie(m_in, a_out.v[p1].m);
			mot_int_to_caractere(a_out.v[p3].m, i1, c2);
			u2 = w_caractere_to_char(a_out.w, c1);
			a_out.v[p1].f[u2] = p3;
			a_out.v[p3].p = p1;
			pointeur_to_arbre_hist(p3, a_out);
			// TODO fonction de copie d'historique
			return;
		}
		if( i4 != i1 && i4 != i3 ){
			cout << "mode5 " << i1 << " " << i2 << " " << i3 << " " << i4 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << endl;
			p1 = a_out.n + 1;
			p4 = a_out.n;
			++a_out.m; // compte un mot de plus TODO actualiser les infos "est mot" partout
			int_to_arbre_icz(2, a_out); // ajoute les deux noeuds
			noeud_init(a_out.v[p1]);
			noeud_init(a_out.v[p4]);
			a_out.v[p2].f[u1] = p4;
			a_out.v[p4].p = p2;
			mot_copie(m_in, a_out.v[p1].m);
			mot_int_to_mot(m_in, i4, a_out.v[p4].m);
			mot_int_to_caractere(m_in, i4, c1);
			u1 = w_caractere_to_char(a_out.w, c1);
			mot_int_to_caractere(a_out.v[p3].m, i4, c3); // TODO les indices commencent (partout) à zéro
			u3 = w_caractere_to_char(a_out.w, c3);
			a_out.v[p4].f[u1] = p1;
			a_out.v[p1].p = p4;
			a_out.v[p4].f[u3] = p3;
			a_out.v[p3].p = p4;
			pointeur_to_arbre_hist(p1, a_out);
			// TODO copier l'historique
			return;
		}
	}
} //}}}
void mot_arbre_to_pointeur(char* c_in, arbre &a_in, pointeur &p_out){ //{{{
	caractere     c1, c2, c3, c4;
	pointeur      p1, p2, p3, p4;
	int           i1, i2, i3, i4;
	unsigned char u1, u2, u3, u4;
	// TODO everything
} //}}}
void pointeur_arbre_to_mot(pointeur &p_in, arbre &a_in, char* m_out){ //{{{
	mot_copie(a_in.v[p_in].m, m_out);
} //}}}
//{{{ 
//}}}
