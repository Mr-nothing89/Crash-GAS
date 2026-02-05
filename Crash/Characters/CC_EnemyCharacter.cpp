// Mr. Nothing.


#include "CC_EnemyCharacter.h"
#include "Crash/AbilitySystem/CC_AbilitySystemComponent.h"
#include "Crash/AbilitySystem/CC_AttributeSet.h"


// Sets default values
ACC_EnemyCharacter::ACC_EnemyCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UCC_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ACC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ACC_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}


void ACC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(AbilitySystemComponent)) return;
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	OnASCInitialized.Broadcast(AbilitySystemComponent,AttributeSet);
	
	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	InitializeAttributes();
}


