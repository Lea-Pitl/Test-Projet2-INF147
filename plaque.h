#pragma once
#define _CRT_SECURE_NO_WARNINGS  /* permet de compiler la librairie <stdio.h> */
#include <stdio.h>				 /* pour la fonction printf() */
#include <stdlib.h>				 /* pour la constante EXIT_SUCCESS */
#include <time.h>
#include <math.h>
/********************************************************************/
/*                    INF 147 - Travail Pratique #2					*/
/*																	*/
/* Date de creation : 09/10/2019									*/
/* Auteurs :	Léa PITAULT (PITL19579909)							*/
/*				Daniel Nguyen (NGUYD								*/
/*																	*/
/*				Librairie pour la gestion des plaques				*/
/*																	*/
/********************************************************************/
//test test
#define  DIM   4            // la largeur de la plaque (3x3 cases en tout)
#define  VIDE  0            // la valeur de la case vide
#define  NBCOUPS  200  // le nombre de coups à faire pour mélanger la plaque initiale

/* Type global pour les 4 déplacements possibles */
typedef enum { NULLE = -1, HAUT, GAUCHE, BAS, DROITE } t_direction; //(-1,0,1,2,3)

/* Type global pour la plaque de jeu */
typedef int t_plaque[DIM][DIM];

/* Constante qui illustre la plaque-solution à trouver */
#if (DIM==3)
t_plaque SOLUTION = { {1, 2, 3}, {4, 5, 6}, {7, 8, VIDE} };
#else
t_plaque SOLUTION = { 1, 2, 3, 4, 5, 6, 7, 8,9, 10, 11, 12, 13, 14, 15, VIDE };
#endif


/********************************************************************/
/*               DECLARATION DE FONCTIONS (PROTOTYPES)				*/
/********************************************************************/


/*
ALEA

Fonction qui genere un nombre aleatoire entre min et max.

PARAMETRE :		min - la valeur minimale (int)
				max - la valeur maximale (int)
Retour : le nombre aleatoire entre min et max (int)
*/
int alea(int min, int max);

/*
 COPIER_PLAQUE

 Fonction qui fait une copie de la plaque source.

 PARAMETRE :	copie - la copie de la plaque ( t_plaque)
				src - la plaque source (const t_plaque)
 Retour : Aucun
*/
void copier_plaque(t_plaque copie, const t_plaque src);

/* CHANGER_PLAQUE

Fonction qui permet de modifier une plaque

PARAMETRE :		pla : la plaque a modifier
				dir : direction du deplacement du bloc vide (0)
				py_0 : position en y du bloc vide
				px_0 : position en x du bloc vide

RETOUR :	1 si le mouvement (la direction) est valide, 0 sinon
*/
int changer_plaque(t_plaque pla, t_direction dir, int *py_0, int *px_0);

/*
AFFICHER_PLAQUE

Fonction qui affiche simplement la plaque reçue à l’écran, « DIM » valeurs par ligne.

PARAMETRE : pla - la plaque de jeu (const t_plaque)
Retour : Aucun

*/
void afficher_plaque(const t_plaque pla);

/* MELANGER_PLAQUE

Fonction qui modifie la plaque de facon aleatoire

PARAMETRES :	pla : plaque a melanger
				py_0in : position en y du bloc vide
				px_0in : position en x du bloc vide

RETOUR : Aucun (modification de la plaque pla)
*/
void melanger_plaque(t_plaque pla, int *py_0in, int *px_0in);

/* TROUVER_POSITION

Fonction qui permet de trouver la position d'un chiffre voulu

PARAMETRES :	pla : la plaque sur laquelle on cherche
				py_0 : position en y du chiffre recherche retourne en reference
				px_0 : position en x du chiffre recherche retourne en reference
				chiffre : chiffre dont on cherche la position
RETOUR : aucun
*/
void trouver_position(const t_plaque pla, int* py_0, int* px_0, int chiffre);

/* EVALUER_PLAQUE

Fonction qui renvoie le nombre total de deplacement
pour que chaque chiffre se retrouvent a la meme place
que dans la SOLUTION

PARAMETRES :	pla - la plaque a evaluer (a comparer avec la SOLUTION)

RETOUR : le nombre de deplacement total
*/
int evaluer_plaque(const t_plaque pla);




/****************************************************/
/*                     FONCTIONS                    */
/****************************************************/


int alea(int min, int max) {
	return (int)(rand() % (max - min + 1) + min);						//Fait appel a rand(). Doit inclure time.h
}

void copier_plaque(t_plaque copie, const t_plaque src) {

	int i, j;

	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			copie[i][j] = src[i][j];
		}
	}
}

int changer_plaque(t_plaque pla, t_direction dir, int *py_0, int *px_0) {
	int resultat;
	int y = *py_0;
	int x = *px_0;

	switch (dir)
	{
	case -1:
		printf("je ne bouge pas");
		break;
	case 0: //HAUT
		y = y - 1;
		break;
	case 1: //GAUCHE
		x = x - 1;
		break;
	case 2: //BAS
		y = y + 1;
		break;
	case 3: //DROITE
		x = x + 1;
		break;
	default:
		printf("Direction non valide");
		break;
	}

	if (y < 0 || y > DIM - 1 || x < 0 || x > DIM - 1) {
		resultat = 0;
		//printf("\nMouvement invalide");
	}
	else {
		pla[*py_0][*px_0] = pla[y][x];
		*py_0 = y;
		*px_0 = x;
		pla[*py_0][*px_0] = 0;
		resultat = 1;
	}
	return resultat;
}

void afficher_plaque(const t_plaque pla) {
	int i, j;
	printf("\n");
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			printf(" %2d", pla[i][j]);
		}
		printf("\n");
	}

}

void melanger_plaque(t_plaque pla, int* py_0in, int* px_0in) {
	int cpt = 0;
	t_direction dir;

	copier_plaque(pla, SOLUTION);					//on copie la solution dans pla
	do {
		dir = (t_direction)alea(0, 3);				//on genere une direction aleatoire
		changer_plaque(pla, dir, py_0in, px_0in);	//modification de pla (si dir valide)
		cpt++;
	} while (cpt < NBCOUPS);						//on repete NBCOUPS fois
}

void trouver_position(const t_plaque pla, int* posy, int* posx, int chiffre) {
	int i = 0;
	int j = 0;
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			if (pla[i][j] == chiffre) {
				*posy = i;
				*posx = j;
			}
		}
	}
}

int evaluer_plaque(const t_plaque pla) {
	int posy, posx;
	int posy_sol, posx_sol;
	int i = 1;
	int sum = 0;
	int deplacement = 0;

	for (i = 1; i < DIM*DIM; i++) {
		trouver_position(pla, &posy, &posx, i);
		trouver_position(SOLUTION, &posy_sol, &posx_sol, i);
		deplacement = abs(posy_sol - posy) + abs(posx_sol - posx);
		printf("\nchiffre : %i et deplacement = %d", i, deplacement);
		sum += deplacement;
	}
	return sum;
}
