#include "PFPlayerController.h"

#include "PFPlayerState.h"
#include "Input/PFInputComponent.h"
#include "Kismet/GameplayStatics.h"

APFPlayerController* APFPlayerController::GetPFPlayerController(const UObject* WorldContextObject)
{
    return Cast<APFPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}

void APFPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
    if (!PFAbilityComponent.IsValid())
    {
        if (const auto* PFPlayerState = GetPlayerState<APFPlayerState>())
            PFAbilityComponent = PFPlayerState->GetAbilitySystemComponent();
    }

    if (PFAbilityComponent.IsValid())
    {
        PFAbilityComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
    }

    Super::PostProcessInput(DeltaTime, bGamePaused);
}