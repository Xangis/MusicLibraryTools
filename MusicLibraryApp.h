#ifndef _MUSICLIBRARYAPP_H_
#define _MUSICLIBRARYAPP_H_

#include "wx/image.h"

class MusicLibraryApp: public wxApp
{
    DECLARE_CLASS( MusicLibraryApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    MusicLibraryApp();
    ~MusicLibraryApp();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();
};

/*!
 * Application instance declaration 
 */
DECLARE_APP(MusicLibraryApp)

#endif
    // _MUSICLIBRARYAPP_H_
