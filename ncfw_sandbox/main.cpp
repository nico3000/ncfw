#include "ncfw/ncfw.hpp"

int main() {
  ncfw::g_logger = std::make_unique<ncfw::Logger>("./ncfw.log");
  NCFW_LOG("Hello {}", "world");
  NCFW_INFO("Hello {}", "world");
  NCFW_WARN("Hello {}", "world");
  NCFW_ERROR("Hello {}", "world");
  NCFW_FATAL("Hello {}", "world");
  // NCFW_ASSERT(false, "Hello {}", "world");
  return 0;
}