#pragma once

#include <raylib.h>
#include <raymath.h>

/*
 * Concepts géométriques
 */

 // Rectangle

typedef struct {
	Vector2 topLeft;
	Vector2 size;
} RectangleV;


float left(RectangleV r);
float right(RectangleV r);
float top(RectangleV r);
float bottom(RectangleV r);
Vector2 topLeft(RectangleV r);
Vector2 topRight(RectangleV r);
Vector2 bottomLeft(RectangleV r);
Vector2 bottomRight(RectangleV r);
Vector2 centre(RectangleV r);

// Transforme un RectangleV en Rectangle equivalent
Rectangle toRaylibRec(RectangleV r);
// Transforme un Rectangle en RectangleV equivalent
RectangleV fromRaylibRec(Rectangle r);
// Créer un RectangleV à partir de son centre et de sa taille.
RectangleV recVCentre(Vector2 centre, Vector2 size);
// Segments (murs, briques)

typedef struct {
	Vector2 start; // point du segment avec l'ordonné (y) la plus petite
	float length;
} VerticalSegment;

VerticalSegment createVerticalSegmentVf(Vector2 start, float length);
VerticalSegment createVerticalSegmentfff(float x, float startY, float length);

typedef struct {
	Vector2 start; // point du segment avec l'abscisse (x) la plus petite
	float length;
} HorizontalSegment;

HorizontalSegment createHorizontalSegmentVf(Vector2 start, float length);
HorizontalSegment createHorizontalSegmentfff(float startX, float y, float length);

// Rectangle décomposé en segments

typedef struct {
	VerticalSegment left;
	VerticalSegment right;
	HorizontalSegment top;
	HorizontalSegment bottom;
} SegmentedRectangle;

// Calcule les quatres segments correspondant à un rectangle.
SegmentedRectangle getSegments(RectangleV r); 

// Arc de cercle (paddle)

typedef struct {
	Vector2 center;
	float radius;
	float startAngleDegree;
	float endAngleDegree;
} CircularArc;

/*
 * Objets se déplaçants
 */

typedef struct {
	Vector2 position;
	Vector2 direction;
} MovingPoint;

typedef struct {
	Vector2 position;
	float radius;
	Vector2 direction;
} MovingCircle;

