// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWorldUserWidget.h"
#include "Components/ActorComponent.h"
#include "SIntercationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USIntercationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USIntercationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FindBestInteractable();

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<USWorldUserWidget> DefaultWidgetClass;
	UPROPERTY()
	USWorldUserWidget* DefaultWidgetInstance;

	UPROPERTY(EditAnywhere,Category="Trace")
	float TraceDistance = 1000.0f;
	UPROPERTY(EditDefaultsOnly,Category="Trace")
	float TraceRadius;
	UPROPERTY(EditDefaultsOnly,Category="Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;
	//ojo: tenemos que hacer el TEnumAsByte porque esto esta en c++ 8 y no permitiria compilar sin esto, en el c++11 ya deja

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PrimaryInteract();
};
