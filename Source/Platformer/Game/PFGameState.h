#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PFGameState.generated.h"

UCLASS()
class PLATFORMER_API APFGameState final : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGameDelegate);

public:
    UPROPERTY(BlueprintAssignable, Category = "Platformer|GameState")
    FOnEndGameDelegate OnEndGameDelegate;

    UFUNCTION(BlueprintPure, Category = "Platformer|GameState", meta=(WorldContext="WorldContextObject"))
    static APFGameState* GetPFGameState(const UObject* WorldContextObject);
};