// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define CUBE_WORLD_SIZE 20
#include "CubeWorldArray.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "CubeVoxel.h"
#include "PerlinNoise.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "CubeGen.generated.h"

UCLASS()
class CUBEWORLD_API ACubeGen : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubeGen();
	~ACubeGen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	CubeWorldArray* cubeWorldArray;


	UPROPERTY()
		USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		int chunkSize = 50;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		float noiseScale = .05f;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		float threshold = .5f;

	/*Blueprint Reference of UsefulActor class*/
	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		TSubclassOf<class ACubeVoxel> cubeVoxel;

	UPROPERTY(EditAnywhere, Category = "ActorSpawning")
		FVector Location;

	/**************************************************/

	UFUNCTION(BlueprintCallable)
		void Generate(FVector StartLocation);

	/*Спавнет массив мира*/
	UFUNCTION(BlueprintCallable)
		void ShowWorld();


};
