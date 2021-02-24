# Newton-fractal-generator
Given a complex polynomial, generate an image using Newton's method.

![x^3 - 1 in the range \[-1,1\]X\[-1,1\]](readme_image.png)

*x^3 - 1 in the range \[-1,1\]X\[-1,1\]*

*To generate this, run ./newtonfractal*

This project allowed me to learn
* C++ object oriented programming
* How to generate ppm images in C++
* regex
* Interpreting command line arguments

To build, just run **make**.

To run, **./newtonfractal [polynomial coefficients]**.

Images are generated as .ppm files




# Command line arguments
By default, the program generates the above image:
* 512x512 pixel resolution
* Draws a 2.0x2.0 rectangle in the complex plane
* The top left of this rectangle is at -1+1i
* Pixels are coloured according to the default palette
* Pixels are shaded according to iteration depth
* Max iteration depth of 4000

* -v: verbose output
* -c \[coefficients\]: control what polynomial is generated, coefficients should go in ascending order of powers of x, separated by spaces, and each coefficient should be of the form **x+yi** or **x-yi**. The regex for a valid coefficient is **"(.\*)([+-].\*)i"**.
* -pw \[integer\]: pixel width of output image
* -ph \[integer\]: pixel height of output image
* -o \[complex number\]: complex coordinates of the top left corner of the image, given in the same format as in -c
* -cw \[double\]: width of rectangle in complex plane
* -ch \[double\]: height of rectangle in complex plane
* --noshading: basins of attraction now one solid colour, not shaded according to iteration depth
* --maxdepth: maximum iteration depth before returning error - raising will reduce runtime, while increasing will reduce number of white artifacts in image

# Future features
* Exponential smoothing of the image to blend different shades of the same regions together
* Multiprocessing support to divide the image into sections to generate concurrently
