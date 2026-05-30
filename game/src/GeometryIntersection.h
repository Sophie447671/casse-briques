#pragma once

#include <raylib.h>
#include <raymath.h>

#include "GeometryPrimitive.h"
#include "BrickbreakerData.h"

/*
 * Données détaillant la collision
 */

typedef struct {
	bool hasIntersection;
	float intersectionDistance; // Toujours >= 0
	Vector2 intersectionPoint;
	Vector2 reflectedDirection; // Nouvelle direction de la balle apr�s collision
	Brick* hittenBrickOrNULL; // Brick touch�e ou NULL si l'intersection ne concerne pas une brique
} IntersectionData;

// Créer une donnée d'intersection représentant l'absence d'intersection.
IntersectionData createIntersectionData();
// Renvois l'intersection la plus proche. On supposera qu'en cas de hasIntersection, les deux intersectionDistance sont positives.
IntersectionData closestIntersectionData(IntersectionData a, IntersectionData b);


/*
 * Calcul d'intersection
 *
 * Chaque fonction ci-dessous calcule l'intersection entre un MovingPoint ou MovingCircle (plus difficile) et l'une des quatres géométries pouvant être tapés.
 */

IntersectionData computeIntersectionVerticalSegment(MovingPoint ball, VerticalSegment segment);
IntersectionData computeIntersectionHorizontalSegment(MovingPoint ball, HorizontalSegment segment); // A DECOMMENTER
IntersectionData computeIntersectionRectangle(MovingPoint ball, RectangleV r); 
IntersectionData computeIntersectionCircularArc(MovingPoint ball, CircularArc arc);

// IntersectionData computeIntersectionVerticalSegmentCircle(MovingCircle ball, VerticalSegment segment); // A DECOMMENTER 
// IntersectionData computeIntersectionHorizontalSegmentCircle(MovingCircle ball, HorizontalSegment segment); // A DECOMMENTER
// IntersectionData computeIntersectionRectangleCircle(MovingCircle ball, RectangleV r); // A DECOMMENTER
// IntersectionData computeIntersectionCircularArcCircle(MovingCircle ball, CircularArc arc); // A DECOMMENTER


// Pour la gestion des angles
float angleFromVector2(Vector2 v);
float normalizeAngle(float angle);
bool isAngleBetween(float angle, float startAngle, float endAngle);