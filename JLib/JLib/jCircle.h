#pragma once
#include "jVector.h"
#include "jColor.h"
#include "jCanvas.h"
#include "jUtility.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jCircle 
{
public:
    jCircle(jVec2f pos, jColor color, float radius) : pos_(pos), color_(color), radius_(radius) {}

    void drawOn(jCanvas & canvas) {
        jContainer::jVecBase<int, 2> circlePoint = jContainer::jVecBase<int, 2>{ 0, (int)radius_ };
        int p = 1 - (int)radius_;
        setCirclePoints(circlePoint, canvas);
        while (circlePoint[0] < circlePoint[1])
        {
            circlePoint[0] = circlePoint[0] + 1;
            if (p < 0)
                p += 2 * circlePoint[0] + 1;
            else {
                circlePoint[1] = circlePoint[1] - 1;
                p += 2 * (circlePoint[0] - circlePoint[1]) + 1;
            }
            setCirclePoints(circlePoint, canvas);
        }
    }

private:
    jVec2f pos_;
    jColor color_;
    float radius_;

    void setCirclePoints(const jContainer::jVecBase<int, 2> &circlePoint, jCanvas &canvas) {
        canvas.setPixel((int)pos_[0] + circlePoint[0], (int)pos_[1] + circlePoint[1], color_);
        canvas.setPixel((int)pos_[0] - circlePoint[0], (int)pos_[1] + circlePoint[1], color_);
        canvas.setPixel((int)pos_[0] + circlePoint[0], (int)pos_[1] - circlePoint[1], color_);
        canvas.setPixel((int)pos_[0] - circlePoint[0], (int)pos_[1] - circlePoint[1], color_);

        canvas.setPixel((int)pos_[0] + circlePoint[1], (int)pos_[1] + circlePoint[0], color_);
        canvas.setPixel((int)pos_[0] - circlePoint[1], (int)pos_[1] + circlePoint[0], color_);
        canvas.setPixel((int)pos_[0] + circlePoint[1], (int)pos_[1] - circlePoint[0], color_);
        canvas.setPixel((int)pos_[0] - circlePoint[1], (int)pos_[1] - circlePoint[0], color_);
    }
};

NAME_SPACE_END
NAME_SPACE_END