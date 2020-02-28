///-----------------------------------------------------------------
///
/// @file      EventBotFrm.cpp
/// @author    Radek
/// Created:   2013-06-30 14:13:18
/// @section   DESCRIPTION
///            EventBotFrm class implementation
///
///------------------------------------------------------------------

#include "EventBotFrm.h"
#include "MyTaskBar.h"
#include "MyMessageDlg.h"

MyTaskBarIcon* MyTaskBar; // wskaznik zadeklaruj globalnie

wxString PolishSign = "¥ÆÊ£ÑÓŒ¯¹æê³ñóœŸ¿";

MyMessageDlg* MyMessageBox;

wxPoint WindowPosition;

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_EventBotFrm_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// EventBotFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(EventBotFrm,wxFrame)
	////Manual Code Start
	EVT_HOTKEY(1,EventBotFrm::OnShowUnshowHotKey)
	EVT_HOTKEY(2,EventBotFrm::OnExitHotKey)
	EVT_HOTKEY(3,EventBotFrm::OnPrintScreenHotKey)
	EVT_HOTKEY(4,EventBotFrm::OnShowPrintScreenFolderHotKey)
	EVT_HOTKEY(5,EventBotFrm::OnPlayPauseHotKey)
	EVT_HOTKEY(6,EventBotFrm::OnStopHotKey)
	////Manual Code End
	
	EVT_CLOSE(EventBotFrm::OnClose)
	EVT_MENU(ID_MNU_NOWY_1002, EventBotFrm::MenuNew)
	EVT_MENU(ID_MNU_OTW_RZ_1003, EventBotFrm::MenuOpen)
	EVT_MENU(ID_MNU_ZAPISZ_1004, EventBotFrm::MenuSave)
	EVT_MENU(ID_MNU_ZAPISZJAKO_1005, EventBotFrm::MenuSaveAs)
	EVT_MENU(ID_MNU_OTW_RZFOLDERLOGS_1045, EventBotFrm::MenuOpenLogsFolder)
	EVT_MENU(ID_MNU_UKRYJOKNO_1051, EventBotFrm::MenuToTray)
	EVT_MENU(ID_MNU_POMOC_1046, EventBotFrm::MenuHelp)
	EVT_TIMER(ID_SECURITYTIMER,EventBotFrm::SecurityTimerTimer)
	EVT_TIMER(ID_STEEPTIMER,EventBotFrm::SteepTimerTimer)
	EVT_TIMER(ID_POSCHANGETIMER,EventBotFrm::PosChangeTimerTimer)
	EVT_TIMER(ID_GAUGETIMER,EventBotFrm::GaugeTimerTimer)
	
	EVT_SPIN_UP(ID_WXSPINBUTTON2,EventBotFrm::OrderActionControlUp)
	EVT_SPIN_DOWN (ID_WXSPINBUTTON2,EventBotFrm::OrderActionControlDown)
	
	EVT_SPIN_UP(ID_WXSPINBUTTON1,EventBotFrm::OrderListControlUp)
	EVT_SPIN_DOWN (ID_WXSPINBUTTON1,EventBotFrm::OrderListControlDown)
	
	EVT_TEXT(ID_WXSPINCTRL2,EventBotFrm::DelaySpinCtrlTextUpdated)
	EVT_CHOICE(ID_WXCHOICE1,EventBotFrm::TypeChoiceSelected)
	EVT_BUTTON(ID_WXBUTTON7,EventBotFrm::StopClick)
	EVT_BUTTON(ID_WXBUTTON6,EventBotFrm::StartClick)
	
	EVT_TEXT(ID_WXSPINCTRL1,EventBotFrm::CycleSpinCtrlTextUpdated)
	EVT_TEXT_ENTER(ID_WXEDIT1,EventBotFrm::LinkEditEnter)
	EVT_BUTTON(ID_WXBUTTON5,EventBotFrm::PosCangeClick)
	EVT_BUTTON(ID_WXBUTTON4,EventBotFrm::DeleteActionClick)
	EVT_BUTTON(ID_WXBUTTON3,EventBotFrm::AddActionClick)
	EVT_LISTBOX(ID_WXLISTBOX2,EventBotFrm::ActionListSelected)
	EVT_BUTTON(ID_WXBUTTON2,EventBotFrm::DeleteSteepClick)
	EVT_BUTTON(ID_WXBUTTON1,EventBotFrm::AddSteepClick)
	EVT_LISTBOX(ID_WXLISTBOX1,EventBotFrm::SteepListSelected)
	EVT_LISTBOX_DCLICK(ID_WXLISTBOX1,EventBotFrm::SteepListDoubleClicked)
END_EVENT_TABLE()
////Event Table End

EventBotFrm::EventBotFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

EventBotFrm::~EventBotFrm()
{
}

wxString ActionNames[] =
{
    "Prze³¹czaj okna - ALT+TAB",
	"Prze³¹czaj okna - WIN+TAB - dla Wista i 7",
	"Zamknij aktywne okno - ALT+F4",
	"Zamknij system - zamyka Windowsa",
	"Uruchom ponownie - powownie uruchamia Windowsa",
	"Uœpij - usypia Windowsa",
	"Wyloguj - wylogowywuje z konta Windows",
	"Kliknij lewy przycisk myszy",
	"Kliknij prawy przycisk myszy",
	"Kliknij œrodkowy przycisk myszy",
	"Dwuktotnie kliknij lewy przycisk myszy",
	"Dwuktotnie kliknij prawy przycisk myszy",
	"Dwuktotnie kliknij œrodkowy przycisk myszy",
	"Scroll w górê",
	"Scroll w dó³",
	"Przesuñ mysz na pozycjê:",
	"Wypisz na klawiaturze tekst ( wolno )",
	"Wypisz na klawiaturze tekst ( œrednio )",
	"Wypisz na klawiaturze tekst ( szybko )",
	"Wypisz na klawiaturze tekst ( b. szybko )",
	"Wypisz na klawiaturze tekst formatowany ( wolno )",
	"Wypisz na klawiaturze tekst formatowany ( œredno )",
	"Wypisz na klawiaturze tekst formatowany ( szybko )",
	"Wypisz na klawiaturze tekst formatowany ( b. szybko )",
	"Otwórz dowolny plik ( w domyœlnym programie ) w tym .exe",
	"SHIFT Shift key - kliknij",
	"SHIFT Shift key - naciœnij",
	"SHIFT Shift key - puœæ",
	"LSHIFT Left Shift key - kliknij",
	"LSHIFT Left Shift key - naciœnij",
	"LSHIFT Left Shift key - puœæ",
	"RSHIFT Right Shift key - kliknij",
	"RSHIFT Right Shift key - naciœnij",
	"RSHIFT Right Shift key - puœæ",
	"CONTROL Ctrl key - kliknij",
	"CONTROL Ctrl key - naciœnij",
	"CONTROL Ctrl key - puœæ",
	"LCONTROL Left Ctrl key - kliknij",
	"LCONTROL Left Ctrl key - naciœnij",
	"LCONTROL Left Ctrl key - puœæ",
	"RCONTROL Right Ctrl key - kliknij",
	"RCONTROL Right Ctrl key - naciœnij",
	"RCONTROL Right Ctrl key - puœæ",
	"MENU Alt key - kliknij",
	"MENU Alt key - naciœnij",
	"MENU Alt key - puœæ",
	"LMENU Left Alt key - kliknij",
	"LMENU Left Alt key - naciœnij",
	"LMENU Left Alt key - puœæ",
	"RMENU Right Alt key - kliknij",
	"RMENU Right Alt key - naciœnij",
	"RMENU Right Alt key - puœæ",
	"LWIN Left Windows key (Microsoft keyboard) - kliknij",
	"LWIN Left Windows key (Microsoft keyboard) - naciœnij",
	"LWIN Left Windows key (Microsoft keyboard) - puœæ",
	"RWIN Right Windows key (Microsoft keyboard) - kliknij",
	"RWIN Right Windows key (Microsoft keyboard) - naciœnij",
	"RWIN Right Windows key (Microsoft keyboard) - puœæ",
	"APPS Applications key (Microsoft keyboard) - kliknij",
	"APPS Applications key (Microsoft keyboard) - naciœnij",
	"APPS Applications key (Microsoft keyboard) - puœæ",
	" A Key " ,
	" B Key " ,
	" C Key " ,
	" D Key " ,
	" E Key " ,
	" F Key " ,
	" G Key " ,
	" H Key " ,
	" I Key " ,
	" J Key " ,
	" K Key " ,
	" L Key " ,
	" M Key " ,
	" N Key " ,
	" O Key " ,
	" P Key " ,
	" Q Key " ,
	" R Key " ,
	" S Key " ,
	" T Key " ,
	" U Key " ,
	" V Key " ,
	" W Key " ,
	" Y Key " ,
	" Z Key " ,
	" X Key " ,
	"RETURN Enter key",
	"ESCAPE Esc key",
	"SPACE Space bar",
	"BACK Backspace key",
	"TAB Tab key",
	"UP Up Arrow key",
	"DOWN Down Arrow key",
	"LEFT Left Arrow key",
	"RIGHT Right Arrow key",
	"CAPITAL Caps Lock key",
	"NUMLOCK Num Lock key",
	"SCROLL Scroll Lock key",
	"INSERT Insert key",
	"DELETE Delete key",
	"HOME Home key",
	"END End key",
	"PRIOR Page Up key",
	"NEXT Page Down key",
	"SNAPSHOT Print Screen key",
	"HELP Help key",
	"PRINT Print key (keyboard-specific)",
	"SELECT Select key",
	"NUMPAD0 0 key (numeric keypad)",
	"NUMPAD1 1 key (numeric keypad)",
	"NUMPAD2 2 key (numeric keypad)",
	"NUMPAD3 3 key (numeric keypad)",
	"NUMPAD4 4 key (numeric keypad)",
	"NUMPAD5 5 key (numeric keypad)",
	"NUMPAD6 6 key (numeric keypad)",
	"NUMPAD7 7 key (numeric keypad)",
	"NUMPAD8 8 key (numeric keypad)",
	"NUMPAD9 9 key (numeric keypad)",
	"MULTIPLY Multiply key (numeric keypad)",
	"DIVIDE Divide key (numeric keypad)",
	"ADD Add key (numeric keypad)",
	"SUBTRACT Subtract key (numeric keypad)",
	"SEPARATOR Separator key (numeric keypad)",
	"DECIMAL Decimal key (numeric keypad)",
	"F1 key",
	"F2 key",
	"F3 key",
	"F4 key",
	"F5 key",
	"F6 key",
	"F7 key",
	"F8 key",
	"F9 key",
	"F10 key",
	"F11 key",
	"F12 key",
	"F13 key",
	"F14 key",
	"F15 key",
	"F16 key",
	"F17 key",
	"F18 key",
	"F19 key",
	"F20 key",
	"F21 key",
	"F22 key",
	"F23 key",
	"F24 key",
	"ScreenLog",
	"Wype³nij formularz",
	"Losuj dane osobowe",
	"Ukryj okno EventBot",
    "Poka¿ okno EventBot",
    "Zamknij okno EventBot",
    "Zapisz dane osobowe do pliku",
    "Zapisz dane logowania do pliku",
    "£aduj dane osobowe/logowania z pliku"
};


void EventBotFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxSaveFileDialog1 =  new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("*.evb*"), wxSAVE);

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_PLIK_1001_Mnu_Obj = new wxMenu(0);
	ID_MNU_PLIK_1001_Mnu_Obj->Append(ID_MNU_NOWY_1002, wxT("Nowy"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PLIK_1001_Mnu_Obj->Append(ID_MNU_OTW_RZ_1003, wxT("Otwórz"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PLIK_1001_Mnu_Obj->Append(ID_MNU_ZAPISZ_1004, wxT("Zapisz"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PLIK_1001_Mnu_Obj->Append(ID_MNU_ZAPISZJAKO_1005, wxT("Zapisz jako"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_PLIK_1001_Mnu_Obj, wxT("Plik"));
	
	wxMenu *ID_MNU_OPCJE_1044_Mnu_Obj = new wxMenu(0);
	ID_MNU_OPCJE_1044_Mnu_Obj->Append(ID_MNU_OTW_RZFOLDERLOGS_1045, wxT("Otwórz folder Logs"), wxT(""), wxITEM_NORMAL);
	ID_MNU_OPCJE_1044_Mnu_Obj->Append(ID_MNU_UKRYJOKNO_1051, wxT("Ukryj okno"), wxT(""), wxITEM_NORMAL);
	ID_MNU_OPCJE_1044_Mnu_Obj->Append(ID_MNU_POMOC_1046, wxT("Pomoc"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_OPCJE_1044_Mnu_Obj, wxT("Opcje"));
	SetMenuBar(WxMenuBar1);

	SecurityTimer = new wxTimer();
	SecurityTimer->SetOwner(this, ID_SECURITYTIMER);
	SecurityTimer->Start(100);

	WxOpenFileDialog1 =  new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("*.evb*"), wxOPEN);

	SteepTimer = new wxTimer();
	SteepTimer->SetOwner(this, ID_STEEPTIMER);

	wxArrayString arrayStringFor_ActionChoiceDialog;
	arrayStringFor_ActionChoiceDialog.Add(wxT("Prze³¹czaj okna - ALT+TAB"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Prze³¹czaj okna - WIN+TAB - dla Wista i 7"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Zamknij aktywne okno - ALT+F4"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Zamknij system - zamyka Windowsa"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Uruchom ponownie - powownie uruchamia Windowsa"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Uœpij - usypia Windowsa"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wyloguj - wylogowywuje z konta Windows"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Kliknij lewy przycisk myszy"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Kliknij prawy przycisk myszy"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Kliknij œrodkowy przycisk myszy"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Dwuktotnie kliknij lewy przycisk myszy"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Dwuktotnie kliknij prawy przycisk myszy"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Dwuktotnie kliknij œrodkowy przycisk myszy"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Scroll w górê"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Scroll w dó³"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Przesuñ mysz na pozycjê:"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst ( wolno )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst ( œrednio )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst ( szybko )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst ( b. szybko )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst formatowany ( wolno )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst formatowany ( œredno )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst formatowany ( szybko )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wypisz na klawiaturze tekst formatowany ( b. szybko )"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Otwórz dowolny plik ( w domyœlnym programie ) w tym .exe"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SHIFT Shift key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SHIFT Shift key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SHIFT Shift key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LSHIFT Left Shift key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LSHIFT Left Shift key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LSHIFT Left Shift key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RSHIFT Right Shift key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RSHIFT Right Shift key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RSHIFT Right Shift key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("CONTROL Ctrl key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("CONTROL Ctrl key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("CONTROL Ctrl key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LCONTROL Left Ctrl key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LCONTROL Left Ctrl key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LCONTROL Left Ctrl key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RCONTROL Right Ctrl key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RCONTROL Right Ctrl key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RCONTROL Right Ctrl key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("MENU Alt key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("MENU Alt key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("MENU Alt key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LMENU Left Alt key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LMENU Left Alt key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LMENU Left Alt key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RMENU Right Alt key - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RMENU Right Alt key - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RMENU Right Alt key - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LWIN Left Windows key (Microsoft keyboard) - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LWIN Left Windows key (Microsoft keyboard) - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LWIN Left Windows key (Microsoft keyboard) - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RWIN Right Windows key (Microsoft keyboard) - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RWIN Right Windows key (Microsoft keyboard) - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RWIN Right Windows key (Microsoft keyboard) - puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("APPS Applications key (Microsoft keyboard) - kliknij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("APPS Applications key (Microsoft keyboard) - naciœnij"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("APPS Applications key (Microsoft keyboard) – puœæ"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("A Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("B Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("C Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("D Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("E Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("G Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("H Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("I Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("J Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("K Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("L Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("M Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("N Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("O Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("P Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Q Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("R Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("S Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("T Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("U Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("V Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("W Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Y Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Z Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("X Key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RETURN Enter key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("ESCAPE Esc key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SPACE Space bar"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("BACK Backspace key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("TAB Tab key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("UP Up Arrow key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("DOWN Down Arrow key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("LEFT Left Arrow key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("RIGHT Right Arrow key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("CAPITAL Caps Lock key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMLOCK Num Lock key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SCROLL Scroll Lock key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("INSERT Insert key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("DELETE Delete key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("HOME Home key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("END End key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("PRIOR Page Up key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NEXT Page Down key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SNAPSHOT Print Screen key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("HELP Help key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("PRINT Print key (keyboard-specific)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SELECT Select key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD0 0 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD1 1 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD2 2 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD3 3 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD4 4 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD5 5 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD6 6 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD7 7 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD8 8 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("NUMPAD9 9 key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("MULTIPLY Multiply key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("DIVIDE Divide key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("ADD Add key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SUBTRACT Subtract key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("SEPARATOR Separator key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("DECIMAL Decimal key (numeric keypad)"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F1 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F2 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F3 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F4 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F5 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F6 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F7 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F8 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F9 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F10 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F11 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F12 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F13 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F14 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F15 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F16 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F17 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F18 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F19 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F20 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F21 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F22 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F23 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("F24 key"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("ScreenLog"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Wype³nij formularz"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Losuj dane osobowe"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Ukryj okno EventBot"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Poka¿ okno EventBot"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Zamknij okno EventBot"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Zapisz dane osobowe do pliku"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("Zapisz dane logowania do pliku"));
	arrayStringFor_ActionChoiceDialog.Add(wxT("£aduj dane osobowe/logowania z pliku"));
	ActionChoiceDialog =  new wxSingleChoiceDialog(this, wxT(""), wxT("Single Choice List"), arrayStringFor_ActionChoiceDialog,NULL);

	NewNameDialog =  new wxTextEntryDialog( this,wxT(""), wxT("Podaj nazwê kroku"), wxT("") ,wxOK | wxCANCEL | wxCENTRE);

	RenameDialog =  new wxTextEntryDialog( this,wxT(""), wxT("Podaj now¹ nazwê kroku"), wxT("") ,wxOK | wxCANCEL | wxCENTRE);

	PosChangeTimer = new wxTimer();
	PosChangeTimer->SetOwner(this, ID_POSCHANGETIMER);

	GaugeTimer = new wxTimer();
	GaugeTimer->SetOwner(this, ID_GAUGETIMER);
	GaugeTimer->Start(100);

	OrderActionControl = new wxSpinButton(this, ID_WXSPINBUTTON2, wxPoint(213, 19), wxSize(10, 140), wxSP_VERTICAL, wxT("OrderActionControl"));
	OrderActionControl->SetRange(0,100);
	OrderActionControl->SetValue(0);

	OrderListControl = new wxSpinButton(this, ID_WXSPINBUTTON1, wxPoint(10, 19), wxSize(10, 297), wxSP_VERTICAL, wxT("OrderListControl"));
	OrderListControl->SetRange(0,100);
	OrderListControl->SetValue(0);

	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, wxT("WxCheckBox1"), wxPoint(822, 133), wxSize(97, 17), 0, wxDefaultValidator, wxT("WxCheckBox1"));
	WxCheckBox1->Show(false);
	WxCheckBox1->Enable(false);

	RangeEdit = new wxTextCtrl(this, ID_WXEDIT3, wxT(""), wxPoint(10, 409), wxSize(270, 23), wxTE_READONLY, wxDefaultValidator, wxT("RangeEdit"));
	RangeEdit->SetForegroundColour(wxColour(wxT("LIGHT GREY")));

	WxGauge1 = new wxGauge(this, ID_WXGAUGE1, 1000, wxPoint(291, 409), wxSize(208, 23), wxGA_HORIZONTAL, wxDefaultValidator, wxT("WxGauge1"));
	WxGauge1->SetRange(1000);
	WxGauge1->SetValue(0);

	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, wxT("Cycliczny co:"), wxPoint(215, 299), wxDefaultSize, 0, wxT("WxStaticText4"));

	DelaySpinCtrl = new wxSpinCtrl(this, ID_WXSPINCTRL2, wxT("10"), wxPoint(419, 322), wxSize(80, 24), wxSP_ARROW_KEYS, 10, 10000000, 10);

	wxArrayString arrayStringFor_TypeChoice;
	arrayStringFor_TypeChoice.Add(wxT("Zwyk³y"));
	arrayStringFor_TypeChoice.Add(wxT("Startowy"));
	arrayStringFor_TypeChoice.Add(wxT("Cykliczny"));
	arrayStringFor_TypeChoice.Add(wxT("Koñcowy"));
	TypeChoice = new wxChoice(this, ID_WXCHOICE1, wxPoint(419, 270), wxSize(80, 23), arrayStringFor_TypeChoice, 0, wxDefaultValidator, wxT("TypeChoice"));
	TypeChoice->SetSelection(0);

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, wxT("OpóŸnienie po kroku ( w ms ):"), wxPoint(215, 325), wxDefaultSize, 0, wxT("WxStaticText3"));

	RangeEditStatic = new wxTextCtrl(this, ID_WXEDIT2, wxT(""), wxPoint(10, 379), wxSize(270, 23), 0, wxDefaultValidator, wxT("RangeEditStatic"));

	FileMemo = new wxTextCtrl(this, ID_WXMEMO1, wxEmptyString, wxPoint(2, 472), wxSize(18230, 169), wxTE_MULTILINE, wxDefaultValidator, wxT("FileMemo"));
	FileMemo->SetMaxLength(0);
	FileMemo->Show(false);
	FileMemo->SetFocus();
	FileMemo->SetInsertionPointEnd();

	Stop = new wxButton(this, ID_WXBUTTON7, wxT("Stop"), wxPoint(400, 378), wxSize(100, 25), 0, wxDefaultValidator, wxT("Stop"));

	Start = new wxButton(this, ID_WXBUTTON6, wxT("Start"), wxPoint(290, 378), wxSize(100, 25), 0, wxDefaultValidator, wxT("Start"));

	CycleSpinCtrl = new wxSpinCtrl(this, ID_WXSPINCTRL1, wxT("10"), wxPoint(419, 295), wxSize(80, 24), wxSP_ARROW_KEYS, 1, 10000000, 10);

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, wxT("Typ kroku:"), wxPoint(215, 274), wxDefaultSize, 0, wxT("WxStaticText2"));

	WxStaticBox5 = new wxStaticBox(this, ID_WXSTATICBOX5, wxT("Wykonywanie sekwencji ze zmiennym parametrem"), wxPoint(3, 356), wxSize(502, 84));

	LinkEdit = new wxTextCtrl(this, ID_WXEDIT1, wxT("Nic do wypisania"), wxPoint(213, 243), wxSize(286, 23), 0, wxDefaultValidator, wxT("LinkEdit"));

	ClickText = new wxStaticText(this, ID_WXSTATICTEXT1, wxT("Klik X: 0 Y: 0"), wxPoint(215, 220), wxDefaultSize, 0, wxT("ClickText"));

	PosCange = new wxButton(this, ID_WXBUTTON5, wxT("Zmieñ"), wxPoint(419, 215), wxSize(81, 25), 0, wxDefaultValidator, wxT("PosCange"));

	DeleteAction = new wxButton(this, ID_WXBUTTON4, wxT("Usuñ"), wxPoint(361, 164), wxSize(139, 25), 0, wxDefaultValidator, wxT("DeleteAction"));

	AddAction = new wxButton(this, ID_WXBUTTON3, wxT("Dodaj"), wxPoint(212, 164), wxSize(139, 25), 0, wxDefaultValidator, wxT("AddAction"));

	wxArrayString arrayStringFor_ActionList;
	ActionList = new wxListBox(this, ID_WXLISTBOX2, wxPoint(223, 20), wxSize(276, 138), arrayStringFor_ActionList, wxLB_SINGLE);

	DeleteSteep = new wxButton(this, ID_WXBUTTON2, wxT("Usuñ"), wxPoint(108, 321), wxSize(89, 25), 0, wxDefaultValidator, wxT("DeleteSteep"));

	AddSteep = new wxButton(this, ID_WXBUTTON1, wxT("Dodaj"), wxPoint(9, 321), wxSize(89, 25), 0, wxDefaultValidator, wxT("AddSteep"));

	wxArrayString arrayStringFor_SteepList;
	SteepList = new wxListBox(this, ID_WXLISTBOX1, wxPoint(20, 20), wxSize(176, 295), arrayStringFor_SteepList, wxLB_SINGLE);

	WxStaticBox3 = new wxStaticBox(this, ID_WXSTATICBOX3, wxT("Parametry akcji i kroku"), wxPoint(206, 199), wxSize(300, 154));

	WxStaticBox2 = new wxStaticBox(this, ID_WXSTATICBOX2, wxT("Lista akcji kroku"), wxPoint(206, 3), wxSize(300, 193));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, wxT("Lista kroków"), wxPoint(3, 3), wxSize(200, 350));

	SetTitle(wxT("EventBot"));
	SetIcon(Self_EventBotFrm_XPM);
	SetSize(8,8,1864,690);
	Center();
	
	////GUI Items Creation End
	
	wxImage::AddHandler(new wxJPEGHandler);
	
	CreateDirectory( GetArgv(0) + "Logs", NULL);
	
	// Ustewienia okna
	
    wxSize WindowSize = GetBestSize();
	
	WindowSize.x += 3;
	WindowSize.y += 3;

    SetSize( WindowSize );
    Center();
    
    SetBackgroundColour(wxColour(240,240,240));
    
    //SetFocus();
    
    ////////////////////////////////////////////////
    
    // przyznawanie uprawnien do zamykania systemu itp.
    
    HANDLE hToken; 
    TOKEN_PRIVILEGES tkp; 
    OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | 
    TOKEN_QUERY, &hToken); 
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
    tkp.PrivilegeCount = 1; 
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
    
    // przyznawanie uprawnien end
    
    // odzcyt ustawien
 
    FileMemo->LoadFile( GetArgv(0) + "config.cfg" );
    
    MainFileName = FileMemo->GetLineText(0);
    MainFilePath = FileMemo->GetLineText(1);
    
    wxPoint WindowPosition;
    
    WindowPosition.x = atoi( FileMemo->GetLineText(2) );
    WindowPosition.y = atoi( FileMemo->GetLineText(3) ); 
    
    SetPosition( WindowPosition ); /////////////////////////////////////
    
    AutoRun =            atoi( FileMemo->GetLineText(4) ); 
    ManualScreenCouter = atoi( FileMemo->GetLineText(5) ); 
    
    SteepsAmount = 0;
    
    if ( GetArgv(1).IsEmpty() && wxFileExists( MainFilePath ) && FileMemo->LoadFile( MainFilePath ) )
    {
        SetTitle( "EventBot - [ " + MainFileName + " ] - " + MainFilePath );
            
        ReLoadSteepList();
        ReLoadActionList(0);
            
        ReLoadSteep(0);
        ReLoadAction(0);
        
        RangeEditStatic->SetValue( FileMemo->GetLineText(0) );
        RangeEdit->Clear();
    }
    else if ( !GetArgv(1).IsEmpty() && wxFileExists( GetArgv(1) ) && FileMemo->LoadFile( GetArgv(1) ) )
    {
        MainFilePath = GetArgv(1);
        WxOpenFileDialog1->SetPath( GetArgv(1) );
        MainFileName = WxOpenFileDialog1->GetFilename();
        
        SetTitle( "EventBot - [ " + MainFileName + " ] - " + MainFilePath );
            
        ReLoadSteepList();
        ReLoadActionList(0);
            
        ReLoadSteep(0);
        ReLoadAction(0);
        
        RangeEditStatic->SetValue( FileMemo->GetLineText(0) );
        RangeEdit->Clear();
        
    } 
    else 
    {
        FileMemo->Clear();
        FileMemo->AppendText("\n");
    }
    
    /*MainFilePath = WxOpenFileDialog1->GetPath();
    MainFileName = WxOpenFileDialog1->GetFilename();*/
    
    MyData.AgeMin = 20;
    MyData.AgeMax = 60;
    MyData.HouseNoMin = 1;
    MyData.HouseNoMax = 60;
    MyData.PasswordLen = 15;
    
    MyData.MailServer = "migmail.pl";
    
    MyData.LoadRandData();
	
	FormatValue = 0;
	SteepsAmount = 0;
	LoopCounter = 0;
	SteepCounter = 0;
		
	FreeRunning = false;
		
	StartPause = false;
	IsStop = true;
		
	GaugeCounter = 0;
	
	// dodanie taska
	//wxIcon MyIco;
	
    MyTaskBar = new MyTaskBarIcon();
    MyTaskBar->SetIcon( GetIcon(), "EventBot" );
    
    MyMessageBox = new MyMessageDlg(this);
    //MyMessageBox->ShowMessage( MAIN_WINDOW_CENTER, "Zapisano zmiany" );
    
    WindowPosition = GetPosition();
    
    // rejestracja hotkeyów
    
    RegisterHotKey(1, wxMOD_SHIFT | wxMOD_CONTROL, VK_SPACE); // pokaz ukryj
    RegisterHotKey(2, wxMOD_SHIFT | wxMOD_CONTROL, 'Z'); // exit
    RegisterHotKey(3, wxMOD_SHIFT | wxMOD_CONTROL, VK_SNAPSHOT); // printsreen
    RegisterHotKey(4, wxMOD_SHIFT | wxMOD_CONTROL, 'F'); // printsreen folder
    RegisterHotKey(5, wxMOD_SHIFT | wxMOD_CONTROL, 'P'); // play pause
    RegisterHotKey(6, wxMOD_SHIFT | wxMOD_CONTROL, 'S'); // stop
    
    
}

void EventBotFrm::CloseApplication()
{
    FileMemo->Clear();
    
	FileMemo->AppendText( MainFileName + "\n" );
	FileMemo->AppendText( MainFilePath + "\n" );
	FileMemo->AppendText( wxString::Format( "%d\n", WindowPosition.x   ) ); // poz okna x
	FileMemo->AppendText( wxString::Format( "%d\n", WindowPosition.y   ) ); // poz okna y
	FileMemo->AppendText( wxString::Format( "%d\n", AutoRun            ) ); // czy po zal¹czeniu od razu idzie
	FileMemo->AppendText( wxString::Format( "%d\n", ManualScreenCouter ) ); // licznik rêczych sreenow
	
	FileMemo->SaveFile( GetArgv(0) + "config.cfg" );
    
    delete  MyTaskBar;
    Destroy();
    
}

void EventBotFrm::OnClose(wxCloseEvent& event)
{
	CloseApplication();
}

int EventBotFrm::GetFirstSteepLineNo( int SteepNo )
{
    int EditLine = 1;  // przesuniecie o 1 bo 1 linia zawiera teraz linie z parametrami
    
    for ( int i = 0; i < SteepNo; i++ )
	{
        EditLine += 5;
        EditLine += atoi( FileMemo->GetLineText( EditLine - 1 ) ) * 4;  // mamay pierwsz¹ linie z danymi czyli nazwe
    }
    
    return EditLine;
}

int EventBotFrm::GetFirstActionLineNo( int SteepNo, int ActionNo )
{
    int EditLine = GetFirstSteepLineNo( SteepNo );
    
    EditLine += 5;
    EditLine += ActionNo * 4; // mamay pierwsz¹ linie z danymi czyli nazwe Akcji
    
    return EditLine;
}

int EventBotFrm::GetLastSteepLineNo( int SteepNo )
{
    int EditLine = 1;   // przesuniecie o 1 bo 1 linia zawiera teraz linie z parametrami
    SteepNo++;
    
    for ( int i = 0; i < SteepNo; i++ )
	{
        EditLine += 5;
        EditLine += atoi( FileMemo->GetLineText( EditLine - 1 ) ) * 4;  // mamay pierwsz¹ linie z danymi czyli nazwe
    }
    
    return EditLine - 1;
}

int EventBotFrm::GetLastActionLineNo( int SteepNo, int ActionNo )
{
    int EditLine = GetFirstSteepLineNo( SteepNo );
    ActionNo++;
    
    EditLine += 5;
    EditLine += ActionNo * 4; // mamay pierwsz¹ linie z danymi czyli nazwe Akcji
    
    return EditLine - 1;
}

void EventBotFrm::ReLoadSettings()
{
}

void EventBotFrm::ReLoadSteep( int SteepNo )
{
	int EditLine = GetFirstSteepLineNo( SteepNo );
    
    TypeChoice->SetStringSelection( FileMemo->GetLineText( EditLine + 1 ) );
    
    CycleSpinCtrl->SetValue( atoi( FileMemo->GetLineText( EditLine + 2 ) ) );
    DelaySpinCtrl->SetValue( atoi( FileMemo->GetLineText( EditLine + 3 ) ) );
}

void EventBotFrm::ReLoadAction( int ActionNo )
{
    int Selection = SteepList->GetSelection();
    
    wxString String;
    int EditLine;
    
    if ( ActionList->GetSelection() >= 0 )
    {
        EditLine = GetFirstActionLineNo( Selection, ActionNo );
        
        String.Printf( "Klik X: %d Y: %d", atoi( FileMemo->GetLineText( EditLine + 1 ) ),  atoi( FileMemo->GetLineText( EditLine + 2 ) )  );
        ClickText->SetLabel( String );
    
        LinkEdit->SetValue( FileMemo->GetLineText( EditLine + 3 ) );
    }
    else    
    {
        ClickText->SetLabel( "Klik X: 0 Y: 0" );
        LinkEdit->Clear();
    }
}

void EventBotFrm::ReLoadSteepList()
{
	int Line = GetFirstSteepLineNo(0);
	SteepsAmount = 0;
	
	SteepList->Clear();

	while ( Line < FileMemo->GetNumberOfLines() - 1 )
	{
        SteepList->AppendString( FileMemo->GetLineText( Line ) );
        
        Line += 5;
        Line += atoi( FileMemo->GetLineText( Line - 1 ) ) * 4;
        
        SteepsAmount++;
    }
    
    SteepList->SetSelection(0);
}

void EventBotFrm::ReLoadActionList( int SteepNo )
{
    int ActionAmount = 0;
	int EditLine = GetFirstSteepLineNo( SteepNo ) + 5;
	
	ActionList->Clear();
    
    ActionAmount = atoi( FileMemo->GetLineText( EditLine - 1 ) );
    
    for ( int i = 0; i < ActionAmount; i++ )
	{   
        ActionList->AppendString( ActionNames[ atoi( FileMemo->GetLineText( EditLine ) ) ] );
        
        EditLine += 4;
    }
    
    ActionList->SetSelection(0);
}

void EventBotFrm::RemoveMemoLines( int FirstLine, int LastLine )
{
    int FirstChar = 0;
	int LastChar = 0;
    
    for ( int i = 0; i < FirstLine; i++ )
	{
        FirstChar += FileMemo->GetLineLength( i ) + 2;
    }
    
    for ( int i = 0; i <= LastLine; i++ )
	{
        LastChar += FileMemo->GetLineLength( i ) + 2;
    }
    
    FileMemo->Remove( FirstChar, LastChar );
}

void EventBotFrm::ReplaceMemoLine( int LineNo, wxString Text )
{
    int FirstChar = 0;
	int LastChar = 0;
    
    for ( int i = 0; i < LineNo; i++ )
	{
        FirstChar += FileMemo->GetLineLength( i ) + 2;
    }
    
    LastChar = FirstChar + FileMemo->GetLineLength( LineNo );

    FileMemo->Replace( FirstChar, LastChar, Text );
}

void EventBotFrm::ReplaceMemoLines( int FirstLine, int LastLine, wxString Text )
{
    int FirstChar = 0;
	int LastChar = 0;
    
    for ( int i = 0; i < FirstLine; i++ )
	{
        FirstChar += FileMemo->GetLineLength( i ) + 2;
    }
    
    for ( int i = 0; i <= LastLine; i++ )
	{
        LastChar += FileMemo->GetLineLength( i ) + 2;
    }
    
    FileMemo->Replace( FirstChar, LastChar - 2, Text );
}

wxString EventBotFrm::GetMemoLines( int FirstLine, int LastLine )
{
    wxString String;
    String.Clear();

    for ( int i = FirstLine; i <= LastLine; i++ )
	{
        String += FileMemo->GetLineText( i ) + "\n";
    }
    
    return String;
}

int EventBotFrm::GetFormatValue() // koncepcja ok 
{
    wxString String;
    String.Clear();
    
    wxString OtherRange;
    OtherRange.Clear();
    
    wxString Number;
    Number.Clear();
    
    int StartNumber = 0;
    int EndNumber = 0;
    int i = 0;
    
    String = RangeEdit->GetValue();
    
    if ( String.IsEmpty() ) return -1;
    
    while ( String[i] != '-' && String.Len() > i )
    {
        Number += String[i];
        i++;
    }
 
    StartNumber = atoi( Number );
    Number.Clear();
    
    i++;
    while ( String[i] != ',' && String.Len() > i)
    {
        Number += String[i];
        i++;
    }
    
    EndNumber = atoi( Number );
    
    OtherRange = String.SubString( i + 1, String.Len() - 1 );
    String.Clear();

    if ( StartNumber < EndNumber ) { String.Printf( "%d-%d,", StartNumber + 1, EndNumber ); }
    String += OtherRange;

    RangeEdit->SetValue( String );
    
    return StartNumber;
}

void EventBotFrm::MakeSteep( int SteepNo, int LoopNo, bool End )
{
	int EditLine = GetFirstSteepLineNo( SteepNo );
	
	wxString SteepType;
	SteepType.Clear();
	int SteepCycle = 0;
	int SteepDelay = 0;
    int ActionAmount = 0;
    
    int ActionNo = 0;
    int ClickX = 0;
    int ClickY = 0;
    wxString Text;
    
    SteepType = FileMemo->GetLineText( EditLine + 1 );
    SteepCycle = atoi( FileMemo->GetLineText( EditLine + 2 ) );
    SteepDelay = atoi( FileMemo->GetLineText( EditLine + 3 ) );
    ActionAmount = atoi( FileMemo->GetLineText( EditLine + 4 ) );
    
    EditLine += 5;  // nazwa akcji

    if
    (   
        ( SteepType == "Zwyk³y" ) ||
        ( SteepType == "Startowy" && LoopNo == 0 ) ||
        ( SteepType == "Cykliczny" && LoopNo % SteepCycle == 0 ) ||
        ( SteepType == "Koñcowy" && End )
    )
    {
        for ( int i = 0; i < ActionAmount; i++ )
	    {
            ActionNo = atoi( FileMemo->GetLineText( EditLine ) );
            ClickX = atoi( FileMemo->GetLineText( EditLine + 1 ) );
            ClickY = atoi( FileMemo->GetLineText( EditLine + 2 ) );
            Text = FileMemo->GetLineText( EditLine + 3 );
        
            ActionExecute( ActionNo, ClickX, ClickY, Text );
        
            EditLine += 4;
        }
        
        SteepTimer->Start( SteepDelay, true );
        GaugeCounter = 0;
    }
    else
    {
        SteepTimer->Start( 50, true );
    }
}

void EventBotFrm::Print( wxString Text, int CharDelay )
{
    int i;
    char c;
    bool IsShift,IsAlt;
    int Counter = 0;
    int RndVal = 0;
    
    wxString Temp;
    wxString Temp2;
    
    for ( i = 0; i < Text.Len(); i++ )
    {
        c = Text[i];
        
        if ( c == '#' )
        {
            switch( Text[i+1] )
            {
                case 'i':  Temp += MyData.Name; break;
                case 'n':  Temp += MyData.SurName; break;
                case 'm':  Temp += MyData.City; break;
                case 'k':  Temp += MyData.PostCode; break;
                case 'u':  Temp += MyData.Street; break;
                case 'd':  Temp += MyData.HouseNo; break;
                case 'l':  Temp += MyData.Nick; break;
                case 'p':  Temp += MyData.Mail; break;
                case 'h':  Temp += MyData.Password; break;
                case 'w':  Temp += MyData.Age; break;  
                case 't':  Temp += MyData.Phone; break; 
                
                // z innej beczki
                
                case 'e':  keybd_event(VK_RETURN,0,0,0);   Sleep(20);  keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
                case 's':  keybd_event(VK_SPACE,0,0,0);   Sleep(20);  keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0);    Sleep(20);  break;
                case 'c':  
                    
                    i+=3;
                    
                    while ( Text[i] != ')' )
                    {
                        Temp2 += Text[i];
                        i++;
                    }
                    i--;
                    
                    Counter = Temp2.Find('-');
                    RndVal = MyData.RandomValue( wxAtoi( Temp2.Left( Counter ) ), wxAtoi( Temp2.Right( Temp2.Len() - Counter - 1 ) ) );
                    
                    keybd_event(VK_RETURN,0,0,0);   Sleep(20);  keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);    Sleep(20);
                    
                    for ( int q = 0; q < RndVal; q++ )
                    {
                        keybd_event(VK_DOWN,0,0,0);   Sleep(10);  keybd_event(VK_DOWN,0,KEYEVENTF_KEYUP,0);    Sleep(10);
                    }
                    
                    keybd_event(VK_RETURN,0,0,0);   Sleep(20);  keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);    Sleep(20);
                    //MyMessageBox->ShowMessage( MAIN_WINDOW_CENTER, wxString::Format("%d", RndVal) );
                    break;
                    
                case 'r':  
                    
                    i+=3;
                    
                    while ( Text[i] != ')' )
                    {
                        Temp2 += Text[i];
                        i++;
                    }
                    i--;
                    
                    Counter = Temp2.Find('-');
                    RndVal = MyData.RandomValue( wxAtoi( Temp2.Left( Counter ) ), wxAtoi( Temp2.Right( Temp2.Len() - Counter - 1 ) ) );
                    
                    Temp += wxString::Format("%d", RndVal);
                    break;
            }
            i++;
        }
        else Temp += c;
    }
    
    Text = Temp;
    
    for ( i = 0; i < Text.Len(); i++ )
    {
        c = Text[i];
        
        if ( isupper( MyData.ConvertToLatin(Text)[i] ) || c == '@' ) 
        { 
            keybd_event(VK_LSHIFT,0,0,0);   
            Sleep(20); 
            IsShift = true;
        }
        
        for ( int a = 0; a < PolishSign.Len(); a++ ) 
        { 
            if( c == PolishSign[a] ) 
            { 
                keybd_event(VK_RMENU,0,0,0);   
                Sleep(20); 
                IsAlt = true;
            }  
        }
        	
        keybd_event( VkKeyScan( c ),0,0,0 );
        
        if ( IsAlt ) 
        { 
            keybd_event(VK_RMENU,0,KEYEVENTF_KEYUP,0);    
            Sleep(20); 
            IsAlt = false;
        }
        
        if ( IsShift ) 
        {    
            keybd_event(VK_LSHIFT,0,KEYEVENTF_KEYUP,0);   
            Sleep(20);
            IsShift = false;
        }
        
        Sleep( CharDelay );
    }	
}

void EventBotFrm::FillForm( wxString Text )
{
    wxString Temp = Text;
    int Counter = 0;
    
    if ( Temp[ Temp.Len() - 1 ] != ';' ) Temp += ';' ;
    
    while ( Temp.Len() )
    {
        Counter = Temp.Find(';');
        
        Print( Temp.Left( Counter ), 5 );
        
        Temp = Temp.Right( Temp.Len() - Counter - 1 );
        
        keybd_event(VK_TAB,0,0,0);   Sleep(20);  keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);    Sleep(20);
    }
}

void EventBotFrm::FotmatPrint( wxString Text, int CharDelay )
{
    char c;
    
    wxString Value;
    Value.Printf( "%d", FormatValue );
    
    Text.Remove( Text.Len() - Value.Len(), Text.Len() - 1 );
    
    Text += Value;
    
    for ( int i = 0; i < Text.Len(); i++ )
    {
        c = Text[i];
        
        if ( isupper(c) || c == '@' ) 
        { 
            keybd_event(VK_LSHIFT,0,0,0);   Sleep(20);
            keybd_event( VkKeyScan( c ),0,0,0 );
            keybd_event(VK_LSHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);
        }
        else keybd_event( VkKeyScan( c ),0,0,0 );
        
        Sleep( CharDelay );
    }	
}

void EventBotFrm::MoveMouse( int x, int y )
{
    SetCursorPos( x, y );
}

void EventBotFrm::LClick( int x, int y )
{
    MoveMouse( x, y );
    Sleep(20);
    
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    Sleep(20); 
    
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);    
    Sleep(20);
     
}

void EventBotFrm::ActionExecute( int ActionNo, int ClickX, int ClickY, wxString Text )
{
    POINT pozycja;	 //odczytanie aktualnej pozycji kursora myszy na ekranie
    GetCursorPos(&pozycja);	//pozycja.x pozycja.y - pozycja kursona myszy na ekranie
    
    int DeltaX = ClickX - pozycja.x;
    int DeltaY = ClickY - pozycja.y;
    
    wxBitmap Bitmap;
    wxImage  Screen;
    static int Couter = 0;
    wxString TempString;
                    
    // Get screen size
    int nWidth;// = GetSystemMetrics(SM_CXSCREEN);
    int nHeight;// = GetSystemMetrics(SM_CYSCREEN);

    // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
    HDC srcHDC;// = GetDC( GetDesktopWindow() );
    HDC destHDC;// = CreateCompatibleDC(srcHDC);
    HBITMAP hBitmap;
    
    wxTextFile MyFile;
    
    switch( ActionNo )
    {
				case	Przelaczaj_okna___ALT_TAB	:
                    
                        keybd_event(VK_MENU,0,0,0); Sleep(20); 
                        keybd_event(VK_TAB,0,0,0); Sleep(20); 
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);  Sleep(20);	
                        keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
                        break;   
                                     
				case	Przelaczaj_okna___WIN_TAB___dla_Wista_i_7	:
                    
                        keybd_event(VK_LWIN,0,0,0); Sleep(20); 
                        keybd_event(VK_TAB,0,0,0); Sleep(20); 
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0); Sleep(20);	
                        keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
                        break;
                            
				case	Zamknij_aktywne_okno___ALT_F4	:

                        keybd_event(VK_MENU,0,0,0); Sleep(20); 
                        keybd_event(VK_F4,0,0,0); Sleep(20); 
                        keybd_event(VK_F4,0,KEYEVENTF_KEYUP,0);  Sleep(20);	
                        keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);  
                        break;
                            
                case	Zamknij_system___zamyka_Windowsa	:	ExitWindowsEx(EWX_POWEROFF,0);	break;
				case	Uruchom_ponownie___powownie_uruchamia_Windowsa	:	ExitWindowsEx(EWX_REBOOT,0);	break;
				case	Uspij___usypia_Windowsa	:	SetSystemPowerState(true,true);    	break;
				case	Wyloguj___wylogowywuje_z_konta_Windows	:	ExitWindowsEx(EWX_LOGOFF,0);	break;
				
                case    Kliknij_lewy_przycisk_myszy:      SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);    Sleep(20);   break;
                case    Kliknij_prawy_przycisk_myszy:     SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);  Sleep(20);   break;      
                case	Kliknij_srodkowy_przycisk_myszy	:	SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);   Sleep(20);	break;
				case	Dwuktotnie_kliknij_lewy_przycisk_myszy	:
                            SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);  Sleep(20);	
                            SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);  Sleep(20);  break;
				case	Dwuktotnie_kliknij_prawy_przycisk_myszy	:
				            SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);  Sleep(20);
				            SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);  Sleep(20);   break;
				case	Dwuktotnie_kliknij_srodkowy_przycisk_myszy	:
				            SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);   Sleep(20);
				            SetCursorPos(ClickX,ClickY);   mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0); Sleep(20); mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);   Sleep(20);	break;
				
                case	Scroll_w_gore	:	mouse_event(MOUSEEVENTF_WHEEL,0,0,120,0); Sleep(20);	break;
				case	Scroll_w_dol	:	mouse_event(MOUSEEVENTF_WHEEL,0,0,-120,0); Sleep(20);	break;
				
                /*case    Porusz_mysza_w_gore:       mouse_event(MOUSEEVENTF_MOVE,0,-10,0,0);   break;
                case    Porusz_mysza_w_dol:        mouse_event(MOUSEEVENTF_MOVE,0,10,0,0);   break;
                case    Porusz_mysza_w_lewo:       mouse_event(MOUSEEVENTF_MOVE,-10,0,0,0);   break;
                case    Porusz_mysza_w_prawo:      mouse_event(MOUSEEVENTF_MOVE,10,0,0,0);   break; */
                
                /*case    Porusz_mysza_w_gore:       SetCursorPos(pozycja.x,pozycja.y-=10);   break;
                case    Porusz_mysza_w_dol:        SetCursorPos(pozycja.x,pozycja.y+=10);   break;
                case    Porusz_mysza_w_lewo:       SetCursorPos(pozycja.x-=10,pozycja.y);   break;
                case    Porusz_mysza_w_prawo:      SetCursorPos(pozycja.x+=10,pozycja.y);   break; */
                
                case	Przesun_mysz_na_pozycje	:	SetCursorPos(ClickX,ClickY);   break;
                
                
                case	Wypisz_na_klawiaturze_tekst_wolno	:  if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); Print( Text, 20 );  break;
                case	Wypisz_na_klawiaturze_tekst_srednio	:  if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); Print( Text, 10 );  break;
                case	Wypisz_na_klawiaturze_tekst_szybko	:  if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); Print( Text, 5 );  break;
                case	Wypisz_na_klawiaturze_tekst_bszybko	:  if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); Print( Text, 2 );  break;
                
                case	Wypisz_na_klawiaturze_tekst_formatowany_wolno	:	if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); FotmatPrint( Text, 20 ); 	  break;
                case	Wypisz_na_klawiaturze_tekst_formatowany_sredno	:	if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); FotmatPrint( Text, 10 ); 	  break;
                case	Wypisz_na_klawiaturze_tekst_formatowany_szybko	:	if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); FotmatPrint( Text, 5 ); 	  break;
                case	Wypisz_na_klawiaturze_tekst_formatowany_bszybko	:	if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY ); Sleep(20); FotmatPrint( Text, 2 ); 	  break;

				case	Otworz_program___otwiera_dowolny_wybrany_program_z_dysku	:	ShellExecute(NULL, "open", Text, NULL, NULL, SW_SHOWNORMAL );	break;
				        
                case	SHIFT_Shift_key___kliknij	:	keybd_event(VK_SHIFT,0,0,0);   Sleep(20);  keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	SHIFT_Shift_key___nacisnij	:	keybd_event(VK_SHIFT,0,0,0);   Sleep(20); break;
				case	SHIFT_Shift_key___pusc	:	keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	LSHIFT_Left_Shift_key___kliknij	:	keybd_event(VK_LSHIFT,0,0,0);   Sleep(20);  keybd_event(VK_LSHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	LSHIFT_Left_Shift_key___nacisnij	:	keybd_event(VK_LSHIFT,0,0,0);   Sleep(20);  break;
				case	LSHIFT_Left_Shift_key___pusc	:	keybd_event(VK_LSHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	RSHIFT_Right_Shift_key___kliknij	:	keybd_event(VK_RSHIFT,0,0,0);   Sleep(20);  keybd_event(VK_RSHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	RSHIFT_Right_Shift_key___nacisnij	:	keybd_event(VK_RSHIFT,0,0,0);   Sleep(20); break;
				case	RSHIFT_Right_Shift_key___pusc	:	keybd_event(VK_RSHIFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	CONTROL_Ctrl_key___kliknij	:	keybd_event(VK_CONTROL,0,0,0);   Sleep(20);  keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	CONTROL_Ctrl_key___nacisnij	:	keybd_event(VK_CONTROL,0,0,0);   Sleep(20);   break;
				case	CONTROL_Ctrl_key___pusc	:	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	LCONTROL_Left_Ctrl_key___kliknij	:	keybd_event(VK_LCONTROL,0,0,0);   Sleep(20);  keybd_event(VK_LCONTROL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	LCONTROL_Left_Ctrl_key___nacisnij	:	keybd_event(VK_LCONTROL,0,0,0);   Sleep(20); break;
				case	LCONTROL_Left_Ctrl_key___pusc	:	keybd_event(VK_LCONTROL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	RCONTROL_Right_Ctrl_key___kliknij	:	keybd_event(VK_RCONTROL,0,0,0);   Sleep(20);  keybd_event(VK_RCONTROL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	RCONTROL_Right_Ctrl_key___nacisnij	:	keybd_event(VK_RCONTROL,0,0,0);   Sleep(20);    break;
				case	RCONTROL_Right_Ctrl_key___pusc	:	keybd_event(VK_RCONTROL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	MENU_Alt_key___kliknij	:	keybd_event(VK_MENU,0,0,0);   Sleep(20);  keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	MENU_Alt_key___nacisnij	:	keybd_event(VK_MENU,0,0,0);   Sleep(20);   break;
				case	MENU_Alt_key___pusc	:	keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	LMENU_Left_Alt_key___kliknij	:	keybd_event(VK_LMENU,0,0,0);   Sleep(20);  keybd_event(VK_LMENU,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
                case	LMENU_Left_Alt_key___nacisnij	:	keybd_event(VK_LMENU,0,0,0);   Sleep(20); break;
				case	LMENU_Left_Alt_key___pusc	:	keybd_event(VK_LMENU,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	RMENU_Right_Alt_key___kliknij	:	keybd_event(VK_RMENU,0,0,0);   Sleep(20);  keybd_event(VK_RMENU,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	RMENU_Right_Alt_key___nacisnij	:	keybd_event(VK_RMENU,0,0,0);   Sleep(20);    break;
				case	RMENU_Right_Alt_key___pusc	:	keybd_event(VK_RMENU,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	LWIN_Left_Windows_key__Microsoft_keyboard____kliknij	:	keybd_event(VK_LWIN,0,0,0);   Sleep(20);  keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	LWIN_Left_Windows_key__Microsoft_keyboard____nacisnij	:	keybd_event(VK_LWIN,0,0,0);   Sleep(20); break;
				case	LWIN_Left_Windows_key__Microsoft_keyboard____pusc	:	keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
			
            	case	RWIN_Right_Windows_key__Microsoft_keyboard____kliknij	:	keybd_event(VK_RWIN,0,0,0);   Sleep(20);  keybd_event(VK_RWIN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	RWIN_Right_Windows_key__Microsoft_keyboard____nacisnij	:	keybd_event(VK_RWIN,0,0,0);   Sleep(20);   break;
				case	RWIN_Right_Windows_key__Microsoft_keyboard____pusc	:	keybd_event(VK_RWIN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	APPS_Applications_key__Microsoft_keyboard____kliknij	:	keybd_event(VK_APPS,0,0,0);   Sleep(20);  keybd_event(VK_APPS,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	APPS_Applications_key__Microsoft_keyboard____nacisnij	:	keybd_event(VK_APPS,0,0,0);   Sleep(20); break;
				case	APPS_Applications_key__Microsoft_keyboard____pusc	:	keybd_event(VK_APPS,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
				case	A_Key	:	keybd_event(VkKeyScan('a'),0,0,0);   Sleep(10); break;
				case	B_Key	:	keybd_event(VkKeyScan('b'),0,0,0);   Sleep(10);	break;
				case	C_Key	:	keybd_event(VkKeyScan('c'),0,0,0);   Sleep(10);	break;
				case	D_Key	:	keybd_event(VkKeyScan('d'),0,0,0);   Sleep(10);	break;
				case	E_Key	:	keybd_event(VkKeyScan('e'),0,0,0);   Sleep(10);	break;
				case	F_Key	:	keybd_event(VkKeyScan('f'),0,0,0);   Sleep(10);	break;
				case	G_Key	:	keybd_event(VkKeyScan('g'),0,0,0);   Sleep(10);	break;
				case	H_Key	:	keybd_event(VkKeyScan('h'),0,0,0);   Sleep(10);	break;
				case	I_Key	:	keybd_event(VkKeyScan('i'),0,0,0);   Sleep(10);	break;
				case	J_Key	:	keybd_event(VkKeyScan('j'),0,0,0);   Sleep(10);	break;
				case	K_Key	:	keybd_event(VkKeyScan('k'),0,0,0);   Sleep(10);	break;
				case	L_Key	:	keybd_event(VkKeyScan('l'),0,0,0);   Sleep(10);	break;
				case	M_Key	:	keybd_event(VkKeyScan('m'),0,0,0);   Sleep(10);	break;
				case	N_Key	:	keybd_event(VkKeyScan('n'),0,0,0);   Sleep(10);	break;
				case	O_Key	:	keybd_event(VkKeyScan('o'),0,0,0);   Sleep(10);	break;
				case	P_Key	:	keybd_event(VkKeyScan('p'),0,0,0);   Sleep(10);	break;
				case	Q_Key	:	keybd_event(VkKeyScan('q'),0,0,0);   Sleep(10);	break;
				case	R_Key	:	keybd_event(VkKeyScan('r'),0,0,0);   Sleep(10);	break;
				case	S_Key	:	keybd_event(VkKeyScan('s'),0,0,0);   Sleep(10);	break;
				case	T_Key	:	keybd_event(VkKeyScan('t'),0,0,0);   Sleep(10);	break;
				case	U_Key	:	keybd_event(VkKeyScan('u'),0,0,0);   Sleep(10);	break;
				case	V_Key	:	keybd_event(VkKeyScan('v'),0,0,0);   Sleep(10);	break;
				case	W_Key	:	keybd_event(VkKeyScan('w'),0,0,0);   Sleep(10);	break;
				case	Y_Key	:	keybd_event(VkKeyScan('y'),0,0,0);   Sleep(10);	break;
				case	Z_Key	:	keybd_event(VkKeyScan('z'),0,0,0);   Sleep(10);	break;
				case	X_Key	:	keybd_event(VkKeyScan('x'),0,0,0);   Sleep(10);	break;
				
				
				case	RETURN_Enter_key	:	keybd_event(VK_RETURN,0,0,0);   Sleep(20);  keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	ESCAPE_Esc_key	:	keybd_event(VK_ESCAPE,0,0,0);   Sleep(20);  keybd_event(VK_ESCAPE,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	SPACE_Space_bar	:	keybd_event(VK_SPACE,0,0,0);   Sleep(20);  keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0);    Sleep(20);  break;
				case	BACK_Backspace_key	:	keybd_event(VK_BACK,0,0,0);   Sleep(20);  keybd_event(VK_BACK,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	TAB_Tab_key	:	keybd_event(VK_TAB,0,0,0);   Sleep(20);  keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
                case	UP_Up_Arrow_key	:	keybd_event(VK_UP,0,0,0);   Sleep(20);  keybd_event(VK_UP,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	DOWN_Down_Arrow_key	:	keybd_event(VK_DOWN,0,0,0);   Sleep(20);  keybd_event(VK_DOWN,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	LEFT_Left_Arrow_key	:	keybd_event(VK_LEFT,0,0,0);   Sleep(20);  keybd_event(VK_LEFT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	RIGHT_Right_Arrow_key	:	keybd_event(VK_RIGHT,0,0,0);   Sleep(20);  keybd_event(VK_RIGHT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	CAPITAL_Caps_Lock_key	:	keybd_event(VK_CAPITAL,0,0,0);   Sleep(20);  keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMLOCK_Num_Lock_key	:	keybd_event(VK_NUMLOCK,0,0,0);   Sleep(20);  keybd_event(VK_NUMLOCK,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	SCROLL_Scroll_Lock_key	:	keybd_event(VK_SCROLL,0,0,0);   Sleep(20);  keybd_event(VK_SCROLL,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	INSERT_Insert_key	:	keybd_event(VK_INSERT,0,0,0);   Sleep(20);  keybd_event(VK_INSERT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	DELETE_Delete_key	:	keybd_event(VK_DELETE,0,0,0);   Sleep(20);  keybd_event(VK_DELETE,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	HOME_Home_key	:	keybd_event(VK_HOME,0,0,0);   Sleep(20);  keybd_event(VK_HOME,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	END_End_key	:	keybd_event(VK_END,0,0,0);   Sleep(20);  keybd_event(VK_END,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	PRIOR_Page_Up_key	:	keybd_event(VK_PRIOR,0,0,0);   Sleep(20);  keybd_event(VK_PRIOR,0,KEYEVENTF_KEYUP,0);    Sleep(20);    break;
				case	NEXT_Page_Down_key	:	keybd_event(VK_NEXT,0,0,0);   Sleep(20);  keybd_event(VK_NEXT,0,KEYEVENTF_KEYUP,0);    Sleep(20); break;
				case	SNAPSHOT_Print_Screen_key	:	keybd_event(VK_SNAPSHOT,0,0,0);   Sleep(20);  keybd_event(VK_SNAPSHOT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	HELP_Help_key	:	keybd_event(VK_HELP,0,0,0);   Sleep(20);  keybd_event(VK_HELP,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	PRINT_Print_key__keyboard_specific_	:	keybd_event(VK_PRINT,0,0,0);   Sleep(20);  keybd_event(VK_PRINT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	SELECT_Select_key	:	keybd_event(VK_SELECT,0,0,0);   Sleep(20);  keybd_event(VK_SELECT,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
			
            	case	NUMPAD0_0_key__numeric_keypad_	:	keybd_event(VK_NUMPAD0,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD0,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD1_1_key__numeric_keypad_	:	keybd_event(VK_NUMPAD1,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD1,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD2_2_key__numeric_keypad_	:	keybd_event(VK_NUMPAD2,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD2,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD3_3_key__numeric_keypad_	:	keybd_event(VK_NUMPAD3,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD3,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD4_4_key__numeric_keypad_	:	keybd_event(VK_NUMPAD4,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD4,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD5_5_key__numeric_keypad_	:	keybd_event(VK_NUMPAD5,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD5,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD6_6_key__numeric_keypad_	:	keybd_event(VK_NUMPAD6,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD6,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD7_7_key__numeric_keypad_	:	keybd_event(VK_NUMPAD7,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD7,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD8_8_key__numeric_keypad_	:	keybd_event(VK_NUMPAD8,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD8,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	NUMPAD9_9_key__numeric_keypad_	:	keybd_event(VK_NUMPAD9,0,0,0);   Sleep(20);  keybd_event(VK_NUMPAD9,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
                case	MULTIPLY_Multiply_key__numeric_keypad_	:	keybd_event(VK_MULTIPLY,0,0,0);   Sleep(20);  keybd_event(VK_MULTIPLY,0,KEYEVENTF_KEYUP,0);	break;
				case	DIVIDE_Divide_key__numeric_keypad_	:	keybd_event(VK_DIVIDE,0,0,0);   Sleep(20);  keybd_event(VK_DIVIDE,0,KEYEVENTF_KEYUP,0);	break;
				case	ADD_Add_key__numeric_keypad_	:	keybd_event(VK_ADD,0,0,0);   Sleep(20);  keybd_event(VK_ADD,0,KEYEVENTF_KEYUP,0);	break;
				case	SUBTRACT_Subtract_key__numeric_keypad_	:	keybd_event(VK_SUBTRACT,0,0,0);   Sleep(20);  keybd_event(VK_SUBTRACT,0,KEYEVENTF_KEYUP,0);	break;
				case	SEPARATOR_Separator_key__numeric_keypad_	:	keybd_event(VK_SEPARATOR,0,0,0);   Sleep(20);  keybd_event(VK_SEPARATOR,0,KEYEVENTF_KEYUP,0);	break;
				case	DECIMAL_Decimal_key__numeric_keypad_	:	keybd_event(VK_DECIMAL,0,0,0);   Sleep(20);  keybd_event(VK_DECIMAL,0,KEYEVENTF_KEYUP,0);	break;
				
                case	F1_key	:	keybd_event(VK_F1,0,0,0);    Sleep(20);  keybd_event(VK_F1,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F2_key	:	keybd_event(VK_F2,0,0,0);    Sleep(20);  keybd_event(VK_F2,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F3_key	:	keybd_event(VK_F3,0,0,0);    Sleep(20);  keybd_event(VK_F3,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F4_key	:	keybd_event(VK_F4,0,0,0);    Sleep(20);  keybd_event(VK_F4,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F5_key	:	keybd_event(VK_F5,0,0,0);    Sleep(20);  keybd_event(VK_F5,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F6_key	:	keybd_event(VK_F6,0,0,0);    Sleep(20);  keybd_event(VK_F6,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F7_key	:	keybd_event(VK_F7,0,0,0);    Sleep(20);  keybd_event(VK_F7,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F8_key	:	keybd_event(VK_F8,0,0,0);    Sleep(20);  keybd_event(VK_F8,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F9_key	:	keybd_event(VK_F9,0,0,0);    Sleep(20);  keybd_event(VK_F9,0,KEYEVENTF_KEYUP,0);     Sleep(20);	break;
				case	F10_key	:	keybd_event(VK_F10,0,0,0);   Sleep(20);  keybd_event(VK_F10,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F11_key	:	keybd_event(VK_F11,0,0,0);   Sleep(20);  keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F12_key	:	keybd_event(VK_F12,0,0,0);   Sleep(20);  keybd_event(VK_F12,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F13_key	:	keybd_event(VK_F13,0,0,0);   Sleep(20);  keybd_event(VK_F13,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F14_key	:	keybd_event(VK_F14,0,0,0);   Sleep(20);  keybd_event(VK_F14,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F15_key	:	keybd_event(VK_F15,0,0,0);   Sleep(20);  keybd_event(VK_F15,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F16_key	:	keybd_event(VK_F16,0,0,0);   Sleep(20);  keybd_event(VK_F16,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F17_key	:	keybd_event(VK_F17,0,0,0);   Sleep(20);  keybd_event(VK_F17,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F18_key	:	keybd_event(VK_F18,0,0,0);   Sleep(20);  keybd_event(VK_F18,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F19_key	:	keybd_event(VK_F19,0,0,0);   Sleep(20);  keybd_event(VK_F19,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F20_key	:	keybd_event(VK_F20,0,0,0);   Sleep(20);  keybd_event(VK_F20,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F21_key	:	keybd_event(VK_F21,0,0,0);   Sleep(20);  keybd_event(VK_F21,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F22_key	:	keybd_event(VK_F22,0,0,0);   Sleep(20);  keybd_event(VK_F22,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F23_key	:	keybd_event(VK_F23,0,0,0);   Sleep(20);  keybd_event(VK_F23,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				case	F24_key	:	keybd_event(VK_F24,0,0,0);   Sleep(20);  keybd_event(VK_F24,0,KEYEVENTF_KEYUP,0);    Sleep(20);	break;
				
				case	SCREEN_LOG	:
                    
/*wxBITMAP_TYPE_INVALID 	
wxBITMAP_TYPE_BMP 	
wxBITMAP_TYPE_BMP_RESOURCE 	
wxBITMAP_TYPE_RESOURCE 	
wxBITMAP_TYPE_ICO 	
wxBITMAP_TYPE_ICO_RESOURCE 	
wxBITMAP_TYPE_CUR 	
wxBITMAP_TYPE_CUR_RESOURCE 	
wxBITMAP_TYPE_XBM 	
wxBITMAP_TYPE_XBM_DATA 	
wxBITMAP_TYPE_XPM 	
wxBITMAP_TYPE_XPM_DATA 	
wxBITMAP_TYPE_TIFF 	
wxBITMAP_TYPE_TIF 	
wxBITMAP_TYPE_TIFF_RESOURCE 	
wxBITMAP_TYPE_TIF_RESOURCE 	
wxBITMAP_TYPE_GIF 	
wxBITMAP_TYPE_GIF_RESOURCE 	
wxBITMAP_TYPE_PNG 	
wxBITMAP_TYPE_PNG_RESOURCE 	
wxBITMAP_TYPE_JPEG 	
wxBITMAP_TYPE_JPEG_RESOURCE 	
wxBITMAP_TYPE_PNM 	
wxBITMAP_TYPE_PNM_RESOURCE 	
wxBITMAP_TYPE_PCX 	
wxBITMAP_TYPE_PCX_RESOURCE 	
wxBITMAP_TYPE_PICT 	
wxBITMAP_TYPE_PICT_RESOURCE 	
wxBITMAP_TYPE_ICON 	
wxBITMAP_TYPE_ICON_RESOURCE 	
wxBITMAP_TYPE_ANI 	
wxBITMAP_TYPE_IFF 	
wxBITMAP_TYPE_TGA 	
wxBITMAP_TYPE_MACCURSOR 	
wxBITMAP_TYPE_MACCURSOR_RESOURCE 	
wxBITMAP_TYPE_ANY 


wxBMPHandler: For loading (including alpha support) and saving, always installed.
wxPNGHandler: For loading and saving. Includes alpha support.
wxJPEGHandler: For loading and saving.
wxGIFHandler: For loading and saving (see below).
wxPCXHandler: For loading and saving (see below).
wxPNMHandler: For loading and saving (see below).
wxTIFFHandler: For loading and saving. Includes alpha support.
wxTGAHandler: For loading and saving. Includes alpha support.
wxIFFHandler: For loading only.
wxXPMHandler: For loading and saving.
wxICOHandler: For loading and saving.
wxCURHandler: For loading and saving.
wxANIHandler: For loading only.*/

                    //wxImage::AddHandler(new wxJPEGHandler);  //na pocz¹tku
                    
                    /*wxBitmap Bitmap;
                    wxImage  Screen;
                    static int Couter = 0;
                    wxString TempString;*/
                    
                    // Get screen size
                    nWidth = GetSystemMetrics(SM_CXSCREEN);
                    nHeight = GetSystemMetrics(SM_CYSCREEN);

                    // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
                    srcHDC = GetDC( GetDesktopWindow() );
                    destHDC = CreateCompatibleDC(srcHDC);
                    hBitmap =CreateCompatibleBitmap(srcHDC,nWidth,nHeight);
                    SelectObject(destHDC,hBitmap); 
                    BitBlt(destHDC,0,0,nWidth,nHeight,srcHDC,0,0,SRCCOPY);

                    // Release the objects
                    ReleaseDC( GetDesktopWindow(),srcHDC);
                    DeleteDC(destHDC);


                    Bitmap.SetHBITMAP( hBitmap );
                    
                    Screen = Bitmap.ConvertToImage();
                    
                    //CreateDirectory("Logs", NULL); //na pocz¹tku
                    
                    TempString.Printf( GetArgv(0) + "Logs/ScreenLog%4d_%d.jpg", Couter, FormatValue );
                    
                    Screen.SaveFile( TempString, wxBITMAP_TYPE_JPEG );
                    
                    Couter++;
                    
	                break;
	                
	           case WYPELNIJ_FORMULARZ:
	               
	               if ( ClickX != 0 && ClickY != 0 ) LClick( ClickX, ClickY );
	               
                   FillForm(Text);
	               
	               break;
	               
	           case LOSUJ_DANE_OSOBOWE:  MyData.LoadRandData();    break;
	           
	           case UKRYJ_OKNO:  Show(false);    break;
	           case POKAZ_OKNO:  Show(true);  Iconize(false);     break;
	           case ZAMKNIJ_OKNO:  CloseApplication();     break;
	           
	           case ZAPISZ_DANE_OSOBOWE:
	               
	                if ( !wxFileExists( GetArgv(0) + "Dane osobowe.txt" ) ) 
                    {
                        MyFile.Create( GetArgv(0) + "Dane osobowe.txt" );
                        MyFile.AddLine( "Dane osobowe.txt" );
                        MyFile.Write();
                        MyFile.Close();
                    }
                        
	                MyFile.Clear();
	                MyFile.Open( GetArgv(0) + "Dane osobowe.txt" );
	               
	                MyFile.AddLine( MyData.Name );      // i
                    MyFile.AddLine( MyData.SurName );   // n
                    MyFile.AddLine( MyData.Age );       // w
                    MyFile.AddLine( MyData.City );      // m
                    MyFile.AddLine( MyData.PostCode );  // k
                    MyFile.AddLine( MyData.Street );    // u
                    MyFile.AddLine( MyData.HouseNo );   // d od dom
                    MyFile.AddLine( MyData.Nick );      // l od login
                    MyFile.AddLine( MyData.Password );  // h
                    MyFile.AddLine( MyData.Mail );      // p od poczta
                    MyFile.AddLine( MyData.Phone );     // t
                    
	                MyFile.Write();
                    MyFile.Close();
	               
	                break;
	               
	            case ZAPISZ_DANE_LOGOWANIA:
                    
                    if ( !wxFileExists( GetArgv(0) + "Dane logowania.txt" ) ) 
                    {
                        MyFile.Create( GetArgv(0) + "Dane logowania.txt" );
                        MyFile.AddLine( "Dane logowania.txt" );
                        MyFile.Write();
                        MyFile.Close();
                    }
                    
                    MyFile.Clear();
	                MyFile.Open( GetArgv(0) + "Dane logowania.txt" );
	               
                    MyFile.AddLine( MyData.Nick );      // l od login
                    MyFile.AddLine( MyData.Password );  // h
                    
	                MyFile.Write();
                    MyFile.Close();
	               
                    break;
                    
	            case LADUJ_DANE_Z_PLIKU:
                    
                    #define PARAMETR FormatValue // bylo LoopCounter
                    
                    if ( wxFileExists( Text ) ) 
                    {
                        int i;
                        
                        MyFile.Clear();
                        MyFile.Open( Text );
                        
                        if ( MyFile.GetFirstLine() == "Dane osobowe.txt" )  
                        {
                            if ( MyFile.GetLineCount() > 1 + PARAMETR * 11 + 10 ) // i + 10 to pierwsza + 10 czyli ostatnia 
                            {
                                i = 1 + PARAMETR * 11;
                            
                                MyData.Name      = MyFile.GetLine( i++ );       // i
                                MyData.SurName   = MyFile.GetLine( i++ );       // n
                                MyData.Age       = MyFile.GetLine( i++ );       // w
                                MyData.City      = MyFile.GetLine( i++ );       // m
                                MyData.PostCode  = MyFile.GetLine( i++ );       // k
                                MyData.Street    = MyFile.GetLine( i++ );       // u
                                MyData.HouseNo   = MyFile.GetLine( i++ );       // d od dom
                                MyData.Nick      = MyFile.GetLine( i++ );       // l od login
                                MyData.Password  = MyFile.GetLine( i++ );       // h
                                MyData.Mail      = MyFile.GetLine( i++ );       // p od poczta
                                MyData.Phone     = MyFile.GetLine( i   );       // t
                            }
                        }
                        else if ( MyFile.GetFirstLine() == "Dane logowania.txt" )
                        {
                            if ( MyFile.GetLineCount() > 1 + PARAMETR * 2 + 1 )
                            {
                                i = 1 + PARAMETR * 2;
                            
                                MyData.Nick      = MyFile.GetLine( i++ );       // l od login
                                MyData.Password  = MyFile.GetLine( i   );       // h
                            }
                        }
                        else
                        {
                            wxMessageBox( "Podany plik:\n\n" + Text + "\n\njest nieprawid³owy" );
                        }
                        
                        MyFile.Close();
                    
                    }
                    else
                    {
                        wxMessageBox( "Podany plik:\n\n" + Text + "\n\nnie istnieje" );
                    }
                    
                    break;
	           
    }
}



/*
 * MenuNew
 */
void EventBotFrm::MenuNew(wxCommandEvent& event)
{
	FileMemo->Clear();
	FileMemo->AppendText("\n");
	SteepList->Clear();
	ActionList->Clear();
	RangeEditStatic->Clear();
	RangeEdit->Clear();
	
	MainFilePath.Clear();
    MainFileName.Clear();
	
	SetTitle( "EventBot" );
	
	SteepsAmount = 0;
}

/*
 * MenuOpen
 */
void EventBotFrm::MenuOpen(wxCommandEvent& event)
{
	if ( WxOpenFileDialog1->ShowModal() == wxID_OK )
    {
        if ( FileMemo->LoadFile( WxOpenFileDialog1->GetPath() ) )
        {
            MainFilePath = WxOpenFileDialog1->GetPath();
            MainFileName = WxOpenFileDialog1->GetFilename();
        
            SetTitle( "EventBot - [ " + MainFileName + " ] - " + MainFilePath );
            
            ReLoadSteepList();
            ReLoadActionList(0);
            
            ReLoadSteep(0);
            ReLoadAction(0);
            
            RangeEditStatic->SetValue( FileMemo->GetLineText(0) );
            RangeEdit->Clear();
        }
    }
}

/*
 * MenuSave
 */
void EventBotFrm::MenuSave(wxCommandEvent& event)
{
	ReplaceMemoLine( 0, RangeEditStatic->GetValue() );
    
    if ( MainFileName == "" )
	{
        if ( WxSaveFileDialog1->ShowModal() == wxID_OK )
        {
            MainFilePath = WxSaveFileDialog1->GetPath();
            MainFileName = WxSaveFileDialog1->GetFilename();
            
            if ( !( MainFileName[ MainFileName.Len() - 4] == '.' &&
                    MainFileName[ MainFileName.Len() - 3] == 'e' &&
                    MainFileName[ MainFileName.Len() - 2] == 'v' &&
                    MainFileName[ MainFileName.Len() - 1] == 'b' ) )
            {
                MainFilePath += ".evb";
                MainFileName += ".evb";
            }
        
            FileMemo->SaveFile( MainFilePath );
            
            SetTitle( "EventBot - [ " + MainFileName + " ] - " + MainFilePath );
        }
    }
    else
    {
        FileMemo->SaveFile( MainFilePath );
    }
}

/*
 * MenuSaveAs
 */
void EventBotFrm::MenuSaveAs(wxCommandEvent& event)
{
	if ( WxSaveFileDialog1->ShowModal() == wxID_OK )
    {
        ReplaceMemoLine( 0, RangeEditStatic->GetValue() );
        
        MainFilePath = WxSaveFileDialog1->GetPath();
        MainFileName = WxSaveFileDialog1->GetFilename();
        
        if ( !( MainFileName[ MainFileName.Len() - 4] == '.' &&
                MainFileName[ MainFileName.Len() - 3] == 'e' &&
                MainFileName[ MainFileName.Len() - 2] == 'v' &&
                MainFileName[ MainFileName.Len() - 1] == 'b' ) )
        {
            MainFilePath += ".evb";
            MainFileName += ".evb";
        }
        
        FileMemo->SaveFile( MainFilePath );
        
        SetTitle( "EventBot - [ " + MainFileName + " ] - " + MainFilePath );
    }
}

/*
 * AddSteepClick
 */
void EventBotFrm::AddSteepClick(wxCommandEvent& event)
{
    NewNameDialog->SetValue( SteepList->GetStringSelection() );
    
    NewNameDialog->ShowModal();
    
    while ( NewNameDialog->GetReturnCode() == NewNameDialog->GetAffirmativeId() && NewNameDialog->GetValue() == "")
    {
        NewNameDialog->ShowModal();
    }
    
    if ( NewNameDialog->GetReturnCode() == NewNameDialog->GetAffirmativeId() && NewNameDialog->GetValue() != "")
    {
        //dodawanie kroku
        
        FileMemo->AppendText( NewNameDialog->GetValue() + "\n" );
        FileMemo->AppendText( TypeChoice->GetStringSelection() + "\n" );
        FileMemo->AppendText( wxString::Format( "%d\n", CycleSpinCtrl->GetValue() ) );
        FileMemo->AppendText( wxString::Format( "%d\n", DelaySpinCtrl->GetValue() ) );
        FileMemo->AppendText( "0\n" );
        
        // odswiezanie
        
        ReLoadSteepList();
        SteepList->SetSelection( SteepsAmount -1 );
        ReLoadSteep( SteepsAmount -1 );
        ReLoadActionList( SteepsAmount -1 );
        ReLoadAction(0);
    }
}

/*
 * DeleteSteepClick
 */
void EventBotFrm::DeleteSteepClick(wxCommandEvent& event)
{
	int Selection = SteepList->GetSelection();
	
	RemoveMemoLines( GetFirstSteepLineNo( Selection ), GetLastSteepLineNo( Selection ) );
	
	if ( Selection ) Selection--;
	else             Selection = 0;
    
    ReLoadSteepList();
    SteepList->SetSelection( Selection );
    ReLoadSteep( Selection );
    ReLoadActionList( Selection );
    ReLoadAction(0);
}

/*
 * SteepListSelected
 */
void EventBotFrm::SteepListSelected(wxCommandEvent& event)
{
	int Selection = SteepList->GetSelection();
    
    ReLoadSteep( Selection );
    ReLoadActionList( Selection );
    ReLoadAction(0);
}

/*
 * SteepListDoubleClicked
 */
void EventBotFrm::SteepListDoubleClicked(wxCommandEvent& event)
{
	int Selection = SteepList->GetSelection();
	int EditLine = GetFirstSteepLineNo( Selection );
    
    RenameDialog->SetValue( SteepList->GetStringSelection() );
    
    RenameDialog->ShowModal();
    
    while ( RenameDialog->GetReturnCode() == RenameDialog->GetAffirmativeId() && RenameDialog->GetValue() == "")
    {
        RenameDialog->ShowModal();
    }
    
    if ( RenameDialog->GetReturnCode() == RenameDialog->GetAffirmativeId() && RenameDialog->GetValue() != "")
    {
        ReplaceMemoLine( EditLine, RenameDialog->GetValue() );
        SteepList->SetString( Selection, RenameDialog->GetValue() );
    }
}

/*
 * AddActionClick
 */
void EventBotFrm::AddActionClick(wxCommandEvent& event)
{
	int Selection = SteepList->GetSelection();
	int FirstLine = GetFirstSteepLineNo( Selection );
	int LastLine =  GetLastSteepLineNo ( Selection );
    wxString String;
	wxString Temp;
    
    ActionChoiceDialog->ShowModal();
    
    if ( ActionChoiceDialog->GetReturnCode() == ActionChoiceDialog->GetAffirmativeId() )
    {
        String = GetMemoLines( LastLine + 1, FileMemo->GetNumberOfLines() - 2 );
        RemoveMemoLines      ( LastLine + 1, FileMemo->GetNumberOfLines() - 2 );
        
        Temp.Printf( "%d", atoi( FileMemo->GetLineText(  FirstLine + 4 ) ) + 1 );  // powiekszenie ilosci akcji o 1
        ReplaceMemoLine( FirstLine + 4, Temp );
        
        Temp.Printf( "%d\n", ActionChoiceDialog->GetSelection() );
        
        FileMemo->AppendText( Temp );
        FileMemo->AppendText( "0\n" );
        FileMemo->AppendText( "0\n" );
        FileMemo->AppendText( /*LinkEdit->GetValue() +*/ "Nic do wypisania\n" );
    
        FileMemo->AppendText( String );
        
        ReLoadActionList( Selection );
        ActionList->SetSelection( ActionList->GetCount() - 1 );
        ReLoadAction( ActionList->GetCount() - 1 );
    }

}

/*
 * DeleteActionClick
 */
void EventBotFrm::DeleteActionClick(wxCommandEvent& event)
{
	int Selection1 = SteepList->GetSelection();
	int Selection2 = ActionList->GetSelection();
	int FirstLine = GetFirstSteepLineNo( Selection1 );
	wxString Temp;
	
	Temp.Printf( "%d", atoi( FileMemo->GetLineText(  FirstLine + 4 ) ) - 1 );  // pomniejszenie ilosci akcji o 1
    ReplaceMemoLine( FirstLine + 4, Temp );
	
	RemoveMemoLines( GetFirstActionLineNo( Selection1, Selection2 ), GetLastActionLineNo( Selection1, Selection2 ) );
	
	if ( Selection2 )  Selection2--;
	else               Selection2 = 0;
    
    ReLoadActionList( Selection1 );
    ActionList->SetSelection( Selection2 );
    ReLoadAction( Selection2 );
}

/*
 * ActionListSelected
 */
void EventBotFrm::ActionListSelected(wxCommandEvent& event)
{
    ReLoadAction( ActionList->GetSelection() );
}

/*
 * PosCangeClick
 */
void EventBotFrm::PosCangeClick(wxCommandEvent& event)
{
	PosChangeTimer->Start(10);
	Enable(false);
}

/*
 * PosChangeTimerTimer
 */
void EventBotFrm::PosChangeTimerTimer(wxTimerEvent& event)
{
	static int Timer = 0;
	int EditLine;
	
	POINT pozycja;	 //odczytanie aktualnej pozycji kursora myszy na ekranie
    GetCursorPos(&pozycja);	//pozycja.x pozycja.y - pozycja kursona myszy na ekranie
    
    ClickText->SetLabel( wxString::Format( "Klik X: %d Y: %d", pozycja.x, pozycja.y ) );
	
	if ( Timer >= 300 )
	{
        PosChangeTimer->Stop();
        
        EditLine = GetFirstActionLineNo( SteepList->GetSelection(), ActionList->GetSelection() );
    
        ReplaceMemoLine( EditLine + 1, wxString::Format( "%d", pozycja.x ) );
        ReplaceMemoLine( EditLine + 2, wxString::Format( "%d", pozycja.y ) );

        //wxMessageBox("Zapisano zmiany","Info");
        MyMessageBox->ShowMessage( MAIN_WINDOW_CENTER, "Zapisano zmiany", 1000 );
        
        Timer = 0;
        Enable(true);
    }
    
    Timer++;
}

/*
 * LinkEditEnter
 */
void EventBotFrm::LinkEditEnter(wxCommandEvent& event)
{
	int EditLine = GetFirstActionLineNo( SteepList->GetSelection(), ActionList->GetSelection() );
    
    ReplaceMemoLine( EditLine + 3, LinkEdit->GetValue() );
}

/*
 * TypeChoiceSelected
 */
void EventBotFrm::TypeChoiceSelected(wxCommandEvent& event )
{
	int EditLine = GetFirstSteepLineNo( SteepList->GetSelection() );
	
	ReplaceMemoLine( EditLine + 1, TypeChoice->GetStringSelection() );
}

/*
 * CycleSpinCtrlTextUpdated
 */
void EventBotFrm::CycleSpinCtrlTextUpdated(wxCommandEvent& event )
{
	int EditLine = GetFirstSteepLineNo( SteepList->GetSelection() );
    
    ReplaceMemoLine( EditLine + 2, wxString::Format( "%d", CycleSpinCtrl->GetValue() ) );
}

/*
 * DelaySpinCtrlTextUpdated
 */
void EventBotFrm::DelaySpinCtrlTextUpdated(wxCommandEvent& event )
{
	int EditLine = GetFirstSteepLineNo( SteepList->GetSelection() );
    
    ReplaceMemoLine( EditLine + 3, wxString::Format( "%d", DelaySpinCtrl->GetValue() ) );
}

void EventBotFrm::PlayPauseFunction()
{
    if ( StartPause )  // byl pause
	{
        StartPause = false;
        Start->SetLabel("Start");
        
        SteepTimer->Stop();
    }
    else  // byl start
    {
        StartPause = true;
        Start->SetLabel("Pause");
        
        if( IsStop ) 
        {
            RangeEdit->SetValue( RangeEditStatic->GetValue() );
            
            FormatValue = GetFormatValue();
	
            if ( FormatValue == -1 )   FreeRunning = true;
	        else                       FreeRunning = false;
	
	        MakeSteep( SteepList->GetSelection(), LoopCounter, false );
        }
        else MakeSteep( SteepList->GetSelection(), LoopCounter, false ); // wykonuje sie krok podswietlony //SteepTimer->Start( 50, true ); // a tu nastepny
    }
    
    IsStop = false;
}

void EventBotFrm::StopFunction()
{
    SteepTimer->Stop();
	IsStop = true;
	LoopCounter = 0;
	
	// przelaczenie guzika na start
	StartPause = false;
    Start->SetLabel("Start");
    
    RangeEdit->Clear();
    SteepList->SetSelection(0);
    ReLoadSteep(0);
    ReLoadActionList(0);
    ReLoadAction(0);
}

/*
 * StartClick
 */
void EventBotFrm::StartClick(wxCommandEvent& event)
{
    PlayPauseFunction();
}

/*
 * StopClick
 */
void EventBotFrm::StopClick(wxCommandEvent& event)
{
	StopFunction();
}

/*
 * SteepTimerTimer
 */
void EventBotFrm::SteepTimerTimer(wxTimerEvent& event)
{

	int SteepNo = SteepList->GetSelection();
	
	if ( SteepNo < SteepList->GetCount() - 1 )
	{ 
        SteepNo++;
        
        SteepList->SetSelection( SteepNo );
        ReLoadActionList( SteepNo );
        ReLoadSteep( SteepNo );
    }
    else
    {
        SteepNo = 0;
        
        SteepList->SetSelection( SteepNo );
        ReLoadActionList( SteepNo );
        ReLoadSteep( SteepNo );
        
        FormatValue = GetFormatValue();
        
        LoopCounter++;
    }
    
    
    if ( FreeRunning )
    {
        MakeSteep( SteepNo, LoopCounter, false );
    }
    else if ( FormatValue > -1 ) 
    {
        if ( RangeEdit->GetValue().IsEmpty() )  MakeSteep( SteepNo, LoopCounter, true );
        else                                    MakeSteep( SteepNo, LoopCounter, false );
    }
    else
    {
        LoopCounter = 0;
        
        IsStop = true;
	
	    // przelaczenie guzika na start
	    StartPause = false;
        Start->SetLabel("Start");
        
        //wxMessageBox("Wykonano","Info");
        MyMessageBox->ShowMessage( MAIN_WINDOW_CENTER, "Wykonano" );
    }

}

/*
 * SecurityTimerTimer
 */
void EventBotFrm::SecurityTimerTimer(wxTimerEvent& event)
{
	static int OldLoopCounter = -1;
    
    if ( SteepList->GetSelection() >= 0 )
	{
        DeleteSteep->Enable(true);
        TypeChoice->Enable(true);
        CycleSpinCtrl->Enable(true);
        DelaySpinCtrl->Enable(true);
        Start->Enable(true);
        OrderListControl->Enable(true);
        AddAction->Enable(true);
    }
    else
    {
        DeleteSteep->Enable(false);
        TypeChoice->Enable(false);
        CycleSpinCtrl->Enable(false);
        DelaySpinCtrl->Enable(false);
        Start->Enable(false);
        OrderListControl->Enable(false);
        AddAction->Enable(false);
    }
    
    if ( ActionList->GetSelection() >= 0 )
	{
        DeleteAction->Enable(true);
        PosCange->Enable(true);
        LinkEdit->Enable(true);
        OrderActionControl->Enable(true);
    }
    else
    {
        DeleteAction->Enable(false);
        PosCange->Enable(false);
        LinkEdit->Enable(false);
        OrderActionControl->Enable(false);
    }
    
    if ( IsIconized() )
	{
        Show(false);   
    }
    
    if( IsShown() ) WindowPosition = GetPosition();
    
    if ( OldLoopCounter != LoopCounter )
    {
        WxStaticBox5->SetLabel( wxString::Format( "Wykonywanie sekwencji ze zmiennym parametrem ( licznik pêtli = %d )", LoopCounter ) );
        OldLoopCounter = LoopCounter;
    }
}

/*
 * GaugeTimerTimer
 */
void EventBotFrm::GaugeTimerTimer(wxTimerEvent& event)
{
	int Interval = SteepTimer->GetInterval();
	
	GaugeCounter++;
	
	WxGauge1->SetValue( ( GaugeCounter * 100000 ) / Interval );
}

/*
 * MenuOpenLogsFolder
 */
void EventBotFrm::MenuOpenLogsFolder(wxCommandEvent& event)
{
    ShellExecute(NULL, "open", GetArgv(0) + "Logs", NULL, NULL, SW_SHOWNORMAL );
}

/*
 * MenuHelp
 */
void EventBotFrm::MenuHelp(wxCommandEvent& event)
{
	wxString Text = "W programie dostêpna jest akcja 'Losuj dane osobowe'. £aduje ona z plików z folderu 'Dane', losowe dane osobowe.\n\n";
    Text += "Aby mieæ dostêp do tych danych nale¿y u¿ywaæ akcji: 'Wypisz text na klawiaturze' lub 'Wype³nij formularz'. W parametrze tekstowym akcji nale¿y u¿ywaæ nastêpuj¹cych symboli:\n\n";
    
    Text += "#i - Losowe imiê\n";
    Text += "#n - Losowe nazwisko\n";
    Text += "#m - Losowe miasto\n";
    Text += "#k - Losowy kod pocztowy\n";
    Text += "#u - Losowa ulica\n";
    Text += "#d - Losowy numer domu\n";
    Text += "#w - Losowy wiek\n";
    Text += "#t - Losowy numer telefonu kom.\n";
    Text += "#l - Losowy login(utworzony od imienia i nazwiska)\n";
    Text += "#h - Losowe silne has³o\n";
    Text += "#p - Losowy mail(login+serwer pocztowy)\n\n";
    
    Text += "Akcja 'Wype³nij formularz' ma nastêpuj¹c¹ sk³adniê(przyk³ad):\n\n";
    Text += "#i;jakiœ text;#t#h;;;#u #d\n\n";
    Text += "Œrednikami oddziela siê kolejne pola formularza, po krórych akcja porusza siê przy u¿yciu klawisza TAB. Dla tej akcji dostêpny jest równie¿ parametr 'Click', który wskazuje pierwsze pole formularza.\n\n";
    
    Text += "Uwaga Ogólna:\n";
    Text += "Dla akcji wypisuj¹cych tekst istnieje paramert 'Click', okreœlaj¹cy punkt poprzedzaj¹cego wypisywanie klikniêcia, gdy jest on równy (0,0), klikniêcie nie jest wykonywane.\n\n\n";
    
    Text += "Copyright (C) (2013-2014) Rados³aw Siwiec";
    
    wxMessageBox( Text, "PodpowiedŸ programu EventBot" );
}

/*
 * OrderListControlDown
 */
void EventBotFrm::OrderListControlDown(wxSpinEvent& event)
{
	int Selection = SteepList->GetSelection();
	wxString Steep1;
	wxString Steep2;
	wxString FileBottom = "";
	
	if ( Selection < SteepList->GetCount() - 1 )
	{
        Steep1 = GetMemoLines( GetFirstSteepLineNo( Selection ), GetLastSteepLineNo( Selection ) );
        Steep2 = GetMemoLines( GetFirstSteepLineNo( Selection + 1 ), GetLastSteepLineNo( Selection + 1 ) );
	   
        if ( Selection < SteepList->GetCount() - 2 )
        {
            FileBottom = GetMemoLines( GetFirstSteepLineNo( Selection + 2 ), FileMemo->GetNumberOfLines() - 2 ); // jest -2 zamiast -1 bo powstaje zawsze naoñcu nie potrzebna linia
        }
        
        RemoveMemoLines( GetFirstSteepLineNo( Selection ), FileMemo->GetNumberOfLines() - 1 );
	   
        FileMemo->AppendText( Steep2 + Steep1 + FileBottom );
	   
        ReLoadSteepList();
        SteepList->SetSelection( Selection + 1 );
    }
}

/*
 * OrderListControlUp
 */
void EventBotFrm::OrderListControlUp(wxSpinEvent& event)
{
	int Selection = SteepList->GetSelection();
	wxString Steep1;
	wxString Steep2;
	wxString FileBottom = "";
	
	if ( Selection )
	{
        Steep1 = GetMemoLines( GetFirstSteepLineNo( Selection ), GetLastSteepLineNo( Selection ) );
        Steep2 = GetMemoLines( GetFirstSteepLineNo( Selection - 1 ), GetLastSteepLineNo( Selection - 1 ) );
	   
        if ( Selection < SteepList->GetCount() - 1 )
        {
            FileBottom = GetMemoLines( GetFirstSteepLineNo( Selection + 1 ), FileMemo->GetNumberOfLines() - 2 ); // jest -2 zamiast -1 bo powstaje zawsze naoñcu nie potrzebna linia
        }
        
        RemoveMemoLines( GetFirstSteepLineNo( Selection - 1 ), FileMemo->GetNumberOfLines() - 1 );
	   
        FileMemo->AppendText( Steep1 + Steep2 + FileBottom );
	   
        ReLoadSteepList();
        SteepList->SetSelection( Selection - 1 );
    }
}

/*
 * OrderActionControlDown
 */
void EventBotFrm::OrderActionControlDown(wxSpinEvent& event)
{
	int Selection1 = SteepList->GetSelection();
    int Selection2 = ActionList->GetSelection();
	wxString Action1;
	wxString Action2;
	
	if ( Selection2 < ActionList->GetCount() - 1 )
	{
        Action1 = GetMemoLines( GetFirstActionLineNo( Selection1, Selection2 ), GetLastActionLineNo( Selection1, Selection2 ) );
        Action2 = GetMemoLines( GetFirstActionLineNo( Selection1, Selection2 + 1 ), GetLastActionLineNo( Selection1, Selection2 + 1 ) );
        
        Action1 = Action1.Left( Action1.Len() - 1 ); // wywalenie entera, entera nie liczy w funkcji len()
        
        ReplaceMemoLines( GetFirstActionLineNo( Selection1, Selection2 ), GetLastActionLineNo( Selection1, Selection2 + 1 ), Action2 + Action1 );
        
        ReLoadActionList( Selection1 );
        ActionList->SetSelection( Selection2 + 1 );
    }
}

/*
 * OrderActionControlUp
 */
void EventBotFrm::OrderActionControlUp(wxSpinEvent& event)
{
	int Selection1 = SteepList->GetSelection();
    int Selection2 = ActionList->GetSelection();
	wxString Action1;
	wxString Action2;
	
	if ( Selection2 )
	{
        Action1 = GetMemoLines( GetFirstActionLineNo( Selection1, Selection2 ), GetLastActionLineNo( Selection1, Selection2 ) );
        Action2 = GetMemoLines( GetFirstActionLineNo( Selection1, Selection2 - 1 ), GetLastActionLineNo( Selection1, Selection2 - 1 ) );
        
        Action2 = Action2.Left( Action2.Len() - 1 ); // wywalenie entera, entera nie liczy w funkcji len()
        
        ReplaceMemoLines( GetFirstActionLineNo( Selection1, Selection2 - 1 ), GetLastActionLineNo( Selection1, Selection2 ), Action1 + Action2 );
        
        ReLoadActionList( Selection1 );
        ActionList->SetSelection( Selection2 - 1 );
    }
}

/*
 * MenuToTray
 */
void EventBotFrm::MenuToTray(wxCommandEvent& event)
{
	Show(false);  
}

/*******************************************************************************
         Obs³uba z hotkey
*******************************************************************************/

void EventBotFrm::OnShowUnshowHotKey(wxKeyEvent& event)
{
    if ( IsShown() )
    {
        Show(false); 
    }
    else
    {
        Show(true);  
        Iconize(false);
    }
}

void EventBotFrm::OnExitHotKey(wxKeyEvent& event)  
{
    CloseApplication();
}

void EventBotFrm::OnPrintScreenHotKey(wxKeyEvent& event)   
{
    wxBitmap Bitmap;
    wxImage  Screen;
    wxString TempString;
                    
    // Get screen size
    int nWidth;// = GetSystemMetrics(SM_CXSCREEN);
    int nHeight;// = GetSystemMetrics(SM_CYSCREEN);

    // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
    HDC srcHDC;// = GetDC( GetDesktopWindow() );
    HDC destHDC;// = CreateCompatibleDC(srcHDC);
    HBITMAP hBitmap;
    
    wxMilliSleep(500);  // opoznienie zeby menu sie schowalo zanim zrobi zrzut
    
    // Get screen size
    nWidth = GetSystemMetrics(SM_CXSCREEN);
    nHeight = GetSystemMetrics(SM_CYSCREEN);

    // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
    srcHDC = GetDC( GetDesktopWindow() );
    destHDC = CreateCompatibleDC(srcHDC);
    hBitmap =CreateCompatibleBitmap(srcHDC,nWidth,nHeight);
    SelectObject(destHDC,hBitmap); 
    BitBlt(destHDC,0,0,nWidth,nHeight,srcHDC,0,0,SRCCOPY);

    // Release the objects
    ReleaseDC( GetDesktopWindow(),srcHDC);
    DeleteDC(destHDC);

    Bitmap.SetHBITMAP( hBitmap );
                    
    Screen = Bitmap.ConvertToImage();
              
    Screen.SaveFile( wxString::Format( GetArgv(0) + "Logs/!ScreenShot%4d.jpg", ManualScreenCouter ), wxBITMAP_TYPE_JPEG );
    
    ManualScreenCouter++;
}

void EventBotFrm::OnShowPrintScreenFolderHotKey(wxKeyEvent& event) 
{
    ShellExecute(NULL, "open", GetArgv(0) + "Logs", NULL, NULL, SW_SHOWNORMAL );
}

void EventBotFrm::OnPlayPauseHotKey(wxKeyEvent& event)
{
    PlayPauseFunction();
}

void EventBotFrm::OnStopHotKey(wxKeyEvent& event)
{
    StopFunction();
}

