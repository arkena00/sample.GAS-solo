#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "Engine/DataAsset.h"

#include "PFAbilitySet.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UCLASS(BlueprintType, Const)
class UPFAbilitySet : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Platformer|AbilitySet")
    TArray<TSubclassOf<UPFAbility>> Abilities;

    UPROPERTY(EditDefaultsOnly, Category = "Platformer|AbilitySet")
    TArray<TSubclassOf<UGameplayEffect>> Effects;
};