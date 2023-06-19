#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	wxImage Img_Tmp= Img_Org.Copy();
	//Img_Cpy = Img_Cpy.ConvertToGreyscale();
	unsigned char* v = Img_Cpy.GetData();
	int width= Img_Cpy.GetSize().x; 
	int height= Img_Cpy.GetSize().y;
	int n = width * height;
	unsigned char* k = (unsigned char*)malloc(3 * n * sizeof(unsigned char));
	double r,r1;
	double g,g1;
	double b,b1;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			/*for (int i = 0; i < 3 * n; i++)
			{
				if (!(i % 3)) {
					r= double(double(v[i]) / 255.) * 6.5;
					k[i] = abs(sin(r)) * 255.;
				}
				if (!(i % 2) && i!=0)
				{
					r = double(double(v[i]) / 255.) * 6.5 ;

					k[i] = abs(cos(r)) * 255.;
					
				}
				else {
					if (i != 0)
					{
						
						r = double(double(v[i]) / 255.) * 6.5;
						k[i] = abs(sin(r + 3.1415)) * 255.;
					}
				}*/
				

			//}

			r = double(Img_Cpy.GetRed(i, j)) / 255. * 6.5 ;
			g = double(Img_Cpy.GetGreen(i, j)) / 255. * 6.5 ;
			b = double(Img_Cpy.GetBlue(i, j)) / 255. * 6.5 ;
			//double x = rotation.GetX() * M_PI / 180.;
			r1 = sin(r)>0 ?(128.+sin(r)*128.):(abs(sin(r)) * 128.);
			g1 = cos(g)>0 ? (128. + cos(g) * 128.):(abs(cos(g)) * 128.);
			b1 = sin(b + 3.1415)>0 ? (128. + sin(b + 3.1415) * 128.) : (abs(sin(b + 3.1415)) * 128.);
			
			/*if (v[i] < 128)
				k[i] = 0;
			else if (v[i] > 128)
				k[i] = 255;
			else
				k[i] = v[i];*/
			Img_Tmp.SetRGB(i, j, r1, g1, b1);
		}
	}
	//Img_Cpy.SetData(k);
	
	Img_Cpy = Img_Tmp.Copy();
	Repaint();
	//Repaint();

 // TO DO: Konwersja do skali szarosci    
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy=Img_Cpy.Blur(5);
	Repaint();
 // TO DO: Rozmywanie obrazu (blur)
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
 // TO DO: Odbicie lustrzane
	Img_Cpy = Img_Org.Copy();
	Img_Cpy = Img_Cpy.Mirror();
	Repaint();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
	Repaint();
 // TO DO: Zamiana kolorow 
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow);
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Rescale(320, 240);
	dc.Clear();
	Repaint();
 // TO DO: Zmiana rozmiarow do 320x240
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy = Img_Cpy.Rotate(M_PI/6.0,wxPoint(Img_Cpy.GetWidth()/2., Img_Cpy.GetHeight()/ 2.));
 // TO DO: Obrot o 30 stopni
	Repaint();
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
	Repaint();
 // TO DO: Przesuniecie Hue o 180 stopni
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow);
	dc.Clear();
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 255, 255, 255);
	Repaint();
 // TO DO: Ustawienie maski obrazu
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	//copy
	Img_Cpy = Img_Org.Copy();
	wxImage Img_tmp = Img_Cpy.Copy();
	Img_Cpy = Img_Cpy.ConvertToGreyscale();

	unsigned char* v = Img_Cpy.GetData();
	int width = Img_Cpy.GetSize().x;
	int height = Img_Cpy.GetSize().y;
	double suma_x,suma_y,s;
	for (int j = 1; j < height-1; j++)
	{
		for (int i = 1; i < width-1; i++)
		{
			suma_y = +Img_Cpy.GetRed(i - 1, j) + Img_Cpy.GetRed(i - 1, j - 1) + Img_Cpy.GetRed(i - 1, j + 1)
				- Img_Cpy.GetRed(i + 1, j) - Img_Cpy.GetRed(i + 1, j - 1) - Img_Cpy.GetRed(i + 1, j + 1);
			suma_x= +Img_Cpy.GetRed(i - 1, j+1) +Img_Cpy.GetRed(i + 1, j +1) + Img_Cpy.GetRed(i, j + 1)
				- Img_Cpy.GetRed(i - 1, j-1) - Img_Cpy.GetRed(i , j - 1) - Img_Cpy.GetRed(i + 1, j -1);
			s = sqrt(suma_y * suma_y + suma_x * suma_x);
			if (s < 0) s = 0;
			else if (s > 255) s = 255;
			Img_tmp.SetRGB(i, j, s, s, s);
		}

	}
	Img_Cpy = Img_tmp.Copy();
	Repaint();
 // TO DO: Pionowa maska Prewitta
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* v = Img_Cpy.GetData();
	int n = Img_Cpy.GetSize().x * Img_Cpy.GetSize().y;
	unsigned char* k = (unsigned char*)malloc(3 * n * sizeof(unsigned char));
	for (int i = 0; i < 3 * n; i++)
	{
		if (v[i] < 128)
			k[i] = 0;
		else if (v[i] > 128)
			k[i] = 255;
		else
			k[i] = v[i] ;

	}
	Img_Cpy.SetData(k);
	Repaint();

 // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
}


void GUIMyFrame1::Contrast(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* v = Img_Cpy.GetData();
	int n = Img_Cpy.GetSize().x * Img_Cpy.GetSize().y;
	unsigned char* k = (unsigned char*)malloc(3 * n * sizeof(unsigned char));
	double l;
	for (int i = 0; i < 3 * n; i++)
	{
		l = v[i];
		if (((l - 0.5*255) * ((double)value/100.+1) + 0.5*255) < 0)
			k[i] = 0;
		else if ((((l - 0.5*255) *((double) value/100.+1) + 0.5*255))> 255)
			k[i] = 255;
		
		else
			k[i] = ((l - 0.5*255) * ((double)value/100.+1) + 0.5*255);

	}
	Img_Cpy.SetData(k);
	Repaint();
 // TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia

}

void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char *v = Img_Cpy.GetData();
	int n = Img_Cpy.GetSize().x*Img_Cpy.GetSize().y;
	unsigned char* k = (unsigned char*)malloc(3*n*sizeof(unsigned char));
	for (int i = 0; i < 3 * n; i++)
	{
		if (v[i] + value < 0)
			k[i] = 0;
		else if (v[i] + value > 255)
			k[i] = 255;
		else
			k[i] = v[i] + value;
		
	}
	Img_Cpy.SetData(k);
	Repaint();
 // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
}