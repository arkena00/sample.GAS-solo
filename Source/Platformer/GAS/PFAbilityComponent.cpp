#include "PFAbilityComponent.h"

#include "Abililty/PFAbility.h"

UPFAbilityComponent::UPFAbilityComponent()
{
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Full;
}

void UPFAbilityComponent::GiveAbilitySet(const TObjectPtr<UPFAbilitySet>& AbilitySet)
{
    for (auto AbilityClass : AbilitySet->Abilities)
    {
        GiveAbility(FGameplayAbilitySpec(AbilityClass));
    }
    for (auto EffectClass : AbilitySet->Effects)
    {
        ApplyGameplayEffectToSelf(EffectClass.GetDefaultObject(), 1.f, MakeEffectContext());
    }
}

void UPFAbilityComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
    Super::AbilitySpecInputPressed(Spec);

    // We don't support UGameplayAbility::bReplicateInputDirectly.
    // Use replicated events instead so that the WaitInputPress ability task works.
    if (Spec.IsActive())
    {
        // Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
    }
}

void UPFAbilityComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
    if (Spec.IsActive())
    {
        // Invoke the InputReleased event. This is not replicated here. If someone is listening, they may replicate the InputReleased event to the server.
        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
    }
}

void UPFAbilityComponent::AbilityInputPressed(const UPFAbility* InAbility)
{
    if (!ensure(InAbility)) return;
    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.Ability == InAbility)
        {
            InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
            InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
        }
    }
}

void UPFAbilityComponent::AbilityInputReleased(const UPFAbility* InAbility)
{
    if (!ensure(InAbility)) return;
    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.Ability == InAbility)
        {
            InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
            InputHeldSpecHandles.Remove(AbilitySpec.Handle);
        }
    }
}

void UPFAbilityComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
    static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
    AbilitiesToActivate.Reset();

    // Process all abilities that activate when the input is held.
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
    {
        if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
        {
            if (AbilitySpec->Ability && !AbilitySpec->IsActive())
            {
                const auto NVAbilityCDO = CastChecked<UPFAbility>(AbilitySpec->Ability);

                if (NVAbilityCDO->GetInputActivationType() == EPFInputActivationType::WhileInputActive)
                {
                    AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
                }
            }
        }
    }

    // Process all abilities that had their input pressed this frame.
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
    {
        if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
        {
            if (AbilitySpec->Ability)
            {
                AbilitySpec->InputPressed = true;

                if (AbilitySpec->IsActive())
                {
                    // Ability is active so pass along the input event.
                    AbilitySpecInputPressed(*AbilitySpec);
                }
                else
                {
                    const auto NVAbilityCDO = CastChecked<UPFAbility>(AbilitySpec->Ability);

                    if (NVAbilityCDO->GetInputActivationType() == EPFInputActivationType::OnInputTriggered)
                    {
                        AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
                    }
                }
            }
        }
    }

    // Try to activate all the abilities that are from presses and holds.
    // We do it all at once so that held inputs don't activate the ability
    // and then also send an input event to the ability because of the press.
    for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
    {
        TryActivateAbility(AbilitySpecHandle);
    }

    // Process all abilities that had their input released this frame.
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
    {
        if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
        {
            if (AbilitySpec->Ability)
            {
                AbilitySpec->InputPressed = false;

                if (AbilitySpec->IsActive())
                {
                    // Ability is active so pass along the input event.
                    AbilitySpecInputReleased(*AbilitySpec);
                }
            }
        }
    }

    // Clear the cached ability handles.
    InputPressedSpecHandles.Reset();
    InputReleasedSpecHandles.Reset();
}