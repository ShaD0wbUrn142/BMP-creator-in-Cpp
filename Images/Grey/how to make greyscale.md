It loops over every pixel and calculates a value t based on how far across the image you are (x / width). That value goes from 0 (black) on the left to near 1 (white) on the right, and setColour uses it to draw a horizontal grayscale gradient.





**For vertical**

float t = (float)y / height;

image.setColour(Colour(t, 0.0f, 1.0f - t), x, y);





**For horizontal**

float t = (float)x / width;

image.setColour(Colour(t, t, t), x, y); // grayscale

