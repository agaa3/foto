#include "LightIntensity.h"
#include "ObjectOnScene.h"
#include <vector>
#include "Vector3.h"

using namespace std;

class Light {
	LightIntensity color;

	Light(LightIntensity col) : color(col) {};
	~Light() = default;

	virtual Vector3 getDiffuse(Vector3 cameraPosition, Vector3 intPoint);
	virtual Vector3 getSpecular(Vector3 cameraPosition, Vector3 intPoint);
	virtual bool isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects);
};