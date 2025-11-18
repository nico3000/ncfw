#pragma once
#include "ncfw/AppModule.hpp"
#include "ncfw/ResCache/Resource.hpp"
#include "ncfw/ResCache/ResourceSource.hpp"

#include <filesystem>
#include <list>
#include <memory>

namespace ncfw {
class ResCache : public AppModule {
public:
  ResCache() {}

  void pushSource(std::unique_ptr<ResourceSource> p_source) { m_sources.emplace_back(std::move(p_source)); }
  std::shared_ptr<Resource> getResource(const std::filesystem::path &p_resourcePath);

private:
  std::vector<std::unique_ptr<ResourceSource>> m_sources;
  std::mutex m_mtx;
  std::unordered_map<std::filesystem::path, std::weak_ptr<Resource>> m_resources;
  std::list<std::shared_ptr<Resource>> m_lru;
};
} // namespace ncfw