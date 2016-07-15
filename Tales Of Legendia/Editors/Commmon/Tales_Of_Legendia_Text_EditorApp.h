//---------------------------------------------------------------------------
//
// Name:        Tales_Of_Legendia_Text_EditorApp.h
// Author:      Vash
// Created:     10/05/10 11.58.38
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __TALES_OF_LEGENDIA_TEXT_EDITORFRMApp_h__
#define __TALES_OF_LEGENDIA_TEXT_EDITORFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class Tales_Of_Legendia_Text_EditorFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
