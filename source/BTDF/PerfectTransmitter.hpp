#pragma once

#include "BTDF.hpp"

class PerfectTransmitter : public BTDF {
public: 
    PerfectTransmitter(Sampler* sampler = NULL, const float kt_ = 0, const float ior_ = 0);
    PerfectTransmitter(const PerfectTransmitter& perf);
    PerfectTransmitter& operator=(const PerfectTransmitter& rhs);
    PerfectTransmitter* clone() const;

    void set_kt(const float k);
    float get_kt() const;
    void set_ior(const float ior_);
    float get_ior() const;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wt) const;
    virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wt, float& pdf) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
    virtual bool tir(const ShadeRec& sr) const;

private:
    float kt;
    float ior;
};