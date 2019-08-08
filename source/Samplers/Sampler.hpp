#pragma once

#include <vector>
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Maths.hpp"
#include "../Utilities/Constants.hpp"

class Sampler{
public:
    Sampler(int samples = 1, int sets = 50);
    Sampler(const Sampler& samp);
    Sampler& operator=(const Sampler& rhs);
    virtual Sampler* clone() const = 0;

    virtual ~Sampler();

    int get_num_samples();
    void set_num_samples(int samples);

    int get_num_sets();
    void set_num_sets(int sets);

    Point2D sample_unit_square();
    
    void map_samples_to_unit_disk();
    void map_samples_to_hemisphere(const float e);
    Point2D sample_unit_disk();
    Point3D sample_hemisphere();
    
protected:
    int num_samples;
    int num_sets;
    unsigned long count;
    int jump;

    std::vector<Point2D> samples;
    std::vector<Point2D> disk_samples;
    std::vector<Point3D> hemisphere_samples;
    
    virtual void generate_samples() = 0;
    void shuffle_x_coordinates();
    void shuffle_y_coordinates();
};