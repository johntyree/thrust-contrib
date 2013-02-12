#include <GNUC_47_compat.h>

#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/copy.h>

#include "../thrust/iterator/tile_iterator.h"

int main() {
    thrust::host_vector<double> v(0);
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);

    thrust::copy(thrust::make_tile_iterator(v.begin(), v.size()),
            thrust::make_tile_iterator(v.begin()+v.size()*3, v.size()),
            std::ostream_iterator<double>(std::cout, " "));
    // Desired output: 4 3 2 1 4 3 2 1 4 3 2 1

    return 0;
}
