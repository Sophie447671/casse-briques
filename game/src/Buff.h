#pragma once

#include <raylib.h>
#include <raymath.h>

#include "GeometryPrimitive.h"

/*
 * Ce fichier contient les structures de données concernant les buffs
 */


// Liste des buffs bossibles
enum BUFF_TYPE {
	NO_BUFF // sans effet
};

// ----------------

// Item représentant le buff
typedef struct {
	RectangleV item;
	enum BUFF_TYPE type;
	bool taken; // A t-il été pris par la raquette ?
	bool toRemove; // Faut-il le supprimer ?
} BuffItem;

// Creer un item "buff" d'un certain type à l'endroit indiqué
// BuffItem createBuffItem(Vector2 center, enum BUFF_TYPE type); // A DECOMMENTER
// Creer un item "buff" de type aléatoire à l'endroit indiqué
// BuffItem createRandomBuff(Vector2 center); // A DECOMMENTER


// ----------------

#define BUFF_MAX_NUMBER 40

// Contient plusieurs buffs
typedef struct {
	BuffItem buffs[BUFF_MAX_NUMBER];
	int size;
} BuffContainer;

// Créer un BuffContainer vide
// BuffContainer createBuffContainer(); // A DECOMMENTER
// Ajoute un BuffItem dans un BuffContainer
// void addBuff(BuffContainer* buffContainer, BuffItem b); // A DECOMMENTER
// Supprime le BuffItem situé à l'indice donné
// void removeBuff(BuffContainer* buffContainer, int index); // A DECOMMENTER



