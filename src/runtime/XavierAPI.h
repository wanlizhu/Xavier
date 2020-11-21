#pragma once

#include "XavierConfig.h"

namespace Xavier
{
    void OpenDocument(
        const char* inFile,
        const char* outFile = "",
        void* window = nullptr,
        bool  enableCUDA = false,
        PFN_OnProgress progressFunc = nullptr,
        PFN_OnError errorFunc = nullptr
    );
    void CloseDocument();

    void Init();
    void Deinit();
    void SetAccelCUDA(bool enable);
    void SetViewer(void* window);
    void SetOnProgressFunc(PFN_OnProgress progressFunc);
    void SetOnErrorFunc(PFN_OnError errorFunc);

    void WorldBegin(const char* world);
    void WorldEnd();
    void RenderWorld(
        const char* world,
        const char* outFile
    );
    
    void DefineFilm(const char* name, const ArgumentSet& args);
    void DefineSampler(const char* name, const ArgumentSet& args);
    void DefineTexture(const char* name, const ArgumentSet& args);
    void DefineMaterial(const char* name, const ArgumentSet& args);
    void DefineLight(const char* name, const ArgumentSet& args);
    void DefineIntegrator(const char* name, const ArgumentSet& args);
    void DefineAccelerator(const char* name, const ArgumentSet& args);
    void DefinePixelFilter(const char* name, const ArgumentSet& args);
    void DefineCoordinates(const char* name, const ArgumentSet& args);
    void DefineMedium(const char* name, const ArgumentSet& args);
    void DefineMesh(const char* name, const ArgumentSet& args);
    void DefineShape(const char* name, const ArgumentSet& args);
    void DefineCamera(const char* name, const ArgumentSet& args);
}
