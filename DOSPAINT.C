  /*****************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  // 		         Main Program
#include <alloc.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <graphics.h>

#include "Wiredefs.h"
#include "DgnTool.h"
#include "mouse.h"
#include "Sub_Dlog.h"
#include "Paint.h"
#include "LoadImg.h"

#define TEMPFILE "temp.rec"

 BOOL CompareMenu(MENU *m1,UCHAR* str);
 int NUM_MENU;
 void Main_Window(char*);
 void setTrue(void);
 WINDOW_FRAME TITLE1;
 int MaxX,MaxY;
 int MenuIndex=0;
 const char File[50];
 const char dFile[50];
 const char TFile[50];

 MENU menu[8];
 MOUSE_COOR EXit;
 MOUSE_COOR Min;
 FRAME Edit;
 BOOL ret;
 EDIT Edit_Paint;
 BOOL Msg;
void main()
{
 int gd=VGA,gm=0x2,i,errorcode;
 UCHAR str[100];
 FRAME f1;
 UCHAR *File_Menu[]={"New","Open Paint","Open","-","Save","Save As","Close","-","Exit"};
 UCHAR *Edit_Menu[]={"Undo","Redo","-","Cut","Copy","Paste","-","Login"};
 UCHAR *View_Menu[]={"Tool Bar","StatusBar","-","Measurement","Pixels","-","Full Screen"};
 UCHAR *Image_Menu[]={"Flip Horizontal","Flip Vertical","-","Clear Image","-","Insert Text","-","Font","Edit Colors"};
 UCHAR *Help_Menu[]={"About Software","Index","-","About me"};

 int MENU_ACTIVE[9]={TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE,TRUE,TRUE};
 int MENU_EDIT_ACTIVE[8]={FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,TRUE,TRUE};
 int MENU_VIEW_ACTIVE[8]={TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE};
 int MENU_IMAGE_ACTIVE[9]={TRUE,TRUE,FALSE,TRUE,FALSE,TRUE,TRUE,TRUE,TRUE};

  errorcode = registerfarbgidriver(EGAVGA_driver_far);
  errorcode = registerfarbgifont(triplex_font_far);
  errorcode = registerfarbgifont(small_font_far);
  errorcode = registerfarbgifont(sansserif_font_far);
  errorcode = registerfarbgifont(gothic_font_far);
  if (errorcode < 0)
  {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);
  }

 initgraph(&gd,&gm,NULL);
 errorcode = graphresult();
 if (errorcode != grOk)
 {
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
 }
 InitStatus();
 Msg=TRUE;
 MaxX=getmaxx()/4;
 MaxY=getmaxy()/4;
 About(DELAY);
 Main_Window("Ready");
 showMouse();
 menu[0]=menuHead(10,22,"File");
 menu[1]=menuHead(50,22,"Edit");
 menu[2]=menuHead(95,22,"View");
 menu[3]=menuHead(140,22,"Image");
 menu[4]=menuHead(200,22,"Help");
 menu[5]=menuHead(250,22,"Exit");

 for(i=0;i<9;i++)
   menu[0]=addItem(menu[0],File_Menu[i],MENU_ACTIVE[i]);
 for(i=0;i<8;i++)
   menu[1]=addItem(menu[1],Edit_Menu[i],MENU_EDIT_ACTIVE[i]);
 for(i=0;i<7;i++)
   menu[2]=addItem(menu[2],View_Menu[i],MENU_VIEW_ACTIVE[i]);
 for(i=0;i<9;i++)
   menu[3]=addItem(menu[3],Image_Menu[i],MENU_IMAGE_ACTIVE[i]);
 for(i=0;i<4;i++)
   menu[4]=addItem(menu[4],Help_Menu[i],TRUE);
   menu[5]=addItem(menu[5],"Exit",TRUE);

  if(Login(160,130))
    menuAction();
 else
    Exit();
}

void Exit()
{
 hideMouse();
 free(s);
 free(legal);
 closegraph();
 exit(1);
}

void Main_Window(char *txt)
{
 struct date d;
 char d1[10],d2[10],d3[10];
 getdate(&d);
 MaxX=getmaxx();
 MaxY=getmaxy();
 TITLE1.x=0;
 TITLE1.y=0;
 TITLE1.x1=MaxX-5;
 TITLE1.y1=MaxY-5;
 INIT_Window(TITLE1.x,TITLE1.y,TITLE1.x1,TITLE1.y1,"Dos Paint : Developed By Ratheesh");
 Internal_Menu_Window(TITLE1.x+3,TITLE1.y+TITLE_HEIGHT+20,TITLE1.x1-2,TITLE1.y1-Status_Bar_Height-1);
 itoa(d.da_day,d1,10);
 itoa(d.da_mon,d2,10);
 itoa(d.da_year,d3,10);
 strcat(d1,"/");
 strcat(d1,d2);
 strcat(d1,"/");
 strcat(d1,d3);
 Status_Bar(txt,d1);
 Window_Button(TITLE.x1-20,TITLE.y+4,TITLE.x1-6,TITLE.y+17,TRUE,"X");
 Window_Button(TITLE.x1-40,TITLE.y+4,TITLE.x1-25,TITLE.y+17,TRUE,"-");
 EXit=WINDOW_CLOSE_ACTIVATE();
 Min=WINDOW_MIN_ACTIVATE();
}


void menuAction()
{
    int i;
    char ch,str[3];
    char KEY;
    BOOL Save_Paint = FALSE;
    BOOL Open_Paint = FALSE;
    BOOL New_Paint  = FALSE;
    CCHAR Save_File[100];
    CCHAR SFileName1[50],SFileName2[50],DFileName[50];
    FRAME Paint_Edit;
    TR_PAINT Paint;
    MENU_POSTION M;
    M.EFLAG=TRUE;
    strcpy(DFileName,NULL);
    showMouse();
    NUM_MENU = 6;
	while(TRUE)
	{
	      if(kbhit())
		 KEY=getch();
		Mouse=mouseStatus();
		  if((Mouse.x > Paint_Edit.x && Mouse.y > Paint_Edit.y) && menu[0].Active[6] == TRUE)
		      if(Mouse.Button == 1)
			 if(TRPaint_Action(&Paint,&Edit_Paint))
			   if(MsgBox("Are you sure you want Close",2)==5) {
			      CLOSE_EDIT_FRAME(&Paint_Edit);
			      menu[0].Active[6]=FALSE;}
		if(Mouse.Button==1 || KEY == ALT_F )
		{
		 for(i=0;i<NUM_MENU;i++)
		  if(MouseOn(&menu[i])|| KEY == ALT_F )
		    {
		      do
		      {
			M.EFLAG=TRUE;
			M.Bool=TRUE;
			M=showMenu(menu[i]);
			  if(M.Bool==FALSE)
			  {   if(M.Flag==TRUE)
			      { i++;if(i==NUM_MENU)i=0;}
			     else
			     if(M.Flag==FALSE)
			      { i--;if(i==-1)i=NUM_MENU-1;}
			  }
			  else
			  break;
		       }while(M.Bool==FALSE);

			if(CompareMenu(&menu[i],"File"))
			 {
			     switch(M.MENU_INDEX)
			     {
			       case 1:
			       if(menu[i].Active[6]==FALSE || MsgBox("Are you sure you want Close",2)==5) {
				   if(menu[i].Active[6]==TRUE)
				      CLOSE_EDIT_FRAME(&Paint_Edit);
				  setTrue();
				  Paint_Edit=Paint_Editor("Noname.bmp");
				  New_Paint = TRUE;
				  Save_Paint=FALSE;
				  Open_Paint=FALSE;
				  Paint=draw_Editor(&Paint_Edit);
				  TRPaint_Action(&Paint,&Edit_Paint);
				 }
			       break;
			       case 2:
				if(menu[0].Active[6]==TRUE && New_Paint==TRUE) {
				       if(MsgBox("Save Changes to NoName..",2)==5) {
					   strcpy((char*)Save_File,NULL);
					   strcat((char*)Save_File,File_Dialog(130,100,SAVE_DIALOG,"","","Sam.bmp","*.Bmp"));
					   if(Save_BMP(&Paint,(char*)&Save_File))
					     MsgBox("File has been Saved Succesfully",0);
					   else
					     MsgBox("Cannot Save File or SupImg.Dat File Not Found",0);
				       }
				 strcpy((char*)File,NULL);
				 strcat((char*)File,File_Dialog(130,100,OPEN_DIALOG,"","","","*.Bmp"));
				 if(getToggle()!=FALSE) {
				      if(Open_BMP(&Paint,File))
					  MsgBox("Cannot Open File or File Not Found",0);
				      else {New_Paint = FALSE; Save_Paint =TRUE; Open_Paint=TRUE;
				      setTrue();
				      menu[0].Active[6]=TRUE;
				      strcpy((char*)TFile,(char*)File);
				      strcpy((char*)Save_File,(char*)File);
				     }
				  }
				}else
				if(menu[0].Active[6]==TRUE && (Save_Paint==TRUE || Open_Paint == TRUE)) {
				       if(MsgBox("Any Save Changes to ..",2)==5) {
					   if(Save_BMP(&Paint,(char*)&Save_File)){}
					   else
					     MsgBox("Cannot Save File or SupImg.Dat File Not Found",0);
				       }
				 strcpy((char*)File,NULL);
				 strcat((char*)File,File_Dialog(130,100,OPEN_DIALOG,"","","","*.Bmp"));
				 if(getToggle()!=FALSE) {
				      if(Open_BMP(&Paint,File))
					  MsgBox("Cannot Open File or File Not Found",0);
				      else { New_Paint = FALSE; Save_Paint=TRUE;Open_Paint=TRUE;
				      setTrue();
				     strcpy((char*)TFile,(char*)File);
				     strcpy((char*)Save_File,(char*)File);
				     }
				  }
				} else
				if(menu[0].Active[6]==FALSE) {
				   strcpy((char*)File,NULL);
				   strcat((char*)File,File_Dialog(130,100,OPEN_DIALOG,"","","","*.Bmp"));
				   if(getToggle()!=FALSE) {
				   Paint_Edit=Paint_Editor((char*)File);
				   Paint=draw_Editor(&Paint_Edit);
				   setTrue();
					if(Open_BMP(&Paint,File))
					     MsgBox("Cannot Open File or File Not Found",0);
					else {Open_Paint = TRUE;  New_Paint=FALSE ; Save_Paint=TRUE;
					strcpy((char*)Save_File,(char*)File);
					strcpy((char*)TFile,(char*)File);
					}
				    }
				}
			       break;
			       case 3:
			       if(menu[0].Active[6]==TRUE) {
				  if(MsgBox("Are you sure you want Close",2)==5){
				     CLOSE_EDIT_FRAME(&Paint_Edit);
				     menu[0].Active[6]=FALSE;
				     strcpy((char*)File,NULL);
				     strcat((char*)File,File_Dialog(130,100,OPEN_DIALOG,"","","Sam.bmp","*.Bmp"));
				     if(getToggle()!=FALSE)
				     {
				       if(Load_BMP(0,0,(char*)&File))
					{ Main_Window((char*)File);
					 REMake_Menu_Head(menu,6);
					 showMouse();
					 strcpy((char*)TFile,(char*)File);}
				      }
				   }
				}else{
				 strcpy((char*)File,NULL);
				 strcat((char*)File,File_Dialog(130,100,OPEN_DIALOG,"","","Sam.bmp","*.Bmp"));
				 if(getToggle()!=FALSE)
				  {
				      if(Load_BMP(0,0,(char*)&File))
				       { Main_Window((char*)File);
					 REMake_Menu_Head(menu,6);
					 showMouse();
					 menu[i].Active[5]=TRUE;
					 strcpy((char*)TFile,(char*)File);}
				   }
				 }
			       break;
			       case 4:
			       if(menu[0].Active[6]==TRUE && New_Paint==TRUE) {
				 strcpy((char*)File,NULL);
				 strcpy((char*)&File,File_Dialog(130,100,SAVE_DIALOG,"","","Sam.bmp","*.Bmp"));
				 if(getToggle()!=FALSE)
				    if(strcmp(File,NULL)!=0)  {
				       if(Save_BMP(&Paint,(char*)&File)) {
					  MsgBox("File has been Saved Succesfully",0);New_Paint=FALSE; Save_Paint=TRUE; Open_Paint=TRUE;
					  strcpy((char*)TFile,(char*)File);
					  strcpy((char*)Save_File,(char*)File);
					  }
					else
					  MsgBox("Cannot Save File or SupImg.Dat File Not Found",0);
				    }
				} else
				if(menu[0].Active[6]==TRUE && Save_Paint==TRUE) {
				 if(getToggle()!=FALSE)
				    if(strcmp(Save_File,NULL)!=0)  {
				       if(Save_BMP(&Paint,(char*)&Save_File)) {
					  MsgBox("File has been Saved Succesfully",0);New_Paint=FALSE; Save_Paint=TRUE; Open_Paint=TRUE;
					  strcpy((char*)TFile,(char*)Save_File);
					  }
					else
					  MsgBox("Cannot Save File or SupImg.Dat File Not Found",0);
				    }
				}
			       break;
			       case 5:
				 strcpy((char*)dFile,NULL);
				 strcpy((char*)dFile,File_Dialog(130,100,3,"Save as Dialog:","Save","","*.bmp"));
				 if(getToggle()!=FALSE)
				    if(strcmp(File,NULL)!=0)
				      { fileCopy((char*)&dFile,(char*)&File);
					strcpy((char*)TFile,(char*)dFile);}
			       break;
			       case 6:
			       if(menu[0].Active[6]==TRUE)
				   if(MsgBox("Are you sure you want Close",2)==5){
				      CLOSE_EDIT_FRAME(&Paint_Edit);
				      menu[0].Active[6]=FALSE;
				   }
			       break;
			       case 7:
				  if(menu[0].Active[6]==TRUE) {
				      if(MsgBox("Are you sure you want Close the Paint",2)==5){
					   CLOSE_EDIT_FRAME(&Paint_Edit);
					   Exit();
					   }
				   }else
				if(MsgBox("Are you sure you want Exit",2)==5)
				    Exit();
				break;
			     }
			    M.MENU_INDEX=-1;
			 }
			else
			if(CompareMenu(&menu[i],"Edit"))
			 {
			     switch(M.MENU_INDEX)
			     {
			       case 1:
				 MsgBox("Memory is Not Enough: Error 1201",0);
			       break;
			       case 2:
				 MsgBox("Memory is Not Enough: Error 1202",0);
			       break;
			       case 3:
				if(menu[0].Active[6] == TRUE) {
				   Edit_Paint.Cut=TRUE;
				   TRPaint_Action(&Paint,&Edit_Paint);}
			       else
				  MsgBox("Select the Image",0);
			       break;
			       case 4:
				if(menu[0].Active[6] == TRUE) {
				   Edit_Paint.Copy=TRUE;
				   TRPaint_Action(&Paint,&Edit_Paint);}
			       else
				  MsgBox("Select the Image",0);
			       break;
			       case 5:
			       if(Edit_Paint.Cut==TRUE || Edit_Paint.Copy==TRUE || Edit_Paint.Paste == TRUE)
			       { Edit_Paint.Paste=TRUE;
				 if(menu[0].Active[6] == TRUE)
				   TRPaint_Action(&Paint,&Edit_Paint);
				 else
				   MsgBox("Copy or Cut the Image",0);
			       }
				 else
				   MsgBox("Copy or Cut the Image",0);
				 break;
			       case 6:
				 Login(160,130);
			       break;
			       }
			    M.MENU_INDEX=-1;
			 }
			 else
			 if(CompareMenu(&menu[i],"View"))
			 {
			     switch(M.MENU_INDEX)
			     {
			       case 1:
				MsgBox("Not Found",0);
			       break;
			       case 2:
				MsgBox("Not Found",0);
			       break;
			       case 3:
				MsgBox("Not Found",0);
			       break;
			       case 4:
				MsgBox("Pixels : 300 x 400",0);
			       break;
			       case 5:
			       if(menu[0].Active[6]==TRUE) {
				  if(MsgBox("Are you sure you want Close",2)==5){
				     CLOSE_EDIT_FRAME(&Paint_Edit);
				     menu[0].Active[6]=FALSE;
				    if(Load_BMP(0,0,(char*)&TFile)) {
				       Main_Window((char*)TFile);
				       REMake_Menu_Head(menu,6);
				       showMouse();}
				  }
				}else{
				if(Load_BMP(0,0,(char*)&TFile)) {
				   Main_Window((char*)TFile);
				   REMake_Menu_Head(menu,6);
				   showMouse();
				 }
			      }
			       break;
			   }
			    M.MENU_INDEX=-1;
			 }
			 else
			 if(CompareMenu(&menu[i],"Image"))
			 {
			     switch(M.MENU_INDEX)
			     {
			       case 1:
				MsgBox("Not Found",0);
			       break;
			       case 2:
				MsgBox("Not Found",0);
			       break;
			       case 3:
			       if(menu[0].Active[6]==TRUE)
				 if(MsgBox("Are you sure you want Clear Image",2)==5)
				    clearEditor(Paint.fx,Paint.fy,Paint.x1,Paint.y1);
			       break;
			       case 4:
			       if(menu[0].Active[6]==TRUE) {
				 Edit_Paint.Text = TRUE;
				 Edit_Paint.TextIndex = 9;
			       }
			       break;
			       case 5:
				 setFontStyle(Text_Font(130,130));
			       break;
			       case 6:
				 setFColor(Text_Color(130,130));
			       break;
			      }
			    M.MENU_INDEX=-1;
			 }
			 else
			 if(CompareMenu(&menu[i],"Help"))
			  {
			     switch(M.MENU_INDEX)
			     {
			       case 1:
				 MsgBox("Help Not Found",0);
			       break;
			       case 2:
				 MsgBox("Index Not Found",0);
			       break;
			       case 3:
			       About(WAIT);
			       break;
			     }
			 }
			 else
			 if(CompareMenu(&menu[i],"Exit"))
			  {
			     switch(M.MENU_INDEX)
			     {
			       case 1:
			       if(menu[0].Active[6]==TRUE) {
				   Msg=MsgBox("Are you sure you want Close",2);
				   if(Msg==5){
				       CLOSE_EDIT_FRAME(&Paint_Edit);
				       menu[0].Active[6]=FALSE;
				       Msg=TRUE;
				    }else Msg=FALSE;
				 }
			    if(Msg==TRUE)
			       if(MsgBox("Are you sure you want Exit",2)==5)
				    Exit();
			      Msg=TRUE;
			       break;
			     }
			}
		      KEY=0;
		     showMouse();
		    }
		   else
		   if(WindowEx(&EXit)&& M.EFLAG!=TRUE)
			if(MsgBox("Are you sure you want Exit",2)==5)
			    Exit();
		   else
		   if(WindowEx(&Min) && M.EFLAG!=TRUE)
		    {}
		    M.EFLAG=FALSE;
		}
		else
		{
		     for(i=0;i<8;i++)
		       if(MouseOn(&menu[i])) menuHlight(&menu[i]);
		       if(WindowEx(&EXit)) EXit_Hlight(&EXit);
		       if(WindowEx(&Min)) EXit_Hlight(&Min);

		}
	}
}

void setTrue(void)
{
       menu[1].Active[0]=TRUE;
       menu[1].Active[1]=TRUE;
       menu[1].Active[3]=TRUE;
       menu[1].Active[4]=TRUE;
       menu[1].Active[5]=TRUE;
       menu[0].Active[4]=TRUE;
       menu[0].Active[6]=TRUE;
       menu[0].Active[5]=TRUE;
}
int MouseOn(MENU *t)
{
 int flag=0;
 if(Mouse.x>=t->MTx && Mouse.x<=t->MTW && Mouse.y>=t->MTy && Mouse.y<=t->MTH) flag=1;
 return flag;
}

BOOL CompareMenu(MENU *m1,UCHAR* str)
{
  BOOL flag=FALSE;
  if(strcmp(m1->menuTitle,str)==0)
  flag=TRUE;
return flag;
}
