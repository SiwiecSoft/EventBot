
#include "MyTaskBar.h"

#ifdef READY_TO_GO

BEGIN_EVENT_TABLE(MyTaskBarIcon, wxTaskBarIcon)   
    EVT_MENU( PU_SWOW_UNSHOW,                   MyTaskBarIcon::OnMenuShowUnshow )  
    EVT_MENU( PU_PLAY_PAUSE,                    MyTaskBarIcon::OnMenuPlayPause ) 
    EVT_MENU( PU_STOP,                          MyTaskBarIcon::OnMenuStop )  
    //EVT_MENU( PU_SWOW_FALSE,                MyTaskBarIcon::OnMenuShowFalse )   
    EVT_MENU( PU_EXIT,                      MyTaskBarIcon::OnMenuExit )  
    EVT_MENU( PU_PRINT_SCREEN,              MyTaskBarIcon::OnMenuPrintScreen )   
    EVT_MENU( PU_SHOW_PRINT_SCREEN_FOLDER,  MyTaskBarIcon::OnMenuShowPrintScreenFolder )  
    
    EVT_TASKBAR_MOVE( MyTaskBarIcon::OnMove )
    EVT_TASKBAR_LEFT_DOWN( MyTaskBarIcon::OnLeftDown )
    EVT_TASKBAR_LEFT_UP( MyTaskBarIcon::OnLeftUp )
    //EVT_TASKBAR_RIGHT_DOWN( MyTaskBarIcon::OnRightDown )
    //EVT_TASKBAR_RIGHT_UP( MyTaskBarIcon::OnRightUp )
    EVT_TASKBAR_LEFT_DCLICK( MyTaskBarIcon::OnLeftDClick )
    EVT_TASKBAR_RIGHT_DCLICK( MyTaskBarIcon::OnRightDClick )
    //EVT_TASKBAR_CLICK( MyTaskBarIcon::OnClick )
END_EVENT_TABLE()   

// nadpisanie funkcji tworzacej menu
 
wxMenu *MyTaskBarIcon::CreatePopupMenu()   
{   
    wxMenu *menu = new wxMenu;   
       
    menu->Append(PU_SWOW_UNSHOW,                    wxT("Poka¿/Ukryj okno - SHIFT+CTRL+Spacja"));   
    menu->Append(PU_PLAY_PAUSE,                     wxT("Start/Pause - SHIFT+CTRL+P")); 
    menu->Append(PU_STOP,                           wxT("Stop - SHIFT+CTRL+S")); 
    //menu->Append(PU_SWOW_FALSE,                     wxT("Ukryj okno"));   
    menu->Append(PU_PRINT_SCREEN,                   wxT("Zrzut ekranu - SHIFT+CTRL+PrtScn"));   
    menu->Append(PU_SHOW_PRINT_SCREEN_FOLDER,       wxT("Poka¿ zrzuty ekranu - SHIFT+CTRL+F"));   
    menu->Append(PU_EXIT,                           wxT("Zamknij - SHIFT+CTRL+Z")); 
    
    return menu;   
} 



// funkcje obslugi zdarzen menu
   
void MyTaskBarIcon::OnMenuShowUnshow(wxCommandEvent& )   
{   
    if ( frame->IsShown() )
    {
        frame->Show(false); 
    }
    else
    {
        frame->Show(true);  
        frame->Iconize(false);
    }
} 

void MyTaskBarIcon::OnMenuPlayPause(wxCommandEvent&)
{
    frame->PlayPauseFunction();
}

void MyTaskBarIcon::OnMenuStop(wxCommandEvent&)
{
    frame->StopFunction();
}

/*void MyTaskBarIcon::OnMenuShowFalse(wxCommandEvent& )   
{   
    frame->Show(false);   
}  */ 
   
void MyTaskBarIcon::OnMenuExit(wxCommandEvent& )   
{   
    frame->CloseApplication();
}     

void MyTaskBarIcon::OnMenuPrintScreen(wxCommandEvent&)
{
    wxBitmap Bitmap;
    wxImage  Screen;
    //static int Couter = 0;
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
                    
    //CreateDirectory("Logs", NULL); //na pocz¹tku
    
    //TempString.Printf( "Logs/!ScreenShot%4d.jpg", Couter );
              
    Screen.SaveFile( wxString::Format( GetArgv(0) + "Logs/!ScreenShot%4d.jpg", frame->ManualScreenCouter ), wxBITMAP_TYPE_JPEG );
    //Screen.SaveFile( "Logs/" + wxNow() + ".jpg", wxBITMAP_TYPE_JPEG );
    
    frame->ManualScreenCouter++;
}

void MyTaskBarIcon::OnMenuShowPrintScreenFolder(wxCommandEvent&)
{
    ShellExecute(NULL, "open", GetArgv(0) + "Logs", NULL, NULL, SW_SHOWNORMAL );
}
   
// funkcje obslugi zdarzen myszy

void MyTaskBarIcon::OnMove( wxTaskBarIconEvent& )
{
}

void MyTaskBarIcon::OnLeftDown( wxTaskBarIconEvent& )
{
}

void MyTaskBarIcon::OnLeftUp( wxTaskBarIconEvent& )
{
    if ( frame->IsShown() )
    {
        frame->Show(false); 
    }
    else
    {
        frame->Show(true);  
        frame->Iconize(false);
    }
}

/*void MyTaskBarIcon::OnRightDown( wxTaskBarIconEvent& )
{
}

void MyTaskBarIcon::OnRightUp( wxTaskBarIconEvent& )
{
}*/

void MyTaskBarIcon::OnLeftDClick( wxTaskBarIconEvent& )
{
}

void MyTaskBarIcon::OnRightDClick( wxTaskBarIconEvent& )
{
}

/*void MyTaskBarIcon::OnClick( wxTaskBarIconEvent& )
{
}*/

// destruktor klasy

MyTaskBarIcon::~MyTaskBarIcon()
{
    RemoveIcon();
}

#endif

