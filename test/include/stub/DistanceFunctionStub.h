#ifndef VDG_TEST_STUB_DISTANCEFUNCTIONSTUB_H
#define VDG_TEST_STUB_DISTANCEFUNCTIONSTUB_H

namespace vdg::test {

template<typename TPoint>
class DistanceFunctionStub {
  public:
    [[nodiscard]] double operator()(const TPoint& /*lhs*/,
                                    const TPoint& /*rhs*/) const {
        return 0;
    }
};

}  // namespace vdg::test

#endif  // VDG_TEST_STUB_DISTANCEFUNCTIONSTUB_H
