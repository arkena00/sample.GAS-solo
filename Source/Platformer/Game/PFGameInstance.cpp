#include "PFGameInstance.h"

#include "Modules/BuildVersion.h"
#include "Platformer/Data/PFAssetManager.h"

void UPFGameInstance::Init()
{
    Super::Init();
}

FString UPFGameInstance::GetVersion()
{
    FBuildVersion BuildVersion;
    FBuildVersion::TryRead(FBuildVersion::GetDefaultFileName(), BuildVersion);
    return BUILD_VERSION + FString("\n") + BuildVersion.GetEngineVersion().ToString();
}