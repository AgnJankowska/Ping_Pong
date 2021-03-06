//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Game_background;
        TImage *Paddle1;
        TImage *Paddle2;
        TImage *Ball;
        TShape *Whole_background;
        TImage *Speed_lvl1a;
        TImage *Speed_lvl2a;
        TImage *Speed_lvl3a;
        TImage *Speed_lvl4a;
        TImage *Speed_lvl5a;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label5;
        TImage *Speed_lvl2;
        TImage *Speed_lvl1;
        TImage *Speed_lvl3;
        TImage *Speed_lvl4;
        TImage *Speed_lvl5;
        TTimer *Timer_ball;
        TTimer *Timer_Paddle1_up;
        TTimer *Timer_Paddle1_down;
        TTimer *Timer_Paddle2_up;
        TTimer *Timer_Paddle2_down;
        TShape *Bonus_area;
        TImage *Image2;
        TLabel *Score;
        TLabel *Label4;
        TLabel *Label6;
        TImage *Image1;
        TImage *Image3;
        TLabel *Actual_amount;
        TLabel *Record_amount;
        TTimer *Timer_speed;
        TButton *Button1;
        TButton *Button2;
        TLabel *Label3;
        TImage *Speed_lvl1b;
        TImage *Speed_lvl2b;
        TImage *Speed_lvl3b;
        TImage *Speed_lvl4b;
        TImage *Speed_lvl5b;
        TTimer *Timer_extra_speed;
        TButton *Button3;
        TTimer *Timer_bonuses;
        void __fastcall Timer_ballTimer(TObject *Sender);
        void __fastcall Timer_Paddle1_upTimer(TObject *Sender);
        void __fastcall Timer_Paddle1_downTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Timer_Paddle2_downTimer(TObject *Sender);
        void __fastcall Timer_Paddle2_upTimer(TObject *Sender);
        void __fastcall Timer_speedTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Timer_extra_speedTimer(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
