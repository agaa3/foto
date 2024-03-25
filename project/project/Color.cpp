#include "Color.h"

Color Color::undefined = Color(-1, -1, -1);

bool operator==(const Color& lhs, const Color& rhs)
{
	if (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b)
	{
		return true;
	}
	return false;
}

void Color::add(float R, float G, float B) {
	this->r += R;
	this->g += G;
	this->b += B;
}

float Color::calculateDifference(const Color& other) {
	float diff = this->r - other.r;
	float temp = this->g - other.g;
	if (temp>diff) {
		diff = temp;
	}
	temp = this->g - other.b;
	if (temp>diff) {
		diff = temp;
	}
	return diff;
}

void Color::setValues(Color newColor) {
	this->r = newColor.r;
	this->g = newColor.g;
	this->b = newColor.b;
	if (newColor.r > 1) {
		this->r = 1;
	}
	if (newColor.g > 1) {
		this->g = 1;
	}
	if (newColor.b > 1) {
		this->b = 1;
	}

}


Color Color::operator+(Color& li) {
	return Color(this->r + li.r, this->g + li.g, this->b + li.b);

}
Color Color::operator-(Color& li) {
	return Color(this->r - li.r, this->g - li.g, this->b - li.b);
}

Color Color::operator/(float num) {
	return Color(this->r / num, this->g / num, this->b / num);
}

Color Color::operator*(float num) {
	return Color(this->r * num, this->g * num, this->b * num);
}

std::ostream& operator<<(std::ostream& str, Color& li) {
	str << "[ " << li.r << ", " << li.g << ", " << li.b << "]";
	return str;
}
