#include "Camera.hpp"
#include "../World/World.hpp"

Camera::Camera(Point3D eye_p, Point3D lookat):
    eye(eye_p),
    look_at(lookat),
    up(0, 1, 0),
    exposure_time(0)
{}

Camera::~Camera()
{}

void Camera::set_eye(const Point3D eye_p){
    eye = eye_p;
}
const Point3D Camera::get_eye() const{
    return eye;
}

void Camera::set_lookat(const Point3D lookat){
    look_at = lookat;
}

const Point3D Camera::get_lookat() const{
    return look_at;
}

void Camera::set_up(const Vector3D up_d){
    up = up_d;
}

const Vector3D Camera::get_up() const{
    return up;
}

void Camera::set_exposure_time(const float exposure_t){
    exposure_time = exposure_t;
}

const float Camera::get_exposure_time() const{
    return exposure_time;
}