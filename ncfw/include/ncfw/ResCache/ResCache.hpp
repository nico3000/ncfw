#pragma once
#include "ncfw/AppModule.hpp"
#include "ncfw/Logger.hpp"

#include <filesystem>

namespace ncfw {
class ResCache : public AppModule {
public:
  ResCache(const std::filesystem::path &p_resFile, const std::filesystem::path &p_backupPath);

private:
};
} // namespace ncfw