#pragma once

#include "CoreMinimal.h"
#include "PFAvatarInputData.h"
#include "PFAvatarData.generated.h"

class UPFAbilitySet;
class UGameplayAbility;
class UGameplayEffect;

UCLASS(BlueprintType, Blueprintable)
class PLATFORMER_API UPFAvatarData : public UDataAsset
{
    GENERATED_BODY()

public:
    // Ability
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Platformer|Avatar")
    TObjectPtr<UPFAbilitySet> AbilitySet;

    // Input
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Platformer|Input")
    TObjectPtr<UPFAvatarInputData> InputData;
};