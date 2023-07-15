#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "PFEffectContext.h"
#include "PFAbilitySystemGlobals.generated.h"

UCLASS()
class PLATFORMER_API UPFAbilitySystemGlobals : public UAbilitySystemGlobals
{
    GENERATED_BODY()

public:
    virtual FPFEffectContext* AllocGameplayEffectContext() const override;
    virtual void InitGameplayCueParameters(FGameplayCueParameters& CueParameters, const FGameplayEffectContextHandle& EffectContext) override;
};