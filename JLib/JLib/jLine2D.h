#pragma once
#include "jVector.h"
#include "jColor.h"
#include "jCanvas.h"

namespace jLib{
namespace jGraphic {

    class jIDrawLineAlgorithm {
    public:
        virtual void drawLine(jCanvas &canvas, const jVec2f &p0_, const jVec2f &p1_, jColor color) = 0;
        virtual ~jIDrawLineAlgorithm() {}
    };

    class jDDALine : public jIDrawLineAlgorithm {
        void drawLine(jCanvas &canvas, const jVec2f &p0_, const jVec2f &p1_, jColor color) override final {
            int dx = static_cast<int>(p1_[0] - p0_[0]);
            int dy = static_cast<int>(p1_[1] - p0_[1]);
            int steps, k;
            float xIncrement, yIncrement, x = p0_[0], y = p0_[1];
            if (abs(dx) > abs(dy)) {
                steps = abs(dx);
            }
            else {
                steps = abs(dy);
            }
            xIncrement = float(dx) / float(steps);
            yIncrement = float(dy) / float(steps);
            canvas.setPixel((int)round(x), (int)round(y), color);
            for (k = 0; k < steps; ++k)
            {
                x += xIncrement;
                y += yIncrement;
                canvas.setPixel(static_cast<int>(round(x)), static_cast<int>(round(y)), color);
            }
        };
    };

    class jLine2D{
    public:
        jLine2D(const jVec2f p0, const jVec2f p1, jColor color) 
            : p0_(p0), p1_(p1), color_(color)
        {
            drawLineAlgoPtr_ = std::make_shared<jDDALine>();
        }
        void drawOn(jCanvas &canvas) {
            drawLineAlgoPtr_->drawLine(canvas, p0_, p1_, color_);
        };
    private:
        jVec2f p0_, p1_;
        jColor color_;
        std::shared_ptr<jIDrawLineAlgorithm> drawLineAlgoPtr_;
    };    
}
}