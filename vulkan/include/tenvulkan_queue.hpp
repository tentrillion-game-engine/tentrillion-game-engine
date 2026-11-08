#ifndef TENTRILLIONGAMEENGINE_TENVULKANQUEUE_HPP
#define TENTRILLIONGAMEENGINE_TENVULKANQUEUE_HPP

#include "tenvulkan_device.hpp"
class tenvulkan_queue {
  public:
	tenvulkan_queue(tenvulkan_device *tenvulkan_device_manager);

  private:
	tenvulkan_device *tenvulkan_device_manager;
};

#endif
