#include "../Headers/Image.h"

int main()
{
    const int width = 640;
    const int height = 480;

    Image image(width, height);

    for (int y = 0; y < height; y++) // loop through all pixels
    {
        for (int x = 0; x < width; x++)
        {
            image.setColour(Colour((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
        }
    }

    image.save(R"(D:\CodeStuff\BMPImage\Images\ImageBMPTest.bmp)");

    Image copy(0, 0);
    copy.Read(R"(D:\CodeStuff\BMPImage\Images\ImageBMPTest.bmp)");
    image.save(R"(D:\CodeStuff\BMPImage\Images\copy.bmp)");

    return 0;
}