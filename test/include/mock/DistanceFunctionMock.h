#ifndef VDG_TEST_MOCK_DISTANCEFUNCTIONMOCK_H
#define VDG_TEST_MOCK_DISTANCEFUNCTIONMOCK_H

#include <gmock/gmock.h>

namespace vdg::test {

template<typename TPoint>
class DistanceFunctionMock {
  public:
    MOCK_METHOD(double, distance, (const TPoint&, const TPoint&), (const));

    [[nodiscard]] double operator()(const TPoint& lhs,
                                    const TPoint& rhs) const {
        return distance(lhs, rhs);
    }
};

}  // namespace vdg::test

#endif  // VDG_TEST_MOCK_DISTANCEFUNCTIONMOCK_H
