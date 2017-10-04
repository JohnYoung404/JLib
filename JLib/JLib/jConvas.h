#pragma once
#include "jBitMap.h"
#include "jColor.h"

namespace jGraphic {

    class jIConvas {
    public:
        virtual uint8_t& getPosRef(int hori, int vert, int cannel) = 0;
        virtual void setPixel(int x, int y, jColor color) = 0;
        virtual ~jIConvas() {};
    };

    class jBitMapConvas : public jIConvas {
    public:
        jBitMapConvas(jBitMap &bitmap) {
            bitmapPtr_ = &bitmap;
        }
        uint8_t& getPosRef(int hori, int vert, int cannel) override {
            return bitmapPtr_->RefOfPos(hori, vert, cannel);
        }
        void setPixel(int x, int y, jColor color) override {
            this->getPosRef(x, y, 0) = color.B();
            this->getPosRef(x, y, 1) = color.G();
            this->getPosRef(x, y, 2) = color.R();
            this->getPosRef(x, y, 3) = color.A();
        }
    private:
        jBitMap* bitmapPtr_;
    };

    class jCanvas {
    public:
        jCanvas(jBitMap & bitmap) {
            canvasPtr_ = std::make_shared<jBitMapConvas>(bitmap);
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
        std::shared_ptr<jIConvas> canvasPtr_;
    };

    

}