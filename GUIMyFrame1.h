#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__
#include <wx/timer.h>
/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
	protected:
		// Handlers for MyFrame1 events.
		void wx_button1click(wxCommandEvent& event);
		void m_button2click(wxCommandEvent& event);
		void m_button3_click(wxCommandEvent& event);
		void m_check(wxCommandEvent& event);
		void m_scrolledWindow_update(wxUpdateUIEvent& event);
		void Repaint();
		void resize(wxSizeEvent& event);
		void exif();
		
	

	public:
		/** Constructor */
		wxImage This_image;
		wxImage cp_image;
		GUIMyFrame1(wxWindow* parent);
		wxString information[6];
		wxString name;
		float actual_size_x;
		float actual_size_y;
		unsigned width;
		unsigned height;
	//// end generated class members









};

#endif // __GUIMyFrame1__
