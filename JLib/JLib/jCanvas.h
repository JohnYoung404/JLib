#pragma once
#include "jBitMap.h"
#include "jColor.h"

namespace jGraphic {

    class jICanvas {
    public:

        virtual void setPixel(int x, int y, jColor color) {
            if (x >= horiBound() || x < 0 || y >= vertBound() || y < 0)  return;
            this->getPosRef(x, y, 0) = color.B();
            this->getPosRef(x, y, 1) = color.G();
            this->getPosRef(x, y, 2) = color.R();
            this->getPosRef(x, y, 3) = color.A();
        };

        virtual uint8_t& getPosRef(int hori, int vert, int cannel) = 0;
        virtual int horiBound() = 0;
        virtual int vertBound() = 0;
        virtual ~jICanvas() {};
    };

    class jBitMapCanvas : public jICanvas {
    public:
        jBitMapCanvas(jBitMap &bitmap) {
            bitmapPtr_ = &bitmap;
        }
        uint8_t& getPosRef(int hori, int vert, int cannel) override {
            return bitmapPtr_->RefOfPos(hori, vert, cannel);
        }
        int horiBound() override {
            return bitmapPtr_->Width();
        }
        int vertBound() override {
            return bitmapPtr_->Height();
        }
    private:
        jBitMap* bitmapPtr_;
    };

    class jCanvas {
    public:
        jCanvas(jBitMap & bitmap) {
            canvasPtr_ = std::make_shared<jBitMapCanvas>(bitmap);
        }
        uint8_t& getPosRef(int hori, int vert, int cannel) {
            if (canvasPtr_ != nullptr) {
                return canvasPtr_->getPosRef(hori, vert, cannel);
            }
        }
        void setPixel(int x, int y, jColor color) {
            canvasPtr_->setPixel(x, y, color);
        }
    private:
        std::shared_ptr<jICanvas> canvasPtr_;
    };



}