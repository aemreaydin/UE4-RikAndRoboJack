// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RikHUD.generated.h"


UCLASS()
class METALGEARNOTSOSOLID_API ARikHUD final : public AHUD
{
	GENERATED_BODY()

public:
	ARikHUD();

protected:
	UTexture2D* CrosshairTexture;

public:
	virtual void DrawHUD() override;
};
