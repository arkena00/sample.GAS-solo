#include "PFPlayerState.h"

#include "Platformer/GAS/PFAbilityComponent.h"
#include "Platformer/GAS/Attribute/PFAttributeSet.h"
#include "Kismet/GameplayStatics.h"

APFPlayerState::APFPlayerState()
{
    NetUpdateFrequency = 100.f;
    PFAbilityComponent = CreateDefaultSubobject<UPFAbilityComponent>("PFAbilityComponent");
    PFAttributeSet = CreateDefaultSubobject<UPFAttributeSet>("PFAttributeSet");
}

UPFAbilityComponent* APFPlayerState::GetAbilitySystemComponent() const
{
    check(PFAbilityComponent);
    return PFAbilityComponent;
}

UPFAttributeSet* APFPlayerState::GetAttributeSet() const
{
    check(PFAttributeSet);
    return PFAttributeSet;
}

APFPlayerState* APFPlayerState::GetPFPlayerState(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<APFPlayerState>();
}