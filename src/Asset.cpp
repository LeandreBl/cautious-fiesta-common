#include <ios>
#include <fstream>

#include "Asset.hpp"
#include "Trace.hpp"

#include "colors.h"

namespace cf
{
Asset::Asset(uint64_t filesize, const std::string &filename)
    : _filesize(filesize), _chksum(0), _filename(filename)
{
	std::ifstream file(_filename, std::ios::binary);
	char buffer[512];

	if (!file.is_open()) {
		trace(false, "%sAsset%s: \"%s\" could not be opened\n", BLACK,
		      RESET, filename.c_str());
		return;
	}
	uint64_t size = 0;
	while (size < filesize) {
		std::streamsize rd = file.readsome(buffer, sizeof(buffer));
		size += rd;
		for (std::streamsize i = 0; i < rd; ++i)
			_chksum ^= buffer[i] ^ 0xff;
	}
	file.close();
}

uint32_t Asset::getChksum() const noexcept
{
	return _chksum;
}

uint64_t Asset::getFileSize() const noexcept
{
	return _filesize;
}

const std::string &Asset::getFileName() const noexcept
{
	return _filename;
}

uint32_t Asset::computeChksum(const std::string &filename) const noexcept
{
	std::ifstream file;
	char buffer[4096];
	uint64_t chk = 0;

	file.open(filename);
	if (!file.is_open())
		return 0;
	std::streamsize rd;
	do {
		rd = file.readsome(buffer, sizeof(buffer));
		for (std::streamsize i = 0; i < rd; ++i)
			chk += ~buffer[i] & 0xF0F0F0F0F;
	} while (rd == sizeof(buffer));
	return chk;
}

} // namespace cf