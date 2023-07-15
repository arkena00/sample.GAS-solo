#include "PFAbilitySystemGlobals.h"

FPFEffectContext* UPFAbilitySystemGlobals::AllocGameplayEffectContext() const
{
    return new FPFEffectContext;
}

// Add custom parameters to gameplay cues
void UPFAbilitySystemGlobals::InitGameplayCueParameters(FGameplayCueParameters& CueParameters,
    const FGameplayEffectContextHandle& EffectContext)
{
}