#pragma once
#include <memory>
#include <cstdint>
#include "jBitMap.h"
#include "jColor.h"

namespace jLib {
namespace jGraphic {

class jICanvas {
public:

    virtual void setPixel(int x, int y, jColor color) {
        if (x >= horiBound() || x < 0 || y >= vertBound() || y < 0)  return;
        if (channels() == 3 || channels() == 4)
        {
            this->at(x, y, 0) = color.B();
            this->at(x, y, 1) = color.G();
            this->at(x, y, 2) = color.R();
            if(channels() == 4) this->at(x, y, 3) = color.A();
        }
    };
    virtual const jColor getPixel(int x, int y) const {
        jGraphic::jColor ret;
        if (channels() == 3 || channels() == 4)
        {
            ret.B() = at(x, y, jMedia::jBitMap::B);
            ret.G() = at(x, y, jMedia::jBitMap::G);
            ret.R() = at(x, y, jMedia::jBitMap::R);
            ret.A() = 255;
            if (channels() == 4) ret.A() = at(x, y, jMedia::jBitMap::A);
        }
        return ret;
    }

    virtual uint8_t& at(int hori, int vert, int cannel) = 0;
    virtual const uint8_t& at(int hori, int vert, int cannel) const = 0;
    virtual const int horiBound() const = 0;
    virtual const int vertBound() const = 0;
    virtual const int channels() const = 0;
    virtual ~jICanvas() {};
};

class jBitMapCanvas : public jICanvas {
public:
    jBitMapCanvas(jMedia::jBitMap &bitmap) {
        bitmapPtr_ = &bitmap;
    }
    uint8_t& at(int hori, int vert, int cannel) override {
        return bitmapPtr_->at(hori, vert, cannel);
    }
    const uint8_t& at(int hori, int vert, int cannel) const override {
        return bitmapPtr_->at(hori, vert, cannel);
    }
    const int horiBound() const override {
        return bitmapPtr_->Width();
    }
    const int vertBound() const override {
        return bitmapPtr_->Height();
    }
    virtual const int channels() const override{
        return bitmapPtr_->Channel();
    }
private:
    jMedia::jBitMap* bitmapPtr_;
};

class jCanvas {
public:
    jCanvas(jMedia::jBitMap & bitmap) {
        canvasPtr_ = std::move(std::make_unique<jBitMapCanvas>(bitmap));
    }
    uint8_t& at(int hori, int vert, int cannel) {
        if (canvasPtr_ != nullptr) {
            return canvasPtr_->at(hori, vert, cannel);
        }
    }
    const uint8_t& at(int hori, int vert, int cannel) const {
        if (canvasPtr_ != nullptr) {
            return canvasPtr_->at(hori, vert, cannel);
        }
    }
    void setPixel(int x, int y, jColor color) {
        canvasPtr_->setPixel(x, y, color);
    }
    const jColor getPixel(int x, int y) const
    {
        canvasPtr_->getPixel(x, y);
    }
    const int horiBound() const {
        return canvasPtr_->horiBound();
    }
    const int vertBound() const {
        return canvasPtr_->vertBound();
    }
private:
    std::unique_ptr<jICanvas> canvasPtr_;
};

}
}

#include "jTestBase.h"
#include "jLine2D.h"
#include "jCircle.h"

namespace jLib {
    class jCanvasTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();
            using jContainer::jPoint2D;

            jMedia::jBitMap m;
            m.LoadImage("srcImg/test.bmp");
            jGraphic::jCanvas cvs = jGraphic::jCanvas(m);
            jGraphic::jLine2D theLine = jGraphic::jLine2D(jPoint2D{ 0.0f, 0.0f }, jPoint2D{ 450.0f, 450.0f }, jGraphic::jColor::Black());
            jGraphic::jLine2D theLine2 = jGraphic::jLine2D(jPoint2D{ 0.0f, 450.0f }, jPoint2D{ 450.0f, 0.0f }, jGraphic::jColor::Red());
            jGraphic::jLine2D theLine3 = jGraphic::jLine2D(jPoint2D{ 0.0f, 200.0f }, jPoint2D{ 450.0f, 0.0f }, jGraphic::jColor::Blue());
            jGraphic::jLine2D theLine4 = jGraphic::jLine2D(jPoint2D{ 0.0f, 450.0f }, jPoint2D{ 200.0f, 0.0f }, jGraphic::jColor::Green());
            jGraphic::jCircle theCircle = jGraphic::jCircle(jPoint2D{ 200, 200 }, jGraphic::jColor::Red(), 150);
            theLine.drawOn(cvs);
            theLine2.drawOn(cvs);
            theLine4.drawOn(cvs);
            theLine3.drawOn(cvs);
            theCircle.drawOn(cvs);
            m.SaveImage("jCanvasTest/canvas_painting_img.bmp");
            std::cout << "Drawn a picture on bitmap canvas." << std::endl;
        }
    };
}