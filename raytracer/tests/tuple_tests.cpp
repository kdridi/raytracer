#include "tuple.hpp"

#include <gmock/gmock.h>

class TupleTest: public testing::Test {
};

// A tuple with w=1.0 is a point
TEST_F(TupleTest, A_tuple_with_w_1_is_a_point) {
    raytracer::Tuple a(4.3, -4.2, 3.1, 1.0);
    EXPECT_EQ(a.x, 4.3);
    EXPECT_EQ(a.y, -4.2);
    EXPECT_EQ(a.z, 3.1);
    EXPECT_EQ(a.w, 1.0);
    EXPECT_TRUE(a.isPoint());
    EXPECT_FALSE(a.isVector());
}
