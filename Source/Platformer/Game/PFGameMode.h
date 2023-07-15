#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PFGameMode.generated.h"

UCLASS()
class PLATFORMER_API APFGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:


protected:
    virtual void BeginPlay() override;
    virtual void StartPlay() override;

private:

};