  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  //  		    Tool for Open and Save Dialog

#include <dir.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

#include <dir.h>
#include <dos.h>

#include "DgnTool.h"
#include "mouse.h"

	       // File    Dialog   Box
UCHAR* File_Dialog(int x,int y,int attrib,char *Title,char *Name1,char *Sam,UCHAR *Exe)
{
  FRAME Save_Dialog;
  TEXTBOX Text1,Text2;
  LISTBOX List1,List2;
  BUTTON  But1,But2;
  BOOL    Thread_Flag = TRUE;
  char old_dir[MAXDIR];
  char new_dir[MAXDIR];
  UCHAR Name[70];
  BOOL BF1;
  char AttribName[20],AttribTitle[20];
  char buffer[MAXPATH];
  char str1[30];
  char ch;
  int MaxX,MaxY,Indx=-1;
  struct ffblk ffblk;
  int done;
  if(attrib==0)
   { strcpy(AttribName,"Open");
     strcpy(AttribTitle,"Open Dialog");}
     else
  if(attrib==1)
   { strcpy(AttribName,"Save");
     strcpy(AttribTitle,"Save Dialog");}
   else
   { strcpy(AttribName,Name1);
     strcpy(AttribTitle,Title);}
  hideMouse();
  Save_Dialog=Frame_Window(x,y,x+Dialog_Width,y+Dialog_Height,AttribTitle);
  MaxX=getMaxx();
  MaxY=getMaxy();
  List1=ListBox(4,25,(MaxX/2)-4,((MaxY/3)*2)+17,"Directories:");
  List2=ListBox((MaxX/2)+1,25,MaxX-2,((MaxY/3)*2)+17,"Files:");

  Label(4,((MaxY/3)*2)+22,"FileName:");
  Label(4,((MaxY/3)*2)+47,"FileExt:");

  Text1=TextBox(95,((MaxY/3)*2)+25,"",165);
  Text2=TextBox(95,((MaxY/3)*2)+50,"",165);

  But1=Button(MaxX-70,((MaxY/3)*2)+24,(MaxX-70)+BUTTON_WIDTH,(((MaxY/3)*2)+24)+BUTTON_HEIGHT,AttribName);
  But2=Button(MaxX-70,(((MaxY/3)*2)+29)+BUTTON_HEIGHT,(MaxX-70)+BUTTON_WIDTH,(((MaxY/3)*2)+29)+BUTTON_HEIGHT*2,"Cancel");
  getcwd(buffer,MAXPATH);
  if (getcwd(old_dir,MAXPATH)==NULL)
  {  MsgBox("Directory Error",0);
     Thread_Flag = FALSE;
  }
  strcpy(str1,buffer);
  strcat(str1,"\\*");
  Text1=setText(Text1,Sam);
  done = findfirst(str1,&ffblk,FA_DIREC);
  while (!done)
  {
    List1=addList(List1,ffblk.ff_name);
    done = findnext(&ffblk);
  }
  Text2=setText(Text2,Exe);
  done = findfirst(Exe,&ffblk,0);
   strcpy(Name,NULL);
   while (!done)
  {
    List2=addList(List2,ffblk.ff_name);
    done = findnext(&ffblk);
  }
  showMouse();
  while(Thread_Flag)
  {
      if(kbhit())
	 ch = getch();
	 if(getToggle()==TRUE && (ch ==TAB_KEY || ch == ESC_KEY))
	 {
	   Indx++; ch=0;
	   if(Indx>=6)Indx=0;
	   if(List1.tabIndex==Indx)
	   {
	     List1.Bool= ShowFocus(Save_Dialog,List1.fx,List1.fy,100);
	      while(List1.Bool!=TRUE)
	      {
		if(kbhit())
		{
		  List1=clearList(List1);
		  getcwd(buffer,MAXPATH);
		  strcpy(str1,NULL);
		  strcpy(str1,buffer);
		  strcat(str1,"\\*");
		  done = findfirst(str1,&ffblk,FA_DIREC);
		  while (!done)
		  {
		    List1=addList(List1,ffblk.ff_name);
		    done = findnext(&ffblk);
		  }
		  done = findfirst(Text2.getText,&ffblk,0);
		  List2=clearList(List2);
		  while (!done)
		  {
		    List2=addList(List2,ffblk.ff_name);
		    done = findnext(&ffblk);
		  }
		  List1=ActionList(List1);

		    if(chdir(List1.getText))
		     { }
		     else
		     {
		     getcwd(buffer,MAXPATH);
		     List1=clearList(List1);
		     done = findfirst("*",&ffblk,FA_DIREC);
		     while (!done)
		     {
		      List1=addList(List1,ffblk.ff_name);
		      done = findnext(&ffblk);
		     }
		     List2=clearList(List2);
		     done = findfirst(Text2.getText,&ffblk,0);
		     while (!done)
		     {
		      List2=addList(List2,ffblk.ff_name);
		      done = findnext(&ffblk);
		     }
		   }   }
		 }
		}
	       else
	       if(List2.tabIndex==Indx)
	       {
		  List2.Bool=ShowFocus(Save_Dialog,List2.fx,List2.fy,100);
		  while(List2.Bool!=TRUE)
		  {
		   if(kbhit())
		   {
		     List2=ActionList(List2);
		    if(strcmp(List2.getText,NULL)!=0)
		       Text1=setText(Text1,List2.getText);
		    }
		   }
		}
	       else
	       if(Text1.tabIndex==Indx)
		{
		    Text2.Bool=FALSE;
		    ActionText(&Text1);
		}
	      else
	       if(Text2.tabIndex==Indx)
		{
		  Text2.Bool=FALSE;
		  while(Text2.Bool!=TRUE)
		  {
		      ActionText(&Text2);
		      if(Text2.Bool==FALSE)
		       {
			List2=clearList(List2);
			done = findfirst(Text2.getText,&ffblk,0);
			 while (!done)
			 {
			  List2=addList(List2,ffblk.ff_name);
			  done = findnext(&ffblk);
			 }
			}
		 }
	       }
		else
	       if(But1.tabIndex==Indx)
		{
		  But1.Bool=ShowFocus(Save_Dialog,But1.fx+2,But1.fy+5,60);
		  BF1=Button_Action(But1);
		  if(BF1==TRUE)
		  {
		    strcpy(buffer,NULL);
		    strcpy(Name,NULL);
		    getcwd(buffer,MAXPATH);
		    strcat(buffer,"\\");
		    strcat(buffer,Text1.getText);
		    strcpy(Name,buffer);
		    Thread_Flag =FALSE;
		  }
		}
		else
		if(But2.tabIndex==Indx)
		{
		 But2.Bool=ShowFocus(Save_Dialog,But2.fx+2,But2.fy+5,60);
		 BF1=Button_Action(But2);
		 if(BF1==TRUE)
		   { Tab_Toggle=FALSE;strcpy(Name,NULL);
		    Thread_Flag =FALSE;
		   }
		}
	}
       else
       if(getToggle()==FALSE)
	 Thread_Flag =FALSE;
	if(ListBox_Click(&List1))
	{
	     List1.Bool= ShowFocus(Save_Dialog,List1.fx,List1.fy,100);
	     List1=clearList(List1);
	     getcwd(buffer,MAXPATH);
	     strcpy(str1,NULL);
	     strcpy(str1,buffer);
	     strcat(str1,"\\*");
	     done = findfirst(str1,&ffblk,FA_DIREC);
	     while (!done)
	     {
	       List1=addList(List1,ffblk.ff_name);
	       done = findnext(&ffblk);
	     }
	     done = findfirst(Text2.getText,&ffblk,0);
	     List2=clearList(List2);
	     while (!done)
	     {
		List2=addList(List2,ffblk.ff_name);
		done = findnext(&ffblk);
	     }
	       List1=ActionList(List1);
	      if(chdir(List1.getText))
	      { }
	       else
	      {
		 getcwd(buffer,MAXPATH);
		 List1=clearList(List1);
		 done = findfirst("*",&ffblk,FA_DIREC);
		 while (!done)
		 {
		    List1=addList(List1,ffblk.ff_name);
		    done = findnext(&ffblk);
		 }
		   List2=clearList(List2);
		   done = findfirst(Text2.getText,&ffblk,0);
		   while (!done)
		   {
		     List2=addList(List2,ffblk.ff_name);
		     done = findnext(&ffblk);
		   }
	   }
	}
	else
	if(ListBox_Click(&List2))
	{
	  List2.Bool=ShowFocus(Save_Dialog,List2.fx,List2.fy,100);
	   List2=ActionList(List2);
	    if(strcmp(List2.getText,NULL)!=0)
	     Text1=setText(Text1,List2.getText);
	}
	else
	if(TextBox_Click(&Text1)){
	   Text2.Bool=FALSE;
	   ActionText(&Text1);
	}else
	if(TextBox_Click(&Text2)){
	    Text2.Bool=FALSE;
	     while(Text2.Bool!=TRUE)
	     {
		 ActionText(&Text2);
		 if(Text2.Bool==FALSE)
		  {
		List2=clearList(List2);
		done = findfirst(Text2.getText,&ffblk,0);
		 while (!done)
		 {
		  List2=addList(List2,ffblk.ff_name);
		  done = findnext(&ffblk);
		 }
	      }
	   }
	}else
	 if(ButtonPress(&But1)) {
	    strcpy(buffer,NULL);
	    strcpy(Name,NULL);
	    getcwd(buffer,MAXPATH);
	    strcat(buffer,"\\");
	    strcat(buffer,Text1.getText);
	    strcpy(Name,buffer);
	    Thread_Flag =FALSE;
	 }
	 else
	 if(ButtonChk(&But1))
	   ButtonHlight(&But1);
	 else
	 if(ButtonPress(&But2)) {
	   Tab_Toggle=FALSE;strcpy(Name,NULL);
	    Thread_Flag =FALSE;
	 }
	 else
	 if(ButtonChk(&But2))
	   ButtonHlight(&But2);
	 else
	 if(CloseWindow(&Save_Dialog)) {
	   Tab_Toggle=FALSE;strcpy(Name,NULL);
	   Thread_Flag =FALSE;
	 }
	 else
	 if(WinClose(&Save_Dialog))
	    Close_Hlight(&Save_Dialog);
  }
  if (chdir(old_dir))
   { Focus.Bool=FALSE;
     strcat(old_dir,"Cannot change the Orig Directory");
     MsgBox(old_dir,0);}
  Focus.Bool=FALSE;
  CLOSE_FRAME(&Save_Dialog);
  return Name;
}
