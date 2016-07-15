///-----------------------------------------------------------------
///
/// @file      Sands Of Destruction Text EditorFrm.h
/// @author    Vash
/// Created:   15/01/2010 20:30:12
/// @section   DESCRIPTION
///            Sands_Of_Destruction_Text_EditorFrm class declaration
///
///------------------------------------------------------------------

#ifndef __SANDS_OF_DESTRUCTION_TEXT_EDITORFRM_H__
#define __SANDS_OF_DESTRUCTION_TEXT_EDITORFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/textctrl.h>
////Header Include End

////Dialog Style Start
#undef Sands_Of_Destruction_Text_EditorFrm_STYLE
#define Sands_Of_Destruction_Text_EditorFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class Sands_Of_Destruction_Text_EditorFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Sands_Of_Destruction_Text_EditorFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Sands Of Destruction Text Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Sands_Of_Destruction_Text_EditorFrm_STYLE);
		virtual ~Sands_Of_Destruction_Text_EditorFrm();
		void WxButton1Click(wxCommandEvent& event);
		void NextClick(wxCommandEvent& event);
		void OpenFile(wxCommandEvent& event);
		void NumberClickUrl(wxTextUrlEvent& event);
		void BackClick(wxCommandEvent& event);
		//void OnClose2(wxCommandEvent& event);
		void OnClose2(wxCommandEvent& event);
		void About(wxCommandEvent& event);
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenuBar *WxMenuBar1;
		wxButton *Back;
		wxButton *Next;
		wxTextCtrl *WxEdit1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_FILE_1013 = 1013,
			ID_MNU_OPEN_1014 = 1014,
			ID_MNU_EXIT_1017 = 1017,
			ID_MNU_ABOUT_1018 = 1018,
			ID_MNU_ABOUT_1019 = 1019,
			
			ID_WXBUTTON2 = 1016,
			ID_WXBUTTON1 = 1015,
			ID_WXEDIT1 = 1009,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
