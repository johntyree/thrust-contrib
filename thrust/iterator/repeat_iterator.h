// GistID: 4770251

#ifndef THRUST_REPEAT_ITERATOR_H
#define THRUST_REPEAT_ITERATOR_H

/* Remove this header */
#include <GNUC_47_compat.h>

#include <iostream>
#include <thrust/iterator/iterator_adaptor.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/copy.h>
#include <thrust/host_vector.h>


namespace thrust
{

// derive repeat_iterator from iterator_adaptor
template<typename Iterator>
  class repeat_iterator
    : public thrust::iterator_adaptor<
        repeat_iterator<Iterator>, // the first template parameter is the name of the type we're creating
        Iterator,                  // the second template parameter is the name of the iterator we're adapting
        thrust::use_default,      // the third template parameter is the name of the iterator's value_type -- it's simply the function's result_type.
        thrust::use_default,            // the fourth template parameter is the name of the iterator's system. use_default will use the same system as the base iterator.
        thrust::use_default,            // the fifth template parameter is the name of the iterator's traversal. use_default will use the same traversal as the base iterator.
        thrust::use_default  // the sixth template parameter is the name of the iterator's reference. Like value_type, it's simply the function's result_type.
      >
{
  public:
    // shorthand for the name of the iterator_adaptor we're deriving from
    typedef thrust::iterator_adaptor<
      repeat_iterator<Iterator>,
      Iterator,
      thrust::use_default,
      thrust::use_default,
      thrust::use_default,
      thrust::use_default
    > super_t;

    // the number of repeats
    unsigned int rep;

    const Iterator begin;

    __host__ __device__
    repeat_iterator(const Iterator &x, int rep) : super_t(x), begin(x), rep(rep) {}

    // befriend thrust::iterator_core_access to allow it access to the private interface below
    friend class thrust::iterator_core_access;

  private:
    // it is private because only thrust::iterator_core_access needs access to it
    __host__ __device__
    typename super_t::reference dereference() const {
      return *(begin + (this->base() - begin) / rep);
    }

};

template<typename T>
__host__ __device__
repeat_iterator<T> make_repeat_iterator(T x, int rep)
{
    repeat_iterator<T> a(x, rep);
    return a;
}

} // end thrust


// int main() {
    // thrust::host_vector<double> v(0);
    // v.push_back(4);
    // v.push_back(3);
    // v.push_back(2);
    // v.push_back(1);

    // thrust::copy(make_repeat_iterator(v.begin(), 9),
            // make_repeat_iterator(v.begin()+v.size()*9, 9),
            // std::ostream_iterator<double>(std::cout, " "));
    // // Desired output: 4 4 4 3 3 3 2 2 2 1 1 1

    // return 0;
// }

#endif // THRUST_REPEAT_ITERATOR_H
