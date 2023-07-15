#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PFGameInstance.generated.h"

UCLASS()
class PLATFORMER_API UPFGameInstance final : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintCallable, Category = "Platformer|GameInstance")
    static FString GetVersion();

private:

};