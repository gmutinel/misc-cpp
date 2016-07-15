//---------------------------------------------------------------------------
//
// Name:        Tales_Of_Legendia_Skit_EditorApp.cpp
// Author:      Vash
// Created:     10/05/10 11.58.40
// Description: 
//
//---------------------------------------------------------------------------

#include "Tales_Of_Legendia_Skit_EditorApp.h"
#include "Tales_Of_Legendia_Skit_EditorFrm.h"

IMPLEMENT_APP(Tales_Of_Legendia_Skit_EditorFrmApp)

bool Tales_Of_Legendia_Skit_EditorFrmApp::OnInit()
{
    Tales_Of_Legendia_Skit_EditorFrm* frame = new Tales_Of_Legendia_Skit_EditorFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int Tales_Of_Legendia_Skit_EditorFrmApp::OnExit()
{
	return 0;
}

