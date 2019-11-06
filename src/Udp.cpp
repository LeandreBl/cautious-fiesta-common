#include "Udp.h"

namespace cf
{
UdpPrctl::UdpPrctl(UdpPrctl::Type type, uint32_t length,
		   uint16_t index) noexcept
{
	_header.type = static_cast<uint32_t>(type);
	_header.length = length;
	_header.magic = UDP_MAGIC;
	_header.index = index;
}

bool UdpPrctl::isCorrect() const noexcept
{
	return _header.magic == UDP_MAGIC
	       && _header.type
			  <= static_cast<uint32_t>(UdpPrctl::Type::UNKNOWN);
}

UdpPrctl::Type UdpPrctl::getType() const noexcept
{
	return static_cast<UdpPrctl::Type>(_header.type);
}

uint32_t UdpPrctl::getLength() const noexcept
{
	return _header.length;
}

uint16_t UdpPrctl::getIndex() const noexcept
{
	return _header.index;
}

UdpPrctl::udpHeader &UdpPrctl::getNativeHandle() noexcept
{
	return _header;
}

const UdpPrctl::udpHeader &UdpPrctl::getNativeHandle() const noexcept
{
	return _header;
}

} // namespace cf