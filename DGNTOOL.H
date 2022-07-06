  /*****************************************************************/
  //		    TR_WordPad :-         Version 2.0
  //	      Developed By
  //			 N.C.C.T
  //			 #109, 2nd Floor
  //			 N.H- ROAD
  //			 CHENNAI - 600034
  //        Programmed By
  //			 T.R.Ratheesh
  //                     tr.ratheesh@gmail.com
  /*****************************************************************/

#ifndef  _DGNTOOL_H
#include "WireDefs.h"

#define   CLIP_ON          TRUE
#define   CLIP_OFF         FALSE
#define   TITLE_HEIGHT      (20)
#define   TITLE_FONT        SANS_SERIF_FONT
#define   TITLE_FONT_SIZE   (1)
#define   Status_Bar_Height (20)
#define   STATUS_FONT       DEFAULT_FONT
#define   STATUS_FONT_SIZE  (1)
#define   TEXTBOX_FONT      DEFAULT_FONT
#define   TEXTBOX_FONT_SIZE (1)
#define   LABEL_FONT        TRIPLEX_FONT
#define   LABEL_FONT_SIZE   (1)
#define   MEM_BLOCKS        (15)
#define   MENU_BLOCKS       (15)
#define   TEXT_SIZE         (20)
#define   Dialog_Width     (340)
#define   Dialog_Height    (230)
#define   BUTTON_WIDTH      (65)
#define   BUTTON_HEIGHT     (20)
#define   MENU_FONT          TRIPLEX_FONT//SANS_SERIF_FONT
#define   MENU_FONT_SIZE     1
#define   OPEN_DIALOG        0
#define   SAVE_DIALOG        1
#define   EDIT_MEM           5
#define   MAXFILEMEM       100
#define   PROJECT_TITLE    "Dos Paint"

#define   BITSPERSECONDS  2400
#define   DATABITS           8
#define   STOPBITS           1
void Internal_Menu_Window(int,int,int,int);
void Internal_Frame(int,int,int,int);
void Frame(int,int,int,int);

extern char    *s;
extern char    *legal;
extern UINT16  MWidth;

typedef struct{
       int x;
       int y;
       int x1;
       int y1;
       UINT16 Wx;
       UINT16 Wy;
       UINT16 Wx1;
       UINT16 Wy1;
       UCHAR str[50];
       BOOL CLOSE;
}WINDOW_FRAME;

typedef struct{
       int x;
       int y;
       int x1;
       int y1;
       int Cx;
       int Cy;
       int Cx1;
       int Cy1;
       int Blocks[15][4];
       void far* WIN_MEM[20];
}FRAME;

typedef struct{
   unsigned int MENU_INDEX;
   int Key_Index;
   int RIGHT;
   int LEFT;
   BOOL Flag;
   BOOL Bool;
   BOOL EFLAG;
}MENU_POSTION;

extern WINDOW_FRAME TITLE;
extern int Index;
extern BOOL Tab_Toggle;

BOOL getToggle(void);
void Frame_Title(UCHAR *);
FRAME Frame_Window(int,int,int,int,UCHAR *);
FRAME Message_Frame(int x,int y,int x1,int y1,UCHAR *text);
void Normal_Frame_Title(UCHAR *text);
void Normal_Frame(int x,int y,int x1,int y1);
void Hlight_Frame(int,int,int,int);
void CLOSE_FRAME(FRAME *CLOSE);
void CLOSE_WINDOW(WINDOW_FRAME);
void INIT_Window(int x,int y,int x1,int y1,UCHAR *text);
void Status_Bar(UCHAR* Status,UCHAR *DATE_TIME);
void Internal_Text_Frame(int x,int y,int x1,int y1,UCHAR *text);
void Window_Button(int,int,int,int,BOOL,UCHAR *);

typedef struct{
  UINT16 Sx;
  UINT16 Sy;
  UINT16 Ex;
  UINT16 Ey;
}MOUSE_COOR;

MOUSE_COOR WINDOW_CLOSE_ACTIVATE(void);
MOUSE_COOR WINDOW_MIN_ACTIVATE(void);
int WindowEx(MOUSE_COOR *t);

UCHAR* File_Dialog(int,int,int,char*,char*,char*,UCHAR* Exe);
void Label(int x,int y,const char *txt);

typedef struct {
    int tx;
    int ty;
    int tx1;
    int ty1;
    int fx;
    int fy;
    int tabIndex;
    BOOL Bool;
    UINT16 Size;
    UCHAR getText[30];
}TEXTBOX;

TEXTBOX ActionPWText(TEXTBOX t1);
TEXTBOX TextBox(int,int,UCHAR *,UINT16);
TEXTBOX ActionText(TEXTBOX*);
TEXTBOX setText(TEXTBOX t1,UCHAR *txt);
void WORD_HIDE(TEXTBOX,int x,int y);
TEXTBOX clearText(TEXTBOX t1);
BOOL  TextBox_Click(TEXTBOX *t);

typedef struct{
  UINT16 cx;
  UINT16 cy;
}CURSOR;
void Load_Cursor(TEXTBOX,int x,int y);

typedef struct {
    int tx;
    int ty;
    int tx1;
    int ty1;
    int fx;
    int fy;
    int Width;
    int Count;
    int Maxx;
    int Maxy;
    int Cx;
    int Cy;
    int tabIndex;
    BOOL Bool;
    int listValue;
    UCHAR listText[50][50];
    UCHAR getText[50];
}LISTBOX;

LISTBOX ListBox(int,int,int,int,UCHAR*);
LISTBOX addList(LISTBOX l1,UCHAR* str);
LISTBOX clearList(LISTBOX t1);
LISTBOX ActionList(LISTBOX);
LISTBOX Load_Gra_Cursor(LISTBOX,int x,int y,int Width);
LISTBOX setList(LISTBOX t1,UCHAR* txt);
BOOL  ListBox_Click(LISTBOX *t);

typedef struct{
  int x;
  int y;
  int x1;
  int y1;
  int fx;
  int fy;
  int fx1;
  int fy1;
  int tabIndex;
  UCHAR getText[30];
  BOOL Bool;
}BUTTON;

BUTTON Button(int,int,int,int,UCHAR *);
BOOL Button_Action(BUTTON);
void Button_Push(BUTTON b1);
void ButtonHlight(BUTTON *t);
void Button_Release(BUTTON b1);
BOOL ButtonPress(BUTTON *t);
int ButtonChk(BUTTON *t);

BOOL MsgBox(UCHAR* str,int);
int getMaxx(void);
int getMaxy(void);
typedef struct{
   int x;
   int y;
   BOOL Bool;
}FOCUS;

extern FOCUS Focus;
void InitStatus(void);
BOOL ShowFocus(FRAME f1,int x,int y,int Size);
void HideFocus(int x,int y,int f);
typedef struct{
  int x;
  int y;
  int x1;
  int y1;
  int MWidth;
  int MHeight;
  int MTx;
  int MTy;
  int Wx;
  int Wy;
  int Wx1;
  int Wy1;
  int MTH;
  int MTW;
  int itemCount;
  int CLine;
  int Count;
  int Index[40];
  UCHAR Active[40];
  UCHAR menuTitle[40];
  UCHAR menuItem[40][40];
  int Blocks[16][4];
}MENU;

MENU menuHead(int,int,UCHAR *tit);
MENU addItem(MENU m1,UCHAR *str,BOOL Bool);
MENU_POSTION showMenu(MENU m1);
void menuAction(void);
void hideMenu(MENU m1);
void menuHlight(MENU *t);
void REMake_Menu_Head(MENU m1[],int Num);
void Internal_Menu_Window(int x,int y,int x1,int y1);
void Internal_Menu_Frame(int x,int y,int x1,int y1);

void Xorbar(int sx,int sy,int ex,int ey,int c);
int MouseOn(MENU *t);
MENU_POSTION HandleMenu(int n,MENU tm);
BOOL MouseOn1(int cx,int cy,int cx1,int cy1);
void CrossLine(int x,int y,int Width);
void EXit_Hlight(MOUSE_COOR *t);

// Editor

typedef struct{
   int x;
   int y;
   int x1;
   int y1;
}IN_FRAME;

IN_FRAME getIN(void);

typedef struct{
 int textStyle;
 int textSize;
 int textWidth;
 int textHeight;
 COLOR textColor;
 COLOR BKColor;
}TRWORD;

typedef struct{
  int x;
  int y;
  int x1;
  int y1;
  int Sx;
  int Ex;
  int LINE;
  int ENDLINE;
  int CPos;
  char Paste[EDITLEN];
  UCHAR Edit_Array[40][EDITLEN];
  int ROW_Flag[40];
  TRWORD TRWord[40];
}EDITOR;

FRAME Editor(char *filename);
FRAME Frame_EDIT_Window(int x,int y,int x1,int y1,UCHAR *text);
EDITOR drawEditor(FRAME *);
EDITOR editData(FRAME * f1);
void CLOSE_EDIT_FRAME(FRAME * CLOSE);
void ActionEdit(EDITOR *Edt);
void fileRead(EDITOR *Edt,FRAME *f1,const char *filename);

void Scroll(int x,int y,int Width,int Height,int Attrib);

typedef struct{
  int font;
  int direction;
  int charsize;
  int horiz;
  int vert;
}OLDTEXT;

typedef struct{
   int x;
   int y;
   int x1;
   int y1;
}WINDOW_PORT;
extern WINDOW_PORT Window;
extern OLDTEXT oldText;

void getOldTextStyle(void);
void setOldTextStyle(void);

void getOldWindowStyle(void);
void setOldWindowStyle(void);
void WriteFile(EDITOR Edt,const char *filename);
void fileCopy(const char *dfile,const char *Sfile);

BOOL Login(int x,int y);
void ProgressBar(int x,int y,char* txt);
void NewUser(int x,int y);
void PortSettings(int,int);
BOOL CloseWindow(FRAME *t);
void Close_Hlight(FRAME *t);
int  WinClose(FRAME *t);
BOOL Edit_Cut(EDITOR *t);
BOOL Edit_Copy(EDITOR *t);
void Edit_Paste(EDITOR *t);
void Exit(void);
void About(int attr);

void Port_Progress_Bar(FRAME*f1,int x,int y,char* txt);
void hideProgress(FRAME *f1);
BOOL setProgress(void);

typedef struct{
     COLOR FColor;
     COLOR BKColor;
     int textFont;
     int textSize;
}THEME;

THEME Text_Font(int x,int y);
THEME Text_Color(int x,int y);

void setFontStyle(THEME F_Style);
void setFColor(THEME F_Color);

void Port_Req_Progress_Bar(FRAME *f1,int x,int y,char* txt);
void Req_setProgress(void);
void hide_Req_Progress(FRAME *f1);

void clearEditor(int x,int y,int x1,int y1);

#define  _DGNTOOL_H
#endif
