
class LightIntensity {
public:
	float R, G, B;

	~LightIntensity() = default;
	LightIntensity() : R(0), G(0), B(0) {};
	LightIntensity(const float& R, const float& G, const float& B);
	LightIntensity(const LightIntensity& li) : R(li.R), G(li.G), B(li.B) {};

	void operator+=(const LightIntensity& li);
	void operator/=(const float& li);
};

