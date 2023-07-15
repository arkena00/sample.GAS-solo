#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Platformer/PFPreprocessor.h"
#include "Platformer/GAS/PFAbilityComponent.h"
#include "PFAttributeSet.generated.h"

UCLASS()
class PLATFORMER_API UPFAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UPFAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    MAKE_ATTRIBUTE_INIT(UPFAttributeSet)

    MAKE_ATTRIBUTE(Damage)
    UPROPERTY()
    FGameplayAttributeData Damage;

    MAKE_ATTRIBUTE(Health)
    UPROPERTY(ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& PreviousData);

    MAKE_ATTRIBUTE(HealthMax)
    UPROPERTY(ReplicatedUsing = OnRep_HealthMax)
    FGameplayAttributeData HealthMax;
    UFUNCTION()
    void OnRep_HealthMax(const FGameplayAttributeData& PreviousData);
};