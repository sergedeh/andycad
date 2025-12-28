#pragma once

#include "../core/utils/CDC.h"

// Placeholder WASM backend for CDC. Implement canvas/WebGL calls later.
class CDC_WASM : public CDC {
public:
    CDC_WASM() = default;
    ~CDC_WASM() override = default;

    void Polyline(LPPOINT points, int count) override;
    void Polyline(const void* points, int count) override;
    void Rectangle(int x, int y, int w, int h) override;
    void BeginPath() override;
    void EndPath() override;
    void FillPath() override;
    void* SelectObject(void* obj) override;
    CPen* SelectObject(CPen* obj) override;
    CBrush* SelectObject(CBrush* obj) override;
    HDC GetSafeHdc() override;
    void MoveTo(int x, int y) override;
    void LineTo(int x, int y) override;
    void TextOut(int x, int y, const char* s) override;
    void TextOut(int x, int y, const std::string& s) override;
    int SetROP2(int mode) override;
    void Ellipse(int x1, int y1, int x2, int y2) override;
};
