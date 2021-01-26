// Fill out your copyright notice in the Description page of Project Settings.


#include "RikHUD.h"

#include "Engine/Canvas.h"

ARikHUD::ARikHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairFinder(TEXT("/Game/UI/FirstPersonCrosshair"));
	if(CrosshairFinder.Object)
	{
		CrosshairTexture = CrosshairFinder.Object;
	}
}

void ARikHUD::DrawHUD()
{
	Super::DrawHUD();

	// Find the center of the screen
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	const FVector2D CrosshairPosition(Center.X - CrosshairTexture->GetSurfaceWidth() / 2, Center.Y - CrosshairTexture->GetSurfaceHeight() / 2);

	FCanvasTileItem TileItem(CrosshairPosition, CrosshairTexture->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
