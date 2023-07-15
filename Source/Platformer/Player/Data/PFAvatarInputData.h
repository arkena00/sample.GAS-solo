#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFAvatarInputData.generated.h"

class UInputAction;
class UInputMappingContext;
class UPlayerMappableInputConfig;

UCLASS(BlueprintType, Blueprintable)
class PLATFORMER_API UPFAvatarInputData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UPlayerMappableInputConfig> Binds;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UInputMappingContext> MappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> Move;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> LookAt;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> Jump;
};