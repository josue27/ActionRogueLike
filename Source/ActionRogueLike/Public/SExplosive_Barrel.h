// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosive_Barrel.generated.h"


class UStaticMeshComponent;
class URadialForceComponent;
UCLASS()
class ACTIONROGUELIKE_API ASExplosive_Barrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosive_Barrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	URadialForceComponent* ForceComp;

	UPROPERTY(EditAnywhere)
	bool bExploded = false;
	UFUNCTION()
	void Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
