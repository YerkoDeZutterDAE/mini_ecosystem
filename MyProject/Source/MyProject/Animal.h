// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animal.generated.h"

UCLASS()
class MYPROJECT_API AAnimal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimal();

	//wonder
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WonderDelay = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WonderAngle = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WonderAngleRange = 50.f;

	// hunger
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Hunger = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FoodLevel = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HungerStart = 70.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HungerEnd = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HungerSpeed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//std::vector<FVector> FoodMemory = {};
		TArray<FVector> FoodMemory = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EatDis = 75.f;

	//age
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Age = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AgeingSpeed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AgeTimeCounter = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int OldAge = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OldAgeSpeedReduction = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxAge = 100;

	//reproduction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Sex = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SexDriveMeter = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SexDriveSpeed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SexDriveStart = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSexDrive = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SexDrive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AAnimal*> PosibullMates = {};

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAnimal> ToSpawn;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void ChangeWonderAngle();
	UFUNCTION(BlueprintCallable)
		void Wonder();
	UFUNCTION(BlueprintCallable)
		void Seek(FVector target);
	UFUNCTION(BlueprintCallable)
		void HandleHunger(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void HandleAge(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void HandleSexDrive(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void AddFood(FVector foodPos);
	UFUNCTION(BlueprintCallable)
		void AddAnimal(AAnimal* animal);
	UFUNCTION(BlueprintCallable)
		void RemoveAnimal(AAnimal* animal);
};
