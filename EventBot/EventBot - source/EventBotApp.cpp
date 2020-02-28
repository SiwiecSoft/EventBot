//---------------------------------------------------------------------------
//
// Name:        EventBotApp.cpp
// Author:      Radek
// Created:     2013-06-30 14:13:17
// Description: 
//
//---------------------------------------------------------------------------

#include "EventBotApp.h"
#include "EventBotFrm.h"

/* wklej do pliku cpp okna w ktorym chcesz uzyc *******************************

extern int MyArgc; 
extern wxString GetArgv( int ArgvNo );

*******************************************************************************/

// Dodatek 1 ///////////////////////////////////////////////////////////////////

char MyArgv[10][500];
int MyArgc;

wxString GetArgv( int ArgvNo )
{
    wxString Temp = wxString::Format( "%s", MyArgv[ ArgvNo ] );
    
    if ( ArgvNo > 0 ) 
        return Temp;
    else
        return Temp.Left( Temp.Find( '\\', true ) + 1 );
}

////////////////////////////////////////////////////////////////////////////////

EventBotFrm* frame;

IMPLEMENT_APP(EventBotFrmApp)

bool EventBotFrmApp::OnInit()
{
    // Dodatek 2 ///////////////////////////////////////////////////////////////
    
    MyArgc = argc;
    
    for ( int i = 0; i < MyArgc; i++ )  strcpy( MyArgv[i], argv[i] );
    
    ////////////////////////////////////////////////////////////////////////////
    
    frame = new EventBotFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int EventBotFrmApp::OnExit()
{
	return 0;
}
