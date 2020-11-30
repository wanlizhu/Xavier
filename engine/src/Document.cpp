#include "Document.h"

namespace Xavier
{
    Document::~Document()
    {}

    bool Document::IsValid() const
    {
        return true;
    }

    void Document::OpenWindow()
    {}

    void Document::CloseWindow()
    {}

    void Document::Render(
        const char* outFile,
        IRenderer*  renderer,
        PFN_OnProgress progressFunc,
        PFN_OnError errorFunc
    )
    {

    }
}