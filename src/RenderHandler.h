//
// Created by ditto on 3/11/2023.
//

#ifndef LOTUS_RENDERHANDLER_H
#define LOTUS_RENDERHANDLER_H


#include <GL/glew.h>
#include <include/cef_render_handler.h>

class RenderHandler : public CefRenderHandler
{
public:
    RenderHandler();

public:
    void init();
    void resize(int w, int h);

    // CefRenderHandler interface
public:
    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override;

    // CefBase interface
public:
IMPLEMENT_REFCOUNTING(RenderHandler);

public:
    GLuint tex() const { return tex_; }

private:
    int width_;
    int height_;

    GLuint tex_;
};


#endif //LOTUS_RENDERHANDLER_H
