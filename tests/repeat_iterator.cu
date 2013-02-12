#include <GNUC_47_compat.h>

#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/copy.h>

#include "../thrust/iterator/repeat_iterator.h"

int main() {
    thrust::host_vector<double> v(0);
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);

    thrust::copy(thrust::make_repeat_iterator(v.begin(), 3),
            thrust::make_repeat_iterator(v.begin()+v.size()*3, 3),
            std::ostream_iterator<double>(std::cout, " "));
    // Desired output: 4 4 4 3 3 3 2 2 2 1 1 1

    return 0;
}
