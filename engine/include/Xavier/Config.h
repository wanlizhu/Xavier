#pragma once

#if defined(_MSC_VER)
#define MSVC
#endif

#include <array>
#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <any>
#include <map>
#include <variant>
#include <optional>
#include <unordered_map>
#include <cassert>

#define SAFE_DELETE(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; }

namespace Xavier
{
#ifdef XAV_USE_FLOAT_AS_DOUBLE
    using Float = double;
#else
    using Float = float;
#endif

    using PFN_OnProgress = std::function<void(int, int)>;
    using PFN_OnError = std::function<void(int, const char*)>;
    using PFN_OnRender = std::function<void()>;
    using PFN_OnResize = std::function<void()>;
    using ArgumentSet = std::unordered_map<std::string, std::any>;

    template<typename T>
    using Array = std::vector<T>;

    template<typename K, typename V>
    using Hash = std::unordered_map<K, V>;

    static constexpr Float FLOAT_MAX = std::numeric_limits<Float>::max();
    static constexpr Float FLOAT_INF = std::numeric_limits<Float>::infinity();
    static constexpr Float FLOAT_EPS = std::numeric_limits<Float>::epsilon();
    static constexpr Float MACHINE_EPS = FLOAT_EPS * 0.5;
    static constexpr Float SHADOW_EPS = 0.0001f;
    static constexpr Float PI = 3.14159265358979323846;
    static constexpr Float INV_PI = 0.31830988618379067154;
    static constexpr Float INV_2PI = 0.15915494309189533577;
    static constexpr Float INV_4PI = 0.07957747154594766788;
    static constexpr Float PI_OVER2 = 1.57079632679489661923;
    static constexpr Float PI_OVER4 = 0.78539816339744830961;
    static constexpr Float SQRT2 = 1.41421356237309504880;

    enum class EPixelFormat
    {
        Undefined = 0,
        R_U8,
        R_F32,
        RG_U8,
        RG_F32,
        RGB_U8,
        RGB_F32,
        RGBA_U8,
        RGBA_F32,
        D24S8,
    };

    enum class EBufferUsage
    {
        Undefined = 0,
    };

    enum class EImageUsage
    {
        Undefined = 0,
    };

    struct Color
    {
        float r = 0.f;
        float g = 0.f;
        float b = 0.f;
        float a = 1.f;

        Color() = default;
        Color(float r_, float g_, float b_, float a_ = 1.f)
            : r(r_), g(g_), b(b_), a(a_)
        {}
    };

    struct Offset
    {
        int x = 0;
        int y = 0;
    };

    struct Extent
    {
        int width = 0;
        int height = 0;
    };

    struct VulkanBufferCreateInfo
    {
        size_t size = 0;
        uint32_t usage = 0; 
    };

    struct VulkanImageCreateInfo
    {
        EPixelFormat format = EPixelFormat::Undefined;
        Extent extent;
        uint32_t mipLevels = 1;
        uint32_t arrayLayers = 1;
        uint32_t samples = 1;
        uint32_t usage = 0;
    };

    struct VulkanRenderPassCreateInfo
    {
        
    };

    struct VulkanEffectCreateInfo
    {
        std::string vsPath;
        std::string psPath;
    };
}
