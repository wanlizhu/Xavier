#pragma once

#include "IDocument.h"

namespace Xavier
{
    class Document : public IDocument
    {
    public:
        Document() = default;
        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;
        virtual ~Document();

        virtual bool IsValid() const override;
        virtual void OpenWindow() override;
        virtual void CloseWindow() override;
        virtual void Render(
            const char* outFile,
            IRenderer * renderer,
            PFN_OnProgress progressFunc,
            PFN_OnError errorFunc
        ) override;
    };
}