// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardActor.h"
#include "CaseActor.h"

ABoardActor::ABoardActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	BpCase = ACaseActor::StaticClass();
}

void ABoardActor::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(ABoardActor::StaticClass()) && IsValid(BpCase))
	{
		UWorld* MyLevel = GetWorld();
		if (IsValid(MyLevel))
		{
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();
			FVector SpawnScale = GetActorScale3D();

			if (cases.Num() == 0)
			{
				for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
					{
						// Compute new transform for this case
						FVector CaseLocation = SpawnLocation + FVector(x * 100.0, y * 100.0, 0.0);
						FTransform CaseTransform(SpawnRotation, CaseLocation, SpawnScale);
						// Spawn it in the world
						ACaseActor* caseActor = (ACaseActor*)MyLevel->SpawnActor(BpCase, &CaseTransform);
						caseActor->Init(this, x, y);
						cases.Add(caseActor);
					}
				}
			}

		}
	}
}

ACaseActor* ABoardActor::GetCase(int x, int y)
{
	return cases[x * 8 + y];
}

void ABoardActor::EndTurn()
{
	m_selectedPiece = nullptr;
	m_ActivePlayerColor = (m_ActivePlayerColor == WHITE) ? BLACK : WHITE;
}
