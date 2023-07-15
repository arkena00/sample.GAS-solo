#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abililty/PFAbilitySet.h"
#include "Platformer/Player/Data/PFAvatarData.h"
#include "PFAbilityComponent.generated.h"

UCLASS()
class PLATFORMER_API UPFAbilityComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

    friend class UPFInputComponent;

public:
    UPFAbilityComponent();

    void GiveAbilitySet(const TObjectPtr<UPFAbilitySet>& AbilitySet);

    // Input
    void AbilityInputPressed(const UPFAbility* InAbility);
    void AbilityInputReleased(const UPFAbility* InAbility);
    void ProcessAbilityInput(float DeltaTime, bool bGamePaused);

protected:
    virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
    virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

private:
    TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
    TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
    TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};