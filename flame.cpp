#include "flame.h"

using namespace std;

Flame::Flame(unsigned long width, unsigned long height) :
    m_histogram(width, vector<unsigned long>(height)), m_color(width, vector<unsigned long>(height)), m_width(width), m_height(height),
    m_scale(100), m_image(0)
{
    m_image = new unsigned char[m_height * m_width];
    srand(time(0)); // And what if the user has already initialized the random generator ?
}

void Flame::render(unsigned long long nbIterations)
{
    // We select a point in the bi-unit square ( [ -1, 1] )
    double x = (rand() % 20000 - 10000) / 20000;
    double y = (rand() % 20000 - 10000) / 20000 ;
    int nbFunctions = m_functions.size();

    // Always 20 + nbIterations iterations at least, the 20 first of which are not plotted.
    for(unsigned i(0); i < 20 ; i++)
    {
        int numFonc = rand() % nbFunctions;
        m_functions[numFonc]->apply(x,y);
    }

    for(unsigned long long i(0); i < nbIterations ; i++ )
    {
        int numFonc = rand() % nbFunctions;
        m_functions[numFonc]->apply(x,y);
        m_histogram[toX(x)][toY(y)] += 1;
    }
}

unsigned char *Flame::toImage()
{
    unsigned char *image = new unsigned char[m_width * m_height];
    //Copy m_image into image : memcpy ?
    return image;
}

unsigned long Flame::getWidth() const
{
   return m_width;
}

unsigned long Flame::getHeight() const
{
    return m_height;
}

double Flame::getScaleFactor() const
{
    return m_scale;
}

void Flame::setScaleFactor(double scaleFactor)
{
    if (m_scale != 0)
    {
        m_scale = scaleFactor;
        clear();// Some recalculations will be needed !
    }
}


/** @todo Giving the histogram and the color array the new dimensions ; idem for the image array
 *
 */
void Flame::setDimensions(unsigned long width, unsigned long height)
{
    m_width = width;
    m_height = height;
    clear();
}

Flame::~Flame()
{
    delete m_image;
}


unsigned long Flame::toX(double x)
{
    return floor(x * m_scale + m_width / 2);
}

unsigned long Flame::toY(double y)
{
    return floor(  - y * m_scale + m_height / 2 );
}

void Flame::clear()
{
    m_histogram.clear();
    m_color.clear();
    delete m_image;
}


