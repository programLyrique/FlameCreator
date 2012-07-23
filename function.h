#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <cmath>
#include <vector>

/**
 * @brief The Function class
 *
 * All the functions used in to generate a fractal have to inherit that class.
 */
class Function
{
public:
    explicit Function();

    /**
     * @brief apply
     *
     * Calculate the function on x and y
     * @param x
     * @param y
     */
    virtual void apply(double& x, double& y)= 0;
    /**
     * @brief getName
     * @return The name of the function
     * @example Horsehoe
     */
    std::string getName() const;
    /**
     * @brief getExpr
     * @return An textual expression of the function
     */
    std::string getExpr() const;
    /**
      * @brief getLatex
      * @return A Latex expression of the function
      */
     std::string getLatex() const;

     /**
      * @brief ~Function
      */
     virtual ~Function(){};

protected:
    /*
     * Should insert manually , to delimitate the couple, but the functions get*
     * automatically add "f(x,y) = ( <put the necessary> )"
     */
    std::string m_name;
    std::string m_expr;
    std::string m_latex;

};

/**
 * @brief The Identity class
 *
 * The identity function.
 *
 * @todo Identity is an affinity.
 */
class Identity : public  Function
{
public:
    explicit Identity();
    virtual void apply(double& x, double& y);
};

/**
 * @brief The Affinity class
 *
 * The affine functions : f(x,y) = (a1 * x + b1* y + c1, a2 * x + b2 * y + c2 )
 *
 * @attention We want contractive functions or contractove functions in average at least, so
 * choose a and b strictly lesser than 1
 */
class Affinity : public Function
{
public:
    /**
     * @brief Affinity
     *
     * f(x,y) = (a1 * x + b1* y + c1, a2 * x + b2 * y + c2 )
     *
     * @param a1
     * @param a2
     * @param b1
     * @param b2
     * @param c1
     * @param c2
     */
    explicit Affinity(double a1=0, double a2=0, double b1=0, double b2=0, double c1=0, double c2=0);

    /**
     * @brief getFX
     * @return an array with a1, b1, c1
     */
    const double *getFX() const;//Mhummmmm... returning a pointer to a private attribute ?
    /**
     * @brief getFY
     * @return an array with a2, b2, c2
     */
    const double *getFY() const;
    /**
     * @brief setCoeff
     * @param a1
     * @param a2
     * @param b1
     * @param b2
     * @param c1
     * @param c2
     * @see Affinity
     */
    void setCoeff(double a1=0, double a2=0, double b1=0, double b2=0, double c1=0, double c2=0);

    virtual void apply(double& x, double& y);

private:
    // Why not having these attributes public ?
    double m_fX[3];
    double m_fY[3];
};

/**
 * @brief The Sinusoidal class
 *
 * f(x, y) = (sin(x), sin(y))
 */
class Sinusoidal : public Function
{
public:
    explicit Sinusoidal();
    virtual void apply(double& x, double& y);
};

/**
 * @brief The Spherical class
 *
 * f(x,y) = 1/r^2 * (x,y)
 */
class Spherical : public Function
{
public:
    explicit Spherical();
    virtual void apply(double& x, double& y);
};

class GenFunction : public Function
{
public:
    explicit GenFunction(unsigned int nbFun);
    virtual void apply(double &x, double &y);

    /**
     * @brief getColom_variations@return the color of the function in ARGB
     */
    int getColor() const;
    /**
     * @brief setColor
     * @param color ARGB color
     */
    void setColor(int color);
    /**
     * @brief setAffinity
     * @param affinity : the affinity which is composed in the functions
     * default : the affine identity
     */
    void setAffinity(Affinity affinity);
    /**
     * @brief setPostTransform
     * @param affinity : the post transform affinity in which the previous resulting function is applied.
     * Default : the affine identity.
     */
    void setPostTransform(Affinity affinity);
    /**
     * @brief setFunction
     * @param num : from 0 to the number of functions - 1. If num >= number of functions,
     * does nothing.
     * @param function : the function to set
     */
    void setFunction(unsigned int num, Function *function);

    ~GenFunction();

    //Maybe creating a class to manipulate colors ? But too specialized ?

    /**
     * @brief toAlpha
     * @param color
     * @return the alphe component of the ARGB color
     */
    static char toAlpha(int color);
    /**
     * @brief toRed
     * @param color
     * @return the red component of the ARGB color
     */
    static char toRed(int color);
    /**
     * @brief toGreen
     * @param color
     * @return the green component of the ARGB color
     */
    static char toGreen(int color);
    /**
     * @brief toBlue
     * @param color
     * @return the blue component of the ARGB color
     */
    static char toBlue(int color);

    /**
     * @brief toColor
     * @param alpha
     * @param red
     * @param green
     * @param blue
     * @return the ARGB color from (alpha, red, green, blue)
     */
    static int toColor(char alpha, char red, char green, char blue);

private:
    //The weight of the generating functions, their sum will be normalized
    std::vector<unsigned int> m_variations;
    //The associated functions (a priori, max 49)
    std::vector<Function *> m_functions;
    //The affinity which is composed in each functions
    Affinity *m_affinity;
    //The affine post transform, in which are applied the previous resulting function
    Affinity *m_postTransform;
    // Color associated to the generating function, in ARGB
    int m_color;

};

#endif // FUNCTION_H
