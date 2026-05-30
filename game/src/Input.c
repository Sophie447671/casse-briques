#pragma once

#include "Input.h"
#include <string.h>
#include "ArduinoComP1DEFI.h"
#include "BrickbreakerData.h";




InputData createInputData()
{
	InputData res;
	res.ballMovement = (Vector2) { 0, 0 };
	res.paddleXMovement = 0;
	res.bottomWallOn = true;
	res.restart = false;
	res.paddleColor = (Color) { 255, 111, 97, 255 };
	return res;
}

void clearInputData(InputData* previousInput)
{
	previousInput->ballMovement = (Vector2) { 0, 0 };
	previousInput->paddleXMovement = 0;
}

void updateInputData(InputData* previousInput, SerialCom sCom)
{
	clearInputData(previousInput);
	updateInputDataWithKeyBoard(previousInput, sCom);
	updateInputDataWithArduino(previousInput, sCom);

}


void updateInputDataWithKeyBoard(InputData* currentInput,  SerialCom sCom)
{
	if (IsKeyDown(KEY_A)) {
		currentInput->ballMovement.x = -1.0f;
	}
	else if (IsKeyDown(KEY_D)) {
		currentInput->ballMovement.x = 1.0f;
	}
	else {
		currentInput->ballMovement.x = 0.0f;
	}
	if (IsKeyDown(KEY_W)) {
		currentInput->ballMovement.y = -1.0f;
	}
	else if (IsKeyDown(KEY_S)) {
		currentInput->ballMovement.y = 1.0f;
	}
	else {
		currentInput->ballMovement.y = 0.0f;
	}

	if (IsKeyDown(KEY_LEFT)) {
		currentInput->paddleXMovement = -1;
		arduinoSendMsg(sCom, TextFormat("LEFT\n")); //allumer led1 en vert pour indiquer un déplacement vers la gauche
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		currentInput->paddleXMovement = 1;
		arduinoSendMsg(sCom, TextFormat("RIGHT\n")); //allumer led3 en vert pour indiquer un déplacement vers la droite
	}
	else {
		currentInput->paddleXMovement = 0.0f;
	}

	if (IsKeyPressed(KEY_B)) {
		currentInput->bottomWallOn = !currentInput->bottomWallOn;
	}

	if (IsKeyPressed(KEY_R)) {
		currentInput->restart = true;
	}
	else {
		currentInput->restart = false;
	}

	if (IsKeyPressed(KEY_SPACE)) {
		//tryLaunchBall(&game);
	}
}


void updateInputDataWithArduino(InputData* currentInput, SerialCom sCom)
{
	char start = '<';
	char end = '>';
	char* msgRecu = arduinoReceiveLatestNewMsg(sCom, start, end);

	if (msgRecu) {
		printf("Message reçu : %s\n", msgRecu);

		int x_position;
		if (sscanf(msgRecu,"<%d>", &x_position)==1){
			currentInput->paddleXMovement = x_position; 
			printf("Position du paddle mise à jour : %d\n", currentInput->paddleXMovement);
		}

		unsigned long distance;
		if (sscanf(msgRecu, "<%lu>", &distance) == 1) {
			if (distance < 25) {
				float proportion = (float)distance / 25; 
				currentInput->paddleXMovement = (int)(proportion * GetScreenWidth());
				printf("Distance mesurée : %lu, Position du paddle mise à jour : %d\n", distance, currentInput->paddleXMovement); //le paddle bouge dès qu'on trouve un obstacle à moins de 25 cm du capteur ultrason.

			}
		}

		//changer la couleur de la paddle en fonction de la vitesse du mouvement de celle-ci
		if (sscanf(msgRecu, "RAPIDE") != NULL) {
			printf("Mouvement rapide détecté \n");
			currentInput->paddleColor = (Color) { 255, 0, 0, 255 };
		}
		else if (sscanf(msgRecu, "LENT") != NULL) {
			printf("Mouvement lent détecté");
			currentInput->paddleColor = (Color) { 255, 255, 0, 255 };
		}
		else if (sscanf(msgRecu, "NONE")!= NULL) {
			currentInput->paddleColor = (Color) { 255, 111, 97, 255 };

		}

		//augmenter la vitesse de la balle dès qu'on appuie sur le BP (<30)
	}
}


