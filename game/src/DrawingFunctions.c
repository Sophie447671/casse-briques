#include "DrawingFunctions.h"

#include <raylib.h>
#include <raymath.h>

#include "GeometryPrimitive.h"

void drawBall(Ball b) {
	DrawCircleV(b.position, b.radius, b.color);
}

void drawPaddle(Paddle paddle)
{
	DrawCircleSector(paddle.arc.center, paddle.arc.radius, paddle.arc.startAngleDegree, paddle.arc.endAngleDegree, 100, paddle.color);
}

void drawBrick(Brick brick)
{
	Rectangle raylibBrick = toRaylibRec(brick.rect);
	DrawRectangleRec(raylibBrick, brick.color);
	DrawRectangleLinesEx(toRaylibRec(brick.rect), 1.0f, BLACK);

}

// ----------------


void drawBricks(BrickContainer* bc)
{
	for (int i = 0; i < bc->size; i++) {
		drawBrick(bc->bricks[i]);
	}
}

void drawBalls(BallContainer* bc)
{
	for (int i = 0; i < bc->size; i++) {
		drawBall(bc->balls[i]);
		//DrawCircleV(bc->balls[i].position, bc->balls[i].radius, bc->balls[i].color);
	}
}

// ----------------

Color targetBrickColor(int hitLeft)
{
	if (hitLeft <= 0) {
		return BLANK;
	}
	else if (hitLeft == 1) {
		return YELLOW;
	}
	else if (hitLeft == 2) {
		return (Color) { 255, 204, 0, 255 };
	}
	else {
		return BLUE;
	}
}

Color fadeToward(Color current, Color target, float fadeValue) {
	Vector4 currentAsV4 = ColorNormalize(current);
	Vector4 targetAsV4 = ColorNormalize(target);

	Vector4 res = Vector4Lerp(currentAsV4, targetAsV4, fadeValue);
	return ColorFromNormalized(res);
}


void fadeBricks(BrickContainer* bc, float fadeValue)
{
	for (int i = 0; i < bc->size; i++) {
		Brick* brick = &bc->bricks[i];


		if (brick->comptRest > 0) {
			Color target = targetBrickColor(brick->comptRest);
			brick->color = fadeToward(brick->color, target, 1.0);
		}

		if (brick->comptRest == 0) {
			brick->color = BLANK;
		}
	}
}


// ----------------


void drawRectangleWithText(const char* text, RectangleV rect, Color background) {
	// TODO
}


void drawBuffs(BuffContainer* bc)
{
	// TODO
}

void drawBuff(BuffItem buff)
{
	// TODO
}


// ----------------


void drawGame(GameData* game)
{
	drawPaddle(game->paddle);
	drawBricks(&game->brickContainer);
	//drawBalls(&game->ballContainer);
	drawBall(game->ball);
	DrawFPS(10, 10);
	DrawText(TextFormat("paddleX :%.1f\n", game->paddle.arc.center.x), 15, 30, 10, BLACK);
	DrawText(TextFormat("ballY : %.1f\n", game->ball.position.y), 15, 40, 10, BLACK);
	DrawText(TextFormat("ballX : %.1f\n", game->ball.position.x), 15, 50, 10, BLACK);
	//DrawText(TextFormat("ball dirx : %.1f\n", game->ball.direction.x), 15, 60, 10, BLACK);
	//DrawText(TextFormat("ball diry : %.1f\n", game->ball.direction.y), 15, 70, 10, BLACK);
	DrawText(TextFormat("Nom : %s", "Sophie VALLENET"), 475, 750, 10, BLACK);
	DrawText(TextFormat("level: %d", game->level), 15, 60, 10, BLACK); 
	DrawText(TextFormat("score: %d", game->score), 15, 70, 10, BLACK);
	DrawText(TextFormat("mur bas actif: %d", game->previousInput.bottomWallOn), 15, 80, 10, BLACK);
	DrawText(TextFormat("taille brickcontainer : %d\n", game->brickContainer.size), 15, 90, 10, BLACK);


}