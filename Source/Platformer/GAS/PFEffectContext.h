#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "PFEffectContext.generated.h"

USTRUCT()
struct FPFEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

    virtual UScriptStruct* GetScriptStruct() const override;
    virtual FPFEffectContext* Duplicate() const override;
    virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

private:
    // Custom data
};

template<>
struct TStructOpsTypeTraits<FPFEffectContext> : public TStructOpsTypeTraitsBase2<FPFEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true
    };
};