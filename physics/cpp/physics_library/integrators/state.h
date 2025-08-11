#ifndef STATE_H
#define STATE_H
#include <vector>

inline std::vector<long double> add_vectors(const std::vector<long double>& a, const std::vector<long double>& b) {
    std::vector<long double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

inline std::vector<long double> multiply_vector(const std::vector<long double>& v, long double scalar) {
    std::vector<long double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * scalar;
    }
    return result;
}



struct State
{
    std::vector<long double> position;
    std::vector<long double> velocity;
};


#endif
