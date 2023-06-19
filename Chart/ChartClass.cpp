#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg= std::move(c);
    x_step=200;
    tab = new wxPoint[x_step];
}

void ChartClass::Set_Range()
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;
 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();
 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();
 for (i=0;i<=x_step;i++)
  {
   y=GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }
 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}


double ChartClass::GetFunctionValue(double x)
{
 if (cfg->Get_F_type()==1) return x*x;
 if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
 return x+sin(x*4.0);
}

void ChartClass::Draw(wxDC* dc, int w, int h)
{
    dc->SetBackground(wxBrush(RGB(255, 255, 255)));
    dc->Clear();
    dc->SetPen(wxPen(RGB(255, 0, 0)));
    dc->DrawRectangle(10, 10, w - 20, h - 20);
    double x0 = cfg->Get_x0();
    double x1 = cfg->Get_x1();
    double y0 = cfg->Get_y0();
    double y1 = cfg->Get_y1();
    double angle = cfg->Get_Alpha();
    double dx = cfg->Get_dX();
    double dy = cfg->Get_dY();
    y_min = Get_Y_min();
    y_max = Get_Y_max();
    double d_X = (x0 + x1) / 2.;
    double d_Y = (y0 + y1) / 2.;


    double x_prim, y_prim;

    wxPoint Centre = wxPoint(w / 2., h / 2.);

    Set_Range();
    if (angle) {
        if (!cfg->RotateScreenCenter())
        {
            T = Get_matrix_translation(dx, dy) * set_scale(double(h / 2.), double(w / 2.)) * Set_scale_Matrix(w - 20, h - 20, x0, x1, y0, y1) * Get_matrix_translation(-d_X, -d_Y);// *Get_matrix_rotationv2(Get_matrix_rotated(-angle), 0, 0);
            Vector x = line2d(T, 0, 0);
            T = Get_matrix_rotationv2(Get_matrix_rotated(-angle), x.GetX(), x.GetY()) * Get_matrix_translation(dx, dy) * set_scale(double(h / 2.), double(w / 2.)) * Set_scale_Matrix(w - 20, h - 20, x0, x1, y0, y1) * Get_matrix_translation(-d_X, -d_Y);
        }

        
        else
        {
            T = Get_matrix_rotationv2(Get_matrix_rotated(-angle), Centre.x, Centre.y)*Get_matrix_translation(dx, dy) * set_scale(double(h / 2.), double(w / 2.)) * Set_scale_Matrix(w - 20, h - 20, x0, x1, y0, y1)* Get_matrix_translation(-d_X,-d_Y);
        }
    }
    else
    {
        T = Get_matrix_translation(dx, dy) * set_scale(double(h / 2.), double(w / 2.))  *Set_scale_Matrix(w - 20, h - 20, x0, x1, y0, y1) *Get_matrix_translation(-d_X, -d_Y);
    } 
    Vector pomoc;
    double x = cfg->Get_x_start();
    double step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
    for (int i = 0; i <= x_step; i++)
    {
        x_prim = x;
        y_prim = GetFunctionValue(x);
        pomoc=line2d(T, x_prim, y_prim);
        tab[i] = wxPoint(pomoc.GetX(),pomoc.GetY());
        x = x + step;
       
    }
    double x_p = cfg->Get_x_start();
    double x_k = cfg->Get_x_stop();
    double line_y =0.;
    //wektory pomocnicze do rysowania osi oraz strza³ek
     Vector pomoc1 = line2d(T, x_p, line_y);
     Vector pomoc2 = line2d(T, x_k, line_y);
     Vector pomoc3 = line2d(T, line_y, y_min);
     Vector pomoc4 = line2d(T, line_y, y_max);
     wxPoint arrow_x[3] = {
          wxPoint(line2d(T, (x_k-0.05), (line_y-0.05)).GetX(),line2d(T, (x_k-0.05), (line_y-0.05)).GetY()),
          wxPoint(pomoc2.GetX(),pomoc2.GetY()),
          wxPoint(line2d(T, (x_k - 0.05), (line_y+0.05)).GetX(),line2d(T, (x_k - 0.05), (line_y+0.05)).GetY()),
     };
     wxPoint arrow_y[3] = {
          wxPoint(line2d(T, (line_y - 0.03), (y_max - 0.06)).GetX(),line2d(T, (line_y - 0.03), (y_max -0.06)).GetY()),
          wxPoint(pomoc4.GetX(),pomoc4.GetY()),
          wxPoint(line2d(T, (line_y + 0.03), (y_max - 0.06)).GetX(),line2d(T, (line_y + 0.03), (y_max - 0.06)).GetY()),
     };

     Set_Range();
    dc->SetClippingRegion(10, 10, w-20, h-20);
    //rysowanie osi
    dc->SetPen(wxPen(RGB(0, 0, 255)));
    //punkty na podzia³kê
    wxPoint v[12] = {wxPoint(line2d(T,0.5*x_p,line_y).GetX(),line2d(T,0.5 * x_p,line_y-0.05).GetY()),
        wxPoint(line2d(T,0.5 * x_p,line_y).GetX(),line2d(T,0.5 * x_p,line_y+0.05).GetY()),
        wxPoint(line2d(T,line_y,Get_Y_min()/2.0).GetX()-10,line2d(T,0.5 * line_y,Get_Y_min() / 2.0).GetY()),
        wxPoint(line2d(T,line_y,Get_Y_min() / 2.0).GetX()+10,line2d(T,0.5 * line_y,Get_Y_min() / 2.0).GetY()),
        wxPoint(line2d(T,1./3. * x_k,line_y).GetX(),line2d(T,1. / 3. * x_k,line_y).GetY() - 10),
        wxPoint(line2d(T,1. / 3. * x_k,line_y).GetX(),line2d(T,1. / 3. * x_k,line_y).GetY() + 10),
        wxPoint(line2d(T,2. / 3. * x_k,line_y).GetX(),line2d(T,2. / 3. * x_k,line_y).GetY() - 10),
        wxPoint(line2d(T,2. / 3. * x_k,line_y).GetX(),line2d(T,2. / 3. * x_k,line_y).GetY() + 10),
        wxPoint(line2d(T,line_y,2. / 3. * y_max).GetX()-10,line2d(T,line_y ,2. / 3. *y_max).GetY()),
        wxPoint(line2d(T,line_y,2. / 3. * y_max).GetX() + 10,line2d(T,line_y ,2. / 3. * y_max).GetY()),
        wxPoint(line2d(T,line_y,1. / 3. * y_max).GetX() - 10,line2d(T,line_y ,1. / 3. * y_max).GetY()),
        wxPoint(line2d(T,line_y,1. / 3. * y_max).GetX() + 10,line2d(T,line_y ,1. / 3. * y_max).GetY())
    
    };



     dc->DrawLine(v[0], v[1]);
     dc->DrawLine(v[2], v[3]);
     dc->DrawLine(v[4], v[5]);
     dc->DrawLine(v[6], v[7]);
     dc->DrawLine(v[8], v[9]);
     dc->DrawLine(v[10], v[11]);
    
    dc->DrawRotatedText(wxString::Format(wxT("%2.2lf"), cfg->Get_x_start()/2.0), wxPoint(v[0].x + 1, v[0].y + 5), angle);
    dc->DrawRotatedText(wxString::Format(wxT("%2.2lf"), y_min / 2.0), wxPoint(v[2].x + 7, v[2].y), angle);
    dc->DrawRotatedText(wxString::Format(wxT("%2.2lf"), 1. / 3. * x_k), wxPoint(v[4].x + 1, v[4].y + 5), angle);
    dc->DrawRotatedText(wxString::Format(wxT("%2.2lf"), 2. / 3. * x_k), wxPoint(v[6].x + 1, v[6].y + 5), angle);
    dc->DrawRotatedText(wxString::Format(wxT("%2.2lf"), 2. / 3. * y_max), wxPoint(v[8].x + 7, v[8].y), angle);
    dc->DrawRotatedText(wxString::Format(wxT("%2.2lf"), 1. / 3. * y_max), wxPoint(v[10].x + 7, v[10].y), angle);

    //rysowanie wykresu
    //
    dc->DrawLine(wxPoint(pomoc1.GetX(), pomoc1.GetY()), wxPoint(pomoc2.GetX(), pomoc2.GetY()));
    dc->DrawLine(wxPoint(pomoc3.GetX(), pomoc3.GetY()), wxPoint(pomoc4.GetX(), pomoc4.GetY()));
   //rysowanie strzalek
    dc->DrawLines(3, arrow_x);
    dc->DrawLines(3, arrow_y);
    dc->SetPen(wxPen(RGB(0, 255, 0)));
    //rysowanie wykresu
    dc->DrawLines(x_step,tab);
}

Vector ChartClass::line2d(Matrix t, double x1, double y1)
{
    Vector P1,P2;
    P1.Set(x1,y1);
    P2 = T * P1; 
    return P2;
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

Matrix ChartClass::set_scale( double h, double w)
{
    Matrix T_1;
   
    T_1.data[0][0] = 1;
    T_1.data[0][2] = w;
    T_1.data[1][2] = h;
    T_1.data[1][1] = 1;
    
    return T_1;

}
Matrix ChartClass::Set_scale_Matrix(int width, int height, double x0, double x1, double y0, double y1)
{
    Matrix T_2;
    double s_x = width / (x1-x0);
    double s_y = -height / (y1-y0);
    T_2.data[0][0] = s_x;
    T_2.data[1][1] = s_y;
    return T_2;

}
Matrix ChartClass::Get_matrix_rotated(double angle) 
{
    Matrix T_3;
    angle *= M_PI / 180.0;//zamiana na radiany
    T_3.data[0][0] = cos(angle);
    T_3.data[0][1] = -sin(angle);
    T_3.data[1][0] = sin(angle);
    T_3.data[1][1] = cos(angle);

    return T_3;
}
Matrix ChartClass::Get_matrix_translation(double dx, double dy)
{
    Matrix T_4;
    T_4.data[0][0] = 1;
    T_4.data[0][2] = dx;
    T_4.data[1][2] = dy;
    T_4.data[1][1] = 1;

    return T_4;
}
Matrix ChartClass::Get_matrix_rotationv2(Matrix  t,double x, double y)
{
    Matrix T_5;
    T_5.data[0][0] = 1;
    T_5.data[0][2] = x;
    T_5.data[1][2] = y;
    T_5.data[1][1] = 1;
    Matrix T_6;
    T_6.data[0][0] = 1;
    T_6.data[0][2] = -x;
    T_6.data[1][2] = -y;
    T_6.data[1][1] = 1;
    Matrix T_7;
    T_7 = T_5 * t * T_6;

    return T_7;
}
ChartClass::~ChartClass()
{


}