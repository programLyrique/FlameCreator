#include "function.h"

using namespace std;

Function::Function() : m_name(""), m_expr(""), m_latex("")
{
}

string Function::getName() const
{
    return m_name;
}

string Function::getExpr() const
{
    return "f(x,y) = (" + m_expr + ")";
}

string Function::getLatex() const
{
    return "f(x,y) = ("+ m_latex + ")";
}

Identity::Identity() : Function()
{
    m_name="Identity";
}

void Identity::apply(double &x, double &y)
{
     x = x;
     y = y;
}



void Affinity::apply(double &x, double &y)
{
    double temp = x;
    x = m_fX[0] * x + m_fX[1] * y + m_fX[2];
    y = m_fY[0] * temp + m_fY[1] * y + m_fY[2];
}

Affinity::Affinity(double a1, double a2, double b1, double b2, double c1, double c2) : Function()
{
    setCoeff(a1, a2, b1, b2, c1, c2);
    m_name = "Affinity";
    //m_expr = a1 + "*x+" + b1 + "*y+" + c1 +"," + a2 + "*x+" + b2 + "*y+" + c2 ;

}

const double* Affinity::getFX() const
{
    return m_fX;
}

const double * Affinity::getFY() const
{
    return m_fY;
}

void Affinity::setCoeff(double a1, double a2, double b1, double b2, double c1, double c2)
{
    m_fX[0] = a1;
    m_fX[1] = b1;
    m_fX[2] = c1;

    m_fY[0] = a2;
    m_fY[1] = b2;
    m_fY[2] = c2;
}




Sinusoidal::Sinusoidal() : Function()
{
    m_name = "Sinusoïdal";
    m_expr = "sin(x),sin(y)";
    m_latex = "\\sin(x) , \\sin(y)";
}

void Sinusoidal::apply(double &x, double &y)
{
    x = sin(x);
    y = sin(y);
}




GenFunction::GenFunction(unsigned int nbFun) : Function(),m_variations(nbFun,0),m_functions(nbFun,new Identity()),m_affinity(0),m_color(0)
{
    m_affinity = new Affinity(1,0,0,1,0,0);
    m_postTransform = new Affinity(1,0,0,1,0,0);
}

void GenFunction::apply(double &x, double &y)
{
    double a(0),b(0);

    for(unsigned int i(0); i <m_variations.size() ; i++)
    {
        double x1(x),y1(y);

        // We calculate for the affinity
        m_affinity->apply(x1, y1);
        //Then we "compose" the result
        m_functions[i]->apply(x1, y1);
        a += m_variations[i] * x1;
        b += m_variations[i] * y1;
    }
    x = a;
    y = b;
    //Finally, all that passes through the post transform ( to change the coordinate system, for instance
    m_postTransform->apply(x,y);
}

int GenFunction::getColor() const
{
    return m_color;
}

void GenFunction::setColor(int color)
{
    m_color = color;
}

void GenFunction::setAffinity(Affinity affinity)
{
    m_affinity = new Affinity(affinity);
}

void GenFunction::setPostTransform(Affinity affinity)
{
    m_postTransform = new Affinity(affinity); // Need to destroy the post transform et the pre transform ?
}

void GenFunction::setFunction(unsigned int num, Function *function)
{
    if( num < m_functions.size())
    {
        m_functions[num] = function;
    }
}

GenFunction::~GenFunction()
{
    delete m_affinity;
    delete m_postTransform;
}

char GenFunction::toAlpha(int color)
{
    return (color >> 24) & 0xff;
}

char GenFunction::toRed(int color)
{
    return (color >> 16) & 0xff;
}

char GenFunction::toGreen(int color)
{
    return (color >> 8) & 0xff;
}

char GenFunction::toBlue(int color)
{
    return color & 0xff;
}

int GenFunction::toColor(char alpha, char red, char green, char blue)
{
    return (alpha << 24) & (red << 16) & (green << 8) & blue;
}


Spherical::Spherical() : Function()
{
    m_name="Spherical";
    m_expr="1/r^2 * x, 1/ r^2 * y";
    m_latex=" \frac{x}{r^2}, \frac{y}{r^2}";
}

void Spherical::apply(double &x, double &y)
{
    double rCarre = x*x + y*y;
    x = x / rCarre;
    y = y / rCarre;
}
