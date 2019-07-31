#include "Sampler.hpp"

class Regular : public Sampler{
public:
    Regular(int samples = 1, int sets = 50);

private:
    void generate_samples();
};