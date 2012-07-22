#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <cmath>

/**
 * @brief The Function class
 *
 * All the functions used in to generate a fractal have to inherit that class.
 */
class Function
{
public:
    Function();

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

protected:
    /*
     * Should insert manually , to delimitate the couple, but the functions get*
     * automatically add f(x,y) = ( <put the necessary> )
     */
    std::string m_name;
    std::string m_expr;
    std::string m_latex;

};

/**
 * @brief The Identity class
 *
 * The identity function.
 */
class Identity : Function
{
public:
    Identity();
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
class Affinity : Function
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
    Affinity(double a1=0, double a2=0, double b1=0, double b2=0, double c1=0, double c2=0);

    /**
     * @brief getFX
     * @return an array with a1, b1, c1
     */
    const double *getFX() const;
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

class Sinusoidal : Function
{
public:
    Sinusoidal();
    virtual void apply(double &x, double &y);
};

#endif // FUNCTION_H
