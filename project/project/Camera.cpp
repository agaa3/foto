#include "Camera.h"
#include "Spotlight.h"

static LightIntensity colorBckg = LightIntensity(0, 1, 0);


Camera::Camera() {
    this->position = Vector3(0, 0, 0);
    this->direction = Vector3(0, 0, 1);
    this->nearPlane = 1;
    this->farPlane = 1000;
    this->up = Vector3(0, 1, 0);
    this->sampler = 0;
    this->spatialContrast = 1;
    this->img = Image(100, 100);
}


Camera::Camera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler, const float& spatialContrast, const vector<ObjectOnScene*>& objects, const vector<Light*>& lights) : position(position), direction(direction), up(up), img(img), sampler(sampler), spatialContrast(spatialContrast), objects(objects), lights(lights) {
    this->radius = sqrt(position.x * position.x + position.y * position.y + position.z * position.z);
    this->nearPlane = 1;
    this->farPlane = 1000;
       
}

Camera::Camera(float radius, Image& img) : radius(radius), img(img) {
    this->position = Vector3(0, 0, radius);
    this->direction = Vector3(0, 0, -1);
    this->up = Vector3(0, 1, 0);
    this->right = direction.cross(up);
    this->right = this->right.normalize();
    this->sampler = 0;
    this->spatialContrast = 1;

}

LightIntensity Camera::shootingRay(const Ray& ray, int depth) { //direction = destination
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    float tForShadows = FLT_MAX;

    Vector3 intPoint;
    Vector3 intPoint2;
    Vector3 normal;
    ObjectOnScene* closestObject = nullptr;
    Vector3 intersectionPoint;
    Vector3 normalIntersection;
    bool intersects = false;


    //sprawdzenie który obiekt jest z przodu
    LightIntensity colorOfPixel = LightIntensity(0);
    for (auto object : this->objects) {

        intersects = object->hit(ray, intPoint, normal, t);

        if (intersects && (t < tempT))
        {
            tempT = t;
            intersectionPoint = intPoint + normal * 0.001;
            closestObject = object;
            normalIntersection = normal;
        }
    }

    if (closestObject != nullptr && closestObject->material.matType == reflective && depth > 0) {
        //colorOfPixel = LightIntensity(0, 1, 0);
        Vector3 I = ray.direction.normalize();
        Vector3 N = normalIntersection.normalize();
        Vector3 reflectedRay = I -N * (N.dotProduct(I) * 2); // -I;
        depth = depth - 1;
        LightIntensity colTemp = shootingRay(Ray(intersectionPoint, reflectedRay), depth);
        colorOfPixel = colorOfPixel + colTemp;
    }
    //jesli nie tlo, to sprawdzanie swiatel i cieni
    else if (closestObject != nullptr && closestObject->material.matType == diffuse) {

        //przejscie po wszystkich swiatlach z punktu przeciecia
        for (auto light : this->lights) {
            colorOfPixel += light->calculateColor(this->objects, intersectionPoint, normalIntersection, closestObject, ray.origin - intersectionPoint);
            
        }
    }
    else if (closestObject != nullptr) {
        if (closestObject->material.matType == reflective) {
            colorOfPixel = LightIntensity(0, 0, 1);
        }
        else {
            colorOfPixel = LightIntensity(1, 0, 0);

        }
    }
    else {
        colorOfPixel = colorBckg;
    }

    return colorOfPixel;
}





























//void Camera::rotateY(float angle) {
//    Vector3 axis = Vector3(sin(angle * M_PI / 180), 0, cos(angle * M_PI / 180));
//
//    position.x = sin(angle * M_PI / 180) * radius;
//    position.z = cos(angle * M_PI / 180) * radius;
//    direction = Vector3(-position.x, -position.y, -position.z);
//    direction = direction.normalize();
//
//    right.x = cos(angle * M_PI / 180);
//    right.z = -sin(angle * M_PI / 180);
//    if (right.y == -0) right.y = 0;
//    right = right.normalize();
//    up = right.cross(direction);
//    //    up.x = -sin(angle * M_PI / 180);
//    //    up.z = -cos(angle * M_PI / 180);
//    //    up = up.normalize();
//}

//void Camera::rotateX(float angle) {
//    position.y = sin(angle * M_PI / 180) * radius;
//    position.z = cos(angle * M_PI / 180) * radius;
//    direction = Vector3(-position.x / radius, -position.y / radius, -position.z / radius);
//    direction = direction.normalize();
//    if (direction.x == -0) direction.x = 0;
//    up = right.cross(direction);
//    up = up.normalize();
//    //    up.y = position.z;
//    //    up.z = -position.y;
//    //    up = up.normalize();
//}
//
//void Camera::rotateZ(float angle) {
//    up.x = sin(angle * M_PI / 180);
//    up.y = cos(angle * M_PI / 180);
//    up = up.normalize();
//    right = direction.cross(up);
//}
//
//
//void Camera::rotateX1(float angle) {
//    position = position.rotateByQuaternion(angle, Vector3(1, 0, 0));
//    direction = direction.rotateByQuaternion(angle, Vector3(1, 0, 0));
//    direction = direction.normalize();
//    up = up.rotateByQuaternion(angle, Vector3(1, 0, 0));
//    up = up.normalize();
//}
//
//void Camera::rotateY1(float angle) {
//    position = position.rotateByQuaternion(angle, Vector3(0, 1, 0));
//    direction = direction.rotateByQuaternion(angle, Vector3(0, 1, 0));
//    direction = direction.normalize();
//    up = up.rotateByQuaternion(angle, Vector3(0, 1, 0));
//    up = up.normalize();
//}
//
//void Camera::rotateZ1(float angle) {
//    position = position.rotateByQuaternion(angle, Vector3(0, 0, 1));
//    direction = direction.rotateByQuaternion(angle, Vector3(0, 0, 1));
//    direction = direction.normalize();
//    up = up.rotateByQuaternion(angle, Vector3(0, 0, 1));
//    up = up.normalize();
//}
//
//void Camera::rotateAxis(float angle, Vector3 axis) {
//    position = position.rotateByQuaternion(angle, axis);
//    direction = direction.rotateByQuaternion(angle, axis);
//    direction = direction.normalize();
//    up = up.rotateByQuaternion(angle, axis);
//    up = up.normalize();
//}