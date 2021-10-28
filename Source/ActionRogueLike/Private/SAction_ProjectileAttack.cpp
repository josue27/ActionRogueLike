// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName="Muzzle_01";
	AttackAnimDelay = 0.2;
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
 {
 	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if(Character)
	{
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect,Character->GetMesh(),HandSocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);
		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"AttackDelay_Elapsed",Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay,Delegate,AttackAnimDelay,false);
	}
 }

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InsitigatorCharacter)
{
	if(ensureAlways(ProjectileClass))
	{
		FVector HandLocation = InsitigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InsitigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InsitigatorCharacter);
		
		FCollisionObjectQueryParams QueryParams;
		QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		QueryParams.AddObjectTypesToQuery(ECC_Pawn);
		
		FVector TraceStart = InsitigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = TraceStart +( InsitigatorCharacter->GetControlRotation().Vector() * 10000.0f);
		FHitResult HitResult;
		
		bool bIsHitting = GetWorld()->LineTraceSingleByObjectType(HitResult,TraceStart,TraceEnd,QueryParams);
		if(bIsHitting)
		{
			//DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,20.0f,16,FColor::Green,false,2.0f);
			TraceEnd = HitResult.ImpactPoint;
	
		}
		//FRotator EndRotation = GetControlRotation();//incorrecto
		FRotator EndRotation = FRotationMatrix::MakeFromX(TraceEnd-HandLocation).Rotator();

		FTransform SpawnTM = FTransform(EndRotation,HandLocation);
	
   
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);

		//DrawDebugLine(GetWorld(),TraceStart,TraceEnd,FColor::Red,false,2.0f);
	}
	StopAction(InsitigatorCharacter);
}



