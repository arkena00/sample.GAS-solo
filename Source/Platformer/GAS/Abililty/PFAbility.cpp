#include "PFAbility.h"

#include "Platformer/GAS/PFAbilityComponent.h"

EPFInputActivationType UPFAbility::GetInputActivationType() const
{
    return InputActivationType;
}

void UPFAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    // auto ASC = Cast<UPFAbilityComponent>(GetAbilitySystemComponentFromActorInfo());
}

void UPFAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo) const
{
    if (const UGameplayEffect* CooldownGE = GetCooldownGameplayEffect())
    {
        const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
        SpecHandle.Data.Get()->DynamicGrantedTags.AddTag(CooldownTag);

        auto Duration = SpecHandle.Data->CalculateModifiedDuration();
        // OnUpdateCooldownDelegate.Broadcast(this, true, Duration);
    }
}

bool UPFAbility::DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent,
    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
    FGameplayTagContainer* OptionalRelevantTags) const
{
    return Super::DoesAbilitySatisfyTagRequirements(AbilitySystemComponent, SourceTags, TargetTags, OptionalRelevantTags);
}

const FGameplayTagContainer* UPFAbility::GetCooldownTags() const
{
    FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
    MutableTags->Reset();
    const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
    if (ParentTags) MutableTags->AppendTags(*ParentTags);
    // MutableTags->AddTag(CooldownTag);
    return MutableTags;
}