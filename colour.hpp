#ifndef COLOUR_H
#define COLOUR_H

class Colour {
public:
	Colour();
	Colour(int r, int g, int b);
	Colour scale(double intensity);
	int _r, _g, _b;
};

#endif