// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	
	int determinSex = (rand() % 2);

	//Set sex
	if (determinSex)
		Sex = true;


}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimal::ChangeWonderAngle()
{
	float addedRange = rand() % int(WonderAngleRange);
	addedRange -= WonderAngleRange * 0.5f;
	WonderAngle += addedRange;
}

void AAnimal::Wonder()
{
	float wonderCos = cos(WonderAngle);
	float wonderSin = sin(WonderAngle);
	float x = speed * wonderCos;
	float z = speed * wonderSin;
	FVector momentum = { x,z,0 };
	AddActorWorldOffset(momentum);
}

void AAnimal::Seek(FVector target)
{
	//target - GetWorldLocation();
	//USceneComponent::GetComponentLocation();
	FVector direction = target - GetActorLocation();
	direction.Normalize();
	direction *= speed;
	AddActorWorldOffset(direction);
}

void AAnimal::HandleHunger(float DeltaTime)
{
	//decreas food
	FoodLevel -= DeltaTime * HungerSpeed;

	//set Hunger
	if (!Hunger)
		if (FoodLevel < HungerStart)
			Hunger = true;

	if(Hunger)
		if (FoodLevel > HungerEnd)
			Hunger = false;

	// Seek for food
	if (!FoodLevel)
		Destroy();

	if (!FoodMemory.Num())
		return;

	Seek(FoodMemory[FoodMemory.Num() - 1]);

	//remove food pos if close enuf
	if (FVector::Distance(FoodMemory[FoodMemory.Num() - 1], GetActorLocation()) <= EatDis)
	{
		FoodMemory.Pop();
	}
}

void AAnimal::HandleAge(float DeltaTime)
{
	//increase food
	if (AgeTimeCounter < AgeingSpeed)
	{
		AgeTimeCounter += DeltaTime;
	}
	else
	{
		AgeTimeCounter = 0.f;
		Age += 1;
	}

	if (Age >= OldAge)
		speed *= OldAgeSpeedReduction;

	if (Age >= MaxAge)
		Destroy();
}

void AAnimal::HandleSexDrive(float DeltaTime)
{
	//increase SexDrive
	SexDriveMeter += DeltaTime * SexDriveSpeed;

	if (SexDriveMeter < SexDriveStart)
	{
		SexDrive = false;
		return;
	}

	SexDrive = true;

	if (!PosibullMates.Num())
		return;

	for (size_t i = 0; i < PosibullMates.Num(); i++)
	{
		if (PosibullMates[i]->Sex == Sex)
			continue;

		if (PosibullMates[i]->SexDriveMeter < PosibullMates[i]->SexDriveStart)
			continue;

		//FActorSpawnParameters();

		SexDriveMeter -= SexDriveStart;
		if (Sex)
		{
			FActorSpawnParameters SpawnInfo;
			//AAnimal* child = GetWorld()->SpawnActor<AAnimal>(ToSpawn, GetActorLocation(), GetActorRotation(), SpawnInfo);
			AAnimal* child = GetWorld()->SpawnActor<AAnimal>(ToSpawn, GetActorLocation(), GetActorRotation(), SpawnInfo);
			if (child)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NEW ANIMAL MADE!"));\

			//GetWorld()->SpawnActor(AAnimal(), );
			break;
		}
		//PosibullMates[i]
	}
}

void AAnimal::AddFood(FVector foodPos)
{
	if (FoodMemory.Find(foodPos) == -1)
	{
		FoodMemory.Push(foodPos);
	}
}

void AAnimal::AddAnimal(AAnimal* animal)
{
	if (PosibullMates.Find(animal) == -1)
	{
		PosibullMates.Push(animal);
	}
}

void AAnimal::RemoveAnimal(AAnimal* animal)
{
	PosibullMates.Remove(animal);
}

