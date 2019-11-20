#pragma once

#include <cstdint>

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace cf {

constexpr uint16_t UDP_MAGIC = 0x0b3a;

class UdpPrctl {
      public:
	enum class Type {
		POSITION,
		VELOCITY,
		SPRITE,
		SPAWN,
		INPUT,
		TIME,
		STATE,
		DESTROY,
		ATTACK,
		UNKNOWN,
		ACK /* this should stay last */
	};

	struct udpHeader {
		uint32_t type;   // packet type
		uint32_t length; // packet payload length
		uint16_t magic;  // packet magic number
		uint16_t index;  // packet index
	} __attribute__((packed));

	struct udpPosition {
		uint64_t objectId;
		sf::Vector2f position;
	};

	struct udpVelocity {
		uint64_t objectId;
		sf::Vector2f speed;
		sf::Vector2f acceleration;
	};

	struct udpSprite {
		uint64_t objectId;
		sf::Vector2f offset;
		sf::Vector2f scale;
		float rotation;
	};

	enum class weaponType {
		NONE = -1,
		DAGGER = 0,
		GUN,
		SPEAR,
		SWORD,
	};

	struct udpPlayerObject {
		size_t nameLen;
		char *name;
		float life;
		float speed;
		float attack;
		float attackSpeed;
		float armor;
		sf::Color color;
		size_t spriteLen;
		char *spriteName;
		int32_t weaponType;
	};

	enum class objType {
		PLAYER = 0,
		WALL,
	};

	struct udpSpawnObject {
		int32_t type;
		uint64_t objectId;
		// extra data depending on type
	};

	enum class inputType {
		UNKNOWN_KEY = -1,
		ATTACK1 = 0,
		ATTACK2,
		UP,
		LEFT,
		DOWN,
		RIGHT,
	};
	enum class inputAction { PRESSED = 0, RELEASED };

	struct udpInput {
		int32_t action;
		int32_t type;
		// extra data depending on type and/or action
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
		uint64_t objectId;
		// extra data depending on type;
	};

	struct udpDestroy {
		uint64_t objectId;
	};

	enum class attackType { DEFAULT = 0, SPECIAL };

	struct udpAttack {
		int32_t attackType;
	};

	UdpPrctl(Type type = Type::UNKNOWN, uint32_t length = 0, uint16_t index = 0) noexcept;
	UdpPrctl(const udpHeader &header) noexcept;
	bool isCorrect() const noexcept;
	Type getType() const noexcept;
	uint32_t getLength() const noexcept;
	uint16_t getIndex() const noexcept;
	udpHeader &getNativeHandle() noexcept;
	const udpHeader &getNativeHandle() const noexcept;

      protected:
	udpHeader _header;
};

const char *toString(UdpPrctl::inputType type) noexcept;
const char *toString(UdpPrctl::inputAction action) noexcept;
const char *toString(UdpPrctl::Type type) noexcept;

} // namespace cf
