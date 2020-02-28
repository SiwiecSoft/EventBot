///-----------------------------------------------------------------
///
/// @file      MyMessageDlg.cpp
/// @author    Radek
/// Created:   2014-04-01 00:45:41
/// @section   DESCRIPTION
///            MyMessageDlg class implementation
///
///------------------------------------------------------------------

#include "MyMessageDlg.h"
#include "EventBotFrm.h"
extern EventBotFrm* frame;

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// MyMessageDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(MyMessageDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(MyMessageDlg::OnClose)
	EVT_LEFT_UP(MyMessageDlg::MyMessageDlgLeftUP)
	EVT_TIMER(ID_WXTIMER1,MyMessageDlg::WxTimer1Timer)
END_EVENT_TABLE()
////Event Table End

MyMessageDlg::MyMessageDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

MyMessageDlg::~MyMessageDlg()
{
} 

void MyMessageDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, wxT("WxCheckBox1"), wxPoint(395, 158), wxSize(97, 17), 0, wxDefaultValidator, wxT("WxCheckBox1"));
	WxCheckBox1->Show(false);
	WxCheckBox1->Enable(false);

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, wxT("Zapisano"), wxPoint(2, 2), wxSize(296, 38), wxTE_READONLY | wxTE_NOHIDESEL | wxTE_CENTRE, wxDefaultValidator, wxT("WxEdit1"));
	WxEdit1->Enable(false);
	WxEdit1->SetForegroundColour(wxColour(wxT("WHITE")));
	WxEdit1->SetBackgroundColour(wxColour(wxT("BLACK")));
	WxEdit1->SetFont(wxFont(20, wxSWISS, wxNORMAL, wxNORMAL, false));

	SetTitle(wxT("MyMessageDlg"));
	SetIcon(wxNullIcon);
	SetSize(8,8,521,226);
	Center();
	
	////GUI Items Creation End
	
	// Ustewienia okna
	
	//wxPoint MainWindowPos = frame->GetScreenPosition();
	
	//int XPos = MainWindowPos.x;
    //int YPos = ( GetSystemMetrics(SM_CYSCREEN) - WindowSize.y ) / 2;
	
	wxSize WindowSize = GetBestSize();
	
	WindowSize.x += 2;
	WindowSize.y += 2;
	
	int nWidth = ( GetSystemMetrics(SM_CXSCREEN) - WindowSize.x ) / 2;
    int nHeight = ( GetSystemMetrics(SM_CYSCREEN) - WindowSize.y ) / 2;
	
	//ShowFullScreen(true);

    SetSize( WindowSize );
    
    SetBackgroundColour(wxColour(0,0,0));
    
    SetPosition( wxPoint( nWidth, nHeight ) );
    
    SetFocus();
}

void MyMessageDlg::OnClose(wxCloseEvent& /*event*/)
{
	EndModal(0);
}


/*
 * MyMessageDlgLeftUP
 */
void MyMessageDlg::MyMessageDlgLeftUP(wxMouseEvent& event)
{
	EndModal(0);
	WxTimer1->Stop();
}

/*
 * WxTimer1Timer
 */
void MyMessageDlg::WxTimer1Timer(wxTimerEvent& event)
{
	EndModal(0);
}

void MyMessageDlg::ShowMessage( wxPoint Pos, wxString Text, int Milisec  )
{
    WxEdit1->SetValue( Text );
    SetPosition( Pos - GetSize()/2 );
    
    if ( Milisec != NULL ) WxTimer1->Start( Milisec, true );
    
    ShowModal();
}
