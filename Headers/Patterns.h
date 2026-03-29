/*
I ain't finding out how to do these on my own + I can't find too many good resouces on how to do more complex things. Thanks gpt lol
*/

#ifndef PATTERNS_H
#define PATTERNS_H

#include <cmath>
#include "Image.h"

namespace Patterns
{
    // ============================================================
    // SOLID COLOUR
    // Fills entire image with one colour
    // ============================================================
    void solid(Image &image, int width, int height, Colour colour)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                image.setColour(colour, x, y);
            }
        }
    }

    // ============================================================
    // ORIGINAL GRADIENT
    // Red increases → right
    // Green decreases → right
    // Blue increases → down
    // ============================================================
    void gradientXY(Image &image, int width, int height)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float r = (float)x / width;
                float g = 1.0f - r;
                float b = (float)y / height;

                image.setColour(Colour(r, g, b), x, y);
            }
        }
    }

    // ============================================================
    // GRAYSCALE HORIZONTAL GRADIENT
    // Left = black, Right = white
    // ============================================================
    void grayscaleHorizontal(Image &image, int width, int height)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float t = (float)x / width;
                image.setColour(Colour(t, t, t), x, y);
            }
        }
    }

    // ============================================================
    // VERTICAL GRADIENT
    // Blends from blue → red vertically
    // ============================================================
    void verticalGradient(Image &image, int width, int height)
    {
        for (int y = 0; y < height; y++)
        {
            float t = (float)y / height;

            for (int x = 0; x < width; x++)
            {
                image.setColour(Colour(t, 0.0f, 1.0f - t), x, y);
            }
        }
    }

    // ============================================================
    // CHECKERBOARD PATTERN
    // Alternates black/white squares
    // checkerSize controls square size
    // ============================================================
    void checkerboard(Image &image, int width, int height, int checkerSize = 50)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                bool isWhite = ((x / checkerSize) + (y / checkerSize)) % 2 == 0;

                if (isWhite)
                    image.setColour(Colour(1, 1, 1), x, y);
                else
                    image.setColour(Colour(0, 0, 0), x, y);
            }
        }
    }

    // ============================================================
    // SINE WAVE PATTERN
    // Uses sine function to create wave-like brightness
    // ============================================================
    void sineWave(Image &image, int width, int height)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float value = (sin(x * 0.05f) + 1.0f) / 2.0f;

                image.setColour(Colour(value, value, 1.0f), x, y);
            }
        }
    }

    // ============================================================
    // SIMPLE COLOUR BLEND
    // Red varies with X, Green with Y, Blue constant
    // ============================================================
    void blendXY(Image &image, int width, int height)
    {
        for (int y = 0; y < height; y++)
        {
            float g = (float)y / height;

            for (int x = 0; x < width; x++)
            {
                float r = (float)x / width;
                float b = 0.5f;

                image.setColour(Colour(r, g, b), x, y);
            }
        }
    }

    // ============================================================
    // RADIAL GRADIENT (CIRCLE EFFECT)
    // Colour depends on distance from center
    // ============================================================
    void radial(Image &image, int width, int height)
    {
        float cx = width / 2.0f;
        float cy = height / 2.0f;

        float maxDist = sqrt(cx * cx + cy * cy);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float dx = x - cx;
                float dy = y - cy;

                float dist = sqrt(dx * dx + dy * dy);
                float t = dist / maxDist;

                image.setColour(Colour(t, 0.0f, 1.0f - t), x, y);
            }
        }
    }
}

#endif