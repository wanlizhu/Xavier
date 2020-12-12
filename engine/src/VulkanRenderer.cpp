#include "VulkanRenderer.h"
#include "vulkan-core/VulkanBuffer.h"
#include "vulkan-core/VulkanImage.h"
#include "vulkan-core/VulkanEffect.h"
#include "vulkan-core/VulkanDescriptorSet.h"
#include "vulkan-core/VulkanRenderPass.h"
#include "vulkan-core/VulkanCommandBuffer.h"
#include "vulkan-core/VulkanSwapChain.h"

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
        SAFE_DELETE(mSwapChain);

        mSwapChain = new VulkanSwapChain(mVkDevice, window);

        for (uint32_t i = 0; i < mQueueFamilyProperties.size(); i++)
        {
            i += mGraphicsQueueFamilyIndex;
            i %= mQueueFamilyProperties.size();

            VkBool32 supportPresent = VK_FALSE;
            VK_ASSERT(vkGetPhysicalDeviceSurfaceSupportKHR(
                    mVkPhysicalDevice,
                    i,
                    mSwapChain->GetSurface(),
                    &supportPresent
            ));

            if (supportPresent == VK_TRUE)
            {
                mPresentQueueFamilyIndex = i;
                break;
            }
        }
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
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        
        VK_ASSERT(vkCreateDevice(mVkPhysicalDevice, &deviceCreateInfo, nullptr, &mVkDevice));
    }
}
