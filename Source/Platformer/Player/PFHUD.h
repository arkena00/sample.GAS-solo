#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PFHUD.generated.h"

UCLASS()
class PLATFORMER_API APFHUD : public AHUD
{
    GENERATED_BODY()

public:
    APFHUD();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, Category = "Platformer|HUD", meta=(WorldContext="WorldContextObject"))
    static APFHUD* GetPFHUD(const UObject* WorldContextObject);

private:

};