#include "ncfw/ResCache/FileSystemSource.hpp"
#include "ncfw/App.hpp"
#include "ncfw/ResCache/Resource.hpp"

#include <fstream>
#include <memory>

namespace ncfw {
FileSystemSource::FileSystemSource(const std::filesystem::path &p_root) : m_root(p_root) {}

std::optional<size_t> FileSystemSource::tryGetResourceByteSize(const std::filesystem::path &p_resourcePath) {
  const std::filesystem::path path = m_root / p_resourcePath;
  std::error_code ec;
  if (std::filesystem::is_regular_file(path, ec)) {
    size_t byteSize = std::filesystem::file_size(path);
    if (!ec) {
      return byteSize;
    }
  }
  return std::nullopt;
}

void FileSystemSource::load(const std::filesystem::path &p_resourcePath, uint8_t *p_dst, size_t p_dstByteSize) {
  const std::filesystem::path path = m_root / p_resourcePath;
  std::ifstream in(path, std::ios::binary);
  NCFW_THROW_UNLESS(in, "Failed to open {} for reading.", path.string());
  in.seekg(0, std::ios::end);
  size_t byteSize = in.tellg();
  NCFW_THROW_UNLESS(p_dstByteSize <= p_dstByteSize, "Insufficient resource dst data size. Needed: {}, given: {}",
                    byteSize, p_dstByteSize);
  in.seekg(0);
  in.read(reinterpret_cast<char *>(p_dst), byteSize);
  NCFW_THROW_UNLESS(in, "Failed to read {} bytes of data from {}.", byteSize, path.string());
}
} // namespace ncfw