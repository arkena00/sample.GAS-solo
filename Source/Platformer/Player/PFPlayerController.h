#pragma once

#include "CoreMinimal.h"
#include "PFPlayerController.generated.h"

UCLASS()
class PLATFORMER_API APFPlayerController final : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "PF|PlayerController", meta=(WorldContext="WorldContextObject"))
    static APFPlayerController* GetPFPlayerController(const UObject* WorldContextObject);

protected:
    virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

private:
    TWeakObjectPtr<UPFAbilityComponent> PFAbilityComponent;
};