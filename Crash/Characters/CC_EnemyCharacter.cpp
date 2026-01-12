// Mr. Nothing.


#include "CC_EnemyCharacter.h"

#include "AbilitySystemComponent.h"


// Sets default values
ACC_EnemyCharacter::ACC_EnemyCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* ACC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ACC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(AbilitySystemComponent)) return;
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	
	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
}


