#include "VulkanRenderer.h"
#include "vulkan-core/VulkanBuffer.h"
#include "vulkan-core/VulkanImage.h"
#include "vulkan-core/VulkanEffect.h"
#include "vulkan-core/VulkanDescriptorSet.h"
#include "vulkan-core/VulkanRenderPass.h"
#include "vulkan-core/VulkanCommandBuffer.h"

namespace Xavier
{
    VulkanRenderer::~VulkanRenderer()
    {
        Deinit();
    }

    bool VulkanRenderer::Init()
    {
        try
        {
            Deinit();
            CreateVulkanInstance();
            CreateVulkanDevice();
        }
        catch (const std::exception& err)
        {
            std::cerr << "error: failed to init vulkan renderer: " << err.what() << std::endl;
            return false;
        }

        return true;
    }

    void VulkanRenderer::Deinit()
    {
        if (mVkInstance == VK_NULL_HANDLE && mVkDevice == VK_NULL_HANDLE)
            return;

    }

    void VulkanRenderer::CreateSwapChain(void* window)
    {
        mSwapchainWindow = window;
        CreateVulkanSwapChain();
    }

    void VulkanRenderer::CreateBuffer(const char* name, const VulkanBufferCreateInfo& info)
    {
        
    }

    void VulkanRenderer::CreateImage(const char* name, const VulkanImageCreateInfo& info)
    {}

    void VulkanRenderer::CreateRenderPass(const char* name, const VulkanRenderPassCreateInfo& info)
    {}

    void VulkanRenderer::CreateEffect(const char* name, const VulkanEffectCreateInfo& info)
    {}

    void VulkanRenderer::ClearColor(Color color)
    {}

    void VulkanRenderer::ClearDS(float depth, uint8_t stencil)
    {}

    void VulkanRenderer::BeginRenderPass(const char* name)
    {}

    void VulkanRenderer::BeginEffect(const char* name)
    {}

    void VulkanRenderer::EndRenderPass()
    {}

    void VulkanRenderer::EndEffect()
    {}

    void VulkanRenderer::UpdateEffectParameter(const char* name, void* data)
    {}

    void VulkanRenderer::Present()
    {}

    void VulkanRenderer::Resize()
    {}

    void EnumerateInstanceExtensions(std::vector<const char*>* extensionNames)
    {
        static std::vector<VkExtensionProperties> properties;
        
        uint32_t count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

        properties.resize(count);
        vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());

        for (auto& prop : properties)
        {
            extensionNames->push_back(prop.extensionName);
        }
    }

    void EnumerateInstanceLayers(std::vector<const char*>* layerNames)
    {
        static std::vector<VkLayerProperties> properties;

        uint32_t count = 0;
        vkEnumerateInstanceLayerProperties(&count, nullptr);

        properties.resize(count);
        vkEnumerateInstanceLayerProperties(&count, properties.data());

        for (auto& prop : properties)
        {
            layerNames->push_back(prop.layerName);
        }
    }

    void VulkanRenderer::CreateVulkanInstance()
    {
        assert(mVkInstance == VK_NULL_HANDLE);

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = "";
        appInfo.pEngineName = "";
        appInfo.applicationVersion = 0;
        appInfo.engineVersion = 0;
        appInfo.apiVersion = VK_VERSION_1_2;

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &appInfo;

        std::vector<const char*> extensionNames;
        EnumerateInstanceExtensions(&extensionNames);
        instanceCreateInfo.enabledExtensionCount = extensionNames.size();
        instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();

#ifdef _DEBUG
        std::vector<const char*> layerNames;
        EnumerateInstanceLayers(&layerNames);
        instanceCreateInfo.enabledLayerCount = layerNames.size();
        instanceCreateInfo.ppEnabledLayerNames = layerNames.data();
#endif
        
        VK_ASSERT(vkCreateInstance(&instanceCreateInfo, nullptr, &mVkInstance));
    }

    void GetPhysicalDeviceExtensions(VkPhysicalDevice physicalDevice, std::vector<const char*>* extensionNames)
    {
        static std::vector<VkExtensionProperties> properties;

        uint32_t count = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, nullptr);

        properties.resize(count);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, properties.data());

        for (auto& prop : properties)
        {
            extensionNames->push_back(prop.extensionName);
        }
    }

    void ChoosePhysicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice)
    {
        std::vector<VkPhysicalDevice> physicalDevices;

        uint32_t count = 0;
        vkEnumeratePhysicalDevices(instance, &count, nullptr);

        physicalDevices.resize(count);
        vkEnumeratePhysicalDevices(instance, &count, physicalDevices.data());

        *physicalDevice = physicalDevices[0];

        for (uint32_t i = 0; i < count; i++)
        {
            VkPhysicalDeviceProperties properties = {};
            vkGetPhysicalDeviceProperties(physicalDevices[i], &properties);

            if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                *physicalDevice = physicalDevices[i];
                return;
            }
        }
    }

    void ChooseDeviceQueues(
        VkPhysicalDevice physicalDevice, 
        uint32_t* graphicsQueueFamilyIndex,
        uint32_t* computeQueueFamilyIndex,
        std::vector<VkQueueFamilyProperties>* queueFamilyProperties,
        std::vector<VkDeviceQueueCreateInfo>* queueCreateInfos
    )
    {
        uint32_t count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);

        queueFamilyProperties->resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, queueFamilyProperties->data());

        auto queues = *queueFamilyProperties;
        VkQueueFlags assignedFlags = 0;

        for (int i = 0; i < count; i++)
        {
            if ((queues[i].queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT)) != 0 &&
                ((assignedFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
            {
                *graphicsQueueFamilyIndex = i;
                assignedFlags |= VK_QUEUE_GRAPHICS_BIT;
            }

            if ((queues[i].queueFlags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT)) != 0 && 
                ((assignedFlags & VK_QUEUE_COMPUTE_BIT) == 0))
            {
                *computeQueueFamilyIndex = i;
                assignedFlags |= VK_QUEUE_COMPUTE_BIT;
            }
        }

        assert(*graphicsQueueFamilyIndex != UINT32_MAX);
        assert(*computeQueueFamilyIndex != UINT32_MAX);

        static const float priority = 1.0f;

        VkDeviceQueueCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.pQueuePriorities = &priority;
        createInfo.queueFamilyIndex = *graphicsQueueFamilyIndex;
        createInfo.queueCount = 1;
        queueCreateInfos->push_back(createInfo);

        if (*graphicsQueueFamilyIndex != *computeQueueFamilyIndex)
        {
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            createInfo.pNext = nullptr;
            createInfo.flags = 0;
            createInfo.pQueuePriorities = &priority;
            createInfo.queueFamilyIndex = *computeQueueFamilyIndex;
            createInfo.queueCount = 1;
            queueCreateInfos->push_back(createInfo);
        }
    }

    void VulkanRenderer::CreateVulkanDevice()
    {
        assert(mVkInstance != VK_NULL_HANDLE);
        assert(mVkDevice == VK_NULL_HANDLE);

        VkPhysicalDeviceFeatures enableFeatures = {};
        std::vector<const char*> extensionNames;
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        ChoosePhysicalDevice(mVkInstance, &mVkPhysicalDevice);
        ChooseDeviceQueues(
            mVkPhysicalDevice, 
            &mGraphicsQueueFamilyIndex,
            &mComputeQueueFamilyIndex,
            &mQueueFamilyProperties, 
            &queueCreateInfos
        );

        GetPhysicalDeviceExtensions(mVkPhysicalDevice, &extensionNames);
        vkGetPhysicalDeviceFeatures(mVkPhysicalDevice, &enableFeatures);

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = nullptr;
        deviceCreateInfo.flags = 0;
        deviceCreateInfo.pEnabledFeatures = &enableFeatures;
        deviceCreateInfo.enabledExtensionCount = extensionNames.size();
        deviceCreateInfo.ppEnabledExtensionNames = extensionNames.data();
        deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
        
        VK_ASSERT(vkCreateDevice(mVkPhysicalDevice, &deviceCreateInfo, nullptr, &mVkDevice));
    }

    void AdjustSwapchainCreateInfo(
        VkSurfaceKHR surface,
        VkSwapchainCreateInfoKHR* createInfo
    )
    {

    }

    void VulkanRenderer::CreateVulkanSwapChain()
    {
        DeleteVulkanSwapChain();
        assert(mSwapchainWindow != nullptr);
        
        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
        surfaceCreateInfo.hwnd = (HWND)mSwapchainWindow;

        VK_ASSERT(vkCreateWin32SurfaceKHR(
            mVkInstance,
            &surfaceCreateInfo,
            nullptr,
            &mVkSurface
        ));

        for (uint32_t i = 0; i < mQueueFamilyProperties.size(); i++)
        {
            i += mGraphicsQueueFamilyIndex;
            i %= mQueueFamilyProperties.size();

            VkBool32 supportPresent = VK_FALSE;
            VK_ASSERT(vkGetPhysicalDeviceSurfaceSupportKHR(
                mVkPhysicalDevice, 
                i, 
                mVkSurface,
                &supportPresent
            ));

            if (supportPresent == VK_TRUE)
            {
                mPresentQueueFamilyIndex = i;
                break;
            }
        }

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = mVkSurface;
        swapchainCreateInfo.minImageCount = 3;
        swapchainCreateInfo.imageExtent = {};
        swapchainCreateInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
        swapchainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        swapchainCreateInfo.clipped = VK_FALSE;
        swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

        AdjustSwapchainCreateInfo(
            mVkSurface,
            &swapchainCreateInfo
        );

        VK_ASSERT(vkCreateSwapchainKHR(
            mVkDevice,
            &swapchainCreateInfo,
            nullptr,
            &mVkSwapchain
        ));

        uint32_t imageCount = 0;
        VK_ASSERT(vkGetSwapchainImagesKHR(
            mVkDevice,
            mVkSwapchain,
            &imageCount,
            nullptr
        ));

        mSwapchainImages.resize(imageCount);
        mSwapchainImageViews.resize(imageCount);
        mSwapchainImageFences.resize(imageCount);
        mSwapchainImageSemaphores.resize(imageCount);
        VK_ASSERT(vkGetSwapchainImagesKHR(
            mVkDevice,
            mVkSwapchain,
            &imageCount,
            mSwapchainImages.data()
        ));

        for (uint32_t i = 0; i < imageCount; i++)
        {
            VkImageViewCreateInfo imageViewCreateInfo = {};
            imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageViewCreateInfo.image = mSwapchainImages[i];
            imageViewCreateInfo.format = swapchainCreateInfo.imageFormat;
            imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
            imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
            imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
            imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
            imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
            imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
            imageViewCreateInfo.subresourceRange.layerCount = 1;
            imageViewCreateInfo.subresourceRange.levelCount = 1;
            
            VK_ASSERT(vkCreateImageView(
                mVkDevice,
                &imageViewCreateInfo,
                nullptr,
                &mSwapchainImageViews[i]
            ));

            VkFenceCreateInfo fenceCreateInfo = {};
            fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
            
            VK_ASSERT(vkCreateFence(
                mVkDevice,
                &fenceCreateInfo,
                nullptr,
                &mSwapchainImageFences[i]
            ));

            VkSemaphoreCreateInfo semaphoreCreateInfo = {};
            semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            
            VK_ASSERT(vkCreateSemaphore(
                mVkDevice,
                &semaphoreCreateInfo,
                nullptr,
                &mSwapchainImageSemaphores[i]
            ));
        }

        AcquireNextSwapChainImage();
    }

    void VulkanRenderer::DeleteVulkanSwapChain()
    {}

    void VulkanRenderer::AcquireNextSwapChainImage()
    {

    }
}
