#include "wx/wx.h"
#include "wx/aboutdlg.h"
#include "wx/strconv.h"
#include "wx/dir.h"
#include "MusicLibrary.h"
#include "taglib.h"

IMPLEMENT_DYNAMIC_CLASS( MusicLibrary, wxDialog )

BEGIN_EVENT_TABLE( MusicLibrary, wxDialog )
    EVT_CLOSE( MusicLibrary::OnCloseWindow )
	EVT_BUTTON( ID_BTN_INFO, MusicLibrary::OnInfo )
END_EVENT_TABLE()


MusicLibrary::MusicLibrary( )
{
}

MusicLibrary::~MusicLibrary()
{
}

MusicLibrary::MusicLibrary( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}


bool MusicLibrary::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	//_helpCtrl = NULL;
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    SetFocus();

	wxFileSystem::AddHandler(new wxZipFSHandler());
	//_helpCtrl = new wxHtmlHelpController(wxHF_CONTENTS);
#ifdef WIN32
	//wxFileName filename = wxStandardPaths::Get().GetDataDir() + _("\\proximacontrol.htb");
#else
	//wxFileName filename = wxString(_("./proximacontrol.htb"));
#endif
	//if( !_helpCtrl->AddBook(filename))
	//{
	//	wxMessageBox( _("Unable to load help file.  Please make sure that proximacontrol.htb is in the program directory." ));
	//}
	// Load icon.
	//if( _icon.LoadFile(_("keyicon.ico"), wxBITMAP_TYPE_ICO ))
	//{
	//	SetIcon(_icon);
	//}

	//Run();

    // Enable drag and drop.
    //SetDropTarget(this);
    //SetDefaultAction(wxDragCopy);

    return true;
}

void MusicLibrary::CreateControls()
{
    MusicLibrary* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer25, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( itemDialog1, wxID_STATIC, _("Directory:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_txtFilename = new wxTextCtrl(itemDialog1, ID_TXT_FILENAME, _(""), wxDefaultPosition, wxSize(460, -1));
	itemBoxSizer3->Add(_txtFilename, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_btnBrowse = new wxButton(itemDialog1, ID_BTN_BROWSE, _("Browse"));
	itemBoxSizer3->Add(_btnBrowse, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_btnIndex = new wxButton(itemDialog1, ID_BTN_INDEX, _("Index"));
	itemBoxSizer3->Add(_btnIndex, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Generate Genre-Based Playlist"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemDialog1, wxID_STATIC, _("Genre:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(itemStaticText15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _lstGenres = new wxChoice( itemDialog1, ID_LIST_GENRES, wxDefaultPosition, wxDefaultSize );
    itemBoxSizer10->Add(_lstGenres, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( itemDialog1, wxID_STATIC, _("Find Songs By Length"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemStaticText13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText16 = new wxStaticText( itemDialog1, wxID_STATIC, _("Min Length:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(itemStaticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* textCtrl2 = new wxTextCtrl(itemDialog1, ID_TXT_FILENAME, _("2:30"), wxDefaultPosition, wxDefaultSize);
	itemBoxSizer9->Add(textCtrl2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( itemDialog1, wxID_STATIC, _("Max Length:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(itemStaticText17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* textCtrl3 = new wxTextCtrl(itemDialog1, ID_TXT_FILENAME, _("3:30"), wxDefaultPosition, wxDefaultSize);
	itemBoxSizer9->Add(textCtrl3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer2->Add(itemBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText14 = new wxStaticText( itemDialog1, wxID_STATIC, _("Rename Songs"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemStaticText14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText18 = new wxStaticText( itemDialog1, wxID_STATIC, _("Separator:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* textCtrl1 = new wxTextCtrl(itemDialog1, ID_TXT_FILENAME, _(" - "), wxDefaultPosition, wxDefaultSize);
	itemBoxSizer8->Add(textCtrl1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer24, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    _lstFiles = new wxListCtrl( itemDialog1, ID_LIST_FILES, wxDefaultPosition, wxSize(600, 120) );
    itemBoxSizer24->Add(_lstFiles, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText19 = new wxStaticText( itemDialog1, wxID_STATIC, _("Number of Songs Indexed:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add(itemStaticText19, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemDialog1, wxID_STATIC, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add(itemStaticText20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _btnInfo = new wxButton(itemDialog1, ID_BTN_INFO, _("Info"));
	itemBoxSizer14->Add(_btnInfo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
}

/**
* Handles window close events.
*/
void MusicLibrary::OnCloseWindow( wxCloseEvent& event )
{
    Destroy();
    event.Skip();
}

/**
* Shows about box.
*/
void MusicLibrary::OnInfo( wxCommandEvent& event )
{
	// Show about box.
    wxAboutDialogInfo info;
    info.SetName(_("Music Library Tools"));
    info.SetVersion(_("1.0"));
    info.SetCopyright(_("Copyright (c) 2006-2016 Zeta Centauri"));
	info.AddDeveloper(_("Jason Champion"));
	//info.SetIcon(_icon);
	info.SetLicense(_("Music Library Tools is freeware and may be distributed freely."));
	info.SetWebSite(_("http://zetacentauri.com"));
	info.SetDescription(_("Music Library Tools uses the wxWidgets and TagLib libraries."));

    wxAboutBox(info);

    event.Skip();
}

void MusicLibrary::FindFiles(wxString directory)
{
    printf("Reading directory: %s", directory);
    _lstFiles->ClearAll();
    wxArrayString files;
#ifndef __APPLE__
    wxDir::GetAllFiles(directory, &files, wxString(_("*.wav")), wxDIR_FILES|wxDIR_DIRS);
#else
    wxString dirname = wxString::Format(_("%s/samples"), wxStandardPaths::Get().GetResourcesDir());
    wxDir::GetAllFiles(dirname, &_waveFileNames, wxString(_("*.wav")), wxDIR_FILES);
#endif
    _numSongs = files.Count();

	if( _numSongs > 0 )
	{
		// Fix paths so they're absolute -- they load as relative.
		for( int i = 0; i < files.Count(); i++ )
		{
            //if (file.Extension == ".wma" || file.Extension == ".mp3" || file.Extension == ".ogg")
            _lstFiles->InsertItem(-1, files[i]);
            //TagLib.File tag;
            //tag = TagLib.File.Create(file.FullName);
            //int nogenres = 0;
            //wxArrayString genres = tag.Tag.Genres;
            //if (genres.size() < 1)
            //{
            //    ++nogenres;
            //    continue;
            //}

        }
    }

    //foreach (String str in genres)
    //{
    //    if (!_genres.ContainsKey(str))
    //    {
    //        _genres[str] = new List<String>();
    //    }
    //    _genres[str].Add(file.FullName);
    //}
    //++songCount;
    //lblNumIndexed.Content = songCount.ToString();

    //foreach (String dir in Directory.GetDirectories(directory))
    //{
    //    FindFiles(dir);
    //}
}

void MusicLibrary::OnIndex( wxCommandEvent& event )
{
    _lstGenres->Clear();
    FindFiles(_txtFilename->GetLabel());
    //RepopulateGenres();
}