#include "Udp.h"

namespace cf {

static const char *STRINGS[] = {
	"Udp::Position", "Udp::Velocity", "Udp::Sprite",  "Udp::Spawn",
	"Udp::Input",    "Udp::Time",     "Udp::Unknown", "Udp::Ack",
};

std::ostream &operator<<(std::ostream &os, UdpPrctl::Type type) noexcept
{
	os << STRINGS[static_cast<int>(type)];
	return os;
}

UdpPrctl::UdpPrctl(UdpPrctl::Type type, uint32_t length, uint16_t index) noexcept
{
	_header.type = static_cast<uint32_t>(type);
	_header.length = length;
	_header.magic = UDP_MAGIC;
	_header.index = index;
}

UdpPrctl::UdpPrctl(const udpHeader &header) noexcept
	: _header(header)
{
}

bool UdpPrctl::isCorrect() const noexcept
{
	return _header.magic == UDP_MAGIC
	       && _header.type <= static_cast<uint32_t>(UdpPrctl::Type::UNKNOWN);
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