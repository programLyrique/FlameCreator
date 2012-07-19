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
    explicit Flame(long width, long height);

private:
    vector< vector<long> > histogram;
    vector< vector<long> > color;
};

#endif // FLAME_H
