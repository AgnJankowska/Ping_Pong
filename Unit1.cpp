//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int x=5;
int y=-5;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_ballTimer(TObject *Sender)
{
  Ball -> Left += x;
  Ball -> Top += y;

  //odbij od górnej œciany
  if(Ball->Top-5 <= Game_background->Top) y = -y;

  //odbij od dolnej œciany
  if(Ball->Top - Game_background->Height + Ball->Height +5 >= Game_background->Top) y = -y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle1_upTimer(TObject *Sender)
{
        if(Paddle1->Top - 5 > 10)
        Paddle1->Top -= 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle1_downTimer(TObject *Sender)
{
        if(Paddle1->Top + Paddle1->Height < Game_background->Height)
        Paddle1->Top += 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle2_upTimer(TObject *Sender)
{
        if(Paddle2->Top - 5 > 10)
        Paddle2->Top -= 5;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle2_downTimer(TObject *Sender)
{
        if(Paddle2->Top + Paddle2->Height < Game_background->Height)
        Paddle2->Top += 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if(Key == VK_UP)     Timer_Paddle1_up->Enabled = true;
   if(Key == VK_DOWN)   Timer_Paddle1_down->Enabled = true;
   if((Key == 'a')||(Key == 'A'))       Timer_Paddle2_up->Enabled = true;
   if((Key == 'z')||(Key == 'Z'))       Timer_Paddle2_down->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if(Key == VK_UP)     Timer_Paddle1_up->Enabled = false;
   if(Key == VK_DOWN)   Timer_Paddle1_down->Enabled = false;
   if((Key == 'a')||(Key == 'A'))       Timer_Paddle2_up->Enabled = false;
   if((Key == 'z')||(Key == 'Z'))       Timer_Paddle2_down->Enabled = false;
}
//---------------------------------------------------------------------------

