//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
float x=5;
float y=5;
int amount_of_punches_1 = 0;
int amount_of_punches_2 = 0;
int amount_of_punches_record = 0;
int player1_wins = 0;
int player2_wins = 0;

bool is_game_active = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_ballTimer(TObject *Sender){
  if(is_game_active){
    Label3->Visible = false;
    Button1->Visible = false;
    Button2->Visible = false;

    Ball -> Left += x;
    Ball -> Top += y;

    //odbij od g�rnej �ciany
    if(Ball->Top <= Game_background->Top){
      sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC );
      y = -y;
    }

    //odbij od dolnej �ciany
    if(Ball->Top - Game_background->Height + Ball->Height >= Game_background->Top){
      sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC );
      y = -y;
    }

    //skucha 1 gracza
    if(Ball->Left < Paddle1->Left + Paddle1->Width/2){
      sndPlaySound ("Sounds/koniec.wav", SND_ASYNC);
      Timer_ball->Enabled = false;
      Timer_speed->Enabled = false;
      Ball->Visible= false;

      Label3->Visible = true;
      Label3->Font->Size = 18;
      Label3->Caption = "Punkt dla gracza nr 2";
      player2_wins++;

      Button1->Visible = true;
      Button1->Caption = "JESZCZE RAZ";
      Button2->Visible = true;
      Button2->Caption = "NOWA GRA";

      amount_of_punches_record = amount_of_punches_1 + amount_of_punches_2;
      if (StrToInt(Record_amount->Caption) < amount_of_punches_record)
      Record_amount->Caption = IntToStr(amount_of_punches_record);

      Score -> Caption = IntToStr(player1_wins) + " : " + IntToStr(player2_wins);
   }

    //odbicie 1 gracza
    else if ((Ball->Left <= Paddle1->Left + Paddle1->Width) &&
            (Ball->Top + Ball->Height/2 > Paddle1->Top) &&
            (Ball->Top - Ball->Height/2 < Paddle1->Top + Paddle1->Height)){
       sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC);
       x = -x;
       amount_of_punches_1++;
       Actual_amount -> Caption = amount_of_punches_1+amount_of_punches_2;
    }

    //skucha 2 gracza
    if(Ball->Left + Ball->Width > Paddle2->Left + Paddle2->Width){
       sndPlaySound ("Sounds/koniec.wav", SND_ASYNC);
       Timer_ball->Enabled = false;
       Timer_speed->Enabled = false;
       Ball->Visible= false;

       Label3->Visible = true;
       Label3->Font->Size = 18;
       Label3->Caption = "Punkt dla gracza nr 1";
       player1_wins++;

       Button1->Visible = true;
       Button1->Caption = "JESZCZE RAZ";
       Button2->Visible = true;
       Button2->Caption = "NOWA GRA";

       amount_of_punches_record = amount_of_punches_1 + amount_of_punches_2;
       if (StrToInt(Record_amount->Caption) < amount_of_punches_record)
       Record_amount->Caption = IntToStr(amount_of_punches_record);

       Score -> Caption = IntToStr(player1_wins) + " : " + IntToStr(player2_wins);
    }

    //odbicie 2 gracza
    else if ((Ball->Left + Ball->Width >= Paddle2->Left) &&
             (Ball->Top + Ball->Height/2> Paddle2->Top) &&
             (Ball->Top - Ball->Height/2< Paddle2->Top + Paddle2->Height)){
       sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC);
       x = -x;
       amount_of_punches_2++;
       Actual_amount -> Caption = amount_of_punches_1+amount_of_punches_2;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle1_upTimer(TObject *Sender){
    if(Paddle1->Top - 5 > 10)
    Paddle1->Top -= 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle1_downTimer(TObject *Sender){
   if(Paddle1->Top + Paddle1->Height < Game_background->Height)
   Paddle1->Top += 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle2_upTimer(TObject *Sender){
   if(Paddle2->Top - 5 > 10)
   Paddle2->Top -= 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_Paddle2_downTimer(TObject *Sender){
   if(Paddle2->Top + Paddle2->Height < Game_background->Height)
   Paddle2->Top += 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift){
   if(Key == VK_UP)                Timer_Paddle2_up->Enabled = true;
   if(Key == VK_DOWN)              Timer_Paddle2_down->Enabled = true;
   if((Key == 'a')||(Key == 'A'))  Timer_Paddle1_up->Enabled = true;
   if((Key == 'z')||(Key == 'Z'))  Timer_Paddle1_down->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift){
   if(Key == VK_UP)                Timer_Paddle2_up->Enabled = false;
   if(Key == VK_DOWN)              Timer_Paddle2_down->Enabled = false;
   if((Key == 'a')||(Key == 'A'))  Timer_Paddle1_up->Enabled = false;
   if((Key == 'z')||(Key == 'Z'))  Timer_Paddle1_down->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_speedTimer(TObject *Sender){
   if(is_game_active){
     if (Speed_lvl4 -> Visible == true){
       x = x*1.15;
       y = y*1.15;
       Speed_lvl5 -> Visible = true;
     }

     else if (Speed_lvl3 -> Visible == true){
       x = x*1.15;
       y = y*1.15;
       Speed_lvl4 -> Visible = true;
     }

     else if (Speed_lvl2 -> Visible == true){
       x = x*1.2;
       y = y*1.2;
       Speed_lvl3 -> Visible = true;
     }

     else if (Speed_lvl1 -> Visible == true){
       x = x*1.2;
       y = y*1.2;
       Speed_lvl2 -> Visible = true;
     }

     else if (Speed_lvl1 -> Visible != true){
       x = x*1.2;
       y = y*1.2;
       Speed_lvl1 -> Visible = true;
     }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Application -> MessageBox ("WITAJ W GRZE PING PONG\n\n Zasady sterowania:\n Gracz 1: Litery A i Z\n Gracz 2: Strza�ka w g�r� i w d�", "PING PONG", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    is_game_active = true;

    Ball->Left = 290;
    Ball->Top = 185;
    Ball->Visible = true;

    Paddle1->Left = 16;
    Paddle1->Top = 128;
    Paddle2->Left =568;
    Paddle2->Top = 128;

    Speed_lvl1 -> Visible = false;
    Speed_lvl2 -> Visible = false;
    Speed_lvl3 -> Visible = false;
    Speed_lvl4 -> Visible = false;
    Speed_lvl5 -> Visible = false;

    x=5; y=5;
    Timer_ball->Enabled = true;
    Timer_speed->Enabled = true;
    amount_of_punches_1 = 0;
    amount_of_punches_2 = 0;
    Actual_amount -> Caption = "0";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Button1->Click();
    Record_amount -> Caption = "0";
    Score -> Caption = "0 : 0";
    player1_wins=0;
    player2_wins=0;
}
//---------------------------------------------------------------------------

