#include "wx/wx.h"
#include "MusicLibraryApp.h"
#include "MusicLibrary.h"

IMPLEMENT_APP( MusicLibraryApp )

IMPLEMENT_CLASS( MusicLibraryApp, wxApp )

BEGIN_EVENT_TABLE( MusicLibraryApp, wxApp )
END_EVENT_TABLE()

MusicLibraryApp::MusicLibraryApp()
{
}

MusicLibraryApp::~MusicLibraryApp()
{
}

bool MusicLibraryApp::OnInit()
{
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.
    wxInitAllImageHandlers();
    MusicLibrary* mainWindow = new MusicLibrary(NULL, ID_KEYBOARD_DLG );
    mainWindow->Show(true);
    return true;
}

int MusicLibraryApp::OnExit()
{
    return wxApp::OnExit();
}

