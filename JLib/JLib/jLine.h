#pragma once
#include "jVector.h"
#include "jColor.h"
#include "jConvas.h"

namespace jGraphic {

    class jIDrawLineAlgorithm {
    public:
        virtual void drawLine(jCanvas &canvas, jPoint3D p0_, jPoint3D p1_, jColor color) = 0;
        virtual ~jIDrawLineAlgorithm() {}
    };

    class jDDALine : public jIDrawLineAlgorithm {
        void drawLine(jCanvas &canvas, jPoint3D p0_, jPoint3D p1_, jColor color) override final {
            int dx = p1_[0] - p0_[0];
            int dy = p1_[1] - p0_[1];
            int steps, k;
            float xIncrement, yIncrement, x = p0_[0], y = p0_[1];
            if (fabs(dx) > fabs(dy)) {
                steps = fabs(dx);
            }
            else {
                steps = fabs(dy);
            }
            xIncrement = float(dx) / float(steps);
            yIncrement = float(dy) / float(steps);
            canvas.setPixel(round(x), round(y), color);
            for (k = 0; k < steps; ++k)
            {
                x += xIncrement;
                y += yIncrement;
                canvas.setPixel(round(x), round(y), color);
            }
        };

    };

    class jLine{
    public:
        jLine(const jPoint3D p0, const jPoint3D p1, jColor color) 
            : p0_(p0), p1_(p1), color_(color)
        {
            drawLineAlgoPtr_ = std::make_shared<jDDALine>();
        }
        void drawOn(jCanvas &canvas) {
            drawLineAlgoPtr_->drawLine(canvas, p0_, p1_, color_);
        };
    private:
        jPoint3D p0_, p1_;
        jColor color_;
        std::shared_ptr<jIDrawLineAlgorithm> drawLineAlgoPtr_;
    };    
}