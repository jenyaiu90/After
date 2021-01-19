    ////////////////////////////////////////
   //        After by SnegirSoft         //
  // License: GNU GPL v2.0              //
 //  File: LastController.h            //
////////////////////////////////////////

#include "LastController.h"

#include "Last.h"

ALastController::ALastController() :
	APlayerController()
{
	SetShowMouseCursor(true);
}

void ALastController::BeginPlay()
{
	SetupInput();
}

void ALastController::SetupInput()
{
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