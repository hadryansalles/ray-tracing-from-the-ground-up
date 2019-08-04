#include "Compound.hpp"

Compound::Compound()
    : GeometricObject()
{}

Compound::Compound(const Compound& comp)
    : GeometricObject(comp) {
    objects.reserve(comp.objects.size());
    for(int i = 0; i < comp.objects.size(); i++){
        add_object(comp.objects[i]->clone());
    }
}

Compound& Compound::operator= (const Compound& rhs){
    if(this == &rhs){
        return (*this);
    }
    GeometricObject::operator=(rhs);
    delete_objects();
    objects.reserve(rhs.objects.size());
    for(int i = 0; i < rhs.objects.size(); i++){
        add_object(rhs.objects[i]->clone());
    }
}
Compound* Compound::clone() const{
    return (new Compound(*this));
}

Compound::~Compound(){
    delete_objects();
    material_ptr = NULL;
}

void Compound::add_object(GeometricObject* object_ptr){
    if(object_ptr != NULL){
        if(object_ptr->get_material() == NULL){
            object_ptr->set_material(material_ptr);   
        }
        objects.push_back(object_ptr);
    }
}

void Compound::set_material(Material* material_p){
    if(objects.size() > 0){
        objects[0]->set_material(material_p);
    }
    for(int i = 1; i < objects.size(); i++){
        objects[i]->set_material(material_p->clone());
    }
}

void Compound::delete_objects(){
    for(int i = 0; i < objects.size(); i++){
        if(objects[i] != NULL){
            delete objects[i];
        }
    }   
    objects.clear();
}

bool Compound::hit(const Ray& ray, float& t, ShadeRec& s) const {
    float t_;
    Normal normal;
    Point3D local_hit_point;
    bool hit = false;
    t = kHugeValue;
    int num_objects = objects.size();

    for(int i = 0; i < num_objects; i++){
        if(objects[i]->hit(ray, t_, s) && (t_ < t)){
            hit = true;
            t = t_;
            material_ptr = objects[i]->get_material();
            normal = s.normal;
            local_hit_point = s.local_hit_point;
        }
    }
    if(hit){
        s.t = t;
        s.normal = normal;
        s.local_hit_point = local_hit_point;
    }
    return hit;
}