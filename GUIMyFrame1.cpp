
#include "GUIMyFrame1.h"
#include "CImg.h"
#include "FreeImage/FreeImage.h"

using namespace cimg_library;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{

}
void GUIMyFrame1::m_scrolledWindow_update(wxUpdateUIEvent& event)
{ 
   // Repaint();
}
void GUIMyFrame1::resize(wxSizeEvent& event)
{
    actual_size_x = this->GetClientSize().GetWidth() - 100;
    actual_size_y = this->GetClientSize().GetHeight();
    if (cp_image.IsOk())
    {
        wxImage tmp = cp_image.Scale(this->GetClientSize().GetWidth() - 100, this->GetClientSize().GetHeight());
        cp_image = tmp.Copy();
        //cp_image = This_image.Copy();
        exif();
        Repaint();
    }
}

void GUIMyFrame1::Repaint()
{
  
   // cp_image.Resize(m_panel1->GetSize(), m_panel1->GetPosition());
    wxClientDC dc(m_panel1);// Pobieramy kontekst okna
    dc.Clear();
    wxBitmap bitmap(cp_image);          // Tworzymy tymczasowa bitmape na podstawie Img_Cp
    dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
   
}

void GUIMyFrame1::wx_button1click(wxCommandEvent& event)
{
    
        wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("JPEG file(*.jpg) | *.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
       
       if (WxOpenFileDialog.ShowModal() == wxID_OK)
        {
           
           name = wxString(WxOpenFileDialog.GetPath());
           //CImg<unsigned char> src(name);
           //zapisujemy obrazek
           wxImage::AddHandler(new wxJPEGHandler);
           wxImage image;
           image.LoadFile(name);
           This_image = image.Copy();
           cp_image = This_image.Copy().Scale(actual_size_x, actual_size_y);
          
             FIBITMAP* bitmap;
             bitmap = FreeImage_Load(FIF_JPEG, WxOpenFileDialog.GetPath(), JPEG_DEFAULT);
             width = FreeImage_GetWidth(bitmap);
             height = FreeImage_GetHeight(bitmap);

             const char* t[6] = { "Artist","Copyright","ResolutionUnit","XResolution",
            "YCbCrPositioning",
             "YResolution"
             };
           
             
             //We can get exif information about image
             FITAG* tag;
         
             for (int i = 0; i < 6; i++) {
                 tag = NULL;
                 FreeImage_GetMetadata(FIMD_EXIF_MAIN, bitmap, t[i], &tag);
                 const char *k = FreeImage_TagToString(FIMD_EXIF_MAIN, tag);
                 //? (FIMD_EXIF_EXIF, tag);
                 information[i] = wxString(std::string(k));
                // buffer->DrawText(std::string(t[i]) + " : " + std::string(k),
                  //   wxPoint(buffer->GetSize().x / 20., buffer->GetSize().y / 20. + (i + 1) * 20));

             }
             exif();
             Repaint();
               
               
       }
       
    
}
void GUIMyFrame1::exif()
{
    std::unique_ptr<wxClientDC> events(new wxClientDC(m_panel3));
    wxBitmap MyBitmap = wxBitmap(m_panel3->GetSize());
    std::unique_ptr<wxBufferedDC> buffer(new wxBufferedDC(events.get(), MyBitmap));
 
    buffer->SetBackground(wxColor(0, 0, 0));

    buffer->DrawText("EXIF Info:",
        wxPoint(buffer->GetSize().x / 20., buffer->GetSize().y / 20. + 10));
    buffer->DrawText("Rozmiar Obrazka:" + std::to_string(width) + "*" + std::to_string(height),
        wxPoint(buffer->GetSize().x / 25., buffer->GetSize().y / 25.));
    const char* t[6] = { "Artist","Copyright","ResolutionUnit","XResolution",
       "YCbCrPositioning",
        "YResolution"
    };
   
    //const char* dane[4];

    //We can get exif information about image
    int i, j;
    for (i = 0,j=1; i < 6,j<13; i++,j+=2) {
      
      
        buffer->DrawText(std::string(t[i]) + " : ",
            wxPoint(buffer->GetSize().x / 20., buffer->GetSize().y / 20. + (j) * 20));

        buffer->DrawText(information[i],
            wxPoint(buffer->GetSize().x / 20., buffer->GetSize().y / 20. + (j + 1) * 20));

    }
}

void GUIMyFrame1::m_button2click(wxCommandEvent& event) 
{ 
    cp_image = This_image.Copy();
    wxImage tmp = cp_image.Copy();
    double width = cp_image.GetWidth();
    double height = cp_image.GetHeight();
    CImg<unsigned char> src(width, height, 1, 3);
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
             src(i, j, 0, 0)=cp_image.GetRed(i,j);
             src(i, j, 0, 1)= cp_image.GetGreen(i, j);
             src(i, j, 0, 2)= cp_image.GetBlue(i, j);
        }
    }
    const float x = 5.0;
    src.blur(x, true, true);
   
    int r, g, b;
            
    for (int j = 20; j < (79); j++)
    {
        for (int i =467; i < 569; i++)
        {
             r= src(i,j,0,0);
             g= src(i, j, 0, 1);
             b= src(i, j, 0, 2);
             tmp.SetRGB(i, j, r, g, b);
        }
    }
    //tmp.SetData(new_data);
    cp_image = tmp.Copy().Scale(actual_size_x,actual_size_y);

    //src.save("nowy");
    Repaint();
}
void GUIMyFrame1::m_button3_click(wxCommandEvent& event) 
{
    cp_image = This_image.Copy();
    wxImage tmp = cp_image.Copy();
    CImg<unsigned char> src(cp_image.GetWidth(), cp_image.GetHeight(), 1, 3);

    for (int j = 0; j < (533); j++)
    {
        for (int i = 0; i < 800; i++)
        {
            src(i, j, 0, 0) = cp_image.GetRed(i, j);
            src(i, j, 0, 1) = cp_image.GetGreen(i, j);
            src(i, j, 0, 2) = cp_image.GetBlue(i, j);
        }
    }
    const unsigned int 	s = 5;
    src.erode(s);

    int r, g, b;

    for (int j = 0; j < (533); j++)
    {
        for (int i = 0; i < 800; i++)
        {
            r = src(i, j, 0, 0);
            g = src(i, j, 0, 1);
            b = src(i, j, 0, 2);
            tmp.SetRGB(i, j, r, g, b);
        }
    }
    //tmp.SetData(new_data);
    cp_image = tmp.Copy().Scale(actual_size_x, actual_size_y);
    //src.save("nowy");
    Repaint();

  
}
void GUIMyFrame1::m_check(wxCommandEvent& event)
{

    gauge1->Show();
    cp_image = This_image.Copy();
    wxImage tmp = cp_image.Copy();

    CImg<unsigned char> src1(cp_image.GetWidth(), cp_image.GetHeight(), 1, 3);

    for (int j = 0; j < (533); j++)
    {
        for (int i = 0; i < 800; i++)
        {
            src1(i, j, 0, 0) = cp_image.GetRed(i, j);
            src1(i, j, 0, 1) = cp_image.GetGreen(i, j);
            src1(i, j, 0, 2) = cp_image.GetBlue(i, j);
        }
    }
    float color[3] = { 1, 1, 1 };
    const float sigma = 10.;
    const float w = cp_image.GetWidth();
    const float h = cp_image.GetHeight();

    /*for (int j = 0; j < (533); j++)
    {
        for (int i = 0; i < 800; i++)
        {
            gauge1->SetValue(i/100);
            src(i, j, 0, 0) = cp_image.GetRed(i, j);
            src(i, j, 0, 1) = cp_image.GetGreen(i, j);
            src(i, j, 0, 2) = cp_image.GetBlue(i, j);
        }
    }*/

    for (int i = 0; i < 120; i++)
    {
        cp_image = This_image.Copy();
        wxImage tmp = cp_image.Copy();
        CImg <float> src(w, h, 1, 3);
        CImg <float> srctmp(w, h, 1, 3);
        gauge1->SetValue(i);
        src.draw_gaussian((w / 2.) + (w * 0.3) * cos((i + 60.0f) * M_PI / 60.f),
            (h / 2.) + (h * 0.3) * sin((i + 60.0f) * M_PI / 60.f),
            120.0f,
            color, 1);
        for (int j = 0; j < (533); j++)
        {
            for (int i = 0; i < 800; i++)
            {
                src1(i, j, 0, 0) = cp_image.GetRed(i, j);
                src1(i, j, 0, 1) = cp_image.GetGreen(i, j);
                src1(i, j, 0, 2) = cp_image.GetBlue(i, j);
            }
        }
       /* srctmp.draw_gaussian(
            (width / 2.) + (w * 0.3) * cos((i * 60.f) * M_PI / 60.f),
            (height / 2.) + (height * 0.3) * sin((i * 60.f) * M_PI / 60.f),
            120.0f,
            color,
            1.0f);
        src += srctmp;*/
        src1.mul(src);

        //src.draw_gaussian(250, sigma, &src._spectrum, 1);
        int r, g, b;

        for (int j = 0; j < (533); j++)
        {
            for (int i = 0; i < 800; i++)
            {
                r = src1(i, j, 0, 0);
                g = src1(i, j, 0, 1);
                b = src1(i, j, 0, 2);
                tmp.SetRGB(i, j, r, g, b);
            }
        }
        cp_image = tmp.Copy().Scale(actual_size_x, actual_size_y);
       
        Repaint();
    }
    gauge1->Hide();
   
}
