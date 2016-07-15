///-----------------------------------------------------------------
///
/// @file      Tales_Of_Legendia_Skit_EditorFrm.cpp
/// @author    Vash
/// Created:   10/05/10 11.58.50
/// @section   DESCRIPTION
///            Tales_Of_Legendia_Skit_EditorFrm class implementation
///
///------------------------------------------------------------------

#include "Tales_Of_Legendia_Skit_EditorFrm.h"
#include <stdio.h>
#include <windows.h>
//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_Tales_Of_Legendia_Skit_EditorFrm_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// Tales_Of_Legendia_Skit_EditorFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Tales_Of_Legendia_Skit_EditorFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Tales_Of_Legendia_Skit_EditorFrm::OnClose)
	EVT_MENU(ID_MNU_OPEN_1005, Tales_Of_Legendia_Skit_EditorFrm::OpenFile)
	EVT_MENU(ID_MNU_CLOSE_1006, Tales_Of_Legendia_Skit_EditorFrm::Quit)
	EVT_BUTTON(ID_WXBUTTON2,Tales_Of_Legendia_Skit_EditorFrm::WxButton2Click)
	EVT_BUTTON(ID_WXBUTTON1,Tales_Of_Legendia_Skit_EditorFrm::WxButton1Click)
	
	EVT_TEXT(ID_WXEDIT1,Tales_Of_Legendia_Skit_EditorFrm::WxEdit1Updated)
END_EVENT_TABLE()
////Event Table End
void LoadTable(void);
void ParseSentences(void);
BYTE buffer[50000],buffer2[500][500],shit[10485760];
FILE *skt, *tbl;
unsigned long int index,PointField,num,point[1000],i,c,len[1000],tmplen,s,news,toRead;
char filename[500],frase[500][5000];
char parsedsent[1000]; //qui andrà la frase parsata da reinserire
unsigned char table[256][256],byte1,byte2;
Tales_Of_Legendia_Skit_EditorFrm::Tales_Of_Legendia_Skit_EditorFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Tales_Of_Legendia_Skit_EditorFrm::~Tales_Of_Legendia_Skit_EditorFrm()
{
}

void Tales_Of_Legendia_Skit_EditorFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(-1, 1), wxSize(598, 446));

	WxEdit1 = new wxTextCtrl(WxPanel1, ID_WXEDIT1, wxT(""), wxPoint(0, 32), wxSize(598, 321), wxTE_MULTILINE, wxDefaultValidator, wxT("WxEdit1"));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, wxT("Back"), wxPoint(25, 367), wxSize(175, 37), 0, wxDefaultValidator, wxT("WxButton1"));

	WxButton2 = new wxButton(WxPanel1, ID_WXBUTTON2, wxT("Next"), wxPoint(396, 367), wxSize(174, 37), 0, wxDefaultValidator, wxT("WxButton2"));

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_FILE_1004_Mnu_Obj = new wxMenu(0);
	ID_MNU_FILE_1004_Mnu_Obj->Append(ID_MNU_OPEN_1005, wxT("Open"), wxT(""), wxITEM_NORMAL);
	ID_MNU_FILE_1004_Mnu_Obj->Append(ID_MNU_CLOSE_1006, wxT("Close"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1004_Mnu_Obj, wxT("File"));
	SetMenuBar(WxMenuBar1);

	SetTitle(wxT("Tales Of Legendia Skit Editor"));
	SetIcon(Self_Tales_Of_Legendia_Skit_EditorFrm_XPM);
	SetSize(8,8,609,482);
	Center();
	
	////GUI Items Creation End
}

void Tales_Of_Legendia_Skit_EditorFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * Quit
 */
void Tales_Of_Legendia_Skit_EditorFrm::Quit(wxCommandEvent& event)
{
	Destroy();
}

/*
 * OpenFile
 */
void Tales_Of_Legendia_Skit_EditorFrm::OpenFile(wxCommandEvent& event)
{
wxFileDialog dialog(this,wxT("Open a file"), wxT(""), wxT(""), wxT("Skit Files (skit_*.mcd)|skit_*.mcd"));
	int res=dialog.ShowModal();
	if(res!=wxID_OK) return;
	wxString fileName=dialog.GetPath();
    sprintf(filename,"%s",fileName.c_str());
    skt=fopen(filename,"r+b");
    LoadTable();
    fseek(skt,0x68,SEEK_SET);
    fread(&PointField,4,1,skt);
    PointField+=0x40;
    fseek(skt,PointField,SEEK_SET);
    fread(buffer,4,1,skt);
    if (buffer[0] == 0x53 && buffer[1] == 0x32 && buffer[2] == 0x42 == buffer[3] == 0x00)
    {
      WxEdit1->SetValue("");
      //sprintf(frase,"\0");
      //empty the string array
      for (i=0;i<num;i++)
      {
       frase[i][0]=0;     
        }
      //frase[0][0]=0;
      fread(&num,4,1,skt);  
      //load the shit into a buffer to recreate the whole file later
    rewind(skt);
    toRead=PointField+0x10+(num*4);
    fread(shit,toRead,1,skt);
    //loaded
      //fseek(skt,8,SEEK_CUR);
      fseek(skt,PointField+0x10,SEEK_SET);
      for (i=0;i<num;i++)
      {
        fread(&point[i],4,1,skt);    
       }
      fseek(skt,PointField+point[num-1],SEEK_SET);
      //recover last length
     bool check=false;
     int f,g;
      while (check != true)
      {
      f=fgetc(skt);
      g=fgetc(skt);
      if (f == 0x00 && g == 0x00)
      check=true;      
       }
      point[num]=ftell(skt)-PointField; 
      for (i=0;i<num;i++)
      {
        fseek(skt,PointField+point[i],SEEK_SET);
        len[i]=point[i+1]-point[i];
        fread(buffer2[i],len[i],1,skt);    
      }
    //creo la frase con la table 
   index=0;
   for (s=0;s<num;s++)
   {
   c=0;
   tmplen=len[s];
   for (i=0;i<tmplen;i++)  
   {
    byte1=buffer2[s][c];
    c++;
    byte2=buffer2[s][c];                         
    c++;
    //if (byte1 == 0x02 && byte2 == 0xD8)
    //{
    // sprintf(frase,"%s\n",frase);
    // }else{
    if (byte1 == 0x00 && byte2 == 0x00)
    {
    i=tmplen;    
    }else{
    if (table[byte1][byte2]=='*')
    {
    sprintf(frase[s],"%s{%X}{%X}",frase[s],byte1,byte2);
    i++;
    }else{                           
        
    sprintf(frase[s],"%s%c",frase[s],table[byte1][byte2]);
    i++;
    }
}
       
    }
    
     }
    //sprintf(frase[s],"%s",frase[s]);
    WxEdit1->SetValue(frase[index]);                    
    fclose(skt);
    }else{
    wxMessageBox("This file doesn't contain text");
    fclose(skt);    
    }
}

/*
 * Next
 */
void Tales_Of_Legendia_Skit_EditorFrm::WxButton2Click(wxCommandEvent& event)
{

int q,linenum,endfile;
linenum=WxEdit1->GetNumberOfLines();
frase[index][0]=0;
for (q=0;q<linenum-1;q++)
{
sprintf(frase[index],"%s%s\n",frase[index],WxEdit1->GetLineText(q).c_str());
}  
sprintf(frase[index],"%s%s\0",frase[index],WxEdit1->GetLineText(linenum-1).c_str());
//frase nuova riportata nell'array di visualizzazione
//ricreazione file
skt=fopen(filename,"w+b");
fwrite(shit,toRead,1,skt);
ParseSentences();
//dentro parsedsent ho la frase da reinserire e news+3 è la lunghezza

for (i=0;i<num;i++)
{   
point[i]=ftell(skt)-PointField;
if (i != index)
{    
fwrite(buffer2[i],len[i],1,skt);
}else{
fwrite(parsedsent,news+4,1,skt);    
}
}
fseek(skt,PointField+0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,skt);
}
fseek(skt,0x00,SEEK_END);
endfile=ftell(skt);
fseek(skt,0x08,SEEK_SET);
fwrite(&endfile,4,1,skt);
//fseek(skt,0x18,SEEK_SET);
//fwrite(&endfile-0x40,4,1,skt); 
fclose(skt);          
//file ricreato con frase nuova e ripuntato

	if (index != num-1)
	{
        index++;
     }    else{
            index=0;    
        }
        
WxEdit1->SetValue(frase[index]); 
}


/*
 * Back
 */
void Tales_Of_Legendia_Skit_EditorFrm::WxButton1Click(wxCommandEvent& event)
{

int q,linenum,endfile;
linenum=WxEdit1->GetNumberOfLines();
frase[index][0]=0;
for (q=0;q<linenum-1;q++)
{
sprintf(frase[index],"%s%s\n",frase[index],WxEdit1->GetLineText(q).c_str());
}  
sprintf(frase[index],"%s%s\0",frase[index],WxEdit1->GetLineText(linenum-1).c_str());
//frase nuova riportata nell'array di visualizzazione
//ricreazione file
skt=fopen(filename,"w+b");
fwrite(shit,toRead,1,skt);
ParseSentences();
//dentro parsedsent ho la frase da reinserire e news+3 è la lunghezza

for (i=0;i<num;i++)
{   
point[i]=ftell(skt)-PointField;
if (i != index)
{    
fwrite(buffer2[i],len[i],1,skt);
}else{
fwrite(parsedsent,news+4,1,skt);    
}
}
fseek(skt,PointField+0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,skt);
}
fseek(skt,0x00,SEEK_END);
endfile=ftell(skt);
fseek(skt,0x08,SEEK_SET);
fwrite(&endfile,4,1,skt);
//fseek(skt,0x18,SEEK_SET);
//fwrite(&endfile-0x40,4,1,skt); 
fclose(skt);          
//file ricreato con frase nuova e ripuntato

if (index != 0)
	{
        index--;
     }    else{
            index=num-1;    
        }
        
WxEdit1->SetValue(frase[index]); 
}




void Tales_Of_Legendia_Skit_EditorFrm::WxEdit1Updated(wxCommandEvent& event)
{
//nulla
}

void LoadTable(void)
{
long int c,endtbl;
unsigned char byte,byte1,byte2,byte3,byte4;        
tbl=fopen("tol.tbl","r+b");
for(i=0;i<256;i++)
           {
             for(c=0;c<256;c++)
             {
                table[i][c]='*';
                }}
           
           fseek(tbl,0x00,SEEK_END);
           endtbl=ftell(tbl);
           rewind(tbl);
           while(ftell(tbl)<endtbl)
           {
             byte1=fgetc(tbl);
             if (byte1 >= 0x30 && byte1 <= 0x39)
             {
                byte1=(byte1-0x30)*0x10;
                }else{
                      byte1=(byte1-0x37)*0x10;
                      }
             byte2=fgetc(tbl);
             if (byte2 >= 0x30 && byte2 <= 0x39)
             {
                byte2=(byte2-0x30);
                }else{
                      byte2=(byte2-0x37);
                      }
              byte3=fgetc(tbl);
             if (byte3 >= 0x30 && byte3 <= 0x39)
             {
                byte3=(byte3-0x30)*0x10;
                }else{
                      byte3=(byte3-0x37)*0x10;
                      }
            byte4=fgetc(tbl);
             if (byte4 >= 0x30 && byte4 <= 0x39)
             {
                byte4=(byte4-0x30);
                }else{
                      byte4=(byte4-0x37);
                      }
             fseek(tbl,1,SEEK_CUR);
             byte=fgetc(tbl);
             table[byte1+byte2][byte3+byte4]=byte; 
             //printf("%x%x = %c\n",byte1+byte2,byte3+byte4,byte);
             fseek(tbl,2,SEEK_CUR);
            
            //add tags here
            table[0x02][0xD8]='\n'; //a capo
            table[0x00][0x00]='\0';  //fine riga
            table[0x00][0xD9]='\0'; 
             }
}

void ParseSentences(void)
{
FILE *txt;
int len2;
txt=fopen("test.dat","w+b");
len2=strlen(frase[index]);
fwrite(frase[index],len2,1,txt);
fclose(txt);
int byte1,byte2,byte;
unsigned long int len,lol;
news=0;
len=strlen(frase[index]);
for (i=0;i<len;i++)
{
lol=news;    
if (frase[index][i] == 0x7B)
{ 
byte1=frase[index][i+1]-0x30;
byte2=frase[index][i+2]-0x30;
if (byte1 > 10)
{
byte1=byte1-0x07;    
}
if (byte2 > 10)
{
byte2=byte2-0x07;    
}
byte=(byte1*0x10)+byte2;
i=i+3;
parsedsent[news]=byte;
news=news+1;
        
}
//gestion IF per i tag
if (frase[index][i] == 0x0A) //a capo
{
parsedsent[news]=0x02;
news=news+1;     
parsedsent[news]=0xD8;
news=news+1;       
}
if (frase[index][i] == 0x20) //spazio
{
parsedsent[news]=0x00;
news=news+1;     
parsedsent[news]=0x30;
news=news+1;       
}
if (frase[index][i] == 0x27) //apostrofo
{
parsedsent[news]=0x19;
news=news+1;     
parsedsent[news]=0x20;
news=news+1;       
}
if (frase[index][i] == 0x22) //virgolette
{
parsedsent[news]=0x1D;
news=news+1;    
parsedsent[news]=0x20;
news=news+1;       
} 
      
if (lol == news)
{
parsedsent[news]=frase[index][i]-0x20;
parsedsent[news+1]=0xFF;
news=news+2;     
}


}//for
parsedsent[news]= 0x00;
parsedsent[news+1]= 0xD9;
parsedsent[news+2]= 0x00;
parsedsent[news+3]= 0x00;
}  //func



