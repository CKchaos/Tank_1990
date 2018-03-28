/***************************************************************
 * Name:      tankApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2016-06-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "tankApp.h"

//(*AppHeaders
#include "tankMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(tankApp);

bool tankApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	tankFrame* Frame = new tankFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
