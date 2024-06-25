#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>
#include <string>
#include <array>

#include "glm/glm.hpp"

namespace
{
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

}

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() { return graphicsFamily.has_value(); }
};

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription() 
	{
        VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() 
	{
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

class VulkanBaseContext
{
public:
	void run();

	std::string ShaderPath()
	{
		return SHADER_PATH;
	}

	const int MAX_FRAMES_IN_FLIGHT = 2;
	const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, -0.5}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5}, {1.0f, 1.0f, 1.0f}},
	{{-0.5f, -0.5f, 0.5}, {1.0f, 1.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5}, {0.0f, 1.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5}, {1.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5}, {1.0f, 1.0f, 1.0f}},

	};
	const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0, 0, 4, 7, 7, 3, 0, 0, 4, 5, 5, 1, 0, 1, 5, 6, 6, 2, 1, 4, 5, 6, 6, 7, 4, 3, 7, 6, 6, 2, 3
	};
	/*const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},

    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};*/
private:
	GLFWwindow* window;

	VkInstance instance;
	VkDevice device;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT debugMessenger;

	VkSurfaceKHR surface;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkFramebuffer> swapChainFramebuffers;


	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	uint32_t currentFrame = 0;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif



//--------------------------------------------------------------------------------
	void initVulkan();
	void initWindow();
	void createInstance();
	void setupDebugMessenger();
	void pickPhysicalDevice();
	void mainLoop();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void cleanup();

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	std::vector<const char*> getRequiredExtensions();
	bool checkValidationLayerSupport();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkShaderModule createShaderModule(const std::vector<char>& code);


	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDeviceSize srcOffset = 0, VkDeviceSize dstOffset = 0);

	void createVertexBuffer();
	void createIndexBuffer();

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void drawFrame();
	void createSemaphores();
	void createFence();

	void cleanupSwapChain();

	void recreateSwapChain();

	bool framebufferResized = false;

public:
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
	void createDescriptorSetLayout();
	void createUniformBuffer();
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	void updateUniformBuffer(uint32_t currentFrame);

	void createDescriptorPool();
	VkDescriptorPool descriptorPool;
	void createDescriptorSets();
	std::vector<VkDescriptorSet> descriptorSets;

	void createTextureImage();
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
};