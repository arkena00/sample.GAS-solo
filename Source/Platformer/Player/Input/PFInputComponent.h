#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Platformer/GAS/PFAbilityComponent.h"
#include "Platformer/GAS/Abililty/PFAbility.h"
#include "Platformer/Player/PFAvatar.h"
#include "Platformer/Player/Data/PFAvatarInputData.h"
#include "PFInputComponent.generated.h"

UCLASS(Config = Input)
class UPFInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    void BindAvatarActions(TObjectPtr<UPFAvatarInputData> AvatarInputData);
    void BindAvatarAbilities(const TArray<TSubclassOf<UPFAbility>>& AbilityClasses);

    template<class FuncType, class UserClass, typename... VarTypes>
    FEnhancedInputActionEventBinding& BindAbility(const UPFAbility* PFAbility, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, VarTypes... Vars);
};

template< class FuncType, class UserClass, typename... VarTypes >
FEnhancedInputActionEventBinding& UPFInputComponent::BindAbility(const UPFAbility* PFAbility, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, VarTypes... Vars)
{
    return BindAction(PFAbility->InputAction, TriggerEvent, Object, Func, PFAbility);
}