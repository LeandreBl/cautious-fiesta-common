#include "Tcp.hpp"
#include "Trace.hpp"
#include "colors.h"

namespace cf
{
const char *pktTypeToString[] = {
	"Login",
	"Logout",
	"Create GameRoom",
	"Delete GameRoom",
	"Get GameRooms List",
	"Join GameRoom",
	"Leave GameRoom",
	"Get GameRoom Players List",
	"Send Message",
	"Receive Message",
	"Toggle Ready",
	"Assets requirement",
	"Assets Loader",
	"Game Started",
	"Ack",
};

TcpPrctl::TcpPrctl(TcpPrctl::Type type, uint64_t length) noexcept
{
	_header.magic = TCP_MAGIC;
	_header.type = static_cast<uint32_t>(type);
	_header.length = length;
}

uint64_t TcpPrctl::getLength() const noexcept
{
	return _header.length;
}

uint32_t TcpPrctl::getType() const noexcept
{
	return _header.type;
}

uint32_t TcpPrctl::getMagic() const noexcept
{
	return _header.magic;
}

bool TcpPrctl::isCorrect() const noexcept
{
	return _header.magic == TCP_MAGIC
	       && _header.type <= static_cast<uint32_t>(TcpPrctl::Type::ACK);
}

TcpPrctl::tcpHeader &TcpPrctl::getNativeHandle() noexcept
{
	return _header;
}

const TcpPrctl::tcpHeader &TcpPrctl::getNativeHandle() const noexcept
{
	return _header;
}

void TcpPrctl::display(bool rcv) const noexcept
{
	trace(isCorrect(),
	      "%c-%sTcpPacket%s: {%smagic%s: %s0x%x%s, %slength%s: %s% -3lu%s, %stype%s: \"%s%s%s\"}\n",
	      (rcv == true) ? '<' : '>', MAGENTA, RESET, YELLOW, RESET, CYAN,
	      _header.magic, RESET, YELLOW, RESET, CYAN, _header.length, RESET,
	      YELLOW, RESET, CYAN, cf::pktTypeToString[_header.type], RESET);
}
} // namespace cf