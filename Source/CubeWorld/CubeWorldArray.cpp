// Fill out your copyright notice in the Description page of Project Settings.
#include "CubeWorldArray.h"

CubeWorldArray::CubeWorldArray()
{
	/*начальное заполнение */
	aWorld.Init(0, CUBE_WORLD_HEIGHT*CUBE_WORLD_WIDTH*CUBE_WORLD_DEPTH);
}

CubeWorldArray::~CubeWorldArray()
{
}

int32 CubeWorldArray::getXYZ(int32 x, int32 y, int32 z)
{
	return aWorld[x + CUBE_WORLD_WIDTH * (y + CUBE_WORLD_DEPTH * z)];
}

void CubeWorldArray::setXYZ(int32 x, int32 y, int32 z, int32 value)
{
	aWorld[x + CUBE_WORLD_WIDTH * (y + CUBE_WORLD_DEPTH * z)] = value;
}
