#pragma once

#include <cstdint>

#include <SFML/System.hpp>

namespace cf
{

constexpr uint16_t UDP_MAGIC = 0x0b3a;

class UdpPrctl
{
      public:
	enum class Type {
		POSITION,
		VELOCITY,
		SPRITE,
		SPAWN,
		INPUT,
		TIME,
		UNKNOWN
	};

	struct udpHeader {
		uint32_t type;   // packet type
		uint32_t length; // packet payload length
		uint16_t magic;  // packet magic number
		uint16_t index;  // packet index
	} __attribute__((packed));

	struct udpPosition {
		uint32_t objectIndex;
		sf::Vector2f position;
	};

	struct udpVelocity {
		uint32_t objectIndex;
		sf::Vector2f speed;
		sf::Vector2f acceleration;
	};

	struct udpSprite {
		uint32_t objectIndex;
		sf::Vector2f offset;
		sf::Vector2f scale;
		float rotation;
	};

	enum class objType {
		PLAYER,
		WALL,
	};

	struct udpSpawnObject {
		int32_t type;
		uint32_t customIndex;
		// extra data depending on type
	};

	enum class inputType {

	};

	struct udpInput {
		int32_t type;
		// extra data depending on type
	};

	enum class timeType {
		REALTIME = 0,
		TIMESCALE,
	};

	struct udpTime {
		int32_t type;
		// extra data depending on type
	};

	enum class stateType {

	};

	struct udpSetState {
		int32_t type;
		uint32_t objectIndex;
		// extra data depending on type;
	};

	struct udpDestroy {
		uint32_t objectIndex;
	};

	UdpPrctl(Type type, uint32_t length, uint16_t index) noexcept;
	bool isCorrect() const noexcept;
	Type getType() const noexcept;
	uint32_t getLength() const noexcept;
	uint16_t getIndex() const noexcept;
	udpHeader &getNativeHandle() noexcept;
	const udpHeader &getNativeHandle() const noexcept;

      protected:
	udpHeader _header;
};
} // namespace cf