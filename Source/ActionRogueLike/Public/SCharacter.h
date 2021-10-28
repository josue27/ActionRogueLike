// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USIntercationComponent;
class USAttributeComponent;
class USActionComponent;
UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;
	
	UPROPERTY(VisibleAnywhere)
	USIntercationComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USActionComponent* ActionComponent;


	
	FTimerHandle TimerHandle_PrimaryAttack;

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void PrimaryInteract();

	UFUNCTION()
	void BlackHoleAttack();

	//UFUNCTION()
	//void PrimaryAttack_TimeElapsed();
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningCompo, float NewHealth, float Delta);

	void SprintStart();
	void SprintEnd();
	
	virtual  void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100.0f);

	

};
