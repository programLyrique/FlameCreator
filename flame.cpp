#include "flame.h"

using namespace std;

Flame::Flame(unsigned long width, unsigned long height) :
    m_alpha(width, vector<unsigned long>(height)), m_R(width, vector<float>(height)), m_G(width, vector<float>(height)),
    m_B(width, vector<float>(height)), m_width(width), m_height(height), m_scale(100), m_image(0), m_finalTransform(0)
{
    m_image = new unsigned char[m_height * m_width];
    m_finalTransform = new GenFunction(1);
    m_finalTransform->setFunction(1,0);
    srand(time(0)); // And what if the user has already initialized the random generator ?
}

void Flame::render(unsigned long long nbIterations)
{
    // We select a point in the bi-unit square ( [ -1, 1] ) : precision 10^-4
    double x = (rand() % (2 * PRECISION) - PRECISION) / (2*PRECISION);
    double y = (rand() % (2*PRECISION) - PRECISION) / (2 * PRECISION) ;

    //We select a random normalized color.
    float c_R = (rand() % PRECISION ) / PRECISION;
    float c_G = ( rand() % PRECISION ) / PRECISION;
    float c_B = ( rand() % PRECISION) / PRECISION;

    int nbFunctions = m_functions.size();

    // Always 20 + nbIterations iterations at least, the 20 first of which are not plotted.
    for(unsigned i(0); i < 20 ; i++)
    {
        int numFonc = rand() % nbFunctions;
        m_functions[numFonc]->apply(x,y);
        m_finalTransform->apply(x,y);
    }

    for(unsigned long long i(0); i < nbIterations ; i++ )
    {
        /* Selecting one of the generating functions : equirepartition
         * Will change : probability will depend on the weight of the function.
         **/
        int numFunc = rand() % nbFunctions;
        GenFunction *curFunc = m_functions[numFunc];
        curFunc->apply(x,y);

        //Colors
        updateColors(c_R, c_G, c_B, curFunc->getColor());

        //The final transform, always called
        m_finalTransform->apply(x, y);
        // We also blend the colors with the color of the final transform
        updateColors(c_R, c_G, c_B, m_finalTransform->getColor());

        //Updating the alpha canal
        m_alpha[toX(x)][toY(y)] += 1;
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

void Flame::setFinalTransform(GenFunction *finalTransform)
{
    delete m_finalTransform;
    m_finalTransform = finalTransform;
}

Flame::~Flame()
{
    delete m_image;
    delete m_finalTransform;
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
    m_alpha.clear();
    m_R.clear();
    m_G.clear();
    m_B.clear();
    delete m_image;
}

void Flame::updateColors(float &r, float &g, float &b, int col)
{
    r = (r + GenFunction::toRed(col)/255)/2;
    g = (g + GenFunction::toGreen(col)/255 )/2;
    b =(b + GenFunction::toBlue(col)/255)/2;
}


