#include "PFAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UPFAttributeSet::UPFAttributeSet()
{

}

void UPFAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UPFAttributeSet, Health);
    DOREPLIFETIME(UPFAttributeSet, HealthMax);
}

void UPFAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& Value)
{
    Super::PreAttributeChange(Attribute, Value);

    if (Attribute == GetHealthAttribute())
    {
        Value = FMath::Clamp<float>(Value, 0.f, GetHealthMax());
    }
}

void UPFAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const auto InputDamage = GetDamage();
    SetDamage(0);

    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        SetHealth(GetHealth() - InputDamage);
    }
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(GetHealth() - InputDamage);
    }

    // const auto TargetPlayer = Data.Target.GetOwner();
    // TargetPlayer->CheckDeath(Data);
}

MAKE_ATTRIBUTE_DEF(UPFAttributeSet, Health);
MAKE_ATTRIBUTE_DEF(UPFAttributeSet, HealthMax);