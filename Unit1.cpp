//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
float x;
float y;
int amount_of_punches_1 = 0;
int amount_of_punches_2 = 0;
int amount_of_punches_record = 0;
int player1_wins = 0;
int player2_wins = 0;
bool is_game_active = false;
bool extra_speed = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void random_direction_of_ball()
{
   randomize();
   int set = random (4) + 1;
   switch(set){
     case 1: {x=10;  y=10;}  break;
     case 2: {x=10;  y=-10;} break;
     case 3: {x=-10; y=10;}  break;
     case 4: {x=-10; y=-10;} break;
   }
}
//---------------------------------------------------------------------------
void extra_speed_on() {
      extra_speed = true;
      Form1->Timer_extra_speed -> Enabled = true;
      Form1->Timer_speed -> Enabled = false;

      Form1->Speed_lvl1b -> Visible = true;
      Form1->Speed_lvl2b -> Visible = true;
      Form1->Speed_lvl3b -> Visible = true;
      Form1->Speed_lvl4b -> Visible = true;
      Form1->Speed_lvl5b -> Visible = true;

      sndPlaySound ("Sounds/premie.wav", SND_ASYNC);
      x = -1.6*x;
      y = 1.3*y;
}
//---------------------------------------------------------------------------
void end_of_game (){
      sndPlaySound ("Sounds/koniec.wav", SND_ASYNC);
      Form1->Timer_ball->Enabled = false;
      Form1->Timer_speed->Enabled = false;
      Form1->Timer_bonuses->Enabled = false;
      Form1->Ball->Visible = false;

      Form1->Speed_lvl1 -> Visible = false;
      Form1->Speed_lvl2 -> Visible = false;
      Form1->Speed_lvl3 -> Visible = false;
      Form1->Speed_lvl4 -> Visible = false;
      Form1->Speed_lvl5 -> Visible = false;
      Form1->Speed_lvl1b -> Visible = false;
      Form1->Speed_lvl2b -> Visible = false;
      Form1->Speed_lvl3b -> Visible = false;
      Form1->Speed_lvl4b -> Visible = false;
      Form1->Speed_lvl5b -> Visible = false;

      Form1->Label3->Visible = true;
      Form1->Label3->Font->Size = 18;

      Form1->Button1->Visible = true;
      Form1->Button1->Caption = "JESZCZE RAZ";
      Form1->Button2->Visible = true;
      Form1->Button2->Caption = "NOWA GRA";
      Form1->Button3->Visible = true;

      amount_of_punches_record = amount_of_punches_1 + amount_of_punches_2;
      if (StrToInt(Form1->Record_amount->Caption) < amount_of_punches_record)
      Form1->Record_amount->Caption = IntToStr(amount_of_punches_record);
      Form1->Score -> Caption = IntToStr(player1_wins) + " : " + IntToStr(player2_wins);
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Application -> MessageBox ("WITAJ W GRZE PING PONG\n\n Zasady sterowania (g�ra / d�):\n Gracz 1: Litery A i Z\n Gracz 2: Strza�ka w g�r� i w d�\n\n Odbicie �rodkiem rakietki powoduje przyspieszenie\n i zmian� k�ta nachylenia pi�eczki.\n\n UDANEJ ROZGRYWKI!", "PING PONG", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Ball->Left = 290;
    Ball->Top = 185;
    Ball->Visible = true;

    Paddle1->Left = 16;
    Paddle1->Top = 128;
    Paddle2->Left =568;
    Paddle2->Top = 128;

    Button1->Visible = false;
    Button2->Visible = false;
    Button3->Visible = false;

    amount_of_punches_1 = 0;
    amount_of_punches_2 = 0;
    Actual_amount -> Caption = "0";

    Label3->Visible=true;
    Label3->Font->Size = 36;

    Label3->Caption="3...";
    Application -> ProcessMessages();
    Sleep(1000);

    Label3->Caption="2...";
    Application -> ProcessMessages();
    Sleep(1000);

    Label3->Caption="1...";
    Application -> ProcessMessages();
    Sleep(1000);

    Label3->Caption="START";
    Application -> ProcessMessages();
    Sleep(1000);
    Label3->Visible = false;

    is_game_active = true;
    random_direction_of_ball();

    Timer_ball->Enabled = true;
    Timer_speed->Enabled = true;
    Timer_bonuses->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Score -> Caption = "0 : 0";
    player1_wins=0;
    player2_wins=0;
    Record_amount -> Caption = "0";
    Button1->Click();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_ballTimer(TObject *Sender){
  if(is_game_active){

    Ball->Left += x;
    Ball->Top += y;

    //odbij od g�rnej �ciany
    if(Ball->Top < Game_background->Top){
      sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC );
      y = -y;
      Ball->Top = Game_background->Top;
    }

    //odbij od dolnej �ciany
    if(Ball->Top + Ball->Height > Game_background->Top + Game_background->Height -5){
      sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC );
      y = -y;
      Ball->Top = Game_background->Top + Game_background->Height - Ball->Height;
    }

    //odbicie 1 gracza srodkiem
    if((Ball->Left < Paddle1->Left + Paddle1->Width) &&
            (Ball->Top + Ball->Height/2 >= Paddle1->Top + Paddle1->Height/2-6) &&
            (Ball->Top + Ball->Height/2 <= Paddle1->Top + Paddle1->Height/2+6)){
       amount_of_punches_1++;
       Actual_amount -> Caption = amount_of_punches_1 + amount_of_punches_2;
       Ball->Left = Paddle1->Left+Paddle1->Width;
       if(extra_speed==false) extra_speed_on();
       else x = -x;
    }

    //odbicie 1 gracza
    else if((Ball->Left < Paddle1->Left + Paddle1->Width) &&
            (Ball->Top + Ball->Height/2 >= Paddle1->Top) &&
            (Ball->Top - Ball->Height/2 <= Paddle1->Top + Paddle1->Height)){
       sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC);
       x = -x;
       Ball->Left = Paddle1->Left+Paddle1->Width;
       amount_of_punches_1++;
       Actual_amount -> Caption = amount_of_punches_1 + amount_of_punches_2;
    }

    //skucha 1 gracza
    else if(Ball->Left < Paddle1->Left + Paddle1->Width/2){
       Label3->Caption = "Punkt dla gracza nr 2";
       player2_wins++;
       end_of_game();
    }

    //odbicie 2 gracza srodkiem
    if((Ball->Left + Ball->Width > Paddle2->Left) &&
            (Ball->Top + Ball->Height/2 >= Paddle2->Top + Paddle2->Height/2-6) &&
            (Ball->Top + Ball->Height/2 <= Paddle2->Top + Paddle2->Height/2+6)){
       amount_of_punches_2++;
       Actual_amount -> Caption = amount_of_punches_1 + amount_of_punches_2;
       Ball->Left = Paddle2->Left - Ball->Width ;
       if(extra_speed==false) extra_speed_on();
       else x = -x;
    }

    //odbicie 2 gracza
    else if((Ball->Left + Ball->Width > Paddle2->Left) &&
             (Ball->Top + Ball->Height/2>= Paddle2->Top) &&
             (Ball->Top - Ball->Height/2<= Paddle2->Top + Paddle2->Height)){
       sndPlaySound ("Sounds/odbicie.wav", SND_ASYNC);
       x = -x;
       Ball->Left = Paddle2->Left - Ball->Width ;
       amount_of_punches_2++;
       Actual_amount -> Caption = amount_of_punches_1+amount_of_punches_2;
    }

    //skucha 2 gracza
    else if(Ball->Left + Ball->Width > Paddle2->Left + Paddle2->Width){
       Label3->Caption = "Punkt dla gracza nr 1";
       player1_wins++;
       end_of_game();
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
       if (Speed_lvl5 -> Visible == true){
         x = x;
         y = y;
       }

       else if (Speed_lvl4 -> Visible == true){
         x = x*1.18;
         y = y*1.18;
         Speed_lvl5 -> Visible = true;
       }

       else if (Speed_lvl3 -> Visible == true){
         x = x*1.18;
         y = y*1.18;
         Speed_lvl4 -> Visible = true;
       }

       else if (Speed_lvl2 -> Visible == true){
         x = x*1.18;
         y = y*1.18;
         Speed_lvl3 -> Visible = true;
       }

       else if (Speed_lvl1 -> Visible == true){
         x = x*1.18;
         y = y*1.18;
         Speed_lvl2 -> Visible = true;
       }

       else if (Speed_lvl1 -> Visible != true){
         x = x*1.18;
         y = y*1.18;
         Speed_lvl1 -> Visible = true;
       }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_extra_speedTimer(TObject *Sender){
      x = x / 1.6;
      y = y / 1.3;
      Speed_lvl1b -> Visible = false;
      Speed_lvl2b -> Visible = false;
      Speed_lvl3b -> Visible = false;
      Speed_lvl4b -> Visible = false;
      Speed_lvl5b -> Visible = false;
      Timer_speed -> Enabled = true;
      Timer_extra_speed -> Enabled = false;
      extra_speed = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender){
   if(Application -> MessageBox ("Czy na pewno zako�czy�?", "Potwierd�", MB_YESNO | MB_ICONQUESTION) == IDYES){
      Application -> Terminate();
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action){
   if(Application -> MessageBox ("Czy na pewno zako�czyc?", "Potwierd�" , MB_YESNO | MB_ICONQUESTION) == IDNO){
        Action = caNone;
   }
}
//---------------------------------------------------------------------------



