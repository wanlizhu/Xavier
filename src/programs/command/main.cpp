#include "IEngine.h"

using namespace Xavier;

int main(int argc, char** argv)
{
    IEngine* engine = AllocateEngine();
    FreeEngine(engine);
    return 0;
}
