#pragma once

namespace jLib {
namespace jGraphic {

class jColor
{
public:
    typedef unsigned char Byte;

    jColor(Byte a = 0, Byte r = 0, Byte g = 0, Byte b = 0) : a_(a), r_(r), g_(g), b_(b) {}

    inline static const jColor Black() {
        return jColor(255, 0, 0, 0);
    }
    inline static const jColor White() {
        return jColor(255, 255, 255, 255);
    }
    inline static const jColor Red() {
        return jColor(255, 255, 0, 0);
    }
    inline static const jColor Green() {
        return jColor(255, 0, 255, 0);
    }
    inline static const jColor Blue() {
        return jColor(255, 0, 0, 255);
    }

    inline const Byte R() const { return r_; }
    inline const Byte G() const { return g_; }
    inline const Byte B() const { return b_; }
    inline const Byte A() const { return a_; }

    friend bool operator==(jColor lhs, jColor rhs);

    friend jColor ColorLerp(jColor from, jColor to, float interpolator);
private:
    Byte a_, r_, g_, b_;
};

}
}

