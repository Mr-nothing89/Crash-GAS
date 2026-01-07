// Mr. Nothing.


#include "CC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Crash/GameplayTags/CCTags.h"

void ACC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(GetLocalPlayer()))
	{
		for (UInputMappingContext* Context : InputMappingContexts)
		{
			InputSubsystem->AddMappingContext(Context,0);
		}
		
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ACC_PlayerController::Jump);
			EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACC_PlayerController::StopJumping);
			EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ACC_PlayerController::Move);
			EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ACC_PlayerController::Look);
			
			EnhancedInputComponent->BindAction(PrimaryAction,ETriggerEvent::Triggered,this,&ACC_PlayerController::Primary);
			EnhancedInputComponent->BindAction(SecondaryAction,ETriggerEvent::Started,this,&ACC_PlayerController::Secondary);
			EnhancedInputComponent->BindAction(TertiaryAction,ETriggerEvent::Started,this,&ACC_PlayerController::Tertiary);
		}
	}
}

void ACC_PlayerController::Jump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ACC_PlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ACC_PlayerController::Move(const FInputActionValue& Value)
{
	if (GetPawn())
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		
		//Find which way is forward
		const FRotator YawRotation(0,GetControlRotation().Yaw,0);
			
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetPawn()->AddMovementInput(ForwardDirection,MovementVector.Y);
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		GetPawn()->AddMovementInput(RightDirection,MovementVector.X);
	}
}

void ACC_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ACC_PlayerController::Primary()
{
	ActivateAbility(CCTags::CCAbilities::Primary);
}

void ACC_PlayerController::Secondary()
{
	ActivateAbility(CCTags::CCAbilities::Secondary);
}

void ACC_PlayerController::Tertiary()
{
	ActivateAbility(CCTags::CCAbilities::Tertiary);
}

void ACC_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()))
	{
		
		ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
	}
}
