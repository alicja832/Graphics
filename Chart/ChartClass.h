#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
#include "vecmat.h"
#include <vector>
class Matrix;

class ChartClass
{
    private:
        std::shared_ptr<ConfigClass> cfg;
        int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
        double x_min,x_max; // zakres zmiennej x
        double y_min,y_max;// zakres wartosci przyjmowanych przez funkcje
        Matrix T;      //macierz transformacji
        double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji
        wxPoint *tab;//tablica skladaj¹ca siê z punktow na wykresie
        Vector line2d(Matrix t, double x1, double y1);
        // powyzej sugerowana funkcja transformujaca odcinki (jesli ktos ma 
        // inny pomysl mozna ja usunac)
       
    public:
        ChartClass(std::shared_ptr<ConfigClass> c);
        void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
        double Get_Y_min(); // zwraca y_min
        double Get_Y_max(); // zwraca y_max
        void Draw(wxDC *dc, int w, int h);  // rysuje wykres
        Matrix set_scale(double h, double w);
        Matrix Set_scale_Matrix(int width, int height, double x0, double x1, double y0, double y1);
        Matrix Get_matrix_rotated(double angle);
        Matrix Get_matrix_translation(double dx, double dy);
        Matrix Get_matrix_rotationv2(Matrix t,double x, double y);
        ~ChartClass();
};

#endif
