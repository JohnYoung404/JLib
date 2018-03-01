#pragma once

#ifdef _MSC_VER
#define jforceinline __forceinline
#define jAlign(bit) __declspec(align(bit))
#endif

#ifdef __GNUC__
#define jforceinline inline __attribute__((always_inline))
#define jAlign(bit) __attribute__((aligned(bit)))
#endif

#ifdef _MSC_VER
#define jDefaultDeprecatedMsg "Function is Deprecated. Contact JohnYoung404@outlook.com for more info."
#define jDeprecated __declspec(deprecated(jDefaultDeprecatedMsg))
#else
#define jDeprecated
#endif

#define NAME_SPACE_BEGIN(name) namespace name{
#define NAME_SPACE_END }

#define JTEST_BEGIN(test_class_name) namespace jLib { \
class test_class_name final : public jITestable { \
public: \
    virtual void test() override { \
        jITestable::test();

#define JTEST_END \
    } \
}; \
}