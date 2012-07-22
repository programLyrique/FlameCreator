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


