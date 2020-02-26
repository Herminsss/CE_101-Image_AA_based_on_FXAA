//---------------------------------------------------------------------------
//
// Name:        Project1App.cpp
// Author:      Li_we
// Created:     25/02/2020 8:04:39 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "Project1App.h"
#include "Project1Frm.h"

IMPLEMENT_APP(Project1FrmApp)

bool Project1FrmApp::OnInit()
{
    Project1Frm* frame = new Project1Frm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int Project1FrmApp::OnExit()
{
	return 0;
}
