#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "PFAvatar.generated.h"

class UPFAvatarData;
class UPFAbilityComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PLATFORMER_API APFAvatar : public ACharacter
{
    GENERATED_BODY()

    friend class UPFInputComponent;

public:
    APFAvatar();

    UFUNCTION(BlueprintCallable, Category = "Platformer|Avatar")
    UPFAbilityComponent* GetAbilityComponent();

    //

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platformer|Component")
    TObjectPtr<USpringArmComponent> SpringArmComponent;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platformer|Component")
    TObjectPtr<UCameraComponent> Camera;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Platformer|Avatar")
    TObjectPtr<UPFAvatarData> Data;

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void PawnClientRestart() override;
    virtual void PossessedBy(AController* NewController) override;

    void InitializeAbilityComponent();

    void AbilityInputPressed(const UPFAbility* Ability);
    void AbilityInputReleased(const UPFAbility* Ability);

    void InputJump(const FInputActionValue& InputActionValue);
    void InputLookAt(const FInputActionValue& InputActionValue);
    void InputMove(const FInputActionValue& InputActionValue);

private:
    TWeakObjectPtr<UPFAbilityComponent> PFAbilityComponent;
};