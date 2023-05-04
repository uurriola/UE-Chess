// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPieceActor.h"
#include "BoardActor.h"
#include "CaseActor.h"

TArray<ACaseActor*> APawnPieceActor::GetAccessibleCases()
{
	TArray<ACaseActor*> accessibleCases;
	
	int direction = (m_Color == BLACK) ? 1 : -1;

	ACaseActor* frontCase = m_Board->GetCase(m_X + direction, m_Y);
	if (frontCase->m_Piece == nullptr)
		accessibleCases.Add(frontCase);
	frontCase = m_Board->GetCase(m_X + 2 * direction, m_Y);
	if (!m_hasMoved && frontCase->m_Piece == nullptr)
		accessibleCases.Add(frontCase);
	ACaseActor* diagonalCase;
	if (m_Y > 0)
	{
		diagonalCase = m_Board->GetCase(m_X + direction, m_Y - 1);
		if (diagonalCase->m_Piece != nullptr && diagonalCase->m_Piece->m_Color != m_Color)
			accessibleCases.Add(diagonalCase);
	}

	if (m_Y < 7)
	{
		diagonalCase = m_Board->GetCase(m_X + direction, m_Y + 1);
		if (diagonalCase->m_Piece != nullptr && diagonalCase->m_Piece->m_Color != m_Color)
			accessibleCases.Add(diagonalCase);
	}

	// TODO: en passant
	// TODO: promotion

	return accessibleCases;
}