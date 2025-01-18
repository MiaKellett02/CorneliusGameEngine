#pragma once

//Library includes.
#include <cstdint>

//Struct definition.
struct Colour {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	Colour() {
		r = 255;
		g = 255;
		b = 255;
	}

	Colour(uint8_t a_r, uint8_t a_g, uint8_t a_b) {
		r = a_r;
		g = a_g;
		b = a_b;
	}
}