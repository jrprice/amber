// Copyright 2018 The Amber Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/vulkan/device.h"

#include <memory>
#include <vector>

#include "src/make_unique.h"

namespace amber {
namespace vulkan {
namespace {

VkPhysicalDeviceFeatures RequestedFeatures(
    const std::vector<Feature>& required_features) {
  VkPhysicalDeviceFeatures requested_features = {};
  for (const auto& feature : required_features) {
    switch (feature) {
      case Feature::kRobustBufferAccess:
        requested_features.robustBufferAccess = VK_TRUE;
        break;
      case Feature::kFullDrawIndexUint32:
        requested_features.fullDrawIndexUint32 = VK_TRUE;
        break;
      case Feature::kImageCubeArray:
        requested_features.imageCubeArray = VK_TRUE;
        break;
      case Feature::kIndependentBlend:
        requested_features.independentBlend = VK_TRUE;
        break;
      case Feature::kGeometryShader:
        requested_features.geometryShader = VK_TRUE;
        break;
      case Feature::kTessellationShader:
        requested_features.tessellationShader = VK_TRUE;
        break;
      case Feature::kSampleRateShading:
        requested_features.sampleRateShading = VK_TRUE;
        break;
      case Feature::kDualSrcBlend:
        requested_features.dualSrcBlend = VK_TRUE;
        break;
      case Feature::kLogicOp:
        requested_features.logicOp = VK_TRUE;
        break;
      case Feature::kMultiDrawIndirect:
        requested_features.multiDrawIndirect = VK_TRUE;
        break;
      case Feature::kDrawIndirectFirstInstance:
        requested_features.drawIndirectFirstInstance = VK_TRUE;
        break;
      case Feature::kDepthClamp:
        requested_features.depthClamp = VK_TRUE;
        break;
      case Feature::kDepthBiasClamp:
        requested_features.depthBiasClamp = VK_TRUE;
        break;
      case Feature::kFillModeNonSolid:
        requested_features.fillModeNonSolid = VK_TRUE;
        break;
      case Feature::kDepthBounds:
        requested_features.depthBounds = VK_TRUE;
        break;
      case Feature::kWideLines:
        requested_features.wideLines = VK_TRUE;
        break;
      case Feature::kLargePoints:
        requested_features.largePoints = VK_TRUE;
        break;
      case Feature::kAlphaToOne:
        requested_features.alphaToOne = VK_TRUE;
        break;
      case Feature::kMultiViewport:
        requested_features.multiViewport = VK_TRUE;
        break;
      case Feature::kSamplerAnisotropy:
        requested_features.samplerAnisotropy = VK_TRUE;
        break;
      case Feature::kTextureCompressionETC2:
        requested_features.textureCompressionETC2 = VK_TRUE;
        break;
      case Feature::kTextureCompressionASTC_LDR:
        requested_features.textureCompressionASTC_LDR = VK_TRUE;
        break;
      case Feature::kTextureCompressionBC:
        requested_features.textureCompressionBC = VK_TRUE;
        break;
      case Feature::kOcclusionQueryPrecise:
        requested_features.occlusionQueryPrecise = VK_TRUE;
        break;
      case Feature::kPipelineStatisticsQuery:
        requested_features.pipelineStatisticsQuery = VK_TRUE;
        break;
      case Feature::kVertexPipelineStoresAndAtomics:
        requested_features.vertexPipelineStoresAndAtomics = VK_TRUE;
        break;
      case Feature::kFragmentStoresAndAtomics:
        requested_features.fragmentStoresAndAtomics = VK_TRUE;
        break;
      case Feature::kShaderTessellationAndGeometryPointSize:
        requested_features.shaderTessellationAndGeometryPointSize = VK_TRUE;
        break;
      case Feature::kShaderImageGatherExtended:
        requested_features.shaderImageGatherExtended = VK_TRUE;
        break;
      case Feature::kShaderStorageImageExtendedFormats:
        requested_features.shaderStorageImageExtendedFormats = VK_TRUE;
        break;
      case Feature::kShaderStorageImageMultisample:
        requested_features.shaderStorageImageMultisample = VK_TRUE;
        break;
      case Feature::kShaderStorageImageReadWithoutFormat:
        requested_features.shaderStorageImageReadWithoutFormat = VK_TRUE;
        break;
      case Feature::kShaderStorageImageWriteWithoutFormat:
        requested_features.shaderStorageImageWriteWithoutFormat = VK_TRUE;
        break;
      case Feature::kShaderUniformBufferArrayDynamicIndexing:
        requested_features.shaderUniformBufferArrayDynamicIndexing = VK_TRUE;
        break;
      case Feature::kShaderSampledImageArrayDynamicIndexing:
        requested_features.shaderSampledImageArrayDynamicIndexing = VK_TRUE;
        break;
      case Feature::kShaderStorageBufferArrayDynamicIndexing:
        requested_features.shaderStorageBufferArrayDynamicIndexing = VK_TRUE;
        break;
      case Feature::kShaderStorageImageArrayDynamicIndexing:
        requested_features.shaderStorageImageArrayDynamicIndexing = VK_TRUE;
        break;
      case Feature::kShaderClipDistance:
        requested_features.shaderClipDistance = VK_TRUE;
        break;
      case Feature::kShaderCullDistance:
        requested_features.shaderCullDistance = VK_TRUE;
        break;
      case Feature::kShaderFloat64:
        requested_features.shaderFloat64 = VK_TRUE;
        break;
      case Feature::kShaderInt64:
        requested_features.shaderInt64 = VK_TRUE;
        break;
      case Feature::kShaderInt16:
        requested_features.shaderInt16 = VK_TRUE;
        break;
      case Feature::kShaderResourceResidency:
        requested_features.shaderResourceResidency = VK_TRUE;
        break;
      case Feature::kShaderResourceMinLod:
        requested_features.shaderResourceMinLod = VK_TRUE;
        break;
      case Feature::kSparseBinding:
        requested_features.sparseBinding = VK_TRUE;
        break;
      case Feature::kSparseResidencyBuffer:
        requested_features.sparseResidencyBuffer = VK_TRUE;
        break;
      case Feature::kSparseResidencyImage2D:
        requested_features.sparseResidencyImage2D = VK_TRUE;
        break;
      case Feature::kSparseResidencyImage3D:
        requested_features.sparseResidencyImage3D = VK_TRUE;
        break;
      case Feature::kSparseResidency2Samples:
        requested_features.sparseResidency2Samples = VK_TRUE;
        break;
      case Feature::kSparseResidency4Samples:
        requested_features.sparseResidency4Samples = VK_TRUE;
        break;
      case Feature::kSparseResidency8Samples:
        requested_features.sparseResidency8Samples = VK_TRUE;
        break;
      case Feature::kSparseResidency16Samples:
        requested_features.sparseResidency16Samples = VK_TRUE;
        break;
      case Feature::kSparseResidencyAliased:
        requested_features.sparseResidencyAliased = VK_TRUE;
        break;
      case Feature::kVariableMultisampleRate:
        requested_features.variableMultisampleRate = VK_TRUE;
        break;
      case Feature::kInheritedQueries:
        requested_features.inheritedQueries = VK_TRUE;
        break;
      case Feature::kFramebuffer:
      case Feature::kDepthStencil:
      case Feature::kFenceTimeout:
      case Feature::kUnknown:
        break;
    }
  }
  return requested_features;
}

bool AreAllRequiredFeaturesSupported(
    const VkPhysicalDeviceFeatures& available_features,
    const std::vector<Feature>& required_features) {
  for (const auto& feature : required_features) {
    switch (feature) {
      case Feature::kRobustBufferAccess:
        if (available_features.robustBufferAccess == VK_FALSE)
          return false;
        break;
      case Feature::kFullDrawIndexUint32:
        if (available_features.fullDrawIndexUint32 == VK_FALSE)
          return false;
        break;
      case Feature::kImageCubeArray:
        if (available_features.imageCubeArray == VK_FALSE)
          return false;
        break;
      case Feature::kIndependentBlend:
        if (available_features.independentBlend == VK_FALSE)
          return false;
        break;
      case Feature::kGeometryShader:
        if (available_features.geometryShader == VK_FALSE)
          return false;
        break;
      case Feature::kTessellationShader:
        if (available_features.tessellationShader == VK_FALSE)
          return false;
        break;
      case Feature::kSampleRateShading:
        if (available_features.sampleRateShading == VK_FALSE)
          return false;
        break;
      case Feature::kDualSrcBlend:
        if (available_features.dualSrcBlend == VK_FALSE)
          return false;
        break;
      case Feature::kLogicOp:
        if (available_features.logicOp == VK_FALSE)
          return false;
        break;
      case Feature::kMultiDrawIndirect:
        if (available_features.multiDrawIndirect == VK_FALSE)
          return false;
        break;
      case Feature::kDrawIndirectFirstInstance:
        if (available_features.drawIndirectFirstInstance == VK_FALSE)
          return false;
        break;
      case Feature::kDepthClamp:
        if (available_features.depthClamp == VK_FALSE)
          return false;
        break;
      case Feature::kDepthBiasClamp:
        if (available_features.depthBiasClamp == VK_FALSE)
          return false;
        break;
      case Feature::kFillModeNonSolid:
        if (available_features.fillModeNonSolid == VK_FALSE)
          return false;
        break;
      case Feature::kDepthBounds:
        if (available_features.depthBounds == VK_FALSE)
          return false;
        break;
      case Feature::kWideLines:
        if (available_features.wideLines == VK_FALSE)
          return false;
        break;
      case Feature::kLargePoints:
        if (available_features.largePoints == VK_FALSE)
          return false;
        break;
      case Feature::kAlphaToOne:
        if (available_features.alphaToOne == VK_FALSE)
          return false;
        break;
      case Feature::kMultiViewport:
        if (available_features.multiViewport == VK_FALSE)
          return false;
        break;
      case Feature::kSamplerAnisotropy:
        if (available_features.samplerAnisotropy == VK_FALSE)
          return false;
        break;
      case Feature::kTextureCompressionETC2:
        if (available_features.textureCompressionETC2 == VK_FALSE)
          return false;
        break;
      case Feature::kTextureCompressionASTC_LDR:
        if (available_features.textureCompressionASTC_LDR == VK_FALSE)
          return false;
        break;
      case Feature::kTextureCompressionBC:
        if (available_features.textureCompressionBC == VK_FALSE)
          return false;
        break;
      case Feature::kOcclusionQueryPrecise:
        if (available_features.occlusionQueryPrecise == VK_FALSE)
          return false;
        break;
      case Feature::kPipelineStatisticsQuery:
        if (available_features.pipelineStatisticsQuery == VK_FALSE)
          return false;
        break;
      case Feature::kVertexPipelineStoresAndAtomics:
        if (available_features.vertexPipelineStoresAndAtomics == VK_FALSE)
          return false;
        break;
      case Feature::kFragmentStoresAndAtomics:
        if (available_features.fragmentStoresAndAtomics == VK_FALSE)
          return false;
        break;
      case Feature::kShaderTessellationAndGeometryPointSize:
        if (available_features.shaderTessellationAndGeometryPointSize ==
            VK_FALSE)
          return false;
        break;
      case Feature::kShaderImageGatherExtended:
        if (available_features.shaderImageGatherExtended == VK_FALSE)
          return false;
        break;
      case Feature::kShaderStorageImageExtendedFormats:
        if (available_features.shaderStorageImageExtendedFormats == VK_FALSE)
          return false;
        break;
      case Feature::kShaderStorageImageMultisample:
        if (available_features.shaderStorageImageMultisample == VK_FALSE)
          return false;
        break;
      case Feature::kShaderStorageImageReadWithoutFormat:
        if (available_features.shaderStorageImageReadWithoutFormat == VK_FALSE)
          return false;
        break;
      case Feature::kShaderStorageImageWriteWithoutFormat:
        if (available_features.shaderStorageImageWriteWithoutFormat == VK_FALSE)
          return false;
        break;
      case Feature::kShaderUniformBufferArrayDynamicIndexing:
        if (available_features.shaderUniformBufferArrayDynamicIndexing ==
            VK_FALSE)
          return false;
        break;
      case Feature::kShaderSampledImageArrayDynamicIndexing:
        if (available_features.shaderSampledImageArrayDynamicIndexing ==
            VK_FALSE)
          return false;
        break;
      case Feature::kShaderStorageBufferArrayDynamicIndexing:
        if (available_features.shaderStorageBufferArrayDynamicIndexing ==
            VK_FALSE)
          return false;
        break;
      case Feature::kShaderStorageImageArrayDynamicIndexing:
        if (available_features.shaderStorageImageArrayDynamicIndexing ==
            VK_FALSE)
          return false;
        break;
      case Feature::kShaderClipDistance:
        if (available_features.shaderClipDistance == VK_FALSE)
          return false;
        break;
      case Feature::kShaderCullDistance:
        if (available_features.shaderCullDistance == VK_FALSE)
          return false;
        break;
      case Feature::kShaderFloat64:
        if (available_features.shaderFloat64 == VK_FALSE)
          return false;
        break;
      case Feature::kShaderInt64:
        if (available_features.shaderInt64 == VK_FALSE)
          return false;
        break;
      case Feature::kShaderInt16:
        if (available_features.shaderInt16 == VK_FALSE)
          return false;
        break;
      case Feature::kShaderResourceResidency:
        if (available_features.shaderResourceResidency == VK_FALSE)
          return false;
        break;
      case Feature::kShaderResourceMinLod:
        if (available_features.shaderResourceMinLod == VK_FALSE)
          return false;
        break;
      case Feature::kSparseBinding:
        if (available_features.sparseBinding == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidencyBuffer:
        if (available_features.sparseResidencyBuffer == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidencyImage2D:
        if (available_features.sparseResidencyImage2D == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidencyImage3D:
        if (available_features.sparseResidencyImage3D == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidency2Samples:
        if (available_features.sparseResidency2Samples == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidency4Samples:
        if (available_features.sparseResidency4Samples == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidency8Samples:
        if (available_features.sparseResidency8Samples == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidency16Samples:
        if (available_features.sparseResidency16Samples == VK_FALSE)
          return false;
        break;
      case Feature::kSparseResidencyAliased:
        if (available_features.sparseResidencyAliased == VK_FALSE)
          return false;
        break;
      case Feature::kVariableMultisampleRate:
        if (available_features.variableMultisampleRate == VK_FALSE)
          return false;
        break;
      case Feature::kInheritedQueries:
        if (available_features.inheritedQueries == VK_FALSE)
          return false;
        break;
      case Feature::kFramebuffer:
      case Feature::kDepthStencil:
      case Feature::kFenceTimeout:
      case Feature::kUnknown:
        break;
    }
  }

  return true;
}

}  // namespace

Device::Device() = default;
Device::Device(VkDevice device) : device_(device), destroy_device_(false) {}
Device::~Device() = default;

void Device::Shutdown() {
  if (destroy_device_) {
    vkDestroyDevice(device_, nullptr);
    vkDestroyInstance(instance_, nullptr);
  }
}

Result Device::Initialize(const std::vector<Feature>& required_features) {
  if (device_ == VK_NULL_HANDLE) {
    Result r = CreateInstance();
    if (!r.IsSuccess())
      return r;

    r = ChoosePhysicalDevice(required_features);
    if (!r.IsSuccess())
      return r;

    r = CreateDevice(required_features);
    if (!r.IsSuccess())
      return r;
  }

  if (queue_ == VK_NULL_HANDLE) {
    vkGetDeviceQueue(device_, queue_family_index_, 0, &queue_);
    if (queue_ == VK_NULL_HANDLE)
      return Result("Vulkan::Calling vkGetDeviceQueue Fail");
  }
  return {};
}

bool Device::ChooseQueueFamilyIndex(const VkPhysicalDevice& physical_device) {
  uint32_t count;
  std::vector<VkQueueFamilyProperties> properties;

  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, nullptr);
  properties.resize(count);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count,
                                           properties.data());

  for (uint32_t i = 0; i < count; ++i) {
    if (properties[i].queueFlags &
        (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) {
      queue_family_flags_ = properties[i].queueFlags;
      queue_family_index_ = i;
      return true;
    }
  }

  for (uint32_t i = 0; i < count; ++i) {
    if (properties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
      queue_family_flags_ = properties[i].queueFlags;
      queue_family_index_ = i;
      return true;
    }
  }

  return false;
}

Result Device::CreateInstance() {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

  VkInstanceCreateInfo instInfo = {};
  instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instInfo.pApplicationInfo = &appInfo;
  // TODO(jaebaek): Enable layers, extensions

  if (vkCreateInstance(&instInfo, nullptr, &instance_) != VK_SUCCESS)
    return Result("Vulkan::Calling vkCreateInstance Fail");

  return {};
}

Result Device::ChoosePhysicalDevice(
    const std::vector<Feature>& required_features) {
  uint32_t count;
  std::vector<VkPhysicalDevice> physical_devices;

  if (vkEnumeratePhysicalDevices(instance_, &count, nullptr) != VK_SUCCESS)
    return Result("Vulkan::Calling vkEnumeratePhysicalDevices Fail");
  physical_devices.resize(count);
  if (vkEnumeratePhysicalDevices(instance_, &count, physical_devices.data()) !=
      VK_SUCCESS)
    return Result("Vulkan::Calling vkEnumeratePhysicalDevices Fail");

  for (uint32_t i = 0; i < count; ++i) {
    VkPhysicalDeviceFeatures available_features = {};
    vkGetPhysicalDeviceFeatures(physical_devices[i], &available_features);

    if (!AreAllRequiredFeaturesSupported(available_features, required_features))
      continue;

    if (ChooseQueueFamilyIndex(physical_devices[i])) {
      physical_device_ = physical_devices[i];
      vkGetPhysicalDeviceMemoryProperties(physical_device_,
                                          &physical_memory_properties_);
      return {};
    }
  }

  return Result("Vulkan::No physical device supports Vulkan");
}

Result Device::CreateDevice(const std::vector<Feature>& required_features) {
  VkDeviceQueueCreateInfo queue_info;
  const float priorities[] = {1.0f};

  queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_info.queueFamilyIndex = queue_family_index_;
  queue_info.queueCount = 1;
  queue_info.pQueuePriorities = priorities;

  VkDeviceCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  info.pQueueCreateInfos = &queue_info;
  info.queueCreateInfoCount = 1;
  // TODO(jaebaek): Enable layers, extensions
  VkPhysicalDeviceFeatures requested_features =
      RequestedFeatures(required_features);
  info.pEnabledFeatures = &requested_features;

  if (vkCreateDevice(physical_device_, &info, nullptr, &device_) != VK_SUCCESS)
    return Result("Vulkan::Calling vkCreateDevice Fail");

  return {};
}

}  // namespace vulkan
}  // namespace amber
