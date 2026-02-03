// Mr. Nothing.


#include "CC_BlueprintLibrary.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward,ToInstigator);
	const float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));
	UE_LOG(LogTemp,Warning,TEXT("Angle: %f"),Angle);
	if (Angle >= 120.f)
	{
		return EHitDirection::Back;
	}
	if (Angle < 120.f && Angle > 60.f)
	{
		const FVector Cross = FVector::CrossProduct(TargetForward,ToInstigator);
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}
	return EHitDirection::Forward;
}

FName UCC_BlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	    case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Forward: return FName("Forward");
		case EHitDirection::Back: return FName("Back");
		default: return FName("None");
	}
}
