#include "PFEffectContext.h"

UScriptStruct* FPFEffectContext::GetScriptStruct() const
{
    return FPFEffectContext::StaticStruct();
}

FPFEffectContext* FPFEffectContext::Duplicate() const
{
    FPFEffectContext* NewContext = new FPFEffectContext();
    *NewContext = *this;
    // Copy context data here
    NewContext->AddActors(Actors);

    return NewContext;
}

bool FPFEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
    bOutSuccess &= Super::NetSerialize(Ar, Map, bOutSuccess);

    // Data serialization
    return true;
}