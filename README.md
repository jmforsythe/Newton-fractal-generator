# Newton-fractal-generator
Given a complex polynomial, generate an image using Newton's method.

This project allowed me to learn
* C++ object oriented programming
* How to generate ppm images in C++

To build, just run **make**.

To run, **./newtonfractal [polynomial coefficients]**.

Images are generated as .ppm files

The polynomial coefficients go in ascending order of powers of x, separated by spaces, and each coefficient should be of the form **x+yi** or **x-yi**.

The regex for a valid coefficient is **"(.\*)([+-].\*)i"**

Currently the following parameters are hardcoded, but I aim to let the user change them with command line arguments:
* The resolution of the image
* The region of the complex plane that is drawn
    * The "origin", the top left point of the region
    * The width and height of the region
* The colours used
* Whether or not to use shading based on time to converge
* Max iteration depth
