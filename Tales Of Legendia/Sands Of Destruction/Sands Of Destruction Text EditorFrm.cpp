///-----------------------------------------------------------------
///
/// @file      Sands Of Destruction Text EditorFrm.cpp
/// @author    Vash
/// Created:   15/01/2010 20:30:12
/// @section   DESCRIPTION
///            Sands_Of_Destruction_Text_EditorFrm class implementation
///
///------------------------------------------------------------------

#include "Sands Of Destruction Text EditorFrm.h"
#include <stdio.h>
#include <windows.h>
//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_Sands_Of_Destruction_Text_EditorFrm_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// Sands_Of_Destruction_Text_EditorFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Sands_Of_Destruction_Text_EditorFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Sands_Of_Destruction_Text_EditorFrm::OnClose)
	EVT_MENU(ID_MNU_OPEN_1014, Sands_Of_Destruction_Text_EditorFrm::OpenFile)
	EVT_MENU(ID_MNU_EXIT_1017, Sands_Of_Destruction_Text_EditorFrm::OnClose2)
	EVT_MENU(ID_MNU_ABOUT_1019, Sands_Of_Destruction_Text_EditorFrm::About)
	EVT_BUTTON(ID_WXBUTTON2,Sands_Of_Destruction_Text_EditorFrm::BackClick)
	EVT_BUTTON(ID_WXBUTTON1,Sands_Of_Destruction_Text_EditorFrm::NextClick)
END_EVENT_TABLE()
////Event Table End

BYTE buffer[50000];
FILE *dat;
unsigned long int num,i,point[5000];
unsigned short int size[5000],number[5000];
char filename[500],sentences[5000][1500];

Sands_Of_Destruction_Text_EditorFrm::Sands_Of_Destruction_Text_EditorFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Sands_Of_Destruction_Text_EditorFrm::~Sands_Of_Destruction_Text_EditorFrm()
{
}


void Sands_Of_Destruction_Text_EditorFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_FILE_1013_Mnu_Obj = new wxMenu(0);
	ID_MNU_FILE_1013_Mnu_Obj->Append(ID_MNU_OPEN_1014, wxT("Open"), wxT(""), wxITEM_NORMAL);
	ID_MNU_FILE_1013_Mnu_Obj->Append(ID_MNU_EXIT_1017, wxT("Exit"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1013_Mnu_Obj, wxT("File"));
	
	wxMenu *ID_MNU_ABOUT_1018_Mnu_Obj = new wxMenu(0);
	ID_MNU_ABOUT_1018_Mnu_Obj->Append(ID_MNU_ABOUT_1019, wxT("About"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_ABOUT_1018_Mnu_Obj, wxT("?"));
	SetMenuBar(WxMenuBar1);

	Back = new wxButton(this, ID_WXBUTTON2, wxT("Back"), wxPoint(2, 241), wxSize(145, 30), 0, wxDefaultValidator, wxT("Back"));

	Next = new wxButton(this, ID_WXBUTTON1, wxT("Next"), wxPoint(216, 241), wxSize(144, 30), 0, wxDefaultValidator, wxT("Next"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, wxT(""), wxPoint(0, -1), wxSize(360, 242), wxTE_CHARWRAP | wxTE_LINEWRAP | wxTE_WORDWRAP | wxTE_MULTILINE, wxDefaultValidator, wxT("WxEdit1"));
	WxEdit1->SetFont(wxFont(10, wxSWISS, wxNORMAL, wxNORMAL, false));

	SetTitle(wxT("Sands Of Destruction Text Editor"));
	SetIcon(Self_Sands_Of_Destruction_Text_EditorFrm_XPM);
	SetSize(8,8,368,324);
	Center();
	
	////GUI Items Creation End
}

void Sands_Of_Destruction_Text_EditorFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}



/*
 * WxButton1Click
 */
void Sands_Of_Destruction_Text_EditorFrm::OpenFile(wxCommandEvent& event)
{
	
    
    wxFileDialog dialog(this,wxT("Open a file"), wxT(""), wxT(""), wxT("Dat Files (*.dat)|*.dat"));
	int res=dialog.ShowModal();
	if(res!=wxID_OK) return;
	wxString fileName=dialog.GetPath();
    sprintf(filename,"%s",fileName.c_str());
    dat = fopen(filename,"r+b");
    fread(&num,4,1,dat);
    fseek(dat,8,SEEK_SET);
    for (i=0;i<num;i++)
    {
     fread(&number[i],2,1,dat);
     fread(&size[i],2,1,dat);
     fread(&point[i],4,1,dat);   
    }   
     for (i=0;i<num;i++)
    {
      fseek(dat,point[i],SEEK_SET);
      fread(sentences[i],size[i],1,dat);
      sentences[i][size[i]]=0;
    }  
    fseek(dat,point[0],SEEK_SET);
    fread(buffer,size[0],1,dat);
    buffer[size[0]]=0;
    WxEdit1->SetValue(buffer);
    i=0;
}


/*
 * NextClick
 */
void Sands_Of_Destruction_Text_EditorFrm::NextClick(wxCommandEvent& event)
{

int linenum,line=0,q,tmp;
linenum=WxEdit1->GetNumberOfLines();
for (q=1;q<=linenum;q++)
{
tmp=WxEdit1->GetLineLength(q);    
line= line+tmp;
line=line+(2*(q-1));    
} 
size[i]=line;

sprintf(sentences[i],"%s",WxEdit1->GetLineText(0).c_str());
for (q=1;q<=linenum;q++)
{
sprintf(sentences[i],"%s\r\n%s",sentences[i],WxEdit1->GetLineText(q).c_str());
}   
sentences[i][size[i]+1]=0; 
//sprintf(tried,"%d\0",line);
//wxMessageBox(tried);   

i=i+1;    
if (i >= num)
{
i=0;
}
//chiudo il file
fclose(dat);
//ricreo file vuoto
dat=fopen(filename,"w+b");
//creao spazio per header e puntatori
fwrite(&num,4,1,dat);

fputc(0x00,dat);  
fputc(0x00,dat);
fputc(0x00,dat);
fputc(0x00,dat);
unsigned long int s;
unsigned short int sentnum=0x00;
for (s=0;s<num;s++)
{
fwrite(&sentnum,2,1,dat);  
sentnum=sentnum+0x01;
fwrite(&size[s],2,1,dat);  
fputc(0x00,dat);  
fputc(0x00,dat);
fputc(0x00,dat);
fputc(0x00,dat);  
}
//wxMessageBox("6");    
//scrivo testo e ricalcolo puntatori
for (s=0;s<num;s++)
{
point[s]=ftell(dat);    
fwrite(sentences[s],size[s],1,dat);
fputc(0x00,dat);  
while (ftell(dat) % 4 != 0)
 {
   fputc(0x00,dat);   
 }   

}
fseek(dat,0x0C,SEEK_SET);
for (s=0;s<num;s++)
{
fwrite(&point[s],4,1,dat);
fseek(dat,4,SEEK_CUR);
}
//riapro il file
fclose(dat);

dat=fopen(filename,"r+b");


//funzione normale di prelevamento testo
fseek(dat,point[i],SEEK_SET);
fread(buffer,size[i],1,dat);
buffer[size[i]]=0;
WxEdit1->SetValue(buffer);
}

/*
 * NumberClickUrl
 */

/*
 * BackClick
 */
void Sands_Of_Destruction_Text_EditorFrm::BackClick(wxCommandEvent& event)
{
int linenum,line=0,q,tmp;
linenum=WxEdit1->GetNumberOfLines();
for (q=1;q<=linenum;q++)
{
tmp=WxEdit1->GetLineLength(q);    
line= line+tmp;
line=line+(2*(q-1));    
} 
size[i]=line;
sprintf(sentences[i],"%s",WxEdit1->GetLineText(0).c_str());
for (q=1;q<=linenum;q++)
{
sprintf(sentences[i],"%s\r\n%s",sentences[i],WxEdit1->GetLineText(q).c_str());
}   
sentences[i][size[i]+1]=0;     
i--;    
if (i == -1)
{
i=num-1;
}
//chiudo il file
fclose(dat);
//ricreo file vuoto
dat=fopen(filename,"w+b");
//creao spazio per header e puntatori
fwrite(&num,4,1,dat);

fputc(0x00,dat);  
fputc(0x00,dat);
fputc(0x00,dat);
fputc(0x00,dat);
unsigned long int s;
unsigned short int sentnum=0x00;
for (s=0;s<num;s++)
{
fwrite(&sentnum,2,1,dat);  
sentnum=sentnum+0x01;
fwrite(&size[s],2,1,dat);  
fputc(0x00,dat);  
fputc(0x00,dat);
fputc(0x00,dat);
fputc(0x00,dat);  
}
//wxMessageBox("6");    
//scrivo testo e ricalcolo puntatori
for (s=0;s<num;s++)
{
point[s]=ftell(dat);    
fwrite(sentences[s],size[s],1,dat);
fputc(0x00,dat);  
while (ftell(dat) % 4 != 0)
 {
   fputc(0x00,dat);   
 }   

}
fseek(dat,0x0C,SEEK_SET);
for (s=0;s<num;s++)
{
fwrite(&point[s],4,1,dat);
fseek(dat,4,SEEK_CUR);
}
//riapro il file
fclose(dat);

dat=fopen(filename,"r+b");


//funzione normale di prelevamento testo
fseek(dat,point[i],SEEK_SET);
fread(buffer,size[i],1,dat);
buffer[size[i]]=0;
WxEdit1->SetValue(buffer);	
}

/*
 * OnClose2
 */
void Sands_Of_Destruction_Text_EditorFrm::OnClose2(wxCommandEvent& event)
{
	Destroy();
}

/*
 * About
 */
void Sands_Of_Destruction_Text_EditorFrm::About(wxCommandEvent& event)
{
	wxMessageBox("Sands Of Destruction Text Editor v0.5 by Vash\n               www.romhacking.it");
}
