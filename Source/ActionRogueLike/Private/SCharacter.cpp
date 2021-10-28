// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SIntercationComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ASCharacter::ASCharacter()
{


	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpingArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	InteractionComp = CreateDefaultSubobject<USIntercationComponent>(TEXT("InteractionComp"));


	
	GetCharacterMovement()->bOrientRotationToMovement = true;//el personaje gira hacia la direccion que lo movemos
	bUseControllerRotationYaw = false;//asi la camara rota alrededor del jugador

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	ActionComponent = CreateDefaultSubobject<USActionComponent>(TEXT("ActionComponent"));
}
void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChange.AddDynamic(this,&ASCharacter::OnHealthChanged);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Debug
	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right",this,&ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteraction",IE_Pressed,this,&ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ASCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&ASCharacter::SprintEnd);


	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ASCharacter::Jump);
}


void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(),value);
}
void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	//X forward
	//Y right
	//z UP
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis((EAxis::Y));
	
	
	AddMovementInput(RightVector *value);
}

void ASCharacter::PrimaryAttack()
{

	ActionComponent->StartActionByName(this,"PrimaryAttack");
	//PlayAnimMontage(AttackAnim);
//
	//GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimeElapsed,0.3f);
	

}

void ASCharacter::PrimaryInteract()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();

	}
}

void ASCharacter::BlackHoleAttack()
{
	ActionComponent->StartActionByName(this,"BlackHoleAttack");

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	//tambien existe check pero es mejor usar ensure o ensureAlways
	//ensure se activa la primera vez despues de compilar, si vuelve a jugar lo ignora
	//ensureAlways se activa siempre sin necesidad de compilar
	//ensure no se queda en shipped builds
	if(ensureAlways(ProjectileClass))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = CameraComp->GetComponentLocation() +( CameraComp->GetComponentRotation().Vector() * 10000.0f);
		FHitResult HitResult;
		FCollisionObjectQueryParams QueryParams;
		QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		bool bIsHitting = GetWorld()->LineTraceSingleByObjectType(HitResult,CameraComp->GetComponentLocation(),TraceEnd,QueryParams);
       if(bIsHitting)
       {
	       DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,20.0f,16,FColor::Green,false,2.0f);
       		TraceEnd = HitResult.ImpactPoint;
	
       }
		//FRotator EndRotation = GetControlRotation();//incorrecto
		FRotator EndRotation = FRotationMatrix::MakeFromX(TraceEnd-HandLocation).Rotator();

        FTransform SpawnTM = FTransform(EndRotation,HandLocation);
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Instigator = this;
   
        GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);

		DrawDebugLine(GetWorld(),TraceStart,TraceEnd,FColor::Red,false,2.0f);
	}

}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningCompo, float NewHealth,
	float Delta)
{
	if(Delta<0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
    
	}
	if(NewHealth <=0.0f && Delta<0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
	
}

void ASCharacter::SprintStart()
{
	ActionComponent->StartActionByName(this,"Sprint");
}

void ASCharacter::SprintEnd()
{
	ActionComponent->StopActionByName(this,"Sprint");

}

void ASCharacter::HealSelf(float Amount /*=100*/)
{
	AttributeComponent->ApplyHealthChange(this,Amount);
}
