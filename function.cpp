#include "function.h"


void Identity::apply(double &x, double &y)
{
}



void Affinity::apply(double &x, double &y)
{
    double temp = x;
    x = m_fX[0] * x + m_fX[1] * y + m_fX[2];
    y = m_fY[0] * temp + m_fY[1] * y + m_fY[2];
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
