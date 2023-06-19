///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/dcbuffer.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/dcclient.h>
#include <memory>
#include <wx/filedlg.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/aui/auibook.h>
#include <wx/panel.h>
#include <wx/frame.h>


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel1;
		wxButton* m_button11;
		wxButton* m_button12;
		wxButton* m_button13;
		wxCheckBox* m_checkBox1;
		wxPanel* m_panel3;
		wxStaticText* m_staticText2;
		wxGauge* gauge1;
		
		
		// Virtual event handlers, override them in your derived class
		virtual void wx_button1click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button2click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button3_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_check( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_scrolledWindow_update(wxUpdateUIEvent& event) { event.Skip(); }
		virtual void resize(wxSizeEvent& event) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("GFK Lab 08"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1120,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};

