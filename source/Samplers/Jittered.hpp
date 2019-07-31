#include "Sampler.hpp"

class Jittered : public Sampler{
public:
    Jittered(int samples = 1, int sets = 50);

private:
    void generate_samples();
};