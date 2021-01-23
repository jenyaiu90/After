    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: LastController.h            //
////////////////////////////////////////

#include "LastController.h"

#include "Last.h"
#include "../../Unit/Unit.h"

ALastController::ALastController() :
	APlayerController()
{
	SetShowMouseCursor(true);
	bEnableMouseOverEvents = true;
}

void ALastController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Selected: %s"), Selected ? *Selected->GetName() : *FString("None")));
}

void ALastController::Select(AActor* Actor)
{
	AEntity* Entity = Cast<AEntity>(Actor);
	bool bNew = false;
	AActor* Old = Selected;
	if (Entity)
	{
		Selected = Entity;
		Entity->Select();
		bNew = true;
	}
	else
	{
		AUnit* Unit = Cast<AUnit>(Actor);
		if (Unit)
		{
			Selected = Unit;
			Unit->Select();
			bNew = true;
		}
	}

	if (bNew && Old)
	{
		Unselect(Old);
	}
}

void ALastController::Unselect(AActor* Actor)
{
	AEntity* Entity = Cast<AEntity>(Actor);
	if (Entity)
	{
		Entity->Unselect();
	}
	else
	{
		AUnit* Unit = Cast<AUnit>(Actor);
		if (Unit)
		{
			Unit->Unselect();
		}
	}
	if (Selected == Actor)
	{
		Selected = nullptr;
	}
}

void ALastController::BeginPlay()
{
	SetupInput();
}

void ALastController::SetupInput()
{
	if (CurrentInputStack.Num() <= 0)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Input stack is empty."));
	}

	ALast* Last = Cast<ALast>(GetPawn());

	if (Last)
	{
		CurrentInputStack[0]->BindAxis("MoveX", Last, &ALast::MoveX);
		CurrentInputStack[0]->BindAxis("MoveY", Last, &ALast::MoveY);

		CurrentInputStack[0]->BindAction("ZoomIn", IE_Pressed, Last, &ALast::ZoomIn);
		CurrentInputStack[0]->BindAction("ZoomOut", IE_Pressed, Last, &ALast::ZoomOut);
		CurrentInputStack[0]->BindAction("Run", IE_Pressed, Last, &ALast::StartRunning);
		CurrentInputStack[0]->BindAction("Run", IE_Released, Last, &ALast::StopRunning);
	}
}