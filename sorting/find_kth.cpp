/**
 *
 * Created by Anna Szymańska on 24.11.2022
 */

#include <vector>

/**
 *
 * @param data
 * @param lower
 * @param upper
 * @param k
 * @return
 */

int get_median(std::vector<int> & data, int lower, int upper, int k) {
    if (upper - lower <= 10) {
        insertion_sort(data, lower, upper);
        return data[k];
    }
    std::vector<int> medians;
    for (int i = lower; i <= upper; i += 5) {
        if (i + 4 <= upper) {
            five_sort(data, i);
            medians.push_back(data[i+2]);
        } else break;
    }

    int m = get_median(medians, 0, medians.size()-1, (upper - lower + 1) / 10);
    int l = lower, r = upper;
    for(int i = l; i <= r; i++) {
        if (data[i] < m) std::swap(data[i], data[l++]);
        else if (data[i] > m) std::swap(data[i--], data[r--]);
    }

    if (l >= k)  {
        return get_median(data, lower, l, k);
    } else if (r <= k) {
        return get_median(data, r, upper, k);
    }
    return m;
}