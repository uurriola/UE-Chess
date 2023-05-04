# UE - Chess

Basic 3D chess game made with Unreal Engine 5.1.

![Gameplay](/Assets/gameplay.gif)

## Gameplay

All paws are controlled using the mouse. Selecting a pawn highlights possible moves.
Selecting a valid target case will move the pawn. Players alternate turns.

## Limits

Three main moves are missing: Castling, En passant and Promotions.

Check and checkmates are partially computed:
* king cannot move on a case that would lead to a check situation,
* in a check position, player is not enforced to defend.
