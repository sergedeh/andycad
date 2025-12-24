#pragma once
#include "MFCStubs.h"
#include "RenderContext.hpp"

// Mac CoreGraphics Stubs for Linux Port
#define kCGTextFillStroke 0
#define kCGEncodingMacRoman 1
struct CGRect { double origin_x, origin_y, size_width, size_height; };
inline CGRect CGRectMake(double x, double y, double w, double h) { return {x,y,w,h}; }

typedef void* CGContextRef;
inline void CGContextMoveToPoint(void* c, double x, double y) {}
inline void CGContextAddLineToPoint(void* c, double x, double y) {}
inline void CGContextShowTextAtPoint(void* c, double x, double y, const char* str, size_t len) {}
inline void CGContextStrokePath(void* c) {}
inline void CGContextSetLineWidth(void* c, double w) {}
inline void CGContextSetRGBStrokeColor(void* c, double r, double g, double b, double a) {}
inline void CGContextSetRGBFillColor(void* c, double r, double g, double b, double a) {}
inline void CGContextFillRect(void* c, CGRect r) {} 
inline void CGContextSetTextDrawingMode(void* c, int mode) {}
inline void CGContextSelectFont(void* c, const char* name, double size, int encoding) {}
inline void CGContextSetFontSize(void* c, double size) {}


class CDC : public RenderContext {
public:
    void* context = nullptr; // Mac context stub

    CDC() {}
    virtual ~CDC() {}
    virtual void Polyline(LPPOINT points, int count) {}
    virtual void Polyline(const void* points, int count) {} 
    virtual void Rectangle(int x, int y, int w, int h) {}
    template<typename RectType> void Rectangle(const RectType& r) {}
    virtual void BeginPath() {}
    virtual void EndPath() {}
    virtual void FillPath() {}
    virtual void* SelectObject(void* obj) { return 0; }
    virtual CPen* SelectObject(CPen* obj) { return 0; }
    virtual CBrush* SelectObject(CBrush* obj) { return 0; }
    virtual HDC GetSafeHdc() { return 0; }
    virtual void MoveTo(int x, int y) {}
    virtual void LineTo(int x, int y) {}
    template<typename T> void MoveTo(const T& p) {}
    template<typename T> void LineTo(const T& p) {}
    virtual void TextOut(int x, int y, const char* s) {}
    virtual void TextOut(int x, int y, const std::string& s) {}
    virtual int SetROP2(int mode) { return 0; }
    virtual void Ellipse(int x1, int y1, int x2, int y2) {}
    template<typename RectType> void Ellipse(const RectType& r) {}
    // RenderContext implementation
    void drawLine(const CVector& start, const CVector& end) override {
        MoveTo(start);
        LineTo(end);
    }
    void drawText(const CVector& pos, const std::string& text) override {
        TextOut((int)pos.x, (int)pos.y, text);
    }
};
