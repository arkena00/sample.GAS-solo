#include "PFAssetManager.h"
#include "PFGameData.h"
#include "AbilitySystemGlobals.h"

void UPFAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    UAbilitySystemGlobals::Get().InitGlobalData();
}

void UPFAssetManager::PostInitialAssetScan()
{
    Super::PostInitialAssetScan();
}

TObjectPtr<UPFGameData> UPFAssetManager::GetGameData()
{
    return GameData;
}

UPFAssetManager* UPFAssetManager::Get()
{
    return &static_cast<UPFAssetManager&>(UAssetManager::Get());
}

UPFAssetManager* UPFAssetManager::GetPFAssetManager()
{
    return Get();
}