///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_button11 = new wxButton( this, wxID_ANY, _("Wczytaj Obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_button11, 0, wxALL, 5 );


	bSizer10->Add( bSizer11, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	m_button12 = new wxButton( this, wxID_ANY, _("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_button12, 0, wxALL, 5 );


	bSizer10->Add( bSizer12, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	m_button13 = new wxButton( this, wxID_ANY, _("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_button13, 0, wxALL, 5 );


	bSizer10->Add( bSizer13, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxHORIZONTAL);

	m_checkBox1 = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer14->Add(m_checkBox1, 1, wxALIGN_TOP | wxALL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, _("Animacja"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->SetLabelMarkup(_("Animacja"));
	m_staticText2->Wrap(-1);
	m_staticText2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	m_staticText2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));
	m_staticText2->Wrap(-1);
	bSizer14->Add(m_staticText2, 1, wxALL, 5);

	bSizer10->Add(bSizer14, 1, wxALIGN_CENTER | wxALIGN_TOP | wxALL, 5);
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer(wxVERTICAL);

	gauge1 = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	gauge1->SetValue(0);
	gauge1->Hide();

	bSizer81->Add(gauge1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL| wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);


	//bSizer15->Add(bSizer81, 0, wxALL | wxEXPAND, 5);
	bSizer10->Add(bSizer81, 0, wxEXPAND|wxALL, 5);

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize(180,300), wxTAB_TRAVERSAL);
	m_panel3->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_panel3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );

	bSizer15->Add( m_panel3, 1, wxEXPAND|wxALL, 5 );


	bSizer10->Add( bSizer15, 4, wxEXPAND, 5 );

	
	bSizer8->Add( bSizer10, 0,wxALL|wxEXPAND, 5 );
	wxBoxSizer *bSizer9 = new wxBoxSizer(wxVERTICAL);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 533), wxTAB_TRAVERSAL);
	m_panel1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
	m_panel1->SetSize(wxSize(800, 533));
	bSizer9->Add(m_panel1,4,wxEXPAND, 5);
	//bSizer8->Add(m_panel1,1, wxALIGN_RIGHT,  5);
	bSizer8->Add(bSizer9, 1,  wxEXPAND|wxFIXED_MINSIZE, 5);
	this->SetSizer( bSizer8 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::wx_button1click ), NULL, this );
	m_button12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button2click ), NULL, this );
	m_button13->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button3_click ), NULL, this );
	m_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_check ), NULL, this );
	m_panel1->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::resize), NULL, this);
	m_panel3->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::resize), NULL, this);
	//WxTimer1->Connect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::Timer1_Timer), NULL, this);
	//virtual void Timer1_Timer(wxTimerEvent& event) { event.Skip(); }
		//(MyFrame1::Timer1_Timer), NULL, this

}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::wx_button1click ), NULL, this );
	m_button12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button2click ), NULL, this );
	m_button13->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button3_click ), NULL, this );
	m_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_check ), NULL, this );
	m_panel1->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::resize), NULL, this);
	m_panel3->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::resize), NULL, this);

}
