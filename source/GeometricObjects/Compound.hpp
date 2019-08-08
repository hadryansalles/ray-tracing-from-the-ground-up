#pragma once

#include "GeometricObject.hpp"
#include "../Utilities/Debug.hpp"
#include "../Materials/Material.hpp"

class Compound: public GeometricObject {
public:
    Compound();
    Compound(const Compound& comp);
    
    Compound& operator= (const Compound& rhs);
    Compound* clone() const;

    virtual ~Compound();

    void add_object(GeometricObject* object_ptr);
    void delete_objects();

    virtual void set_material(Material* material_p);
    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;
    virtual bool shadow_hit(const Ray& ray, float& tmin) const;
protected:
    std::vector<GeometricObject*> objects;
};