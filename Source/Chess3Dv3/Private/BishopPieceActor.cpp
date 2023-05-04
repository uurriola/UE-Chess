// Fill out your copyright notice in the Description page of Project Settings.


#include "BishopPieceActor.h"
#include "BoardActor.h"
#include "CaseActor.h"

TArray<ACaseActor*> ABishopPieceActor::GetAccessibleCases()
{
	TArray<ACaseActor*> accessibleCases;
	for (int deltaX : {-1, 1})
	{
		for (int deltaY : {-1, 1})
		{
			for (int d = 1; d < 8; d++)
			{
				int x = m_X + d * deltaX, y = m_Y + d * deltaY;
				if (x >= 0 && x < 8 && y >= 0 && y < 8)
				{
					ACaseActor* targetCase = m_Board->GetCase(x, y);
					if (targetCase->m_Piece == nullptr)
						accessibleCases.Add(targetCase);
					else
					{
						// Stop on first case with a piece
						if (targetCase->m_Piece->m_Color != m_Color)
							accessibleCases.Add(targetCase);
						break;
					}
				}
				else
					break;
			}
		}
	}

	return accessibleCases;
}

