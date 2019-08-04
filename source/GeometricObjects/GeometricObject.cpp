#include "GeometricObject.hpp"

#include "../Utilities/Constants.hpp"
#include "../Materials/Material.hpp"

GeometricObject::GeometricObject(Material* material_p)
	: 	material_ptr(material_p)
{}

GeometricObject::GeometricObject (const GeometricObject& object){
	if(object.material_ptr){
		material_ptr = object.material_ptr->clone();
	}
	else{
		material_ptr = NULL;
	}
}	

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if(material_ptr){
		delete material_ptr;
		material_ptr = NULL;
	}
	if(rhs.material_ptr){
		material_ptr = rhs.material_ptr->clone();
	}

	return (*this);
}

BBox GeometricObject::get_bounding_box(){
	return BBox();
}

GeometricObject::~GeometricObject () {
	if(material_ptr != NULL){
		delete material_ptr;
		material_ptr = NULL;
	}
}

void GeometricObject::set_material(Material* material_p){
	if(material_ptr != NULL){
		delete material_ptr;
	}
	material_ptr = material_p;
}

Material* GeometricObject::get_material() const{
	return material_ptr;
}