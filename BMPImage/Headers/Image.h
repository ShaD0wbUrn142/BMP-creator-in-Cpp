#pragma once
#include <vector>

struct Colour
{
    float r, g, b;

    // constructors
    Colour();
    Colour(float r, float g, float b);
    ~Colour();
};

class Image
{
public:
    Image(int width, int height);
    ~Image();

    Colour getColour(int x, int y) const;
    void setColour(const Colour &colour, int x, int y);

    void Read(const char *path);

    void save(const char *path) const;

private:
    int m_width;
    int m_height;
    std::vector<Colour> m_colour;
};