// Mr. Nothing.


#include "CC_WidgetComponent.h"

#include "Crash/AbilitySystem/CC_AbilitySystemComponent.h"
#include "Crash/AbilitySystem/CC_AttributeSet.h"
#include "Crash/Characters/CC_BaseCharacter.h"


void UCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();
	
	if (!IsASCInitialized())
	{
		CrashCharacter->OnASCInitialized.AddDynamic(this,&UCC_WidgetComponent::OnASCInitialized);
		return;
	}
	
	InitializeAttributeDelegate();
	
}

void UCC_WidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<ACC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UCC_AttributeSet>(CrashCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
}

bool UCC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCC_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this,&UCC_WidgetComponent::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UCC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC,UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UCC_AttributeSet>(AS);
	
	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
	
}

void UCC_WidgetComponent::BindToAttributeChanges()
{
	//TODO: Listen for changes to GameplayAttributes and update our widgets Accordingly.
}

