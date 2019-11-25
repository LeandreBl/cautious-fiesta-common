#include "Udp.hpp"

namespace cf {

const char *toString(UdpPrctl::Type type) noexcept
{
	switch (type) {
	case UdpPrctl::Type::POSITION:
		return "Udp::Position";
	case UdpPrctl::Type::VELOCITY:
		return "Udp::Velocity";
	case UdpPrctl::Type::SPRITE:
		return "Udp::Sprite";
	case UdpPrctl::Type::SPAWN:
		return "Udp::Spawn";
	case UdpPrctl::Type::INPUT:
		return "Udp::Input";
	case UdpPrctl::Type::TIME:
		return "Udp::Time";
	case UdpPrctl::Type::STATE:
		return "Udp::State";
	case UdpPrctl::Type::DESTROY:
		return "Udp::Destroy";
	case UdpPrctl::Type::ATTACK:
		return "Udp::Attack";
	case UdpPrctl::Type::UNKNOWN:
		return "Udp::Unknown";
	case UdpPrctl::Type::ACK:
		return "Udp::Ack";
	default:
		return "<not handled>";
	}
}

const char *toString(UdpPrctl::inputType type) noexcept
{
	switch (type) {
	case UdpPrctl::inputType::UNKNOWN_KEY:
		return "Udp::inputType::UnknownKey";
	case UdpPrctl::inputType::ATTACK1:
		return "Udp::inputType::Attack1";
	case UdpPrctl::inputType::ATTACK2:
		return "Udp::inputType::Attack2";
	case UdpPrctl::inputType::UP:
		return "Udp::inputType::Up";
	case UdpPrctl::inputType::LEFT:
		return "Udp::inputType::Left";
	case UdpPrctl::inputType::DOWN:
		return "Udp::inputType::Down";
	case UdpPrctl::inputType::RIGHT:
		return "Udp::inputType::Right";
	default:
		return "<not handled>";
	}
}

const char *toString(UdpPrctl::inputAction action) noexcept
{
	switch (action) {
	case UdpPrctl::inputAction::PRESSED:
		return "Udp::inputAction::Pressed";
	case UdpPrctl::inputAction::RELEASED:
		return "Udp::inputAction::Released";
	default:
		return "<not handled>";
	}
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