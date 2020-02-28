///-----------------------------------------------------------------
///
/// @file      EventBotFrm.h
/// @author    Radek
/// Created:   2013-06-30 14:13:18
/// @section   DESCRIPTION
///            EventBotFrm class declaration
///
///------------------------------------------------------------------

#ifndef __EVENTBOTFRM_H__
#define __EVENTBOTFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/choicdlg.h>
#include <wx/textdlg.h>
#include <wx/timer.h>
#include <wx/spinbutt.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef EventBotFrm_STYLE
#define EventBotFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxSTAY_ON_TOP | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

#define	Przelaczaj_okna___ALT_TAB	0
#define	Przelaczaj_okna___WIN_TAB___dla_Wista_i_7	1
#define	Zamknij_aktywne_okno___ALT_F4	2
#define	Zamknij_system___zamyka_Windowsa	3
#define	Uruchom_ponownie___powownie_uruchamia_Windowsa	4
#define	Uspij___usypia_Windowsa	5
#define	Wyloguj___wylogowywuje_z_konta_Windows	6
#define	Kliknij_lewy_przycisk_myszy	7
#define	Kliknij_prawy_przycisk_myszy	8
#define	Kliknij_srodkowy_przycisk_myszy	9
#define	Dwuktotnie_kliknij_lewy_przycisk_myszy	10
#define	Dwuktotnie_kliknij_prawy_przycisk_myszy	11
#define	Dwuktotnie_kliknij_srodkowy_przycisk_myszy	12
#define	Scroll_w_gore	13
#define	Scroll_w_dol	14
#define	Przesun_mysz_na_pozycje	15
#define	Wypisz_na_klawiaturze_tekst_wolno	16
#define	Wypisz_na_klawiaturze_tekst_srednio	17
#define	Wypisz_na_klawiaturze_tekst_szybko	18
#define	Wypisz_na_klawiaturze_tekst_bszybko	19
#define	Wypisz_na_klawiaturze_tekst_formatowany_wolno	20
#define	Wypisz_na_klawiaturze_tekst_formatowany_sredno	21
#define	Wypisz_na_klawiaturze_tekst_formatowany_szybko	22
#define	Wypisz_na_klawiaturze_tekst_formatowany_bszybko	23
#define	Otworz_program___otwiera_dowolny_wybrany_program_z_dysku	24
#define	SHIFT_Shift_key___kliknij	25
#define	SHIFT_Shift_key___nacisnij	26
#define	SHIFT_Shift_key___pusc	27
#define	LSHIFT_Left_Shift_key___kliknij	28
#define	LSHIFT_Left_Shift_key___nacisnij	29
#define	LSHIFT_Left_Shift_key___pusc	30
#define	RSHIFT_Right_Shift_key___kliknij	31
#define	RSHIFT_Right_Shift_key___nacisnij	32
#define	RSHIFT_Right_Shift_key___pusc	33
#define	CONTROL_Ctrl_key___kliknij	34
#define	CONTROL_Ctrl_key___nacisnij	35
#define	CONTROL_Ctrl_key___pusc	36
#define	LCONTROL_Left_Ctrl_key___kliknij	37
#define	LCONTROL_Left_Ctrl_key___nacisnij	38
#define	LCONTROL_Left_Ctrl_key___pusc	39
#define	RCONTROL_Right_Ctrl_key___kliknij	40
#define	RCONTROL_Right_Ctrl_key___nacisnij	41
#define	RCONTROL_Right_Ctrl_key___pusc	42
#define	MENU_Alt_key___kliknij	43
#define	MENU_Alt_key___nacisnij	44
#define	MENU_Alt_key___pusc	45
#define	LMENU_Left_Alt_key___kliknij	46
#define	LMENU_Left_Alt_key___nacisnij	47
#define	LMENU_Left_Alt_key___pusc	48
#define	RMENU_Right_Alt_key___kliknij	49
#define	RMENU_Right_Alt_key___nacisnij	50
#define	RMENU_Right_Alt_key___pusc	51
#define	LWIN_Left_Windows_key__Microsoft_keyboard____kliknij	52
#define	LWIN_Left_Windows_key__Microsoft_keyboard____nacisnij	53
#define	LWIN_Left_Windows_key__Microsoft_keyboard____pusc	54
#define	RWIN_Right_Windows_key__Microsoft_keyboard____kliknij	55
#define	RWIN_Right_Windows_key__Microsoft_keyboard____nacisnij	56
#define	RWIN_Right_Windows_key__Microsoft_keyboard____pusc	57
#define	APPS_Applications_key__Microsoft_keyboard____kliknij	58
#define	APPS_Applications_key__Microsoft_keyboard____nacisnij	59
#define	APPS_Applications_key__Microsoft_keyboard____pusc	60
#define	A_Key	61
#define	B_Key	62
#define	C_Key	63
#define	D_Key	64
#define	E_Key	65
#define	F_Key	66
#define	G_Key	67
#define	H_Key	68
#define	I_Key	69
#define	J_Key	70
#define	K_Key	71
#define	L_Key	72
#define	M_Key	73
#define	N_Key	74
#define	O_Key	75
#define	P_Key	76
#define	Q_Key	77
#define	R_Key	78
#define	S_Key	79
#define	T_Key	80
#define	U_Key	81
#define	V_Key	82
#define	W_Key	83
#define	Y_Key	84
#define	Z_Key	85
#define	X_Key	86
#define	RETURN_Enter_key	87
#define	ESCAPE_Esc_key	88
#define	SPACE_Space_bar	89
#define	BACK_Backspace_key	90
#define	TAB_Tab_key	91
#define	UP_Up_Arrow_key	92
#define	DOWN_Down_Arrow_key	93
#define	LEFT_Left_Arrow_key	94
#define	RIGHT_Right_Arrow_key	95
#define	CAPITAL_Caps_Lock_key	96
#define	NUMLOCK_Num_Lock_key	97
#define	SCROLL_Scroll_Lock_key	98
#define	INSERT_Insert_key	99
#define	DELETE_Delete_key	100
#define	HOME_Home_key	101
#define	END_End_key	102
#define	PRIOR_Page_Up_key	103
#define	NEXT_Page_Down_key	104
#define	SNAPSHOT_Print_Screen_key	105
#define	HELP_Help_key	106
#define	PRINT_Print_key__keyboard_specific_	107
#define	SELECT_Select_key	108
#define	NUMPAD0_0_key__numeric_keypad_	109
#define	NUMPAD1_1_key__numeric_keypad_	110
#define	NUMPAD2_2_key__numeric_keypad_	111
#define	NUMPAD3_3_key__numeric_keypad_	112
#define	NUMPAD4_4_key__numeric_keypad_	113
#define	NUMPAD5_5_key__numeric_keypad_	114
#define	NUMPAD6_6_key__numeric_keypad_	115
#define	NUMPAD7_7_key__numeric_keypad_	116
#define	NUMPAD8_8_key__numeric_keypad_	117
#define	NUMPAD9_9_key__numeric_keypad_	118
#define	MULTIPLY_Multiply_key__numeric_keypad_	119
#define	DIVIDE_Divide_key__numeric_keypad_	120
#define	ADD_Add_key__numeric_keypad_	121
#define	SUBTRACT_Subtract_key__numeric_keypad_	122
#define	SEPARATOR_Separator_key__numeric_keypad_	123
#define	DECIMAL_Decimal_key__numeric_keypad_	124
#define	F1_key	125
#define	F2_key	126
#define	F3_key	127
#define	F4_key	128
#define	F5_key	129
#define	F6_key	130
#define	F7_key	131
#define	F8_key	132
#define	F9_key	133
#define	F10_key	134
#define	F11_key	135
#define	F12_key	136
#define	F13_key	137
#define	F14_key	138
#define	F15_key	139
#define	F16_key	140
#define	F17_key	141
#define	F18_key	142
#define	F19_key	143
#define	F20_key	144
#define	F21_key	145
#define	F22_key	146
#define	F23_key	147
#define	F24_key	148
#define	SCREEN_LOG	149
#define	WYPELNIJ_FORMULARZ	150
#define LOSUJ_DANE_OSOBOWE  151
#define UKRYJ_OKNO  152
#define POKAZ_OKNO  153
#define ZAMKNIJ_OKNO 154
#define ZAPISZ_DANE_OSOBOWE     155
#define ZAPISZ_DANE_LOGOWANIA   156
#define LADUJ_DANE_Z_PLIKU      157

// moje

#define MAIN_WINDOW_CENTER GetPosition() + GetSize()/2

#include <wx/textfile.h>

extern int MyArgc; 
extern wxString GetArgv( int ArgvNo );


class EventBotFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		EventBotFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("EventBot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = EventBotFrm_STYLE);
		virtual ~EventBotFrm();
		
		typedef struct
		{
            wxString Name;      // i
            wxString SurName;   // n
            wxString City;      // m
            wxString PostCode;  // k
            wxString Street;    // u
            wxString HouseNo;   // d od dom
            wxString Nick;      // l od login
            wxString Mail;      // p od poczta
            wxString Age;       // w
            wxString Password;  // h
            wxString Phone;     // t
            
            //static char PolishSign[] = {165,198,202,163,209,211,140,143,175,185,230,234,179,241,243,156,159,191};
            
            //const static wxString PolishSign = "•∆ £—”åèØπÊÍ≥ÒÛúüø";
            
            int AgeMin;
            int AgeMax;
            int HouseNoMin;
            int HouseNoMax;
            int PasswordLen;
            
            wxString MailServer; // without @
        
            void LoadRandData()
            {
                wxTextFile Text;
                wxString Temp;
                int i;
                
                Text.Open( GetArgv(0) + "Dane/imiona.txt");
                Name = Text.GetLine( RandomValue( 0, Text.GetLineCount() ) );
                Text.Close();
                
                Text.Open( GetArgv(0) + "Dane/nazwiska.txt");
                SurName = Text.GetLine( RandomValue( 0, Text.GetLineCount() ) );
                Text.Close();
                
                Text.Open( GetArgv(0) + "Dane/miasta.txt");
                Temp = Text.GetLine( RandomValue( 0, Text.GetLineCount() ) );
                Text.Close();
                
                City = Temp.Right( Temp.Len() - 7 );
                PostCode = Temp.Left(6);
                
                Text.Open( GetArgv(0) + "Dane/ulice.txt");
                Street = Text.GetLine( RandomValue( 0, Text.GetLineCount() ) );
                Text.Close();
                
                
                Temp.Printf("%d", RandomValue( HouseNoMin, HouseNoMax ) );
                HouseNo = Temp;
                
                Temp.Printf("%d", RandomValue( 100, 1000 ) );
                Nick = MakeLowerCase( ConvertToLatin( Name + SurName + Temp ) );
                
                Mail = Nick + '@' + MailServer;
                
                Temp.Printf("%d", RandomValue( AgeMin, AgeMax ) );
                Age = Temp;
                
                // 48 - 57 - cyfry (1) grupa symboli
                // 65 - 90 - litery duøe (2) grupa symboli
                // 97 - 122 - litery ma≥e (3) grupa symboli
                
                Password.Clear();
                
                for ( i = 0; i < PasswordLen; i++ )
                {
                    switch ( RandomValue(0,3) ) // wybÛr grupy symboli
                    {
                        case 0: Password += RandomValue(48,57); Sleep(10);  break;
  
                        case 1: Password += RandomValue(65,90); Sleep(10);  break;
                            
                        case 2: Password += RandomValue(97,122); Sleep(10);  break;
                    }
                }
                
                Password[ RandomValue( 0, Password.Len() ) ] = '@';
                
                Temp.Printf("%d", RandomValue( 600000000, 999999999 ) );
                Phone = Temp;
            }
            
            wxString ConvertToLatin( wxString Str )
            {
                int i;
                
                for ( int i = 0; i < Str.Len(); i++ )
                {
                    switch ( Str[i] )
                    {
                        case 'π':    Str[i] = 'a';      break;
                        case 'Ê':    Str[i] = 'c';      break;
                        case 'Í':    Str[i] = 'e';      break;
                        case '≥':    Str[i] = 'l';      break;
                        case 'Ò':    Str[i] = 'n';      break;
                        case 'Û':    Str[i] = 'o';      break;
                        case 'ú':    Str[i] = 's';      break;
                        case 'ü':    Str[i] = 'z';      break;
                        case 'ø':    Str[i] = 'z';      break;
                        
                        case '•':    Str[i] = 'A';      break;
                        case '∆':    Str[i] = 'C';      break;
                        case ' ':    Str[i] = 'E';      break;
                        case '£':    Str[i] = 'L';      break;
                        case '—':    Str[i] = 'N';      break;
                        case '”':    Str[i] = 'O';      break;
                        case 'å':    Str[i] = 'S';      break;
                        case 'è':    Str[i] = 'Z';      break;
                        case 'Ø':    Str[i] = 'Z';      break;
                    }
                }
                
                return Str;
            }
            
            int RandomValue( int min, int max )
            {
                LARGE_INTEGER Val;
                long long Counter;
                
                QueryPerformanceCounter(&Val);
                Counter = Val.QuadPart;
                
                return (int)( Counter % ( max - min ) + min );
            }
            
            wxString MakeLowerCase( wxString Str )
            {
                int i;
                Str.MakeLower();
                
                for ( int i = 0; i < Str.Len(); i++ )
                {
                    switch ( Str[i] )
                    {
						case	'•':	Str[i]	=	'π';	break;
						case	'∆':	Str[i]	=	'Ê';	break;
						case	' ':	Str[i]	=	'Í';	break;
						case	'£':	Str[i]	=	'≥';	break;
						case	'—':	Str[i]	=	'Ò';	break;
						case	'”':	Str[i]	=	'Û';	break;
						case	'å':	Str[i]	=	'ú';	break;
						case	'è':	Str[i]	=	'ü';	break;
						case	'Ø':	Str[i]	=	'ø';	break;
                    }
                }
                
                return Str;
            }
            
            wxString MakeUpperCase( wxString Str )
            {
                int i;
                Str.MakeUpper();
                
                for ( int i = 0; i < Str.Len(); i++ )
                {
                    switch ( Str[i] )
                    {
	                    case	'π':	Str[i]	=	'•';	break;
	                    case	'Ê':	Str[i]	=	'∆';	break;
	                    case	'Í':	Str[i]	=	' ';	break;
	                    case	'≥':	Str[i]	=	'£';	break;
	                    case	'Ò':	Str[i]	=	'—';	break;
	                    case	'Û':	Str[i]	=	'”';	break;
	                    case	'ú':	Str[i]	=	'å';	break;
	                    case	'ü':	Str[i]	=	'è';	break;
	                    case	'ø':	Str[i]	=	'Ø';	break;
                    }
                }
                
                return Str;
            }
            
        }personaldata;
        
        personaldata MyData;
        
        void CloseApplication();
        
        int GetFirstSteepLineNo( int SteepNo );
        int GetFirstActionLineNo( int SteepNo, int ActionNo );
        int GetLastSteepLineNo( int SteepNo );
        int GetLastActionLineNo( int SteepNo, int ActionNo );
        
        void ReLoadSettings();
		void ReLoadSteep( int SteepNo );
		void ReLoadAction( int ActionNo );
		void ReLoadSteepList();
		void ReLoadActionList( int SteepNo );
		void RemoveMemoLines( int FirstLine, int LastLine );
		void ReplaceMemoLine( int LineNo, wxString Text );
		void ReplaceMemoLines( int FirstLine, int LastLine, wxString Text );
		wxString GetMemoLines( int FirstLine, int LastLine );
		int GetFormatValue();
		void MakeSteep( int SteepNo, int LoopNo, bool End = false );
		void ActionExecute( int ActionNo, int ClickX, int ClickY, wxString Text );
		
		void Print( wxString Text, int CharDelay );
		void FotmatPrint( wxString Text, int CharDelay );
		void FillForm( wxString Text );
		void MoveMouse( int x, int y );
		void LClick( int x, int y );
		
		
		wxString MainFilePath;
        wxString MainFileName;

		
		int FormatValue;
		int SteepsAmount;
		int LoopCounter;
		int SteepCounter;
		
		bool AutoRun;
		bool FreeRunning;
		
		bool StartPause;
		bool IsStop;
		
		int GaugeCounter;
		//int Interval;
		
		int ManualScreenCouter;
		
		void MenuNew(wxCommandEvent& event);
		void MenuOpen(wxCommandEvent& event);
		void MenuSave(wxCommandEvent& event);
		void MenuSaveAs(wxCommandEvent& event);
		void AddSteepClick(wxCommandEvent& event);
		void DeleteSteepClick(wxCommandEvent& event);
		void SteepListSelected(wxCommandEvent& event);
		void SteepListDoubleClicked(wxCommandEvent& event);
		void AddActionClick(wxCommandEvent& event);
		void DeleteActionClick(wxCommandEvent& event);
		void ActionListSelected(wxCommandEvent& event);
		void PosCangeClick(wxCommandEvent& event);
		void PosChangeTimerTimer(wxTimerEvent& event);
		void LinkEditEnter(wxCommandEvent& event);
		void TypeChoiceSelected(wxCommandEvent& event );
		void CycleSpinCtrlTextUpdated(wxCommandEvent& event );
		void DelaySpinCtrlTextUpdated(wxCommandEvent& event );
		
		void PlayPauseFunction();
		void StopFunction();
		
		void StartClick(wxCommandEvent& event);
		void StopClick(wxCommandEvent& event);
		void SteepTimerTimer(wxTimerEvent& event);
		void SecurityTimerTimer(wxTimerEvent& event);
		void GaugeTimerTimer(wxTimerEvent& event);
		void MenuOpenLogsFolder(wxCommandEvent& event);
		void MenuHelp(wxCommandEvent& event);
		void OrderListControlDown(wxSpinEvent& event);
		void OrderListControlUp(wxSpinEvent& event);
		void OrderActionControlDown(wxSpinEvent& event);
		void OrderActionControlUp(wxSpinEvent& event);
		void MenuToTray(wxCommandEvent& event);
		
		void OnShowUnshowHotKey(wxKeyEvent& event); 
        void OnExitHotKey(wxKeyEvent& event);   
        void OnPrintScreenHotKey(wxKeyEvent& event);   
        void OnShowPrintScreenFolderHotKey(wxKeyEvent& event);  
        void OnPlayPauseHotKey(wxKeyEvent& event);
        void OnStopHotKey(wxKeyEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxSaveFileDialog1;
		wxMenuBar *WxMenuBar1;
		wxTimer *SecurityTimer;
		wxFileDialog *WxOpenFileDialog1;
		wxTimer *SteepTimer;
		wxSingleChoiceDialog *ActionChoiceDialog;
		wxTextEntryDialog *NewNameDialog;
		wxTextEntryDialog *RenameDialog;
		wxTimer *PosChangeTimer;
		wxTimer *GaugeTimer;
		wxSpinButton *OrderActionControl;
		wxSpinButton *OrderListControl;
		wxCheckBox *WxCheckBox1;
		wxTextCtrl *RangeEdit;
		wxGauge *WxGauge1;
		wxStaticText *WxStaticText4;
		wxSpinCtrl *DelaySpinCtrl;
		wxChoice *TypeChoice;
		wxStaticText *WxStaticText3;
		wxTextCtrl *RangeEditStatic;
		wxTextCtrl *FileMemo;
		wxButton *Stop;
		wxButton *Start;
		wxSpinCtrl *CycleSpinCtrl;
		wxStaticText *WxStaticText2;
		wxStaticBox *WxStaticBox5;
		wxTextCtrl *LinkEdit;
		wxStaticText *ClickText;
		wxButton *PosCange;
		wxButton *DeleteAction;
		wxButton *AddAction;
		wxListBox *ActionList;
		wxButton *DeleteSteep;
		wxButton *AddSteep;
		wxListBox *SteepList;
		wxStaticBox *WxStaticBox3;
		wxStaticBox *WxStaticBox2;
		wxStaticBox *WxStaticBox1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_PLIK_1001 = 1001,
			ID_MNU_NOWY_1002 = 1002,
			ID_MNU_OTW_RZ_1003 = 1003,
			ID_MNU_ZAPISZ_1004 = 1004,
			ID_MNU_ZAPISZJAKO_1005 = 1005,
			ID_MNU_OPCJE_1044 = 1044,
			ID_MNU_OTW_RZFOLDERLOGS_1045 = 1045,
			ID_MNU_UKRYJOKNO_1051 = 1051,
			ID_MNU_POMOC_1046 = 1046,
			
			ID_SECURITYTIMER = 1039,
			ID_STEEPTIMER = 1035,
			ID_POSCHANGETIMER = 1036,
			ID_GAUGETIMER = 1043,
			ID_WXSPINBUTTON2 = 1050,
			ID_WXSPINBUTTON1 = 1049,
			ID_WXCHECKBOX1 = 1048,
			ID_WXEDIT3 = 1047,
			ID_WXGAUGE1 = 1040,
			ID_WXSTATICTEXT4 = 1034,
			ID_WXSPINCTRL2 = 1032,
			ID_WXCHOICE1 = 1031,
			ID_WXSTATICTEXT3 = 1030,
			ID_WXEDIT2 = 1029,
			ID_WXMEMO1 = 1028,
			ID_WXBUTTON7 = 1027,
			ID_WXBUTTON6 = 1026,
			ID_WXSPINCTRL1 = 1021,
			ID_WXSTATICTEXT2 = 1020,
			ID_WXSTATICBOX5 = 1019,
			ID_WXEDIT1 = 1018,
			ID_WXSTATICTEXT1 = 1017,
			ID_WXBUTTON5 = 1016,
			ID_WXBUTTON4 = 1015,
			ID_WXBUTTON3 = 1014,
			ID_WXLISTBOX2 = 1013,
			ID_WXBUTTON2 = 1012,
			ID_WXBUTTON1 = 1011,
			ID_WXLISTBOX1 = 1010,
			ID_WXSTATICBOX3 = 1008,
			ID_WXSTATICBOX2 = 1007,
			ID_WXSTATICBOX1 = 1006,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
