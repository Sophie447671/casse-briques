/*******************************************************************************************
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

/**
*  Projet 1 DEFI
*     Nom prénom : Vallenet Sophie
*     Numéro binôme sur Moodle : K
*/

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "ArduinoComP1DEFI.h"

#include "BrickbreakerData.h"
#include "DrawingFunctions.h"
#include "GameLogic.h"



//----------------------------------------------------------------------------------
// Fonction main
//----------------------------------------------------------------------------------
int main(void)
{
	//--------------------------------------------------------------------------------------
	// Initialization (code exécuté une fois au début du programme)
	//--------------------------------------------------------------------------------------
	InitWindow(600,760, "Projet 1 DEFI - VALLENET Sophie"); //doit être 600x800-
	InitAudioDevice();      // Initialize audio device
	SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

	/* --> Votre code ici (A) */
	GameData gameData = createGame(); 
	gameData.brickContainer = createLevel1();
	gameData.ballContainer = createBallContainer();

	//openArduinoConnection(gameData.sCom);
	//openSerialConnection(gameData.sCom);
	//startArduinoConnection("COM24", 9600);
	//startArduinoConnection(&gameData.sCom, 9600);
	gameData.sCom = startArduinoConnection("COM24", 9600);

	Vector2 ballInput = {
	.x = 0,
	.y = 0
	};

	float paddleInputMouvement = 0;

	//--------------------------------------------------------------------------------------
	// Game loop principale (code exécuté à chaque frame (60 fois par secondes))
	//--------------------------------------------------------------------------------------
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		/*
		 * Gestion de tout ce qui n'est pas l'affichage ici
		 */

		 /* --> Votre code ici (B) */

		gameData.paddleInputMouvement = paddleInputMouvement;
		gameData.ballInput = ballInput;	
		updateGame(&gameData);
		checkVictoryAndChangeLevel(&gameData);


		//float ballInputNorm = Vector2Length(ballInput);

		
		/*if (ballInputNorm > 0.01) {
			gameData.ball.direction = Vector2Scale(ballInput, ballInputNorm);
		}
		else {
			gameData.ball.direction.x = 0;
			gameData.ball.direction.y = 0;
		}*/

		//Exe 29, rebond.
		/*float distanceAParcourir = gameData.ball.speed * GetFrameTime();
		VerticalSegment murGauche = createVerticalSegmentVf((Vector2) { 0, 0 }, 740);
		MovingPoint mp = {
			.position = gameData.ball.position,
			.direction = gameData.ball.direction
		};
		IntersectionData inter = computeIntersectionVerticalSegment(mp, murGauche);

		if (inter.hasIntersection && inter.intersectionDistance <= distanceAParcourir) {
			// Hack, on ferra mieux après
			gameData.ball.position = inter.intersectionPoint;
			gameData.ball.direction = inter.reflectedDirection;
		}
		else {
			gameData.ball.position = Vector2Add(gameData.ball.position, Vector2Scale(gameData.ball.direction, distanceAParcourir));
		}*/

		/*
		Vector2 ballMovement = Vector2Scale(ball.direction, GetFrameTime());
		ball.position = Vector2Add(ball.position, ballMovement);*/



		/*
		 * Gestion de l'affichage ici
		 */
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);


			/* --> Votre code ici (C) */

			//drawBall(gameData.ball);
			//drawPaddle(gameData.paddle);
			//drawBricks(&gameData.brickContainer);
			//drawBalls(gameData.ballContainer);
			drawGame(&gameData);


		}
		EndDrawing();
	}

	//--------------------------------------------------------------------------------------
	// De-Initialization (code exécuté une fois à la fin du programme)
	//--------------------------------------------------------------------------------------

	/* --> Votre code ici (D) */

	CloseAudioDevice();     // Close audio context
	CloseWindow();          // Close window and OpenGL context
	closeArduinoConnection(gameData.sCom);
	return 0;
}
