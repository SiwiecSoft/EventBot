
#include <wx/taskbar.h>
#include <wx/menu.h>

/*********************************************************************************************

    Przed zdjeciem komentarzy zrob nastepujace rzeczy:
        - w pliku *App.cpp   rozdziel linie   "NazwaKlasy* frame = new NazwaKlasy(NULL);"
          tak ze NazwaKlasy* frame; znajdzie sie poza funkcja "bool NazwaKlasyApp::OnInit()"
          a wewnatrz pozostanie   "frame = new NazwaKlasy(NULL);"
        - teraz wskaznik frame na twoje okno glowne jest globalny
        - podmien nazwe klasy na wlasna
        - teraz mozesz zdjac ten komentarz
        
    Aby dodac ikonke do taskbar urzyj:
        MyTaskBarIcon* MyTaskBar; // wskaznik zadeklaruj globalnie
        MyTaskBar = new MyTaskBarIcon();
        MyTaskBar->SetIcon( GetIcon() );
        
    Przy zamykaniu okna pamietaj o usunieciu tego obiektu:
        delete  MyTaskBar;
        
*********************************************************************************************/

#include "EventBotFrm.h"
extern EventBotFrm* frame;

#define READY_TO_GO

class MyTaskBarIcon: public wxTaskBarIcon   
{   
public:   
    MyTaskBarIcon() {};   
     
    void OnMenuShowUnshow(wxCommandEvent&); 
    void OnMenuPlayPause(wxCommandEvent&); 
    void OnMenuStop(wxCommandEvent&); 
    //void OnMenuShowFalse(wxCommandEvent&);  
    void OnMenuExit(wxCommandEvent&);   
    void OnMenuPrintScreen(wxCommandEvent&);  
    void OnMenuShowPrintScreenFolder(wxCommandEvent&);  
    
    void OnMove( wxTaskBarIconEvent& );
    void OnLeftDown( wxTaskBarIconEvent& );
    void OnLeftUp( wxTaskBarIconEvent& );
    //void OnRightDown( wxTaskBarIconEvent& );
    //void OnRightUp( wxTaskBarIconEvent& );
    void OnLeftDClick( wxTaskBarIconEvent& );
    void OnRightDClick( wxTaskBarIconEvent& );
    //void OnClick( wxTaskBarIconEvent& );
   
    virtual wxMenu *CreatePopupMenu();   
    virtual ~MyTaskBarIcon();
   
    DECLARE_EVENT_TABLE()  
    
    enum {   
    PU_SWOW_TRUE = 10001,   
    PU_SWOW_FALSE,   
    PU_EXIT,
    PU_PRINT_SCREEN,
    PU_SHOW_PRINT_SCREEN_FOLDER,
    PU_SWOW_UNSHOW,
    PU_PLAY_PAUSE,
    PU_STOP
    };  
};

