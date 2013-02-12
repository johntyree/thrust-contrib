#ifndef THRUST_TILE_ITERATOR_H
#define THRUST_TILE_ITERATOR_H

/* Remove this header */
#include <GNUC_47_compat.h>

#include <thrust/iterator/iterator_adaptor.h>


namespace thrust
{

// derive tile_iterator from iterator_adaptor
template<typename Iterator>
  class tile_iterator
    : public thrust::iterator_adaptor<
        tile_iterator<Iterator>, // name of the type we're creating
        Iterator,                // name of the iterator we're adapting
        thrust::use_default,     // name of the iterator's value_type
        thrust::use_default,     // name of the iterator's system
        thrust::use_default,     // name of the iterator's traversal
        thrust::use_default      // name of the iterator's reference
      >
{
  public:
    // shorthand for the name of the iterator_adaptor we're deriving from
    typedef thrust::iterator_adaptor<
      tile_iterator<Iterator>,
      Iterator,
      thrust::use_default,
      thrust::use_default,
      thrust::use_default,
      thrust::use_default
    > super_t;

    __host__ __device__
    tile_iterator(const Iterator &x, int n) : super_t(x), begin(x), n(n) {}

    // befriend thrust::iterator_core_access to allow it access to the private interface below
    friend class thrust::iterator_core_access;

  private:
    // Repeat after every n elements
    unsigned int n;

    // Used to compute a 'starting' point.
    const Iterator begin;

    // it is private because only thrust::iterator_core_access needs access to it
    __host__ __device__
    typename super_t::reference dereference() const {
      return *(begin + (this->base() - begin) % n);
    }

};

template<typename T>
__host__ __device__
tile_iterator<T> make_tile_iterator(T x, int n)
{
    tile_iterator<T> a(x, n);
    return a;
}

} // end thrust

#endif // THRUST_TILE_ITERATOR_H
