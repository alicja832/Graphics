#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}
Matrix4 scaled(Vector4& scale, double w, double h,double transZ)
{
	Matrix4 T;
	T.data[0][0] = scale.GetX() * w / 180.-transZ/2;
	T.data[1][1] = scale.GetY() * h / 180.-transZ/2;// +transZ;
	T.data[2][2] = scale.GetZ() * w / 180.-transZ/2;
	return T;
}
Matrix4 translation(Vector4& translation,double w,double h)
{
	Matrix4 T;
	T.data[0][3] = translation.GetX()*w/100.-w/2.;
	T.data[1][3] = -translation.GetY()*h/100.+ 1.5*h;
	T.data[2][3] = translation.GetZ() * h / 100. - w / 2.;//poniewa¿ na wejsciu by³o na 100(srodek)
	T.data[0][0] = 1;
	T.data[1][1] = 1;
	T.data[2][2] = 1;
	return T;
}
Matrix4 rotation(Vector4& rotation)
{
	Matrix4 TX;
	double x = rotation.GetX() * M_PI/180.;
	TX.data[0][0] = 1;
	TX.data[1][1] = -cos(x);
	TX.data[1][2] = -sin(x);
	TX.data[2][1] = sin(x);
	TX.data[2][2] = cos(x);
	TX.data[3][3] = 1;
	Matrix4 TY;
	double y= rotation.GetY() * M_PI / 180.;
	TY.data[0][0] = cos(y);
	TY.data[0][2] = sin(y);
	TY.data[1][1] = 1;
	TY.data[2][0] = -sin(y);
	TY.data[2][2] = cos(y);
	TY.data[3][3] = 1;
	Matrix4 TZ;
	double z = rotation.GetZ() * M_PI / 180.;
	TZ.data[0][0] = cos(z);
	TZ.data[0][1] = -sin(z);
	TZ.data[1][0] = sin(z);
	TZ.data[1][1] = cos(z);
	TZ.data[2][2] = 1;
	TZ.data[3][3] = 1;
	Matrix4 T = TX * TY * TZ;
	return T;

}

void GUIMyFrame1::Repaint()
{
	if (data.empty())
		return;

	//wektory do transformacji obrazu 3D
	Vector4 trans;
	trans.Set(WxSB_TranslationX->GetValue(),
		WxSB_TranslationY->GetValue(),
		WxSB_TranslationZ->GetValue());
	Vector4 rotate;
	rotate.Set(-WxSB_RotateX->GetValue(),
		-WxSB_RotateY->GetValue(),
		-WxSB_RotateZ->GetValue());
	Vector4 scale;
	scale.Set(WxSB_ScaleX->GetValue(),
		WxSB_ScaleY->GetValue(),
		WxSB_ScaleZ->GetValue());
	double w = WxPanel->GetSize().x;
	double h = WxPanel->GetSize().y;


	std::unique_ptr<wxClientDC> events(new wxClientDC(WxPanel));
	wxBitmap MyBitmap = wxBitmap(WxPanel->GetSize());
	std::unique_ptr<wxBufferedDC> buffer(new wxBufferedDC(events.get(), MyBitmap));

	//macierz przekszta³cajaca
	Matrix4 T= translation(trans,w,h)*
		rotation(rotate)*scaled(scale,w,h, WxSB_TranslationZ->GetValue());
	buffer->Clear();
	// Napisaæ program do dwuwymiarowej wizualizacji obiektów trójwymiarowych wyœwietlanych metod¹ 
	//krawêdziow¹.
	Vector4 elem_1;
	Vector4 elem_2;

	int k = data.size();
	int i;
	for (i = 0; i < k; i++) {

			elem_1.Set(data[i].begin.x,
				data[i].begin.y,
				data[i].begin.z);
			elem_2.Set(data[i].end.x,
				data[i].end.y,
				data[i].end.z);


			elem_1 = T * elem_1;
			elem_1.Set(elem_1.GetX() / elem_1.data[3], elem_1.GetY() / elem_1.data[3],
				elem_1.GetZ() / elem_1.data[3]);


			elem_2 = T * elem_2;
			elem_2.Set(elem_2.GetX() / elem_2.data[3], elem_2.GetY() / elem_2.data[3],
				elem_2.GetZ() / elem_2.data[3]);
		
	buffer->SetPen(wxColor(data[i].color.R, data[i].color.G, data[i].color.B));
	buffer->DrawLine(elem_1.GetX(),elem_1.GetY(), elem_2.GetX(), elem_2.GetY());
	}
	
}
	
	