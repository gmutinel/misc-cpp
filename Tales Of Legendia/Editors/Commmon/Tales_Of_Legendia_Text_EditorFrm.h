///-----------------------------------------------------------------
///
/// @file      Tales_Of_Legendia_Text_EditorFrm.h
/// @author    Vash
/// Created:   10/05/10 11.58.50
/// @section   DESCRIPTION
///            Tales_Of_Legendia_Text_EditorFrm class declaration
///
///------------------------------------------------------------------

#ifndef __TALES_OF_LEGENDIA_Text_EDITORFRM_H__
#define __TALES_OF_LEGENDIA_Text_EDITORFRM_H__

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
#include <wx/panel.h>
////Header Include End

////Dialog Style Start
#undef Tales_Of_Legendia_Text_EditorFrm_STYLE
#define Tales_Of_Legendia_Text_EditorFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class Tales_Of_Legendia_Text_EditorFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Tales_Of_Legendia_Text_EditorFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Tales Of Legendia Text Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Tales_Of_Legendia_Text_EditorFrm_STYLE);
		virtual ~Tales_Of_Legendia_Text_EditorFrm();
		void OpenFile(wxCommandEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
		void Quit(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void Tales_Of_Legendia_Text_EditorFrmActivate(wxActivateEvent& event);
		void About(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenuBar *WxMenuBar1;
		wxButton *WxButton2;
		wxButton *WxButton1;
		wxTextCtrl *WxEdit1;
		wxPanel *WxPanel1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_FILE_1004 = 1004,
			ID_MNU_OPEN_1005 = 1005,
			ID_MNU_CLOSE_1006 = 1006,
			ID_MNU___1015 = 1015,
			ID_MNU_ABOUT_1016 = 1016,
			
			ID_WXBUTTON2 = 1014,
			ID_WXBUTTON1 = 1012,
			ID_WXEDIT1 = 1007,
			ID_WXPANEL1 = 1003,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
