/**
 * Implementation of position sort.
 * The code uses thrust library.
 */

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/scan.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <thrust/execution_policy.h>
#include <thrust/functional.h>


struct BitFunctor {
    int pos;
    BitFunctor(int pos) : pos(pos) {}

    __device__ int operator()(int value) const {
        return (value >> pos) & 1;
    }
};

struct SortFunctor {
    const int *d_a, *d_bits_pref;
    int* d_tmp;
    int n, n_zeros, pos;

    SortFunctor(const int* d_a, const int* d_bits_pref, int* d_tmp, int n, int n_zeros, int pos)
            : d_a(d_a), d_bits_pref(d_bits_pref), d_tmp(d_tmp), n(n), n_zeros(n_zeros), pos(pos) {}

    __device__ void operator()(int i) const {
        int val = d_a[i], idx;
        bool bit = (val >> pos) & 1;
        if (bit) {
            idx = n_zeros + d_bits_pref[i];
        } else {
            idx = i - d_bits_pref[i];
        }
        d_tmp[idx] = val;
    }
};

void gpusort(int n, int *a) {
    thrust::device_vector<int> d_a(a, a + n);
    thrust::device_vector<int> d_tmp(n);
    thrust::device_vector<int> d_bits(n+1);
    thrust::device_vector<int> d_bits_pref(n+1);

    int max_val = *thrust::max_element(d_a.begin(), d_a.end());
    int n_bits = sizeof(int) * 8 - __builtin_clz(max_val);

    for (int pos = 0; pos < n_bits; ++pos) {
        thrust::transform(d_a.begin(), d_a.end(), d_bits.begin(), BitFunctor(pos));
        thrust::exclusive_scan(d_bits.begin(), d_bits.end(), d_bits_pref.begin(), 0);

        int n_zeros = n - d_bits_pref[n];
        thrust::for_each(thrust::counting_iterator<int>(0), thrust::counting_iterator<int>(n),
                SortFunctor(
                        thrust::raw_pointer_cast(d_a.data()),
                        thrust::raw_pointer_cast(d_bits_pref.data()),
                        thrust::raw_pointer_cast(d_tmp.data()),
                        n, n_zeros, pos
                        ));
        d_a.swap(d_tmp);
    }
    thrust::copy(d_a.begin(), d_a.end(), a);
}
