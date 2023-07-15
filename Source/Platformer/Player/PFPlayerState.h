#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Platformer/GAS/Attribute/PFAttributeSet.h"
#include "PFPlayerState.generated.h"

class UPFAbilityComponent;


UCLASS()
class PLATFORMER_API APFPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    APFPlayerState();
  
    UFUNCTION(BlueprintCallable, Category = "Platformer|PlayerState")
    virtual UPFAbilityComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "Platformer|PlayerState")
    UPFAttributeSet* GetAttributeSet() const;

    //

    UFUNCTION(BlueprintPure, Category = "Platformer|PlayerState", meta=(WorldContext="WorldContextObject"))
    static APFPlayerState* GetPFPlayerState(const UObject* WorldContextObject);

protected:

private:
    UPROPERTY()
    TObjectPtr<UPFAbilityComponent> PFAbilityComponent;
    UPROPERTY()
    TObjectPtr<UPFAttributeSet> PFAttributeSet;
};