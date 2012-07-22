#ifndef FLAME_H
#define FLAME_H

#include <vector>

using namespace std;

class Flame
{
public:
    /**
     * @brief Flame
     * @param width
     * @param height
     */
    explicit Flame(unsigned long width, unsigned long height);

    /**
     * @brief render
     */
    void render();

private:
    // Use directly an C++ array ?
    vector< vector<unsigned long> > histogram;
    vector< vector<unsigned long> > color;
};

#endif // FLAME_H
