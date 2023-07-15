#include "PFGameState.h"
#include "Kismet/GameplayStatics.h"

APFGameState* APFGameState::GetPFGameState(const UObject* WorldContextObject)
{
    return Cast<APFGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}