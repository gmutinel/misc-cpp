//---------------------------------------------------------------------------
//
// Name:        Sands Of Destruction Text EditorApp.cpp
// Author:      Vash
// Created:     15/01/2010 20:30:12
// Description: 
//
//---------------------------------------------------------------------------

#include "Sands Of Destruction Text EditorApp.h"
#include "Sands Of Destruction Text EditorFrm.h"

IMPLEMENT_APP(Sands_Of_Destruction_Text_EditorFrmApp)

bool Sands_Of_Destruction_Text_EditorFrmApp::OnInit()
{
    Sands_Of_Destruction_Text_EditorFrm* frame = new Sands_Of_Destruction_Text_EditorFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int Sands_Of_Destruction_Text_EditorFrmApp::OnExit()
{
	return 0;
}
