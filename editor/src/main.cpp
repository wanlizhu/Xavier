#include <iostream>
#include "Xavier/IEngine.h"

using namespace Xavier;

int main(int argc, char** argv)
{
    IEngine* engine = AllocateEngine(argc, argv);
    
    IDocument* doc = engine->OpenDocument("");
    doc->SetRenderer(engine->GetRenderer());
    doc->OpenWindow();

    if (engine->IsRayTracingEnabled())
    {
        doc->RunRayTracing(
            "",
            nullptr,
            nullptr
        );
    }
    else
    {
        doc->WaitUntilWindowClosed();
    }

    engine->CloseDocument(doc);
    FreeEngine(engine);

    return 0;
}