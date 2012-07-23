#ifndef FLAME_H
#define FLAME_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "function.h"

//Precision for the randomly generated numbers
#define PRECISION 10000

/**
 * @brief The Flame class
 *
 * Represents a fractal flame, which can be rendered into an image.
 *
 * @todo Resizing, plotting out of the right area @see toX @see setDimensions
 * @todo Creating a copy constructor and so on
 */
class Flame
{
public:
    /**
     * @brief Flame
     * Always rendered centered on the origin.
     * @param width
     * @param height
     */
    explicit Flame(unsigned long width, unsigned long height);

    /**
     * @brief render
     * @param nbIterations number of iterations in the chaos game.
     */
    void render(unsigned long long nbIterations);

    /**
     * @brief toImage
     * @return A RGBA image (copy of the internal representation)
     */
    unsigned char * toImage();

    /**
     * @brief getWidth
     * @return width of the area where is rendered the fractal.
     */
    unsigned long getWidth() const;
    /**
     * @brief getHeight
     * @return height of the area where is rendered the fractal.
     */
    unsigned long getHeight() const;
    /**
     * @brief getScaleFactor
     *
     * If s is the scale factor, 1 pixel = 1/s
     * Default : s = 100
     */
    double getScaleFactor() const;
    /**
     * @brief setScaleFactor
     * @param scaleFactor
     *
     * If s is the scale factor, 1 pixel = 1/ s
     */
    void setScaleFactor(double scaleFactor);

    /**
     * @brief setDimension
     * @param width
     * @param height
     * @attention You have to render again the fractal.
     * @todo Having an intelligent resizing that keeps the origin when reducing the
     * dimensions ; it would make it possible not to render again the fractal in that case.
     */
    void setDimensions(unsigned long width, unsigned long height);

    /**
     * @brief setFinalTransform
     *
     * The final transform is always called, every time in the loop.
     *
     * @param finalTransform
     */
    void setFinalTransform(GenFunction *finalTransform);

    ~Flame();

protected:
    /**
     * @brief toX
     * Convert the coordonnates of the real canevas ( [ -width / 2 ; width/2] x [ -heigth/2 ; height / 2 ] )
     * to the flat coordonnates of the bidimensionnal vectors (change of repere).
     * @todo What if the resulting x is outside of the plotting area ? Fixing that !
     * @param x
     * @return
     */
    unsigned long toX(double x);
    /**
     * @brief toY
     * @param y @see toX
     * @todo @see toX
     * @return
     */
    unsigned long toY(double y);

    /**
     * @brief clear
     *
     * Erase all the histograms and such
     */
    void clear();
    /**
     * @brief updateColors
     * @param r red (normalized)
     * @param g green
     * @param b blue
     * @param col The color of the function
     */
    void updateColors(float& r,float& g,float& b, int col);

    // Use directly an C++ array ?
    // The case (x,y) is incremented by one every time the (x,y) case is got during the chaos game
    std::vector< std::vector<unsigned long> > m_alpha;
    // Color components : in [0,255]. Promoted after that to integers.
    std::vector< std::vector<float> > m_R;
    std::vector< std::vector<float> > m_G;
    std::vector< std::vector<float> > m_B;

    unsigned long m_width;
    unsigned long m_height;

    // Scale factor : by default, 1 pixel = 1/100
    double m_scale;

    // Size : m_width * m_height
    unsigned char *m_image;

    // The generating functions
    std::vector< GenFunction * > m_functions;

    // The final transform
    GenFunction *m_finalTransform;
};

#endif // FLAME_H
