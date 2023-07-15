#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PFAssetManager.generated.h"

class UPFGameData;

UCLASS(Config = Game)
class PLATFORMER_API UPFAssetManager : public UAssetManager
{
    GENERATED_BODY()

public:
    inline static FPrimaryAssetType GameDataType{ "PFGameData" };

    virtual void StartInitialLoading() override;
    virtual void PostInitialAssetScan() override;

    TObjectPtr<UPFGameData> GetGameData();

    static UPFAssetManager* Get();

    UFUNCTION(BlueprintPure, Category = "Platformer|AssetManager", meta=(WorldContext="WorldContextObject"))
    static UPFAssetManager* GetPFAssetManager();

    //

private:
    UPROPERTY()
    TObjectPtr<UPFGameData> GameData;
};