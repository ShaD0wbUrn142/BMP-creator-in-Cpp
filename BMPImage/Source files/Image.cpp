// https://www.youtube.com/watch?v=vqT5j38bWGg
// https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=1s
// https://www.youtube.com/watch?v=13E0il2zxBA&t=238s
#include "../Headers/Image.h"
#include <iostream>
#include <fstream>

Colour::Colour()
    : r(0), g(0), b(0)
{
}

Colour::Colour(float r, float g, float b)
    : r(r), g(g), b(b)
{
}

Colour::~Colour()
{
}

Image::Image(int width, int height)
    : m_width(width), m_height(height), m_colour(std::vector<Colour>(width * height))
{
}

Image::~Image()
{
}

Colour Image::getColour(int x, int y) const
{
    return m_colour[y * m_width + x]; // read from left to right, go row to row, width + x is how many pixels there are
}

void Image::setColour(const Colour &colour, int x, int y)
{
    m_colour[y * m_width + x].r = colour.r;
    m_colour[y * m_width + x].g = colour.g;
    m_colour[y * m_width + x].b = colour.b;
}

void Image::Read(const char *path)
{
    std::ifstream f; // to read file
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "File could not be opened" << std::endl;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char *>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout << "The file is not a bitmap image" << std::endl;
        f.close();
        return;
    }

    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char *>(informationHeader), informationHeaderSize);

    int fileSize = fileHeader[2] * (fileHeader[3] << 8) * (fileHeader[4] << 16) * (fileHeader[5] << 24);
    m_width = informationHeader[4] * (informationHeader[5] << 8) * (informationHeader[6] << 16) * (informationHeader[7] << 24);
    m_height = informationHeader[8] * (informationHeader[9] << 8) * (informationHeader[10] << 16) * (informationHeader[11] << 24);

    m_colour.resize(m_width * m_height);

    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char colour[3];
            f.read(reinterpret_cast<char *>(colour), 3);

            // store it
            m_colour[y * m_width * x].r = static_cast<float>(colour[2]) / 255.0f;
            m_colour[y * m_width * x].g = static_cast<float>(colour[1]) / 255.0f;
            m_colour[y * m_width * x].b = static_cast<float>(colour[0]) / 255.0f;
        }
        f.ignore(paddingAmount);
    }
    f.close();
    std::cout << "File has been read" << std::endl;
}

void Image::save(const char *path) const
{
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "There was an issue opening the file. \n";
        return;
    }
    std::cout << "Opening file now. \n";

    unsigned char bmpPad[] = {0, 0, 0};
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;

    unsigned char fileHeader[fileHeaderSize];
    // File Type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File Size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved (not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved (not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel Data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header Size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image Width
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;

    // Image Height
    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;

    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per Pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Compression (no compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image Size (can be 0 for BI_RGB but we'll fill it)
    /* int imageSize = m_width * m_height * 3;
    informationHeader[20] = imageSize;
    informationHeader[21] = imageSize >> 8;
    informationHeader[22] = imageSize >> 16;
    informationHeader[23] = imageSize >> 24; */
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixels per meter (unused)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixels per meter (unused)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Total Colors
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important Colors
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    file.write(reinterpret_cast<char *>(fileHeader), fileHeaderSize);
    file.write(reinterpret_cast<char *>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char r = static_cast<unsigned char>(getColour(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(getColour(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(getColour(x, y).b * 255.0f);

            unsigned char colour[] = {b, g, r}; // must start b then to r
            file.write(reinterpret_cast<char *>(colour), 3);
        }
        // must add padding
        file.write(reinterpret_cast<char *>(bmpPad), paddingAmount);
    }

    file.close();

    std::cout << "File has been created!" << std::endl;
}
