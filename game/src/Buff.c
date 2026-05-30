#include "Buff.h"

#include "BrickbreakerData.h"

BuffItem createBuffItem(Vector2 center, enum BUFF_TYPE type)
{
	BuffItem buff; // TODO
	return buff;
}


BuffItem createRandomBuff(Vector2 center)
{
	int randVal = GetRandomValue(0, 99);
	// TODO
	return createBuffItem(center, NO_BUFF);
}


BuffContainer createBuffContainer()
{
	BuffContainer bc; // TODO
	return bc;
}

void addBuff(BuffContainer* buffContainer, BuffItem b)
{
	// TODO
}

void removeBuff(BuffContainer* buffContainer, int index)
{
	// TODO
}
