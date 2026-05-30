#pragma once

#include "GameLogic.h"
#include "ArduinoComP1DEFI.h"

void movePaddle(Paddle* p, float paddleXMovement) {
	float angleInRadians = (p->arc.endAngleDegree - p->arc.startAngleDegree) * (PI / 180.0);

	float deltaX = p->arc.radius * fabs(sin(angleInRadians / 2.0f));

	p->arc.center.x += paddleXMovement * p->speed;

	if (p->arc.center.x - deltaX < 0) {
		p->arc.center.x = deltaX; 
	}
	else if (p->arc.center.x + deltaX > GetScreenWidth()) {
		p->arc.center.x = GetScreenWidth() - deltaX; 
	}
}

MovingPoint ballAsMP(Ball b)
{
	MovingPoint mp; 
	mp.direction = b.direction;
	mp.position = b.position;
	return mp;
}

MovingCircle ballAsMC(Ball b)
{
	MovingCircle mc; 
	return mc;
}




void moveBall(Ball* b, GameData* gameData) {
	float ballSpeed = b->speed * GetFrameTime();
	float ballInputNorm = Vector2Length(gameData->previousInput.ballMovement);

	if (ballInputNorm > 0.01f) {
		b->direction = Vector2Normalize(gameData->previousInput.ballMovement);
	}
	float remainingDistance = ballSpeed;
	while (remainingDistance > 0.0f) {
		IntersectionData intersection = collide(*b, gameData);
		float distanceToIntersection = Vector2Distance(b->position, intersection.intersectionPoint);

		if (intersection.hasIntersection && distanceToIntersection <= remainingDistance) {
			b->position = intersection.intersectionPoint;
			b->direction = Vector2Scale(intersection.reflectedDirection, 1.0f);
			remainingDistance -= distanceToIntersection;

			if (intersection.hittenBrickOrNULL) {
				intersection.hittenBrickOrNULL->comptRest--; 
				gameData->score++;
				arduinoSendMsg(gameData->sCom, TextFormat("Score\n")); //allumer la LED2 en bleu dès qu'une brique est cassée
			}
		}
		else {
			b->position.x += b->direction.x * remainingDistance;
			b->position.y += b->direction.y * remainingDistance;

			if (b->position.x < 0) {
				b->position.x = 0;
				b->direction.x *= -1;
				arduinoSendMsg(gameData->sCom, TextFormat("CollisionWall")); //faire clignoter la LED2 en rouge
			}
			else if (b->position.x + b->radius * 2 > GetScreenWidth()) {
				b->position.x = GetScreenWidth() - b->radius * 2;
				b->direction.x *= -1;
			}

			if (b->position.y < 0) {
				b->position.y = 0;
				b->direction.y *= -1;
			}
			else if (b->position.y + b->radius * 2 > GetScreenHeight()) {
				b->position.y = GetScreenHeight() - b->radius * 2;
				b->direction.y *= -1;
			}

			remainingDistance = 0.0f;
		}
	}
}


IntersectionData collide(Ball b, GameData* gameData) {
	IntersectionData interData;
	interData.hasIntersection = false;  


	IntersectionData paddleInter = collidePaddle(b, gameData->paddle);

	IntersectionData brickInter;
	for (int i = 0; i < gameData->brickContainer.size; i++) {
		Brick* brick = &gameData->brickContainer.bricks[i];
		brickInter = collideBrick(b, brick);

		if (brickInter.hasIntersection) {
			interData = closestIntersectionData(interData, brickInter);
		}
	}

	IntersectionData wallInter = collideWall(b, gameData->previousInput.bottomWallOn);

	interData = closestIntersectionData(interData, paddleInter);
	interData = closestIntersectionData(interData, wallInter);

	return interData;
}

IntersectionData collideWall(Ball b, bool bottomWallOn)
{
	MovingPoint movingBall;
	movingBall.position = b.position;
	movingBall.direction = b.direction;

	VerticalSegment leftWall = { 0, 0, GetScreenHeight() };
	VerticalSegment rightWall = { GetScreenWidth() - 1, 0, GetScreenHeight() };
	HorizontalSegment topWall = { 0, 0, GetScreenWidth() };

	IntersectionData interTop = computeIntersectionHorizontalSegment(movingBall, topWall);
	IntersectionData interLeft = computeIntersectionVerticalSegment(movingBall, leftWall);
	IntersectionData interRight = computeIntersectionVerticalSegment(movingBall, rightWall);

	IntersectionData interData = closestIntersectionData(interTop, interLeft);
	interData = closestIntersectionData(interData, interRight);

	if (bottomWallOn) {
		HorizontalSegment bottomWall = { 0, GetScreenHeight() - 1, GetScreenWidth() };
		IntersectionData interBottom = computeIntersectionHorizontalSegment(movingBall, bottomWall);
		interData = closestIntersectionData(interData, interBottom);
	}
	else {
		b.position.y += b.direction.y; 
	}

	return interData;
}

IntersectionData collidePaddle(Ball b, Paddle paddle) {
	IntersectionData interData;
	MovingPoint movingBall;
	movingBall.position = b.position;
	movingBall.direction = b.direction;

	interData = computeIntersectionCircularArc(movingBall, paddle.arc);

	if (interData.hasIntersection) {
		float collisionPosition = interData.intersectionPoint.x - paddle.arc.center.x;

		float influenceFactor = collisionPosition / paddle.arc.radius;

		if (influenceFactor > 1.0f) {
			influenceFactor = 1.0f;
		}
		else if (influenceFactor < -1.0f) {
			influenceFactor = -1.0f;
		}

		float angleMax = PI / 3.0f; 
		float angleRebond = influenceFactor * angleMax; 

		b.direction.x = sin(angleRebond);
		b.direction.y = -fabs(cos(angleRebond)); 

		float norm = sqrt(b.direction.x * b.direction.x + b.direction.y * b.direction.y);
		if (norm > 0) {
			b.direction.x /= norm;
			b.direction.y /= norm;
		}

		interData.reflectedDirection = b.direction;
	}

	return interData;
}





IntersectionData collideBrick(Ball b, Brick* brick) {
	IntersectionData interData;
	MovingPoint movingBall;
	movingBall.position = b.position;
	movingBall.direction = b.direction;

	interData.hasIntersection = false;

	if (brick->comptRest > 0) {
		interData = computeIntersectionRectangle(movingBall, brick->rect);
		if (interData.hasIntersection) {
			interData.hittenBrickOrNULL = brick;
		}
	}
	return interData;
}



void checkVictoryAndChangeLevel(GameData* game) {
	if (game->brickContainer.size == 0) {
		game->level++;
		game->brickContainer = createLevel(game->level);
		arduinoSendMsg(game->sCom, "LEVELSUP\n"); //les 3LEDS clignotent en rouge 1 fois 
	}
	if (game->previousInput.restart) {
		game->level = 1;
		game->score = 0;
		game->brickContainer = createLevel(game->level);
		game->previousInput.restart = false;
	}
}

void moveBalls(GameData* game)
{
	for (int i = 0; i < game->ballContainer.size; i++) {
		moveBall(&game->ballContainer.balls[i], game);
	}
}


void tryLaunchBall(GameData* game) {
	if (game->ballContainer.size < BALL_MAX_NUMBER) {
		Ball newBall = createBall((Vector2) { 300, 300 }); 
		newBall.radius = 10; 
		addBall(&game->ballContainer, newBall); 
		game->ballContainer.size++;
	}
}



void checkScore(GameData* game) {
	if (game->score > 0 && game->score % 10 == 0) {
		if (game->ballContainer.size < BALL_MAX_NUMBER) {
			Ball newBall = createBall((Vector2) { 300, 300 }); 
			newBall.radius = 10;
			addBall(&game->ballContainer, newBall); 
		}
	}
}
void updateGame(GameData* game)
{
	moveBall(&game->ball, game);
	//moveBalls(&game->ballContainer, game);
	movePaddle(&game->paddle, game->previousInput.paddleXMovement, game);
	fadeBricks(&game->brickContainer);
	removeFadedBricks(&game->brickContainer);
	checkVictoryAndChangeLevel(game);
	checkScore(game);
	updateInputData(&game->previousInput, game->sCom);
}

void moveBuffs(GameData* game)
{
	// TODO
}

void moveBuff(BuffItem* buff, GameData* game)
{
	// TODO
}

void updateBuffsAfterMove(GameData* game)
{
	// TODO
}

void applyBuff(enum BUFF_TYPE buff, GameData* game)
{
	// TODO
}

