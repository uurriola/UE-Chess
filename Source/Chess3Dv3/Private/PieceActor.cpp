// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceActor.h"
#include "BoardActor.h"
#include "CaseActor.h"

APieceActor::APieceActor()
{
	OnClicked.AddUniqueDynamic(this, &APieceActor::ClickedLog);
}

void APieceActor::Init(ABoardActor* board, int x, int y, TEnumAsByte<PieceColor> color, class UMaterial* material)
{
	m_Board = board;
	m_X = x;
	m_Y = y;
	m_Color = color;
	SetMaterial(material, true);
}

void APieceActor::SetMaterial(class UMaterial* material, bool saveAsDefault)
{
	TArray<UStaticMeshComponent*> pieceMeshes;
	GetComponents<UStaticMeshComponent>(pieceMeshes);
	for (auto pieceMesh : pieceMeshes)
	{
		pieceMesh->SetMaterial(0, material);
	}
	if (saveAsDefault)
		m_DefaultMaterial = material;
}

void APieceActor::HighlightMaterial()
{
	if (m_isHighlighted)
		SetMaterial(m_DefaultMaterial, false);
	else
		SetMaterial(m_HighlightMaterial, false);
	m_isHighlighted = !m_isHighlighted;

	TArray<ACaseActor*> cs = GetAccessibleCases();
	for (auto c : cs)
	{
		c->HighlightMaterial();
	}
}

TArray<ACaseActor*> APieceActor::GetAccessibleCases()
{
	// TODO: make this a pure virtual ?
	TArray<ACaseActor*> accessibleCases;

	return accessibleCases;
}

void APieceActor::ClickedLog(AActor* Target, FKey ButtonPressed)
{
	// Piece selection

	if (m_Color == m_Board->m_ActivePlayerColor)
	{
		if (m_Board->m_selectedPiece != nullptr)
			m_Board->m_selectedPiece->HighlightMaterial();
		// Highlight current piece and accessible cases
		HighlightMaterial();
		m_Board->m_selectedPiece = this;
	}
	// Move on a piece
	else if (m_Board->m_selectedPiece != nullptr)
		m_Board->m_selectedPiece->Move(m_Board->GetCase(m_X, m_Y));
	// TODO: unselect previous piece? on invalid click? On right click?
}

bool APieceActor::isValidMove(ACaseActor* targetCase)
{
	int targetX = targetCase->m_X, targetY = targetCase->m_Y;
	for (auto cs : GetAccessibleCases())
	{
		if (cs->m_X == targetX && cs->m_Y == targetY)
			return true;
	}
	return false;
}

void APieceActor::Move(ACaseActor* targetCase)
{
	if (isValidMove(targetCase))
	{
		HighlightMaterial();

		m_Board->GetCase(m_X, m_Y)->m_Piece = nullptr;
		// TODO: make something cleaner than just destroying
		// "Destroy" opponent piece if any
		if (targetCase->m_Piece != nullptr)
			targetCase->m_Piece->Destroy();
		targetCase->m_Piece = this;
		m_X = targetCase->m_X;
		m_Y = targetCase->m_Y;

		SetActorLocation(targetCase->GetActorLocation());

		m_hasMoved = true;
		m_Board->EndTurn();
	}
}