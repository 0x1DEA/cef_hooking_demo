#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cocos2d.h>
#include "MinHook.h"
#include "include/internal/cef_win.h"
#include "RenderHandler.h"
#include "include/cef_app.h"
#include "WebCore.h"
#include <functional>
#include <fstream>

using namespace cocos2d;

bool loaded = false;
bool initialized;
bool result;
HGLRC context;

WebCoreManager webCoreMgr;
std::weak_ptr<WebCore> webCore;

float vertices[] = {
        -1, -1, 0,
        1, -1, 0,
        -1, 1, 0,
        1, 1, 0,
};

float texcoords[] = {
        0, 1,
        1, 1,
        0, 0,
        1, 0,
};

unsigned short indices[] = {
        0, 1, 3,
        0, 3, 2,
};

GLint pos_loc = -1;
GLint texcoord_loc = -1;
GLint tex_loc = -1;
GLint mvp_loc = -1;

void (__thiscall* CCEGLView_swapBuffers)(CCEGLView*);
void __fastcall CCEGLView_swapBuffers_H(CCEGLView* self) {
    auto* shader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor);
    shader->use();
    shader->setUniformsForBuiltins();

    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | cocos2d::kCCVertexAttribFlag_Color);

    if(result) {
        auto window = self->getWindow();

        if (!loaded) {
            //context = wglCreateContext(hdc);
            //auto hwnd = WindowFromDC(*reinterpret_cast<HDC*>(reinterpret_cast<uintptr_t>(window) + 0x244));
        }

        //auto glView = CCEGLView::sharedOpenGLView();
        //auto size = cocos2d::CCDirector::sharedDirector()->getWinSize();


        // draw
        /*
        GLfloat mvp[4] = {-1.0f, 1.0f, -1.0f, 1.0f};
        glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, mvp);

        glEnableVertexAttribArray(pos_loc);
        glEnableVertexAttribArray(texcoord_loc);
         */

        // bind texture
        //glBindTexture(GL_TEXTURE_2D, webCore.lock()->render_handler()->tex());

        // draw
        /*
        glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, texcoords);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_SHORT, indices);
         */

        webCoreMgr.update();
    }

    double x1 = 100;
    double y1 = 100;
    double sidelength = 100;
    double halfside = sidelength / 2;

    glColor3d(0,0,0);
    glBegin(GL_POLYGON);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();

    CCEGLView_swapBuffers(self);
}

DWORD WINAPI thread(void *hModule) {
    std::ofstream log;
    std::string logfile;
    logfile = std::to_string(std::time(nullptr));
    logfile.append("_lotus.txt");
    log.open(logfile, std::ios::out | std::ios::app);
    log << "----- Lotus Start" << std::endl;
    int exit_code = 0;
    log << "Setting up CEF" << std::endl;
    //result = webCoreMgr.setUp(&exit_code);

    if (!result)
    {
        log << "Failed to initialize CEF" << std::endl;
    } else {
        log << "Creating browser" << std::endl;
        std::string url = "http://google.com";
        //webCore = webCoreMgr.createBrowser(url);
        //webCore.lock()->reshape(500, 500);
    }
    log << "Hooking" << std::endl;
    auto base = GetModuleHandleA("libcocos2d.dll");
    MH_Initialize();
    MH_CreateHook(GetProcAddress(base, "?swapBuffers@CCEGLView@cocos2d@@UAEXXZ"), CCEGLView_swapBuffers_H, reinterpret_cast<void**>(&CCEGLView_swapBuffers));
    MH_EnableHook(MH_ALL_HOOKS);

    log << "Finished startup" << std::endl;
    log.close();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD s, LPVOID) {
    if (s == DLL_PROCESS_ATTACH) {

        DisableThreadLibraryCalls(module);
        CreateThread(0, 0, thread, module, 0, 0);
    }
    return TRUE;
}
