// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardActor.generated.h"

class ACaseActor;
class APieceActor;

UENUM()
enum PieceColor : int
{
	BLACK,
	WHITE
};

UCLASS()
class CHESS3DV3_API ABoardActor : public AActor
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ACaseActor> BpCase;

	UPROPERTY(BlueprintReadWrite)
	TArray< ACaseActor*> cases;

	APieceActor* m_selectedPiece;

	TEnumAsByte<PieceColor> m_ActivePlayerColor = WHITE;

	ABoardActor(); 

	ACaseActor* GetCase(int x, int y);
	void EndTurn();
protected:
	virtual void BeginPlay() override;

};
