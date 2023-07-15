#include "PFAvatar.h"

#include "EnhancedInputSubsystems.h"
#include "PFPlayerState.h"
#include "Camera/CameraComponent.h"
#include "Input/PFInputComponent.h"
#include "Data/PFAvatarData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Platformer/Log.h"
#include "Platformer/GAS/Abililty/PFAbilitySet.h"

APFAvatar::APFAvatar()
{
    // Springarm
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 90.0f), FRotator(-30, 0.0f, 0.0f));
    SpringArmComponent->TargetArmLength = 800.f;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->CameraLagSpeed = 30.0f;
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SetupAttachment(GetMesh());


    // Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArmComponent.Get(), USpringArmComponent::SocketName);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bIgnoreBaseRotation = true;
}

UPFAbilityComponent* APFAvatar::GetAbilityComponent()
{
    if (!ensure(PFAbilityComponent.IsValid())) return nullptr;
    return PFAbilityComponent.Get();
}

void APFAvatar::AbilityInputPressed(const UPFAbility* Ability)
{
    if (ensure(PFAbilityComponent.IsValid())) PFAbilityComponent->AbilityInputPressed(Ability);
}

void APFAvatar::AbilityInputReleased(const UPFAbility* Ability)
{
    if (ensure(PFAbilityComponent.IsValid())) PFAbilityComponent->AbilityInputReleased(Ability);
}

void APFAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (auto* PFInputComponent = Cast<UPFInputComponent>(PlayerInputComponent))
    {
        if (ensure(Data)) PFInputComponent->BindAvatarActions(Data->InputData);
        if (ensure(Data && Data->AbilitySet)) PFInputComponent->BindAvatarAbilities(Data->AbilitySet->Abilities);
    }
    else PF_warning("SetupPlayerInputComponent failed");
}

void APFAvatar::PawnClientRestart()
{
    Super::PawnClientRestart();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            if (ensure(Data && Data->InputData)) Subsystem->AddMappingContext(Data->InputData->MappingContext, 0);
            else PF_warning("Missing avatar data");
        }
    }
}

void APFAvatar::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitializeAbilityComponent();
}

void APFAvatar::InitializeAbilityComponent()
{
    if (!PFAbilityComponent.IsValid() && GetPlayerState())
    {
        PFAbilityComponent = GetPlayerStateChecked<APFPlayerState>()->GetAbilitySystemComponent();
        PFAbilityComponent->InitAbilityActorInfo(GetPlayerState(), this);
        PFAbilityComponent->GiveAbilitySet(Data->AbilitySet);
    }
    else PF_warning("AbilityComponent initialization failed");
}

void APFAvatar::InputJump(const FInputActionValue& InputActionValue)
{
    ACharacter::Jump();
}

void APFAvatar::InputLookAt(const FInputActionValue& InputActionValue)
{
    const FVector2D Value = InputActionValue.Get<FVector2D>();

    if (Value.X != 0.f) AddControllerYawInput(Value.X);
    if (Value.Y != 0.f) AddControllerPitchInput(Value.Y);
}

void APFAvatar::InputMove(const FInputActionValue& InputActionValue)
{
    if (Controller)
    {
        const FVector2D Value = InputActionValue.Get<FVector2D>();
        const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

        if (Value.X != 0.f)
        {
            const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
            AddMovementInput(MovementDirection, Value.X);
        }

        if (Value.Y != 0.f)
        {
            const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
            AddMovementInput(MovementDirection, Value.Y);
        }
    }
}