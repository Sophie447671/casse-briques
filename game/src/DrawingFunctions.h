#pragma once



//#include <raylib.h>
//#include <raymath.h>

#include "BrickbreakerData.h"
#include "Buff.h"


// ----------------

void drawBall(Ball b);
void drawPaddle(Paddle p); 
void drawBrick(Brick b); 

// ----------------

void drawBricks(BrickContainer* bc);
// void drawBalls(BallContainer * bc); // A DECOMMENTER

// ----------------

// Calcule la couleur associé au nombre de coup restant pour détruire la brique
Color targetBrickColor(int hitLeft); 

// Rapproche une couleur d'une autre. 
// La couleur renvoyée correspond à un entre-deux entre current et target. 
// Plus fadeValue est proche de 1, plus le résultat est proche de target.
Color fadeToward(Color current, Color target, float fadeValue);

// Rapproche la couleur de chaque brique de la couleur correspondant à leur hitLeft
// void fadeBricks(BrickContainer* bc, float fadeValue); // A DECOMMENTER

// ----------------

// Dessine un rectangle contenant un texte.
// void drawRectangleWithText(const char* text, RectangleV rect, Color background); // A DECOMMENTER

// void drawBuffs(BuffContainer* bc); // A DECOMMENTER
// void drawBuff(BuffItem buff); // A DECOMMENTER

// ----------------

void drawGame(GameData* game); 
