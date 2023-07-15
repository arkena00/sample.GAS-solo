#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogPlatformer, Log, All);

#define PF_log(message, ...) UE_LOG(LogPlatformer, Display, TEXT(message), __VA_ARGS__)
#define PF_warning(message, ...) UE_LOG(LogPlatformer, Warning, TEXT(message), __VA_ARGS__)
#define PF_error(message, ...) UE_LOG(LogPlatformer, Error, TEXT(message), __VA_ARGS__)

#define PF_glog(message, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(message), __VA_ARGS__));