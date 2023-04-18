#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#define EPSILON 0.00001
#define double_equals(a, b) (fabs((a) - (b)) < EPSILON)

#define map_range(x, in_min, in_max, out_min, out_max) \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

#endif // __UTILS_HPP__
