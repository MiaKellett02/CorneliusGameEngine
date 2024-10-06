#pragma once

//Libary includes.
#include <cmath>

//Struct definition.
struct Vector2 {
	float x, y;

	Vector2() { x = 0; y = 0; }
	Vector2(const Vector2& copy) {
		x = copy.GetX();
		y = copy.GetY();
	}

	Vector2(float a_x, float a_y) { x = a_x; y = a_y; }

	const float GetX() const { return x; }
	const float GetY() const { return y; }

	void Normalize() {
		//Calculate magnitude.
		float magnitude = std::sqrt(x * x + y * y);

		//Zero check.
		if (magnitude > 0) {
			x /= magnitude;
			y /= magnitude;
		}
	}

	float Magnitude() {
		return std::sqrt(x * x + y * y);
	}

	float SqrMagnitude() {
		return x * x + y * y;
	}

	//Operator overrides.
	Vector2 operator*(int multiplier) const {
		return Vector2(x * multiplier, y * multiplier);
	}

	Vector2 operator*(float multiplier) const {
		return Vector2(x * multiplier, y * multiplier);
	}

	Vector2 operator/(int division) const {
		return Vector2(x / division, y / division);
	}

	Vector2 operator/(float division) const {
		return Vector2(x / division, y / division);
	}

	Vector2 operator+(Vector2 other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(Vector2 other) const {
		return Vector2(x - other.x, y - other.y);
	}
};