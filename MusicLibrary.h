#ifndef _MUSICLIBRARY_H_
#define _MUSICLIBRARY_H_

/*!
 * Includes
 */
#include "wx/filesys.h"
#include "wx/fs_zip.h"
#include "wx/html/helpctrl.h"
#include "wx/stdpaths.h"
#include "wx/listctrl.h"

/*!
 * Control identifiers
 */
#define ID_KEYBOARD_DLG 10000
#define SYMBOL_WXKEYBOARD_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxWANTS_CHARS|wxMINIMIZE_BOX
#define SYMBOL_WXKEYBOARD_TITLE _("Music Library Tools")
#define SYMBOL_WXKEYBOARD_IDNAME ID_KEYBOARD_DLG
#define SYMBOL_WXKEYBOARD_SIZE wxSize(400, 300)
#define SYMBOL_WXKEYBOARD_POSITION wxDefaultPosition
#define ID_TXT_FILENAME 10001
#define ID_BTN_BROWSE 10002
#define ID_BTN_PLAY 10003
#define ID_BTN_STOP 10004
#define ID_BTN_EXIT 10005
#define ID_BTN_INFO 10006
#define ID_TXT_NUMEVENTS 10007
#define ID_TXT_NUMTRACKS 10008
#define ID_TXT_LENGTH 10009
#define ID_TXT_LOADEDFILE 10010
#define ID_MIDI_DEVICE 10011
#define ID_TXT_SIZE 10012
#define ID_TXT_TYPE 10013
#define ID_BTN_SAVE 10014
#define ID_BTN_TIME 10015
#define ID_TXT_TIME_ELAPSED 10016
#define ID_BTN_INDEX 10017
#define ID_LIST_GENRES 10018
#define ID_LIST_FILES 10019
#define ID_BTN_FIND 10020
#define ID_BTN_RENAME 10021
#define ID_BTN_GENERATE 10022

/*!
 * Compatibility
 */
#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

class MusicLibrary: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( MusicLibrary )
    DECLARE_EVENT_TABLE()
public:
    /// Constructors
    MusicLibrary( );
    MusicLibrary( wxWindow* parent, wxWindowID id = SYMBOL_WXKEYBOARD_IDNAME, const wxString& caption = SYMBOL_WXKEYBOARD_TITLE, const wxPoint& pos = SYMBOL_WXKEYBOARD_POSITION, const wxSize& size = SYMBOL_WXKEYBOARD_SIZE, long style = SYMBOL_WXKEYBOARD_STYLE );
	~MusicLibrary();
    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_WXKEYBOARD_IDNAME, const wxString& caption = SYMBOL_WXKEYBOARD_TITLE, const wxPoint& pos = SYMBOL_WXKEYBOARD_POSITION, const wxSize& size = SYMBOL_WXKEYBOARD_SIZE, long style = SYMBOL_WXKEYBOARD_STYLE );
    void CreateControls();
    void OnCloseWindow( wxCloseEvent& event );
	void OnInfo( wxCommandEvent& event );
    void OnIndex( wxCommandEvent& event );
    void OnBrowse( wxCommandEvent& event );
    void FindFiles(wxString directory);
private:
	wxMutex _mutex;
	wxIcon _icon;
	wxButton* _btnBrowse;
    wxButton* _btnInfo;
    wxButton* _btnIndex;
    wxButton* _btnFind;
    wxButton* _btnRename;
    wxButton* _btnGenerate;
	wxTextCtrl* _txtFilename;
    wxChoice* _lstGenres;
    wxListCtrl* _lstFiles;
    int _numSongs;
    wxArrayString _genres;
};

#endif
