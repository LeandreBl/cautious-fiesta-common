#include "Udp.hpp"

namespace cf {

static const char *TYPE_STRINGS[] = {
	"Udp::Position", "Udp::Velocity", "Udp::Sprite", "Udp::Spawn",   "Udp::Input", "Udp::Time",
	"Udp::State",    "Udp::Destroy",  "Udp::Attack", "Udp::Unknown", "Udp::Ack",
};

static const char *INPUT_TYPES_STRINGS[] = {
	"Input::UnknownKey", "Attack1", "Attack2", "Up", "Left", "Down", "Right"};

static const char *INPUT_ACTION_STRINGS[] = {"Pressed", "Released"};

const char *toString(UdpPrctl::Type type) noexcept
{
	return TYPE_STRINGS[static_cast<int>(type)];
}

const char *toString(UdpPrctl::inputType type) noexcept
{
	return INPUT_TYPES_STRINGS[static_cast<int>(type) + 1];
}

const char *toString(UdpPrctl::inputAction action) noexcept
{
	return INPUT_ACTION_STRINGS[static_cast<int>(action)];
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
	       && _header.type <= static_cast<uint32_t>(UdpPrctl::Type::ACK);
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