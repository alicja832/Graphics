#include "GUIMyFrame1.h"
#include "wx/dcbuffer.h"
#include <wx/dcmemory.h>
GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
	Bitmap.Create(500, 500, 24);
	PrepareData(0);
	//Repaint();
	
}


void GUIMyFrame1::m_button1_click( wxCommandEvent& event )
{
	PrepareData(1);
	Repaint();
// TODO: Implement m_button1_click
}

void GUIMyFrame1::m_button2_click( wxCommandEvent& event )
{
	PrepareData(2);
	Repaint();
// TODO: Implement m_button2_click
}

void GUIMyFrame1::m_button3_click( wxCommandEvent& event )
{
	PrepareData(3);
	Repaint();
// TODO: Implement m_button3_click
}

void GUIMyFrame1::m_button4_click( wxCommandEvent& event )
{
	PrepareData(4);
	Repaint();
// TODO: Implement m_button4_click
}

void GUIMyFrame1::m_cb_color_click( wxCommandEvent& event )
{

	Repaint();
// TODO: Implement m_cb_color_click
}

void GUIMyFrame1::m_s_rotation_onscroll( wxScrollEvent& event )
{
	m_st_rotation->SetLabel(wxString::Format("Obrot: %d stopni.",m_s_rotation->GetValue()));
	Repaint();
}

void GUIMyFrame1::m_s_tilt_onscroll( wxScrollEvent& event )
{
// TODO: Implement m_s_tilt_onscroll
	Repaint();
}

void GUIMyFrame1::PrepareData(int fun)
{
	int i;
	float x, y;
	srand(376257);

	switch (fun)
	{
	case 0: NoPoints = 5;
		FunctionData[0][0] = -1.0;	FunctionData[0][1] = 1.0;	FunctionData[0][2] = 0.0;
		FunctionData[1][0] = 1.0;	FunctionData[1][1] = 1.0;	FunctionData[1][2] = 25.0;
		FunctionData[2][0] = 1.0;	FunctionData[2][1] = -1.0;	FunctionData[2][2] = 5.0;
		FunctionData[3][0] = -1.0;	FunctionData[3][1] = -1.0;	FunctionData[3][2] = 25.0;
		FunctionData[4][0] = 0.0;	FunctionData[4][1] = 0.0;	FunctionData[4][2] = 15.0;
		break;
	case 1: NoPoints = 20;
		for (i = 0; i < NoPoints; i++)
		{
			x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			FunctionData[i][0] = x;
			FunctionData[i][1] = y;
			FunctionData[i][2] = 200 * (float(rand()) / RAND_MAX);
		}
		break;
	case 2: NoPoints = 100;
		for (i = 0; i < NoPoints; i++)
		{
			x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			FunctionData[i][0] = x;
			FunctionData[i][1] = y;
			FunctionData[i][2] = x * (2 * x - 7) * (2 * y + 1) + 2 * y;
		}
		break;
	case 3: NoPoints = 10;
		for (i = 0; i < NoPoints; i++)
		{
			x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			FunctionData[i][0] = x;
			FunctionData[i][1] = y;
			FunctionData[i][2] = x * sin(2 * y);
		}
		break;
	case 4: NoPoints = 100;
		for (i = 0; i < NoPoints; i++)
		{
			x = 2 * (float(rand()) / RAND_MAX) - 1;
			y = 2 * (float(rand()) / RAND_MAX) - 1;
			FunctionData[i][0] = x;
			FunctionData[i][1] = y;
			FunctionData[i][2] = sin(8 * (x * x + y * y));
		}
		break;
	}
}
float GUIMyFrame1::Shepard(float x, float y)
{
	float w = 0, z = 0;
	float s_w = 0, s_z = 0;
	min = FunctionData[0][2];
	max = min;
	for (int i = 0; i < NoPoints; i++)
	{
		if (FunctionData[i][2] > max)
			max = FunctionData[i][2];
		if (FunctionData[i][2] < min)
			min = FunctionData[i][2];
	}
	for (int i = 0; i < NoPoints; i++)
	{
		w = 1 / abs((x - FunctionData[i][0]) * (x - FunctionData[i][0]) + (y - FunctionData[i][1]) * (y - FunctionData[i][1]));
		s_w += w;
		s_z += w * FunctionData[i][2];
	}
	return s_z / s_w;
}

void GUIMyFrame1::Repaint()
{
	
	double scale =  m_s_tilt->GetValue();
	double alfa= m_s_rotation->GetValue() * M_PI / 180.;
	double width = 1, height = 1. + scale * 0.015;
	wxMemoryDC pan;
	wxClientDC dc(m_panel1);
	pan.SelectObject(Bitmap);

	pan.SetBackground(*wxWHITE_BRUSH);
	pan.Clear();

	

	unsigned char* data = new unsigned char[3 * WIDTH * HEIGHT];


	float Shp[WIDTH][HEIGHT];
	double x,x1, y;

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			x = static_cast<float>(i) / 100.0f - 2.5;
			y = -static_cast<float>(j) / 100.0f + 2.5f;
			x1 =x* cos(alfa) + y * sin(alfa) ;

			y =-(x) * sin(alfa) + (y) * cos(alfa);
			x = x1;

			Shp[i][j] = Shepard(x,y);

		}
	}


	//red-blue map
	if (m_cb_color->IsChecked())
	{
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				float color = (Shp[i][j] - min) / (max - min);
				data[j * WIDTH * 3 + i * 3 + 0] = 255 * color;
				data[j * WIDTH * 3 + i * 3 + 1] = 0;
				data[j * WIDTH * 3 + i * 3 + 2] = 255 * (1 - color);
			}
		}

	}
	//grey scale
	else {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				float color = (Shp[i][j] - min) / (max - min);
				data[j * WIDTH * 3 + i * 3 + 0] = 255 * color;
				data[j * WIDTH * 3 + i * 3 + 1] = 255 * color;
				data[j * WIDTH * 3 + i * 3 + 2] = 255 * color;
			}
		}
	}
	

	
	wxImage Tmp(WIDTH, HEIGHT, data);
	pan.DrawBitmap(wxBitmap(Tmp), 0, 0);
	

	
	dc.Blit(0, 0, 500, 500, &pan, 0, 0);
	pan.SelectObject(wxNullBitmap);
}