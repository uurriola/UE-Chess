// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PieceActor.h"
#include "RookPieceActor.generated.h"

/**
 * 
 */
UCLASS()
class CHESS3DV3_API ARookPieceActor : public APieceActor
{
	GENERATED_BODY()

public:
	virtual TArray<ACaseActor*> GetAccessibleCases() override;
};
