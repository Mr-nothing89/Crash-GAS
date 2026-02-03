// Mr. Nothing.

#pragma once

#include "CoreMinimal.h"
#include "Crash/AbilitySystem/Abilities/CC_GameplayAbility.h"
#include "CC_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class CRASH_API UCC_HitReact : public UCC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void CachedHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly,Category="Crash|Abilities")
	FVector AvatarForward;
	
	UPROPERTY(BlueprintReadOnly,Category="Crash|Abilities")
	FVector ToInstigator;
};
