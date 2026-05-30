#include <GeometryPrimitive.h>


float left(RectangleV r)
{
	return r.topLeft.x;
}

float right(RectangleV r)
{
	return r.topLeft.x + r.size.x;
}

float top(RectangleV r)
{
	return r.topLeft.y;
}

float bottom(RectangleV r)
{
	return r.topLeft.y + r.size.y;
}

Vector2 topLeft(RectangleV r)
{
	return r.topLeft;
}

Vector2 topRight(RectangleV r)
{
	Vector2 res = {right(r), top(r)};
	return res;
}

Vector2 bottomLeft(RectangleV r)
{
	Vector2 res = {left(r), bottom(r)};
	return res;
}

Vector2 bottomRight(RectangleV r)
{
	Vector2 res = {right(r), bottom(r)};
	return res;
}

Vector2 centre(RectangleV r)
{
	Vector2 res = { r.topLeft.x + r.size.x/2, r.topLeft.y + r.size.y /2 };
	return res;
}

Rectangle toRaylibRec(RectangleV r)
{
	Rectangle out = { r.topLeft.x,r.topLeft.y,r.size.x,r.size.y };
	return out;
}

RectangleV fromRaylibRec(Rectangle r)
{
	RectangleV out = { r.x,r.y,r.width,r.height };
	return out;
}

RectangleV recVCentre(Vector2 centre, Vector2 size)
{
	RectangleV out = { centre.x - size.x / 2,centre.y - size.y / 2 };
	return out;
}

// -----------------

VerticalSegment createVerticalSegmentfff(float x, float startY, float length)
{
	VerticalSegment vs;
	vs.start = (Vector2) { x, startY };
	vs.length = length;
	return vs;
}

VerticalSegment createVerticalSegmentVf(Vector2 start, float length)
{
	VerticalSegment vs;
	vs = createVerticalSegmentfff(start.x, start.y, length);
	return vs;
}

HorizontalSegment createHorizontalSegmentfff(float startX, float y, float length)
{
	HorizontalSegment hs;
	hs.start = (Vector2) { startX, y };
	hs.length = length;
	return hs;
}

HorizontalSegment createHorizontalSegmentVf(Vector2 start, float length)
{
	HorizontalSegment hs;
	hs = createHorizontalSegmentfff(start.x, start.y, length);
	return hs;
}


SegmentedRectangle getSegments(RectangleV r)
{
	SegmentedRectangle out; 
	out.left = createVerticalSegmentVf(topLeft(r), r.size.y);
	out.right = createVerticalSegmentVf((Vector2) { r.topLeft.x + r.size.x, r.topLeft.y }, r.size.y);
	out.top = createHorizontalSegmentVf(topLeft(r), r.size.x);
	out.bottom = createHorizontalSegmentVf((Vector2) { r.topLeft.x, r.topLeft.y + r.size.y }, r.size.x);
	return out;
}



