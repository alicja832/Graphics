#include <wx/wxprec.h>
#include <wx/fontenum.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame();
private:
	wxColor currentcolor;
	wxButton* WxButton1;//zapis do pliku
	wxButton* WxColor;
	wxTextCtrl* WxEdit1;//tekst wypisujacy sie
	wxCheckBox* WxCheckBox1;//czy chce banana
	wxStaticText* WxStaticText1;//wypisuje sie tekst który się wpisuje
	wxString napis;//tekst rotacyjny
	wxScrollBar* WxScrollBar1;//scroll zmieniajacy polozenie banana
	wxBitmap MyBitmap;
	wxImage  MyImage;//cos co przechowuje banana
	wxPoint Banan;
	wxPoint Centre;
	wxTimer* WxTimer1;
	bool banan;
	wxChoice* Wx_figure;//ikonka z odpowiednim kształtem
	wxArrayString str;
	wxBoxSizer* Box_one;
	wxBoxSizer* Box_two;
	wxGauge* Pass;
	wxPoint ptsB[3] =
	{
		wxPoint((GetSize().x - 200) / 2 - 30, GetSize().y / 2 + 50),  wxPoint((GetSize().x - 200) / 2, GetSize().y / 2 + 30),
		 wxPoint((GetSize().x - 200) / 2 + 30, GetSize().y / 2 +50),
	};
	int a;

	void Lapka();
	void Timer1_Timer(wxTimerEvent& e);
	void draw();
	void WxEdit1_Updated(wxCommandEvent& e);
	void WxCheckBox1_Click(wxCommandEvent& e);
	void WxScrollBar1_Scroll(wxScrollEvent& e);
	void WxSave_Click(wxCommandEvent& e);
	void WxChoise(wxCommandEvent& e);
	void Form_Paint(wxPaintEvent& event);
	void Choose_Color(wxCommandEvent& e);
	void change_bananposition(int a);
	int x;
	enum
	{
		ID_WXBUTTON1 = 1001,
		ID_WXEDIT1 = 1002,
		ID_WXCHECKBOX1 = 1003,
		ID_WXSCROLLBAR1 = 1004,
		ID_WXCHOICE = 1005,
		ID_WXBUTTON2 = 1006,
		ID_WXTIMER1 = 1007
	};

};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	SetProcessDPIAware();
	MyFrame* frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "GFK Lab 03")
{

	
	a = 0;
	banan = false;
	napis = wxString("tekst");
	Box_one = new wxBoxSizer(wxVERTICAL);

	
	SetTitle(_("GFK Lab 03"));
	SetIcon(wxNullIcon);
	SetSize(100, 100, 1000, 600);
	
	x = 0;
	currentcolor = wxColor(0, 0, 0);
	const wxSize sizeM = this->GetTextExtent("M");
	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Zapis do pliku"), wxPoint(int(0.8 * (GetSize().GetWidth())), 15), wxSize(/*113*/10 * sizeM.GetX(), (int)(1.5f * (float)sizeM.GetY())), 0, wxDefaultValidator, _("WxButton1"));

	Box_one->Add(WxButton1, 0, wxALIGN_CENTER | wxALL, 5);

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("tekst"), wxPoint(800, 150), wxSize(130, 40), 0, wxDefaultValidator, _("WxEdit1"));
	Box_one->Add(WxEdit1, 0, wxALIGN_CENTER | wxALL, 5);
	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, _("Banan"), wxPoint(800, 65), wxSize(105, 30), 0, wxDefaultValidator, _("WxCheckBox1"));
	Box_one->Add(WxCheckBox1, 0, wxALIGN_CENTER | wxALL, 5);
	WxScrollBar1 = new wxScrollBar(this, ID_WXSCROLLBAR1, wxPoint(800, 106), wxSize(160, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxScrollBar1"));
	WxScrollBar1->SetScrollbar(10, 15, 100, 10);
	Box_one->Add(WxScrollBar1, 0, wxALIGN_CENTER | wxALL, 2);
	WxColor = new wxButton(this, ID_WXBUTTON2, _("Kolor Gwiazdki"), wxPoint(800, 360), wxSize(150, 30), 0, wxDefaultValidator, _("WxButton1"));
	Box_one->Add(WxColor, 0, wxALIGN_CENTER | wxALL, 5);
	str.Add("Gwiazdka");
	str.Add("Słonce");
	str.Add("Księżyc");
	Wx_figure = new wxChoice(this, ID_WXCHOICE, wxPoint(800, 200), wxDefaultSize, str);
	Wx_figure->SetSelection(0);
	Box_one->Add(Wx_figure, 0, wxALIGN_CENTER | wxALL, 5);
	Pass = new wxGauge(this, ID_WXSCROLLBAR1, 85, wxPoint(800, 106), wxSize(250, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxScrollBar1"));
	Box_one->Add(Pass, 0, wxALIGN_CENTER | wxALL, 4);
	Pass->SetValue(0);
	Box_two = new wxBoxSizer(wxVERTICAL);
	Box_two->Add(Box_one, 0, wxALIGN_RIGHT | wxALL, 5);
	Centre = Banan = wxPoint(340, 240);
	this->SetSizer(Box_two);
	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	Bind(wxEVT_BUTTON, &MyFrame::WxSave_Click, this, ID_WXBUTTON1);
	Bind(wxEVT_TEXT, &MyFrame::WxEdit1_Updated, this, ID_WXEDIT1);
	Bind(wxEVT_CHECKBOX, &MyFrame::WxCheckBox1_Click, this, ID_WXCHECKBOX1);
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::WxScrollBar1_Scroll, this, ID_WXSCROLLBAR1);
	Bind(wxEVT_CHOICE, &MyFrame::WxChoise, this, ID_WXCHOICE);
	Bind(wxEVT_PAINT, &MyFrame::Form_Paint, this);
	Bind(wxEVT_BUTTON, &MyFrame::Choose_Color, this, ID_WXBUTTON2);
	Bind(wxEVT_TIMER, &MyFrame::Timer1_Timer, this, ID_WXTIMER1);
	
	Center();

}
void MyFrame::WxChoise(wxCommandEvent& e)
{
	draw();
}

void MyFrame::WxEdit1_Updated(wxCommandEvent& e)
{

	if (WxEdit1)
	{

		napis = WxEdit1->GetValue();
		draw();
	}
}

//funcja czy chcemy bananka czy nie:-)
void MyFrame::WxCheckBox1_Click(wxCommandEvent& e)
{
	if (WxCheckBox1->IsChecked())
	{
		WxTimer1->Start(100);
		//Lapka();
	}
	else
	{
		WxTimer1->Stop();
		change_bananposition(0);
	}
	draw();

}

void MyFrame::WxScrollBar1_Scroll(wxScrollEvent& e)
{
	if (WxCheckBox1->IsChecked())

	{
		a = WxScrollBar1->GetThumbPosition();
		Pass->SetValue(a);
		change_bananposition(a);
		draw();
		
	}
}



void MyFrame::WxSave_Click(wxCommandEvent& e)
{
	wxString filename;
	wxFileDialog WxSaveFileDialog1(this, _("Choose a directory"), _(""), _(""), _("*.*"), wxFD_SAVE);
	WxSaveFileDialog1.SetWildcard("PNG files (*.png)|*.png");
	if (WxSaveFileDialog1.ShowModal() == wxID_CANCEL) return;
	else 
	{
		wxImage ToSave = MyBitmap.ConvertToImage();
		ToSave.AddHandler(new wxPNGHandler);
		ToSave.SaveFile(WxSaveFileDialog1.GetPath());
	}
}



void MyFrame::Form_Paint(wxPaintEvent& event)
{

	this->draw();
}
void MyFrame::draw()
{
	if (a == 0) {
		Banan = wxPoint((GetSize().x - 200) / 2 - 80, GetSize().y / 2 + 30);
		Centre = Banan;
	}
	wxPoint pts[3] =
	{
		wxPoint((GetSize().x - 200) / 2 - 40, GetSize().y / 2 + 80),  wxPoint((GetSize().x - 200) / 2, GetSize().y / 2 + 30),
		 wxPoint((GetSize().x - 200) / 2 + 40, GetSize().y / 2 + 80)
	};
	
		wxPoint ptsB[3] =

		{
			wxPoint(Banan.x+50,Banan.y+10),  wxPoint((GetSize().x - 200) / 2, GetSize().y / 2 - 10),
			 wxPoint((GetSize().x - 200) / 2 + 30, GetSize().y / 2 + 40),
		};
		wxPoint star[5] = { wxPoint(60*GetSize().x/1000,80* GetSize().y / 600),wxPoint(35 * GetSize().x / 1000,35 * GetSize().y / 600),wxPoint(90 * GetSize().x / 1000,60 * GetSize().y / 600),wxPoint(30 * GetSize().x / 1000,60 * GetSize().y / 600),wxPoint(80 * GetSize().x / 1000,35 * GetSize().y / 600)};
	std::unique_ptr<wxClientDC> events(new wxClientDC(this));
	MyBitmap = wxBitmap(this->GetSize());
	std::unique_ptr<wxBufferedDC> buffer(new wxBufferedDC(events.get(), MyBitmap));
	buffer->SetBackground(wxColor(255, 255, 255));
	buffer->Clear();
	wxPen MyPen;

	buffer->SetFont(wxFont(30, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, _("Tahoma")));
	buffer->DrawRotatedText(napis, wxPoint((GetSize().x - 200) / 2+80, GetSize().y / 2 + 80), 90);
	buffer->SetFont(wxFont(25, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, _("Romana")));
	buffer->DrawText(napis, wxPoint((GetSize().x - 200) / 2 - 80, GetSize().y / 2+90));
	buffer->SetPen(wxPen(*wxBLACK, 2));
	
	//głowa
	buffer->DrawCircle((GetSize().x-200)/2, GetSize().y/2-50, 20);
	buffer->DrawLine((GetSize().x - 200) /2, GetSize().y / 2 - 30, (GetSize().x - 200) / 2, GetSize().y / 2+30);
	buffer->DrawCircle((GetSize().x - 200) / 2-5, GetSize().y / 2 - 60, 4);
	buffer->DrawCircle((GetSize().x - 200) / 2 + 5, GetSize().y / 2 - 60, 4);


	buffer->DrawLines(3, pts);


	if (WxCheckBox1->IsChecked())
	{

		

		MyImage.AddHandler(new wxPNGHandler);
		MyImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
		MyBitmap = wxBitmap(MyImage);
		buffer->DrawBitmap(MyBitmap, Banan);
		//zmiana miny
		buffer->DrawArc((GetSize().x - 200) / 2 - 7, GetSize().y / 2 - 40, (GetSize().x - 200) / 2 + 7, GetSize().y / 2 - 40, (GetSize().x - 200) / 2, GetSize().y / 2 - 39);

		buffer->DrawLines(3, ptsB);
	}
	else
	{
		buffer->DrawLines(3, ptsB);
		buffer->DrawLine((GetSize().x - 200) / 2 - 7, GetSize().y / 2 - 40, (GetSize().x - 200) / 2 + 7, GetSize().y / 2 - 40);
	}

	if (Wx_figure->GetSelection() == 1)
	{
		buffer->SetBrush(wxBrush(wxColor(255, 255, 0)));
		buffer->SetPen(wxPen(*wxBLACK, 1));
		buffer->DrawCircle(250 * GetSize().x / 1000, 100 * GetSize().y / 600, 30);
	}
	else if (Wx_figure->GetSelection() == 2)

	{
		buffer->SetBrush(wxBrush(wxColor(0, 255, 255)));
		buffer->DrawArc(250*GetSize().x / 1000, 100 * GetSize().y / 600, 280*GetSize().x / 1000, 150 * GetSize().y / 600, 265 * GetSize().x / 1000, 125 * GetSize().y / 600);
	}
	else
	{
		buffer->SetBrush(wxBrush(currentcolor));
		buffer->DrawPolygon(5, star, 250 * GetSize().x / 1000, 100* GetSize().y / 600);
	}
	buffer->CalcBoundingBox(this->GetSize().x, this->GetSize().y);

}
void MyFrame::Lapka()
{
	if (!WxCheckBox1->IsChecked()) return;
	WxScrollBar1->SetThumbPosition(a);
	if(a<85)
		a++;
	a--;
	change_bananposition(a);
	draw();
	Lapka();

}
void MyFrame::change_bananposition(int a)
{

	Banan.y = Centre.y - a / 2;
	if (a < 43)
		Banan.x = Centre.x - a / 10;
	else
		Banan.x = Centre.x + a / 20;
	
}
void MyFrame::Choose_Color(wxCommandEvent& e)
{
	wxColourDialog ColorDialog(this, nullptr);
	if (ColorDialog.ShowModal() == wxID_CANCEL)
		return;
	currentcolor = ColorDialog.GetColourData().GetColour();
	draw();
}
void MyFrame::Timer1_Timer(wxTimerEvent& e)
{
	//wxDateTime now = wxDateTime::Now();
	
	//WxStaticText1->SetLabel(wxString::Format("%d", now.GetHour()) + ":" + wxString::Format("%02d", now.GetMinute()) + ":" + wxString::Format("%02d", now.GetSecond()));
	/*WxScrollBar1->SetThumbPosition(a++);
	Pass->SetValue(a);
	this->change_bananposition(a);
	this->draw();*/
	if ((a) > 85 || x==1)
	{
		WxScrollBar1->SetThumbPosition(a--);
		Pass->SetValue(a);
		this->change_bananposition(2*a);
		this->draw();
		x = 1;
		if (a == 0)
			x = 0;
	}
	else {
		WxScrollBar1->SetThumbPosition(a++);
		Pass->SetValue(a);
		this->change_bananposition(2*a);
		this->draw();
	}
}
