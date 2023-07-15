﻿#pragma once

UENUM(BlueprintType)
enum class EPFInputActivationType : uint8
{
    // Try to activate the ability when the input is triggered.
    OnInputTriggered,
    // Continually try to activate the ability while the input is active.
    WhileInputActive,
    // Try to activate the ability when an avatar is assigned.
    OnSpawn
};