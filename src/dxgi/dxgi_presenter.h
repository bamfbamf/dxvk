#pragma once

#include <dxvk_device.h>
#include <dxvk_surface.h>
#include <dxvk_swapchain.h>

#include "../spirv/spirv_module.h"

namespace dxvk {
  
  /**
   * \brief DXGI presenter
   * 
   * Renders the back buffer from the
   * \ref DxgiSwapChain to the Vulkan
   * swap chain.
   */
  class DxgiPresenter : public RcObject {
    
  public:
    
    DxgiPresenter(
      const Rc<DxvkDevice>& device,
            HWND            window,
            UINT            bufferWidth,
            UINT            bufferHeight);
    
    ~DxgiPresenter();
    
    /**
     * \brief Initializes back buffer image
     * \param [in] image Back buffer image
     */
    void initBackBuffer(
      const Rc<DxvkImage>& image);
    
    /**
     * \brief Renders image to the screen
     * \param [in] view Source image view
     */
    void presentImage(
      const Rc<DxvkImageView>& view);
    
  private:
    
    enum BindingIds : uint32_t {
      Sampler = 0,
      Texture = 1,
    };
    
    Rc<DxvkDevice>      m_device;
    Rc<DxvkContext>     m_context;
    
    Rc<DxvkSurface>     m_surface;
    Rc<DxvkSwapchain>   m_swapchain;
    
    Rc<DxvkSemaphore>   m_acquireSync;
    Rc<DxvkSemaphore>   m_presentSync;
    
    Rc<DxvkSampler>     m_sampler;
    
    Rc<DxvkShader> createVertexShader();
    Rc<DxvkShader> createFragmentShader();
    
    Rc<DxvkBindingLayout> createBindingLayout();
    
    Rc<DxvkGraphicsPipeline> createPipeline();
    
  };
  
}
