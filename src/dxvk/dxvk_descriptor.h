#pragma once

#include "dxvk_include.h"

namespace dxvk {
  
  /**
   * \brief Descriptor info
   * 
   * Stores information that is required to
   * update a single resource descriptor.
   */
  struct DxvkDescriptorInfo {
    VkDescriptorImageInfo  image       = { VK_NULL_HANDLE, VK_NULL_HANDLE, VK_IMAGE_LAYOUT_UNDEFINED };
    VkDescriptorBufferInfo buffer      = { VK_NULL_HANDLE, 0, 0 };
    VkBufferView           texelBuffer = VK_NULL_HANDLE;
  };
  
  
  /**
   * \brief Descriptor set allocator
   * 
   * Creates descriptor pools on demand and
   * allocates descriptor sets from those pools.
   */
  class DxvkDescriptorAlloc {
    
  public:
    
    DxvkDescriptorAlloc(
      const Rc<vk::DeviceFn>& vkd);
    ~DxvkDescriptorAlloc();
    
    DxvkDescriptorAlloc             (const DxvkDescriptorAlloc&) = delete;
    DxvkDescriptorAlloc& operator = (const DxvkDescriptorAlloc&) = delete;
    
    /**
     * \brief Allocates a descriptor set
     * 
     * \param [in] layout Descriptor set layout
     * \returns The descriptor set
     */
    VkDescriptorSet alloc(
      VkDescriptorSetLayout layout);
    
    /**
     * \brief Resets descriptor set allocator
     * 
     * Destroys all descriptor sets and
     * resets the Vulkan descriptor pools.
     */
    void reset();
    
  private:
    
    Rc<vk::DeviceFn> m_vkd;
    
    std::vector<VkDescriptorPool> m_pools;
    size_t                        m_poolId = 0;
    
    VkDescriptorPool createDescriptorPool();
    
    VkDescriptorSet allocFrom(
      VkDescriptorPool      pool,
      VkDescriptorSetLayout layout) const;
    
  };
  
}