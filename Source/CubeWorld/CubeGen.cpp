// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeGen.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ACubeGen::ACubeGen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/CubeWorld/VoxelCube"));
	UStaticMesh* Asset = MeshAsset.Object;

	Mesh->SetStaticMesh(Asset);

	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepWorldTransform);

	cubeWorldArray = new CubeWorldArray();

}

ACubeGen::~ACubeGen()
{
	delete cubeWorldArray;
}

// Called when the game starts or when spawned
void ACubeGen::BeginPlay()
{
	Super::BeginPlay();

	//FVector Location(0.0f, 0.0f, 0.0f);
	//FRotator Rotation(0.0f, 0.0f, 0.0f);
	//FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor<AProjectile>(Location, Rotation, SpawnInfo);

	Generate(FVector(1, 1, 1));
	ShowWorld();

}

// Called every frame
void ACubeGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeGen::Generate(FVector StartLocation)
{
	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn;
	int32 x, y, z;
	if (cubeVoxel) {

		FVector pVector;
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Print32f(TEXT("IM Spawn")));

		//go through each block position
		for (x = 0; x < chunkSize; x++) {
			for (y = 0; y < chunkSize; y++) {
				for (z = 0; z < chunkSize; z++) {

					float noiseValue = pn.noise(x * noiseScale, y * noiseScale, z * noiseScale);//get value of the noise at given x, y, and z.
					//UE_LOG(LogTemp, Warning, TEXT("noiseValue, %f "), noiseValue);
					if (noiseValue >= threshold) {//is noise value above the threshold for placing a block?

						//ignore this block if it's a sphere and it's outside of the radius (ex: in the corner of the chunk, outside of the sphere)
						//distance between the current point32 with the center point32. if it's larger than the radius, then it's not inside the sphere.
						/*float raduis = chunkSize / 2;
						if (sphere && Vector3.Distance(new Vector3(x, y, z), Vector3.one * raduis) > raduis)
							continue;*/
							//pVector + StartLocation = FVector(x * 100, y * 100, z * 100);
						cubeWorldArray->setXYZ(x, y, z, 1);

						//aWorldMap.Add(FVector(x * 100, y * 100, z * 100)+ StartLocation);

					}
					else {
						cubeWorldArray->setXYZ(x, y, z, 0);
					}

				}
			}
		}

		/*помечаем на удаление блоки в заполенных областях*/
		for (x = 1; x < chunkSize - 1; x++) {
			for (y = 1; y < chunkSize - 1; y++) {
				for (z = 1; z < chunkSize - 1; z++) {

					if (
						(cubeWorldArray->getXYZ(x + 1, y, z) > 0) &&
						(cubeWorldArray->getXYZ(x + 1, y, z) > 0) &&
						(cubeWorldArray->getXYZ(x, y + 1, z) > 0) &&
						(cubeWorldArray->getXYZ(x, y - 1, z) > 0) &&
						(cubeWorldArray->getXYZ(x, y, z + 1) > 0) &&
						(cubeWorldArray->getXYZ(x, y, z - 1) > 0)
						)
					{
						cubeWorldArray->setXYZ(x, y, z, 1000);

					}
				}//z
			}//y
		}//x

		 /*удаляем блоки в заполенных областях*/
		for (x = 1; x < chunkSize - 1; x++) {
			for (y = 1; y < chunkSize - 1; y++) {
				for (z = 1; z < chunkSize - 1; z++) {

					if (
						(cubeWorldArray->getXYZ(x + 1, y, z) == 1000) &&
						(cubeWorldArray->getXYZ(x + 1, y, z) == 1000) &&
						(cubeWorldArray->getXYZ(x, y + 1, z) == 1000) &&
						(cubeWorldArray->getXYZ(x, y - 1, z) == 1000) &&
						(cubeWorldArray->getXYZ(x, y, z + 1) == 1000) &&
						(cubeWorldArray->getXYZ(x, y, z - 1) == 1000)
						)
					{
						cubeWorldArray->setXYZ(x, y, z, 0);

					}
				}//z
			}//y
		}//x



	}

}

/*Спавнет массив мира*/
void ACubeGen::ShowWorld()
{
	UWorld* world = GetWorld();
	FActorSpawnParameters spawnParams;

	int32 counter = 0;
	spawnParams.Owner = this;
	FRotator rotator = FRotator(0.0f, 0.0f, 0.0f);
	for (int32 x = 0; x < chunkSize; x++) {
		for (int32 y = 0; y < chunkSize; y++) {
			for (int32 z = 0; z < chunkSize; z++) {

				if (cubeWorldArray->getXYZ(x, y, z) == 1)
				{
					world->SpawnActor<ACubeVoxel>(cubeVoxel, FVector(x * 100, y * 100, z * 100), rotator, spawnParams);
					counter++;
					//UE_LOG(LogTemp, Warning, TEXT("Spawn at, %s"), FVector(x * 100, y * 100, z * 100) + this->GetActorLocation);

				}
			}//z
		}//y
	}//x

	//UE_LOG(LogTemp, Warning, TEXT("counter, %d"), counter);


}

