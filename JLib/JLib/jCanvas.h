#pragma once
#include <memory>
#include <cstdint>
#include "jBitMap.h"
#include "jPNG.h"
#include "jColor.h"
#include "jStringUtil.h"

namespace jLib {
namespace jGraphic {

class jICanvas {
public:
    virtual void setPixel(int x, int y, jColor color) = 0;
    virtual const jColor getPixel(int x, int y) const = 0;
    virtual bool LoadImage(const char* filename) = 0;
    virtual bool SaveImage(const char* filename) = 0;
    virtual void CreateEmpty(int width, int height) = 0;
    virtual uint8_t& at(int hori, int vert, int cannel) = 0;
    virtual const uint8_t& at(int hori, int vert, int cannel) const = 0;
    virtual const int horiBound() const = 0;
    virtual const int vertBound() const = 0;
    virtual const int channels() const = 0;
    virtual ~jICanvas() {};
};

// bitmap Canvas
class jBitMapCanvas : public jICanvas {
public:
    jBitMapCanvas()
    {
        _bitmapPtr = std::make_shared<jMedia::jBitMap>();
    }
    jBitMapCanvas(const std::shared_ptr<jMedia::jBitMap> &otherPtr) {
        _bitmapPtr = otherPtr;
    }
    uint8_t& at(int hori, int vert, int cannel) override {
        return _bitmapPtr->at(hori, vert, cannel);
    }
    const uint8_t& at(int hori, int vert, int cannel) const override {
        return _bitmapPtr->at(hori, vert, cannel);
    }
    const int horiBound() const override {
        return _bitmapPtr->Width();
    }
    const int vertBound() const override {
        return _bitmapPtr->Height();
    }
    virtual const int channels() const override{
        return _bitmapPtr->Channel();
    }
    virtual bool LoadImage(const char* filename) override
    {
        return _bitmapPtr->LoadImage(filename);
    }
    virtual bool SaveImage(const char* filename) override
    {
        return _bitmapPtr->SaveImage(filename);
    }
    virtual void CreateEmpty(int width, int height) override
    {
        return _bitmapPtr->CreateEmpty(width, height);
    }
    virtual void setPixel(int x, int y, jColor color) override
    {
        if (x < 0 || x >= horiBound() || y < 0 || y >= horiBound())  return;
        _bitmapPtr->SetPixel(x, y, color);
    }
    virtual const jColor getPixel(int x, int y) const override
    {
        return _bitmapPtr->GetPixel(x, y);
    }
private:
    std::shared_ptr<jMedia::jBitMap> _bitmapPtr;
};

// PNG Canvas
class jPngCanvas : public jICanvas {
public:
    jPngCanvas()
    {
        _pngPtr = std::make_shared<jMedia::jPNG>();
    }
    jPngCanvas(const std::shared_ptr<jMedia::jPNG> &otherPtr) {
        _pngPtr = otherPtr;
    }
    uint8_t& at(int hori, int vert, int cannel) override {
        return _pngPtr->at(hori, vert, cannel);
    }
    const uint8_t& at(int hori, int vert, int cannel) const override {
        return _pngPtr->at(hori, vert, cannel);
    }
    const int horiBound() const override {
        return _pngPtr->Width();
    }
    const int vertBound() const override {
        return _pngPtr->Height();
    }
    virtual const int channels() const override {
        return _pngPtr->Channel();
    }
    virtual bool LoadImage(const char* filename) override
    {
        return _pngPtr->LoadImage(filename);
    }
    virtual bool SaveImage(const char* filename) override
    {
        return _pngPtr->SaveImage(filename);
    }
    virtual void CreateEmpty(int width, int height) override
    {
        return _pngPtr->CreateEmpty(width, height);
    }
    virtual void setPixel(int x, int y, jColor color) override
    {
        if (x < 0 || x >= horiBound() || y < 0 || y >= horiBound())  return;
        _pngPtr->SetPixel(x, y, color);
    }
    virtual const jColor getPixel(int x, int y) const override
    {
        return _pngPtr->GetPixel(x, y);
    }
private:
    std::shared_ptr<jMedia::jPNG> _pngPtr;
};

class jCanvas {
public:
    jCanvas() = default;
    jCanvas(std::shared_ptr<jMedia::jBitMap> bitmapPtr) {
        canvasPtr_ = std::move(std::make_unique<jBitMapCanvas>(bitmapPtr));
    }
    jCanvas(std::shared_ptr<jMedia::jPNG> pngPtr) {
        canvasPtr_ = std::move(std::make_unique<jPngCanvas>(pngPtr));
    }
    void CreateEmpty(int width, int height)
    {
        canvasPtr_->CreateEmpty(width, height);
    }
    bool LoadImage(const char* filename)
    {
        if (jStringUtil::endsWith(filename, ".bmp") || jStringUtil::endsWith(filename, ".BMP"))
        {
            canvasPtr_ = std::move(std::make_unique<jBitMapCanvas>());
            return canvasPtr_->LoadImage(filename);
        }
        else if (jStringUtil::endsWith(filename, ".png") || jStringUtil::endsWith(filename, ".PNG"))
        {
            canvasPtr_ = std::move(std::make_unique<jPngCanvas>());
            return canvasPtr_->LoadImage(filename);
        }
        return false;
    }
    bool SaveImage(const char* filename)
    {
        return canvasPtr_->SaveImage(filename);
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

}}

#include "jTestBase.h"
#include "jLine2D.h"
#include "jCircle.h"

namespace jLib {
    class jCanvasTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();

            jGraphic::jCanvas cvs;
            cvs.LoadImage("srcImg/test.bmp");
            jGraphic::jLine2D theLine = jGraphic::jLine2D(jVec2f{ 0.0f, 0.0f }, jVec2f{ 450.0f, 450.0f }, jGraphic::jColor::Black());
            jGraphic::jLine2D theLine2 = jGraphic::jLine2D(jVec2f{ 0.0f, 450.0f }, jVec2f{ 450.0f, 0.0f }, jGraphic::jColor::Red());
            jGraphic::jLine2D theLine3 = jGraphic::jLine2D(jVec2f{ 0.0f, 200.0f }, jVec2f{ 450.0f, 0.0f }, jGraphic::jColor::Blue());
            jGraphic::jLine2D theLine4 = jGraphic::jLine2D(jVec2f{ 0.0f, 450.0f }, jVec2f{ 200.0f, 0.0f }, jGraphic::jColor::Green());
            jGraphic::jCircle theCircle = jGraphic::jCircle(jVec2f{ 200, 200 }, jGraphic::jColor::Red(), 150);
            theLine.drawOn(cvs);
            theLine2.drawOn(cvs);
            theLine4.drawOn(cvs);
            theLine3.drawOn(cvs);
            theCircle.drawOn(cvs);
            cvs.SaveImage("jCanvasTest/canvas_painting_img.bmp");
            std::cout << "Drawn a picture on bitmap canvas." << std::endl;

            cvs.LoadImage("srcImg/test2.png");
            theLine.drawOn(cvs);
            theLine2.drawOn(cvs);
            theLine4.drawOn(cvs);
            theLine3.drawOn(cvs);
            theCircle.drawOn(cvs);
            cvs.SaveImage("jCanvasTest/canvas_painting_img_2.png");
            std::cout << "Drawn a picture on PNG canvas." << std::endl;
        }
    };
}