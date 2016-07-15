//---------------------------------------------------------------------------
//
// Name:        Sands Of Destruction Text EditorApp.h
// Author:      Vash
// Created:     15/01/2010 20:30:12
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __SANDS_OF_DESTRUCTION_TEXT_EDITORFRMApp_h__
#define __SANDS_OF_DESTRUCTION_TEXT_EDITORFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class Sands_Of_Destruction_Text_EditorFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
