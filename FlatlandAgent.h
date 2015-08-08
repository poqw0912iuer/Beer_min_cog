#ifndef FlatlandAgentH
#define FlatlandAgentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
friend class Agent;
friend class TGenotype;
__published:	// IDE-managed Components
        TEdit *Edit2;
        TLabel *Label2;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit3;
        TEdit *Edit4;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TGroupBox *GroupBox2;
        TRadioButton *RadioButton6;
        TRadioButton *RadioButton7;
        TLabel *Label10;
        TEdit *Edit8;
        TEdit *Edit5;
        TEdit *Edit9;
        TButton *Button5;
        TLabel *Label3;
        TLabel *Label4;
        TTrackBar *TrackBar1;
        TStringGrid *StringGrid1;
        TButton *Button1;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        int cross_probability, mut_probability;
        int E;
        int population, generations, generation;
        int steps;
        float *max, *average, *st_dew;
        TGenotype *best_genotype;
        int SelectionMechanismNr;
        int weight_bits, num_Weights, num_Neurons;
        bool turn_left, turn_right, strait_ahead;
        int flatland_memory1[64], flatland_memory2[64], flatland_memory3[64], flatland_memory4[64], flatland_memory5[64];
        int temp_size ,steps_per_time;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
