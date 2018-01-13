#pragma once

namespace jLib {
namespace jGraphic {

class jColor
{
public:
    typedef unsigned char Byte;

    constexpr jColor(Byte a = 0, Byte r = 0, Byte g = 0, Byte b = 0) : a_(a), r_(r), g_(g), b_(b) {}

    inline static constexpr jColor Black() {
        return jColor(255, 0, 0, 0);
    }
    inline static constexpr jColor White() {
        return jColor(255, 255, 255, 255);
    }
    inline static constexpr jColor Red() {
        return jColor(255, 255, 0, 0);
    }
    inline static constexpr jColor Green() {
        return jColor(255, 0, 255, 0);
    }
    inline static constexpr jColor Blue() {
        return jColor(255, 0, 0, 255);
    }

    inline const Byte R() const { return r_; }
    inline Byte& R() { return r_; }
    inline const Byte G() const { return g_; }
    inline Byte& G() { return g_; }
    inline const Byte B() const { return b_; }
    inline Byte& B() { return b_; }
    inline const Byte A() const { return a_; }
    inline Byte& A() { return a_; }

    friend constexpr bool operator==(jColor lhs, jColor rhs);

    friend jColor ColorLerp(jColor from, jColor to, float interpolator);
private:
    Byte a_, r_, g_, b_;
};

}
}

