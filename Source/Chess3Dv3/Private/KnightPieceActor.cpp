// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPieceActor.h"
#include "BoardActor.h"
#include "CaseActor.h"

TArray<ACaseActor*> AKnightPieceActor::GetAccessibleCases()
{
	TArray<ACaseActor*> accessibleCases;
	for (int deltaX : {-2, -1, 1, 2})
	{
		for (int deltaY : {-2, -1, 1, 2})
		{
			if (deltaX == deltaY || deltaX == -deltaY)
				continue;
			int x = m_X + deltaX, y = m_Y + deltaY;
			if (x >= 0 && x < 8 && y >= 0 && y < 8)
			{
				ACaseActor* targetCase = m_Board->GetCase(x, y);
				// Avoid case with a piece
				if (targetCase->m_Piece == nullptr || targetCase->m_Piece->m_Color != m_Color)
					accessibleCases.Add(targetCase);
			}
		}
	}

	return accessibleCases;
}

