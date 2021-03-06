#include "VulkanRenderer.h"
#include "vulkan-core/VulkanBuffer.h"
#include "vulkan-core/VulkanImage.h"
#include "vulkan-core/VulkanEffect.h"
#include "vulkan-core/VulkanDescriptorSet.h"
#include "vulkan-core/VulkanRenderPass.h"
#include "vulkan-core/VulkanCommandBuffer.h"
#include "vulkan-core/VulkanSwapChain.h"
#include "vulkan-core/VulkanCommandQueue.h"

namespace Xavier
{
    VulkanRenderer::~VulkanRenderer()
    {
        Deinit();
    }

    void VulkanRenderer::Init()
    {
        Deinit();
        CreateVulkanInstance();
        CreateVulkanDevice();
    }

    void VulkanRenderer::Deinit()
    {
        mSwapChain = nullptr;

        if (mVkDevice)
        {
            vkDestroyDevice(mVkDevice, nullptr);
            mVkDevice = VK_NULL_HANDLE;
        }

        if (mVkInstance)
        {
            vkDestroyInstance(mVkInstance, nullptr);
            mVkInstance = VK_NULL_HANDLE;
        }
    }

    void VulkanRenderer::CreateSwapChain(void* window)
    {
        CreateSurface(window);
        ChoosePresentQueue();

        mSwapChain = std::make_shared<VulkanSwapChain>(mVkDevice, mVkSurface);
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

    void VulkanRenderer::ClearColor(Color color)
    {}

    void VulkanRenderer::ClearDS(float depth, uint8_t stencil)
    {}

    void VulkanRenderer::Present()
    {
        if (mSwapChain)
        {
            mSwapChain->Present(mPendingSemaphores);
        }
    }

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

    void VulkanRenderer::CreateSurface(void* window)
    {}

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

    void ChooseDeviceQueueFamily(
        VkPhysicalDevice physicalDevice, 
        std::vector<VkQueueFamilyProperties>* properties,
        std::vector<VkDeviceQueueCreateInfo>* createInfos
    )
    {
        uint32_t queueCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, nullptr);

        properties->resize(queueCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, properties->data());

        for (uint32_t i = 0; i < queueCount; i++)
        {
            static const float priority = 1.f;
            VkDeviceQueueCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            createInfo.pNext = nullptr;
            createInfo.flags = 0;
            createInfo.pQueuePriorities = &priority;
            createInfo.queueFamilyIndex = i;
            createInfo.queueCount = 1;

            createInfos->push_back(createInfo);
        }
    }

    void VulkanRenderer::CreateVulkanDevice()
    {
        assert(mVkInstance != VK_NULL_HANDLE);
        assert(mVkDevice == VK_NULL_HANDLE);

        ChoosePhysicalDevice(mVkInstance, &mVkPhysicalDevice);

        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        ChooseDeviceQueueFamily(mVkPhysicalDevice, &queueFamilyProperties, &queueCreateInfos);

        VkPhysicalDeviceFeatures enableFeatures = {};
        vkGetPhysicalDeviceFeatures(mVkPhysicalDevice, &enableFeatures);

        std::vector<const char*> extensionNames;
        GetPhysicalDeviceExtensions(mVkPhysicalDevice, &extensionNames);
        
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

        for (uint32_t i = 0; i < queueFamilyProperties.size(); i++)
        {
            if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
                mGraphicsQueue == nullptr)
            {
                mGraphicsQueue = std::make_shared<VulkanCommandQueue>(
                    mVkDevice, 
                    i,
                    queueFamilyProperties[i]
                );
            }

            if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) &&
                mTransferQueue == nullptr)
            {
                mTransferQueue = std::make_shared<VulkanCommandQueue>(
                    mVkDevice, 
                    i,
                    queueFamilyProperties[i]
                );
            }
        }
    }

    void VulkanRenderer::ChoosePresentQueue()
    {
        assert(mVkSurface != VK_NULL_HANDLE);

    }
}
