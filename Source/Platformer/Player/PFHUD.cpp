#include "PFHUD.h"

#include "PFPlayerState.h"
#include "Kismet/GameplayStatics.h"

APFHUD::APFHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APFHUD::BeginPlay()
{
    Super::BeginPlay();
}

APFHUD* APFHUD::GetPFHUD(const UObject* WorldContextObject)
{
    return Cast<APFHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());
}