#include "PFInputComponent.h"

void UPFInputComponent::BindAvatarActions(TObjectPtr<UPFAvatarInputData> AvatarInputData)
{
    auto* Avatar = Cast<APFAvatar>(GetOwner());
    BindAction(AvatarInputData->Jump, ETriggerEvent::Started, Avatar, &APFAvatar::InputJump);
    BindAction(AvatarInputData->LookAt, ETriggerEvent::Triggered, Avatar, &APFAvatar::InputLookAt);
    BindAction(AvatarInputData->Move, ETriggerEvent::Triggered, Avatar, &APFAvatar::InputMove);
}

void UPFInputComponent::BindAvatarAbilities(const TArray<TSubclassOf<UPFAbility>>& AbilityClasses)
{
    auto* Avatar = Cast<APFAvatar>(GetOwner());
    for (auto AbilityClass : AbilityClasses)
    {
        BindAbility(AbilityClass.GetDefaultObject(), ETriggerEvent::Started, Avatar, &APFAvatar::AbilityInputPressed);
        BindAbility(AbilityClass.GetDefaultObject(), ETriggerEvent::Completed, Avatar, &APFAvatar::AbilityInputReleased);
    }
}