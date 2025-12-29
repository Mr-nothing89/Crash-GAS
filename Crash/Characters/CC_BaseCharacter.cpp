// Mr. Nothing.


#include "CC_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"


// Sets default values
ACC_BaseCharacter::ACC_BaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;
	
	// Thick and refresh bones transforms whether render or not - for bone updates on a Dedicated Server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ACC_BaseCharacter::GiveStartupAbilities()
{
	if (IsValid(GetAbilitySystemComponent()))
	{
		for (const TSubclassOf<UGameplayAbility>& Ability : StartupAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
			GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
		}
	}
	
}


