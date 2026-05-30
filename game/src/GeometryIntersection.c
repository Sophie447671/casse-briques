#include "GeometryIntersection.h"


// -----------------

IntersectionData createIntersectionData() {
	IntersectionData interData;
	interData.hittenBrickOrNULL = NULL;
	interData.hasIntersection = false;
	interData.intersectionDistance = 0;
	interData.intersectionPoint = (Vector2) { 0, 0 };
	interData.reflectedDirection = (Vector2) { 0, 0 };
	return interData;
}

IntersectionData closestIntersectionData(IntersectionData a, IntersectionData b) {
	if (a.hasIntersection && b.hasIntersection) {
		if (a.intersectionDistance < b.intersectionDistance) {
			return a;
		}
		else {
			return b;
		}
	}
	else if (a.hasIntersection) {
		return a;
	}
	else if (b.hasIntersection) {
		return b;
	}
	else {
		return a;
	}

}


// -----------------

IntersectionData computeIntersectionVerticalSegment(MovingPoint ball, VerticalSegment segment)
{
	IntersectionData interData = createIntersectionData();
	if (ball.direction.x == 0) {
		return interData;
	}

	float D = (segment.start.x - ball.position.x) / ball.direction.x;
	if (D < 0 || (D >= 0 && D < 0.01)) {
		return interData;
	}

	Vector2 intersectionPoint = {
		ball.position.x + D * ball.direction.x,
		ball.position.y + D * ball.direction.y,
	};

	if (intersectionPoint.y<segment.start.y || intersectionPoint.y>segment.start.y + segment.length) {
		return createIntersectionData();
	}

	interData.hasIntersection = true;
	interData.intersectionDistance = D;
	interData.intersectionPoint = intersectionPoint;
	interData.reflectedDirection = (Vector2) { -ball.direction.x, ball.direction.y };
	return interData;
}

IntersectionData computeIntersectionHorizontalSegment(MovingPoint ball, HorizontalSegment segment)
{
	IntersectionData interData = createIntersectionData();

	if (ball.direction.y == 0) {
		return interData;
	}

	float D = (segment.start.y - ball.position.y) / ball.direction.y;
	if (D < 0 || (D >= 0 && D < 0.01)) {
		return interData;
	}

	Vector2 intersectionPoint = {
		ball.position.x + D * ball.direction.x,
		ball.position.y + D * ball.direction.y,
	};

	if (intersectionPoint.x<segment.start.x || intersectionPoint.x>segment.start.x + segment.length) {
		return createIntersectionData();
	}

	interData.hasIntersection = true;
	interData.intersectionDistance = D;
	interData.intersectionPoint = intersectionPoint;
	interData.reflectedDirection = (Vector2) { ball.direction.x, -ball.direction.y };

	return interData;
}

IntersectionData computeIntersectionRectangle(MovingPoint ball, RectangleV r)
{
	IntersectionData interData = createIntersectionData();
	SegmentedRectangle segments = getSegments(r);
	IntersectionData leftIntersection = computeIntersectionVerticalSegment(ball, segments.left);
	IntersectionData rightIntersection = computeIntersectionVerticalSegment(ball, segments.right);
	IntersectionData topIntersection = computeIntersectionHorizontalSegment(ball, segments.top);
	IntersectionData bottomIntersection = computeIntersectionHorizontalSegment(ball, segments.bottom);

	interData = closestIntersectionData(leftIntersection, rightIntersection);
	interData = closestIntersectionData(interData, topIntersection);
	interData = closestIntersectionData(interData, bottomIntersection);

	return interData;
}

IntersectionData computeIntersectionCircularArc(MovingPoint ball, CircularArc arc)
{
	IntersectionData interData = createIntersectionData();

	// projection du centre de l'arc sur la droite du movement
	float d_proj = Vector2DotProduct(Vector2Subtract(arc.center, ball.position), ball.direction);
	Vector2 projectionPoint = Vector2Add(ball.position, Vector2Scale(ball.direction, d_proj));

	float distanceProjCenter = Vector2Distance(arc.center, projectionPoint);
	if (d_proj < 0 || distanceProjCenter > arc.radius) {
		return interData; // NO HIT
	}

	// Phytagore
	float distanceProjHit = sqrtf(arc.radius * arc.radius - distanceProjCenter * distanceProjCenter);

	// Distance entre balle et point d'intersection
	float d_hit = d_proj - distanceProjHit / Vector2Length(ball.direction);
	Vector2 intersectionPoint = Vector2Add(ball.position, Vector2Scale(ball.direction, d_hit));

	// Vecteur normal à l'arc de cercle en le point d'intersection
	Vector2 normal = Vector2Normalize(Vector2Subtract(intersectionPoint, arc.center));
	Vector2 orthogonal = { -normal.y, normal.x };

	float coordNormal = Vector2DotProduct(ball.direction, normal);
	float coordOrtho = Vector2DotProduct(ball.direction, orthogonal);

	Vector2 reflected = Vector2Add(Vector2Scale(normal, -coordNormal), Vector2Scale(orthogonal, coordOrtho));
	reflected = Vector2Normalize(reflected);

	float angleInterPoint = angleFromVector2(normal);
	if (!isAngleBetween(angleInterPoint, arc.startAngleDegree, arc.endAngleDegree)) {
		return interData; // NO HITs
	}

	interData.hasIntersection = true;
	interData.intersectionDistance = d_hit;
	interData.intersectionPoint = intersectionPoint;
	interData.reflectedDirection = reflected;

	return interData;


}

// -----------------

IntersectionData computeIntersectionVerticalSegmentCircle(MovingCircle ball, VerticalSegment segment) {
	return createIntersectionData(); // TODO
}

IntersectionData computeIntersectionHorizontalSegmentCircle(MovingCircle ball, HorizontalSegment segment) {
	return createIntersectionData(); // TODO
}

IntersectionData computeIntersectionRectangleCircle(MovingCircle ball, RectangleV r)
{
	return createIntersectionData(); // TODO
}

IntersectionData computeIntersectionCircularArcCircle(MovingCircle ball, CircularArc arc)
{
	return createIntersectionData(); // TODO
}


// ----------------- 

float angleFromVector2(Vector2 v)
{
	return Vector2Angle((Vector2) { 1, 0 }, v) / PI * 180;
}

float normalizeAngle(float angle)
{
	float angleMod360 = fmod(angle, 360);
	if (angle < 0) angle += 360;
	return angle;

}

bool isAngleBetween(float angle, float startAngle, float endAngle)
{
	float angleNorm = normalizeAngle(angle);
	float sAngleNorm = normalizeAngle(startAngle);
	float eAngleNorm = normalizeAngle(endAngle);

	if (sAngleNorm <= eAngleNorm) {
		return sAngleNorm <= angleNorm && angleNorm <= eAngleNorm;
	}
	else {
		return !(eAngleNorm <= angleNorm && angleNorm <= sAngleNorm);
	}
}
