#pragma once

#include <raylib.h>
#include <raymath.h>

#include "BrickbreakerData.h"
#include "GeometryPrimitive.h"
#include "GeometryIntersection.h"
#include "Input.h"
#include "Buff.h"
#include "DrawingFunctions.h"

// Calcule la nouvelle version de la raquette après déplacement
void movePaddle(Paddle* p, float paddleXMovement); 

// Trandforme une balle en "MovingPoint"
MovingPoint ballAsMP(Ball b);
// // Trandforme une balle en "MovingCircle"
// MovingCircle ballAsMC(Ball b); // A DECOMMENTER 

// Déplace une balle. Plus tard, cette fonction mettera aussi à jour les briques tapées par la balle. 
void moveBall(Ball* b, GameData* gameData); 
// Calcule la première intersection entre la balle et l'environnement
IntersectionData collide(Ball b, GameData* gameData /*Ball b, Paddle paddle, Brick brick*/); // SIGNATURE A CHANGER
// Calcule la première intersection entre la balle et les murs
IntersectionData collideWall(Ball b, bool bottomWallOn); 
// Calcule la première intersection entre la balle et la raquette (si elle existe)
IntersectionData collidePaddle(Ball b, Paddle paddle);  
// Calcule la première intersection entre la balle et une brique (si elle existe)
IntersectionData collideBrick(Ball b, Brick* brick);  



// Vérifie si le niveau est fini. Peut aussi redémarer le jeu.
void checkVictoryAndChangeLevel(GameData* game); 

// Déplace plusieurs balles
// void moveBalls(GameData* game); // A DECOMMENTER 
// Essaye de lancer une nouvelle balle à partir de la position de la raquette.
// void tryLaunchBall(GameData* game);  // A DECOMMENTER 

// Gère tout les aspects perméttant de mettre à jour la logique du jeu
void updateGame(GameData* game);

// Déplace plusieurs buffs.
// void moveBuffs(GameData* game); // A DECOMMENTER 
// Déplace un buff vers le bas. Enregistre aussi le ramassage de buff et la disparition de ceux-ci en dehors de l'écran
// void moveBuff(BuffItem* buff, GameData* game); // A DECOMMENTER 
// Applique les buffs ramassés, supprime les buffs ramassés et perdus.
// void updateBuffsAfterMove(GameData* game); // A DECOMMENTER 
// Applique un buff
// void applyBuff(enum BUFF_TYPE buff, GameData* game); // A DECOMMENTER 