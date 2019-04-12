// Fill out your copyright notice in the Description page of Project Settings.
/* массив точек мира */
/* будет браться из DB */
#pragma once
#define CUBE_WORLD_HEIGHT 200
#define CUBE_WORLD_WIDTH 200
#define CUBE_WORLD_DEPTH 200
#include "CoreMinimal.h"

/**
 * 
 */
class CUBEWORLD_API CubeWorldArray
{
public:
	CubeWorldArray();
	~CubeWorldArray();

	/* весь мир */
	/* aWorld[x + width * (y + depth * z)] */
	/* x is the height, y is the width and z is the depth. To access arr[6][3][7] use arr[6 + 5 * (3 + 20 * 7)] */
	TArray<int32> aWorld;

	/* выдает текстуру по координате */
	int32 getXYZ(int32 x, int32 y, int32 z);

	/* устанавливает текстуру в точку мира */
	void setXYZ(int32 x, int32 y, int32 z, int32 value);
};
