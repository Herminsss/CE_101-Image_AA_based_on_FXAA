///-----------------------------------------------------------------
///
/// @file      Project1Frm.cpp
/// @author    Li_we
/// Created:   25/02/2020 8:04:39 PM
/// @section   DESCRIPTION
///            Project1Frm class implementation
///
///------------------------------------------------------------------

#include "Project1Frm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Project1Frm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Project1Frm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Project1Frm::OnClose)
	EVT_ACTIVATE(Project1Frm::Project1FrmActivate)
	EVT_BUTTON(ID_WXBUTTON2,Project1Frm::WxButton2Click)
	EVT_BUTTON(ID_WXBUTTON1,Project1Frm::WxButton1Click0)
END_EVENT_TABLE()
////Event Table End

Project1Frm::Project1Frm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Project1Frm::~Project1Frm()
{
}

void Project1Frm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Upload Image"), wxPoint(646, 22), wxSize(231, 42), 0, wxDefaultValidator, _("WxButton1"));

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(40, 24), wxSize(533, 373));

	WxButton2 = new wxButton(this, ID_WXBUTTON2, _("Anti-alias image"), wxPoint(647, 165), wxSize(231, 43), 0, wxDefaultValidator, _("WxButton2"));

	WxButton3 = new wxButton(this, ID_WXBUTTON3, _("Save Image"), wxPoint(647, 328), wxSize(228, 38), 0, wxDefaultValidator, _("WxButton3"));

	SetTitle(_("Project1"));
	SetIcon(wxNullIcon);
	SetSize(8,8,946,455);
	Center();
	
	////GUI Items Creation End
}

void Project1Frm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void Project1Frm::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxPanel1UpdateUI
 */
void Project1Frm::WxPanel1UpdateUI(wxUpdateUIEvent& event)
{
	// insert your code here
}

/*
 * Project1FrmActivate
 */
void Project1Frm::Project1FrmActivate(wxActivateEvent& event)
{
	// insert your code here
}

/*
 * WxButton2Click
 */
void Project1Frm::WxButton2Click(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxButton1Click0
 */
void Project1Frm::WxButton1Click0(wxCommandEvent& event)
{
	// insert your code here
}
