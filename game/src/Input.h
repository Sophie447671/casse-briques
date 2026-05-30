#pragma once

#include <raylib.h>
#include <raymath.h>
#include "ArduinoComP1DEFI.h"

/*
 * Ce fichier contient tout le nécessaire pour gérer les entrées utilisateur
 */

typedef struct {
	float paddleXMovement;	// fleche gauche / fleche droite
	// Cheat
	Vector2 ballMovement;	// zqsd
	bool bottomWallOn;
	bool restart;
	Color paddleColor;
} InputData;

// Initialise les inputs
InputData createInputData(); 
//Remet à 0 toutes les données demandant un appui constant de l'utilisateur
void clearInputData(InputData* previousInput); 

// Met à jours les input selon l'état du clavier et de la carte arduino
void updateInputData(InputData* previousInput, SerialCom sCom); 

// Met à jours les input selon l'état du clavier
void updateInputDataWithKeyBoard(InputData* currentInput, SerialCom sCom);

// Met à jours les input selon l'état de la carte arduino
void updateInputDataWithArduino(InputData* currentInput, SerialCom sCom);
