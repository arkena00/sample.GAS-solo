#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Abilities/GameplayAbility.h"
#include "Platformer/Player/Input/PFInputActivationType.h"
#include "PFAbility.generated.h"

UCLASS()
class PLATFORMER_API UPFAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Platformer|Ability")
    EPFInputActivationType GetInputActivationType() const;

    //

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Platformer|Ability")
    EPFInputActivationType InputActivationType = EPFInputActivationType::OnInputTriggered;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Platformer|Ability")
    TObjectPtr<UInputAction> InputAction;

protected:
    virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
    virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
    virtual const FGameplayTagContainer* GetCooldownTags() const override;

private:
    UPROPERTY()
    FGameplayTagContainer TempCooldownTags;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Platformer|Ability", meta=(AllowPrivateAccess=true))
    FGameplayTag CooldownTag;
};