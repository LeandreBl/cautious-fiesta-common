#pragma once

#include <cstdint>

namespace cf
{

constexpr uint32_t TCP_MAGIC = 0x0b3a4;

class TcpPrctl
{
      public:
	struct tcpHeader {
		uint32_t magic;  // packet magic number
		uint32_t type;   // packet type
		uint64_t length; // packet payload length
	};

	enum class Type {
		LOGIN = 0,
		LOGOUT,
		CREATE_GAMEROOM,
		DELETE_GAMEROOM,
		GET_GAMEROOMS_LIST,
		JOIN_GAMEROOM,
		LEAVE_GAMEROOM,
		GET_GAMEROOM_PLAYERS_LIST,
		SEND_MESSAGE,
		RECEIVE_MESSAGE,
		TOGGLE_READY,
		ASSETS_REQUIREMENT,
		ASSETS_SEND,
		GAME_STARTED,
		ACK, /* this should stay the last enum type */
	};

	TcpPrctl() noexcept = default;
	TcpPrctl(TcpPrctl::Type type, uint64_t length = 0) noexcept;
	~TcpPrctl() noexcept = default;
	uint64_t getLength() const noexcept;
	uint32_t getType() const noexcept;
	uint32_t getMagic() const noexcept;
	bool isCorrect() const noexcept;
	struct tcpHeader &getNativeHandle() noexcept;
	const struct tcpHeader &getNativeHandle() const noexcept;
	void display(bool recv = true) const noexcept;

      private:
	tcpHeader _header;
};
} // namespace cf
