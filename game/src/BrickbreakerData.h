#pragma once

#include <raylib.h>
#include <raymath.h>

#include "GeometryPrimitive.h"
#include "Input.h"
#include "Buff.h"

/*
 * Ce fichier contient les structures de donn�es principales de notre jeu
 */

 // ----------------

 // Donn�es d'une balle
typedef struct {
	Vector2 position;
	Vector2 direction;
	float radius;
	float speed;
	Color color;
}Ball;


// Cr�er une balle avec les param�tres par d�faut � la position indiqu�e.
Ball createBall(Vector2 startPos);

// ----------------

// Donn�es de la raquette (paddle)
typedef struct {
	CircularArc arc;
	float speed;
	Color color;
} Paddle;

// Cr�er une raqutte avec les param�tres par d�faut.
Paddle createPaddle(Vector2 position, float radius);

// ----------------

// Donn�es d'une brique
typedef struct {
	RectangleV rect;
	int comptRest;
	Color color;
} Brick;

// Cr�er une brick avec les param�tres par d�faut � la position indiqu�e et de taille indiqu�e.
Brick createBrick(Vector2 topLeft, Vector2 size, int comptRest);


// ----------------

// Nombre max de briques
#define BRICK_MAX_NUMBER 50

/* Conteneur de brique
 * Celui-ci contient un tableau de briques (bricks) et la taille de ce tableau (size)
 */
typedef struct {
	Brick bricks[BRICK_MAX_NUMBER];
	int size;
} BrickContainer;

// Creer un BrickContainer vide (size = 0)
BrickContainer createBrickContainer();
// Ajoute une brique a la fin d'un BrickContainer si possible
void addBrick(BrickContainer* brickContainer, Brick b);
// Supprime la brique situ� � l'indice index 
void removeBrick(BrickContainer* brickContainer, int index);

// Supprime toutes les briques transparentes
void removeFadedBricks(BrickContainer* brickContainer);

// ----------------

// Nombre max de balles
#define BALL_MAX_NUMBER 40

/* Conteneur de balles
 * Celui-ci contient un tableau de balles (balls) et la taille de ce tableau (size)
 */
typedef struct {
	Ball balls[BALL_MAX_NUMBER];
	int size;
} BallContainer;

// Cr�er un BallContainer vide
BallContainer createBallContainer(); 
// Ajoute une Ball dans un BallContainer
// void addBall(BallContainer* ballContainer, Ball b); // A DECOMMENTER 
// Supprime la Ball situ� � l'indice donn�
// void removeBall(BallContainer* ballContainer, int index); // A DECOMMENTER 

// Supprime les balles marqu�es 'toRemove'
// void removeDeadBalls(BallContainer* ballContainer); // A DECOMMENTER 


// ----------------
// ----------------


// Structure principale contenant quasiment toutes les donn�es du jeu
typedef struct GameData {
	Ball ball;
	Paddle paddle;
	BrickContainer brickContainer;
	BallContainer ballContainer;
	int level;
	int score;
	InputData previousInput;
	SerialCom sCom;
	float paddleInputMouvement;
	Vector2 ballInput;
} GameData;

// Cr�er un nouveau jeu (niveau 0 et sans briques)
GameData createGame(); 

/* Level creation */

// Donne la position du coin haut-gauche d'une brique plac�e sur une grille
Vector2 getPositionInArrayArrangement(Vector2 startPos, Vector2 brickSize, int line, int column); 

// Creation des diff�rents niveaux
BrickContainer createLevel1(); 
BrickContainer createLevel2(); 
BrickContainer createLevel(int level); 



