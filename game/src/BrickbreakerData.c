#include "BrickbreakerData.h"
#include "DrawingFunctions.h"
// ----------------


Ball createBall(Vector2 startPos)
{
	Ball ball;
	ball.position = startPos;
	ball.direction = (Vector2) { 0.0f, -1.0f };
	ball.radius = 10.0f;
	ball.speed = 170.0f;
	ball.color = (Color) {178, 34, 34, 255};
	return ball;
}


// ----------------

Paddle createPaddle(Vector2 position, float radius)
{
	Paddle paddle;
	paddle.arc.center = position;
	paddle.arc.radius = 50;
	paddle.arc.startAngleDegree = 210;
	paddle.arc.endAngleDegree = 330;   
	paddle.speed = 5.0f;
	paddle.color = (Color) { 255, 111, 97, 255 };
	return paddle;
}


// ----------------


Brick createBrick(Vector2 topLeft, Vector2 size, int comptRest)
{
	Brick brick;
	brick.rect.topLeft = topLeft;
	brick.rect.size = size;
	brick.comptRest = comptRest;
	brick.color = targetBrickColor(comptRest);
	return brick;
}

// ----------------

BrickContainer createBrickContainer()
{
	BrickContainer bc = {
		.size = 0
	};
	return bc;
}

void addBrick(BrickContainer* bc, Brick b)
{
	if (bc->size < BRICK_MAX_NUMBER) {
		bc->bricks[bc->size] = b;
		bc->size ++;
	}
}

void removeBrick(BrickContainer* bc, int index)
{
	if (0 <= index && index < bc->size) {
		bc->bricks[index] = bc->bricks[bc->size - 1];
		bc->size -= 1;
	}
}


void removeFadedBricks(BrickContainer* brickContainer)
{
	int i = 0;
	while (i < brickContainer->size) {
		if (brickContainer->bricks[i].color.a == 0) {
			removeBrick(brickContainer, i);
		}
		else {
			i++;
		}
	}
}

// ----------------

BallContainer createBallContainer()
{
	BallContainer bc = {
		.size = 3,
	};
	return bc;
}

void addBall(BallContainer* ballContainer, Ball b)
{
	if (ballContainer->size < BALL_MAX_NUMBER) {
		ballContainer->balls[ballContainer->size] = b;
		ballContainer->size++;
	}
}

void removeBall(BallContainer* ballContainer, int index)
{
	if (0 <= index && index < ballContainer->size) {
		ballContainer->balls[index] = ballContainer->balls[ballContainer->size - 1];
		ballContainer->size--;
	}
}

void removeDeadBalls(BallContainer* ballContainer)
{
	for (int i = 0; i < ballContainer->size; i++) {
		if (ballContainer->balls[i].position.y > GetScreenHeight()) { 
			removeBall(ballContainer, i);
			i--; 
		}
	}
}



// ----------------

GameData createGame()
{
	GameData gd;
	gd.ball = createBall((Vector2) { 300, 300 });
	gd.paddle = createPaddle((Vector2) { 300, 650 }, 60);
	gd.level = 1;
	gd.brickContainer = createLevel(gd.level); 
	gd.score = 0;
	gd.previousInput = createInputData();
	gd.sCom = startArduinoConnection("COM24", 9600);
	return gd;
}


// ----------------

Vector2 getPositionInArrayArrangement(Vector2 startPos, Vector2 brickSize, int line, int column)
{	
	startPos.x += column * brickSize.x;
	startPos.y += line * brickSize.y;
	return startPos;
}

BrickContainer createLevel1() {
	BrickContainer bc = createBrickContainer();
	Vector2 brickSize = { 50, 25 };
	Vector2 startPos = { 60, 120 };
	int comptRest = 1;
	for (int lignes = 0; lignes < 5; lignes++) {
		for (int colonnes = 0; colonnes < 10; colonnes++) {
			Vector2 brickPos = getPositionInArrayArrangement(startPos, brickSize, lignes, colonnes);
			Brick newBrick = { brickPos, brickSize, comptRest, targetBrickColor(comptRest) };
			addBrick(&bc, newBrick);
		}
	}
	return bc;
}

BrickContainer createLevel2() {
	BrickContainer bc = createBrickContainer();
	Vector2 brickSize = { 50, 25 };
	Vector2 startPos = { 60, 120 };
	int comptRest = 2;
	for (int lignes = 0; lignes < 5; lignes++) {
		for (int colonnes = 0; colonnes < 10; colonnes++) {
			Vector2 brickPos = getPositionInArrayArrangement(startPos, brickSize, lignes, colonnes);
			Brick newBrick = { brickPos, brickSize, comptRest, targetBrickColor(comptRest) };
			addBrick(&bc, newBrick);
		}
	}
	return bc;
}



BrickContainer createLevel3() {

	BrickContainer bc = createBrickContainer();
	Vector2 brickSize = { 50, 25 };
	Vector2 startPos = { 60, 120 };
	int comptRest = 1;

	for (int lignes = 0; lignes < 10; lignes++) {
		for (int colonnes = 0; colonnes < 10; colonnes++) {
			Vector2 brickPos = getPositionInArrayArrangement(startPos, brickSize, lignes, colonnes);

			if ((lignes + colonnes) % 5 == 0) {
				comptRest = 3;
			}
			if ((lignes + colonnes) % 2 == 0) {
				comptRest = 2;

			}
			else {
				comptRest = 1;
			}

			Brick newBrick = { brickPos, brickSize, comptRest, targetBrickColor(comptRest) };
			addBrick(&bc, newBrick);
		}
	}
	return bc;

}
BrickContainer createLevel4() {
	BrickContainer bc = createBrickContainer();
	Vector2 brickSize = { 50, 25 };  
	Vector2 startPos = { 60, 120 };
	int comptRest = 1;

	for (int lignes = 0; lignes < 5; lignes++) {
		for (int colonnes = 0; colonnes < 10; colonnes++) {
			Vector2 brickPos = getPositionInArrayArrangement(startPos, brickSize, lignes, colonnes);

			if ((lignes + colonnes) % 2 == 0) {
				comptRest = 3;
			}
			else {
				comptRest = 1;
			}

			Brick newBrick = { brickPos, brickSize, comptRest, targetBrickColor(comptRest) };
			addBrick(&bc, newBrick);
		}
	}
	return bc;
}



BrickContainer createLevel(int level)
{
	if (level==1){
		return createLevel1();
	}
	else if (level == 2) {
		return createLevel2();  
	}
	else if (level == 3){
		return createLevel3();
	}
	else if (level == 4) {
		return createLevel4();
	}
	else {
		return createLevel1();
	}
}