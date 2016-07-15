///-----------------------------------------------------------------
///
/// @file      Tales_Of_Legendia_Text_EditorFrm.cpp
/// @author    Vash
/// Created:   10/05/10 11.58.50
/// @section   DESCRIPTION
///            Tales_Of_Legendia_Text_EditorFrm class implementation
///
///------------------------------------------------------------------

#include "Tales_Of_Legendia_Text_EditorFrm.h"
#include <stdio.h>
#include <windows.h>
//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_Tales_Of_Legendia_Text_EditorFrm_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// Tales_Of_Legendia_Text_EditorFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Tales_Of_Legendia_Text_EditorFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Tales_Of_Legendia_Text_EditorFrm::OnClose)
	EVT_MENU(ID_MNU_OPEN_1005, Tales_Of_Legendia_Text_EditorFrm::OpenFile)
	EVT_MENU(ID_MNU_CLOSE_1006, Tales_Of_Legendia_Text_EditorFrm::Quit)
	EVT_MENU(ID_MNU_ABOUT_1016, Tales_Of_Legendia_Text_EditorFrm::About)
	EVT_BUTTON(ID_WXBUTTON2,Tales_Of_Legendia_Text_EditorFrm::WxButton2Click)
	EVT_BUTTON(ID_WXBUTTON1,Tales_Of_Legendia_Text_EditorFrm::WxButton1Click)
	
	EVT_TEXT(ID_WXEDIT1,Tales_Of_Legendia_Text_EditorFrm::WxEdit1Updated)
END_EVENT_TABLE()
////Event Table End
void LoadTable(void);
void ParseSentences(void);
BYTE buffer[50000],buffer2[5000][500],shit[100][10485760],head[0x10100],texthead[0x10100];
FILE *skt, *tbl;
unsigned long int tmpPoint[500],tmp,go,gopint,index,PointField,num=0,point[5000],i,c,len[5000],tmplen,s,news,toRead,numFiles,pointFiles[500];
unsigned long int numSubFiles,subLen[100],subPoint[100],DoNotIns,format;
char filename[500],frase[5000][5000];
char parsedsent[5000]; //qui andrà la frase parsata da reinserire
unsigned char table[256][256],byte1,byte2;
Tales_Of_Legendia_Text_EditorFrm::Tales_Of_Legendia_Text_EditorFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Tales_Of_Legendia_Text_EditorFrm::~Tales_Of_Legendia_Text_EditorFrm()
{
}

void Tales_Of_Legendia_Text_EditorFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(-1, 1), wxSize(518, 386));

	WxEdit1 = new wxTextCtrl(WxPanel1, ID_WXEDIT1, wxT(""), wxPoint(0, 28), wxSize(518, 278), wxTE_MULTILINE, wxDefaultValidator, wxT("WxEdit1"));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, wxT("Back"), wxPoint(22, 318), wxSize(151, 32), 0, wxDefaultValidator, wxT("WxButton1"));

	WxButton2 = new wxButton(WxPanel1, ID_WXBUTTON2, wxT("Next"), wxPoint(343, 318), wxSize(151, 32), 0, wxDefaultValidator, wxT("WxButton2"));

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_FILE_1004_Mnu_Obj = new wxMenu(0);
	ID_MNU_FILE_1004_Mnu_Obj->Append(ID_MNU_OPEN_1005, wxT("Open"), wxT(""), wxITEM_NORMAL);
	ID_MNU_FILE_1004_Mnu_Obj->Append(ID_MNU_CLOSE_1006, wxT("Close"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1004_Mnu_Obj, wxT("File"));
	
	wxMenu *ID_MNU___1015_Mnu_Obj = new wxMenu(0);
	ID_MNU___1015_Mnu_Obj->Append(ID_MNU_ABOUT_1016, wxT("About"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU___1015_Mnu_Obj, wxT("?"));
	SetMenuBar(WxMenuBar1);

	SetTitle(wxT("Tales Of Legendia Text Editor"));
	SetIcon(Self_Tales_Of_Legendia_Text_EditorFrm_XPM);
	SetSize(8,8,522,419);
	Center();
	
	////GUI Items Creation End
}

void Tales_Of_Legendia_Text_EditorFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * Quit
 */
void Tales_Of_Legendia_Text_EditorFrm::Quit(wxCommandEvent& event)
{
	Destroy();
}

/*
 * OpenFile
 */
void Tales_Of_Legendia_Text_EditorFrm::OpenFile(wxCommandEvent& event)
{
wxFileDialog dialog(this,wxT("Open a file"), wxT(""), wxT(""), wxT("Text Files (*.text)|*.text"));
	int res=dialog.ShowModal();
	if(res!=wxID_OK) return;
	wxString fileName=dialog.GetPath();
    sprintf(filename,"%s",fileName.c_str());
    skt=fopen(filename,"r+b");
    LoadTable();
      
//controllo header per verificare il formato
fread(buffer,4,1,skt);
format=0;
if (buffer[0] == 0x4D && buffer[1] == 0x53 && buffer[2] == 0x47 && buffer[3] == 0x45) //MSGE
{
    format=1;
}

if (buffer[0] == 0x53 && buffer[1] == 0x32 && buffer[2] == 0x42 && buffer[3] == 0x00) //S2B
{
    format=1;
}
if (format ==0)
{      
//table caricata, ora raccolgo i sottofile e raggiungo il testo
fseek(skt,0x08,SEEK_SET);
fread(&numSubFiles,4,1,skt);
fseek(skt,0x10,SEEK_SET);
for (i=0;i<numSubFiles;i++) //leggo i valori relativi ai sotto file
{
fread(&subLen[i],4,1,skt);
fseek(skt,4,SEEK_CUR);
fread(&subPoint[i],4,1,skt);    
fseek(skt,4,SEEK_CUR);
}
//carico l'header nel buffer
rewind(skt);
fread(head,(numSubFiles*0x10)+0x10,1,skt); 
for (i=0;i<numSubFiles;i++) //carico i sottofile nel buffer multidimensionale e individuo quello con il testo
{
fseek(skt,subPoint[i],SEEK_SET);    
fread(buffer,4,1,skt);
if (buffer[0] == 0x53 && buffer[1] == 0x32 && buffer[2] == 0x42 && buffer[3] == 0x00)
{
PointField=subPoint[i];
DoNotIns=i;
}
fseek(skt,subPoint[i],SEEK_SET); 
fread(shit[i],subLen[i],1,skt);        
}    
      
     /*  char diobue[100];
      sprintf(diobue,"%X",DoNotIns);
      wxMessageBox(diobue);   */

      fseek(skt,PointField+4,SEEK_SET);
      WxEdit1->SetValue("");
      //sprintf(frase,"\0");
      //empty the string array
      for (i=0;i<num;i++)
      {
       frase[i][0]=0;     
        }

      fread(&num,4,1,skt);  
      //load the textfile header into a buffer to recreate the whole file later
   fseek(skt,PointField,SEEK_SET);
    toRead=0x10+(num*4);
    fread(texthead,toRead,1,skt);
    //loaded
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
    if (byte1<16 && byte2>15)
    {
    sprintf(frase[s],"%s{0%X}{%X}",frase[s],byte1,byte2);    
    }
    if (byte1>15 && byte2<16)
    {
    sprintf(frase[s],"%s{%X}{0%X}",frase[s],byte1,byte2);    
    }
    if (byte1<16 && byte2<16)
    {
    sprintf(frase[s],"%s{0%X}{0%X}",frase[s],byte1,byte2);    
    }
    
    if (byte1>15 && byte2>15)
    {          
    sprintf(frase[s],"%s{%X}{%X}",frase[s],byte1,byte2);
    }
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
}else{ //format else
WxEdit1->SetValue("");
for (i=0;i<num;i++)
      {
       frase[i][0]=0;     
        }
PointField=0x00;        
fseek(skt,PointField+4,SEEK_SET);        
fread(&num,4,1,skt);  
      //load the textfile header into a buffer to recreate the whole file later
   fseek(skt,PointField,SEEK_SET);
    toRead=0x10+(num*4);
    fread(texthead,toRead,1,skt);
    //loaded
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
    if (byte1<16 && byte2>15)
    {
    sprintf(frase[s],"%s{0%X}{%X}",frase[s],byte1,byte2);    
    }
    if (byte1>15 && byte2<16)
    {
    sprintf(frase[s],"%s{%X}{0%X}",frase[s],byte1,byte2);    
    }
    if (byte1<16 && byte2<16)
    {
    sprintf(frase[s],"%s{0%X}{0%X}",frase[s],byte1,byte2);    
    }
    
    if (byte1>15 && byte2>15)
    {          
    sprintf(frase[s],"%s{%X}{%X}",frase[s],byte1,byte2);
    }
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
}    
}

/*
 * Next
 */
void Tales_Of_Legendia_Text_EditorFrm::WxButton2Click(wxCommandEvent& event)
{

int q,linenum;
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
//fwrite(shit,toRead,1,skt);
ParseSentences();
//dentro parsedsent ho la frase da reinserire e news+4 è la lunghezza

//comincio a ricreare il file
if (format == 0)
{
fwrite(head,(numSubFiles*0x10)+0x10,1,skt);
int off;
for (c=0;c<numSubFiles;c++)
{
if (c != DoNotIns)
{
subPoint[c]=ftell(skt);
fwrite(shit[c],subLen[c],1,skt);
while (ftell(skt) % 0x10 != 0)
{
fputc(0x00,skt);    
}    
}else{  
off=ftell(skt);          
fwrite(texthead,0x10+(num*4),1,skt);
for (i=0;i<num;i++)
{   
point[i]=ftell(skt)-PointField;
if (i != index)
{    
fwrite(buffer2[i],len[i],1,skt);
}else{
fwrite(buffer2[i],news+4,1,skt); 
len[i]=news+4;    
}
}
subLen[DoNotIns]=ftell(skt)-off; //prima salvo la lunghezza poi paddo
while (ftell(skt) % 0x10 != 0)
{
fputc(0x00,skt);    
} 
fseek(skt,PointField+0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,skt);
}
fseek(skt,0x00,SEEK_END);

}//else
}//for C

fseek(skt,0x00,SEEK_END);
/*for (c=0;c<0x10;c++)
{
fputc(0x00,skt); //add extra padding to the end of the file    
}*/
fseek(skt,0x10,SEEK_SET);
//ripunto
off=0;

for (c=0;c<numSubFiles;c++)
{
fwrite(&subLen[c],4,1,skt);
off=subLen[c];
while (off % 0x10 != 0)
{
off=off+1;    
} 
fwrite(&off,4,1,skt);
fwrite(&subPoint[c],4,1,skt);    
fseek(skt,4,SEEK_CUR);   
}
fclose(skt);            
//file ricreato con frase nuova e ripuntato
}else{ //format 1   
fwrite(texthead,0x10+(num*4),1,skt);
for (i=0;i<num;i++)
{   
point[i]=ftell(skt)-PointField;
if (i != index)
{    
fwrite(buffer2[i],len[i],1,skt);
}else{
fwrite(buffer2[i],news+4,1,skt); 
len[i]=news+4;   
}
}
fseek(skt,PointField+0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,skt);
}
fclose(skt);
}


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
void Tales_Of_Legendia_Text_EditorFrm::WxButton1Click(wxCommandEvent& event)
{

int q,linenum;
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
//fwrite(shit,toRead,1,skt);
ParseSentences();
//dentro parsedsent ho la frase da reinserire e news+4 è la lunghezza

//comincio a ricreare il file
if (format == 0)
{
fwrite(head,(numSubFiles*0x10)+0x10,1,skt);
int off;
for (c=0;c<numSubFiles;c++)
{
if (c != DoNotIns)
{
subPoint[c]=ftell(skt);
fwrite(shit[c],subLen[c],1,skt);
while (ftell(skt) % 0x10 != 0)
{
fputc(0x00,skt);    
}    
}else{  
off=ftell(skt);          
fwrite(texthead,0x10+(num*4),1,skt);
for (i=0;i<num;i++)
{   
point[i]=ftell(skt)-PointField;
if (i != index)
{    
fwrite(buffer2[i],len[i],1,skt);
}else{
fwrite(buffer2[i],news+4,1,skt); 
len[i]=news+4;     
}
}
subLen[DoNotIns]=ftell(skt)-off; //prima salvo la lunghezza poi paddo
while (ftell(skt) % 0x10 != 0)
{
fputc(0x00,skt);    
} 
fseek(skt,PointField+0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,skt);
}
fseek(skt,0x00,SEEK_END);

}//else
}//for C

fseek(skt,0x00,SEEK_END);
/*for (c=0;c<0x10;c++)
{
fputc(0x00,skt); //add extra padding to the end of the file    
}*/
fseek(skt,0x10,SEEK_SET);
//ripunto
off=0;
for (c=0;c<numSubFiles;c++)
{
fwrite(&subLen[c],4,1,skt);
off=subLen[c];
while (off % 0x10 != 0)
{
off=off+1;    
} 
fwrite(&off,4,1,skt);
fwrite(&subPoint[c],4,1,skt);    
fseek(skt,4,SEEK_CUR);   
}
fclose(skt);          
//file ricreato con frase nuova e ripuntato
}else{ //format 1   
fwrite(texthead,0x10+(num*4),1,skt);
for (i=0;i<num;i++)
{   
point[i]=ftell(skt)-PointField;
if (i != index)
{    
fwrite(buffer2[i],len[i],1,skt);
}else{
fwrite(buffer2[i],news+4,1,skt); 
len[i]=news+4; 
}
}
fseek(skt,PointField+0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,skt);
}
fclose(skt);
}
if (index != 0)
	{
        index--;
     }    else{
            index=num-1;    
        }
        
WxEdit1->SetValue(frase[index]); 
}




void Tales_Of_Legendia_Text_EditorFrm::WxEdit1Updated(wxCommandEvent& event)
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
/*FILE *txt;
int len2;
txt=fopen("test.dat","w+b");
len2=strlen(frase[index]);
fwrite(frase[index],len2,1,txt);*/
//fclose(txt);

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
buffer2[index][news]=byte;
news=news+1;
        
}
//gestion IF per i tag
if (frase[index][i] == 0x0A) //a capo
{
buffer2[index][news]=0x02;
news=news+1;     
buffer2[index][news]=0xD8;
news=news+1;       
}
if (frase[index][i] == 0x20) //spazio
{
buffer2[index][news]=0x00;
news=news+1;     
buffer2[index][news]=0x30;
news=news+1;       
}
if (frase[index][i] == 0x27) //apostrofo
{
buffer2[index][news]=0x19;
news=news+1;     
buffer2[index][news]=0x20;
news=news+1;       
}
if (frase[index][i] == 0x22) //virgolette
{
buffer2[index][news]=0x1D;
news=news+1;    
buffer2[index][news]=0x20;
news=news+1;       
} 
      
if (lol == news)
{
buffer2[index][news]=frase[index][i]-0x20;
buffer2[index][news+1]=0xFF;
news=news+2;     
}


}//for
buffer2[index][news]= 0x00;
buffer2[index][news+1]= 0xD9;
buffer2[index][news+2]= 0x00;
buffer2[index][news+3]= 0x00;

//fwrite(parsedsent,news+4,1,txt);
//fclose(txt);

}  //func






/*
 * About
 */
void Tales_Of_Legendia_Text_EditorFrm::About(wxCommandEvent& event)
{
	wxMessageBox("Tales Of Legendia Text Editor v0.81 by Vash\n               www.romhacking.it");
}
