// Mr. Nothing.


#include "CC_BaseCharacter.h"


// Sets default values
ACC_BaseCharacter::ACC_BaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;
	
	// Thick and refresh bones transforms whether render or not - for bone updates on a Dedicated Server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}


