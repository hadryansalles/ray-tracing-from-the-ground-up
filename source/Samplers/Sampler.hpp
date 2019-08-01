#pragma once

#include <vector>
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Maths.hpp"
#include "../Utilities/Constants.hpp"

class Sampler{
public:
    Sampler(int samples = 1, int sets = 50);
    virtual ~Sampler();

    int get_num_samples();
    void set_num_samples(int samples);

    int get_num_sets();
    void set_num_sets(int sets);

    Point2D sample_unit_square();
    virtual void generate_samples() = 0;

    void map_samples_to_unit_disk();
    Point2D sample_unit_disk();
    
protected:
    int num_samples;
    int num_sets;
    unsigned long count;
    int jump;

    std::vector<Point2D> samples;
    std::vector<Point2D> disk_samples;
};