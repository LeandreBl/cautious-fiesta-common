#pragma once

#include <cstdint>

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace cf
{

constexpr uint16_t UDP_MAGIC = 0x0b3a;

class UdpPrctl
{
public:
	enum class Type
	{
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

	struct udpHeader
	{
		uint32_t type;   // packet type
		uint32_t length; // packet payload length
		uint16_t magic;  // packet magic number
		uint16_t index;  // packet index
	} __attribute__((packed));

	struct udpPosition
	{
		uint64_t objectId;
		float posx;
		float posy;
	} __attribute__((packed));

	struct udpVelocity
	{
		uint64_t objectId;
		float speedx;
		float speedy;
		float accelerationx;
		float accelerationy;
	} __attribute__((packed));

	struct udpSprite
	{
		uint64_t objectId;
		float offsetx;
		float offsety;
		float scalex;
		float scaley;
		float rotation;
	} __attribute__((packed));

	enum class weaponType
	{
		NONE = -1,
		DAGGER = 0,
		GUN,
		SPEAR,
		SWORD,
	};

	struct udpPlayerObject
	{
		size_t nameLen;
		char *name;
		float life;
		float speed;
		float attack;
		float attackSpeed;
		float armor;
		uint8_t color_r;
		uint8_t color_g;
		uint8_t color_b;
		uint8_t color_a;
		size_t spriteLen;
		char *spriteName;
		int32_t weaponType;
	} __attribute__((packed));

	struct udpEnnemyObject
	{
		size_t nameLen;
		char *name;
		size_t spriteLen;
		char *spriteName;
	} __attribute__((packed));

	struct udpWeaponObject
	{
		uint64_t playerId;
		int32_t weaponType;
		uint64_t spriteNameLen;
		char *spriteName;
	} __attribute__((packed));

	enum class spawnType
	{
		PLAYER = 0,
		OBSTACLE,
		WEAPON,
		PROJECTILE,
		ENNEMY,
	};

	struct udpProjectileObject
	{
		float posx;
		float posy;
		float angle;
		float speed;
		uint8_t color_r;
		uint8_t color_g;
		uint8_t color_b;
		uint8_t color_a;
		uint64_t spriteNameLen;
		char *spriteName;
	} __attribute__((packed));

	struct udpSpawnObject
	{
		int32_t type;
		uint64_t objectId;
		// extra data depending on type
	} __attribute__((packed));

	struct inputAttack
	{
		int32_t vx;
		int32_t vy;
	};

	enum class inputType
	{
		UNKNOWN_KEY = -1,
		ATTACK1 = 0,
		ATTACK2,
		UP,
		LEFT,
		DOWN,
		RIGHT,
	};
	enum class inputAction
	{
		PRESSED = 0,
		RELEASED
	};

	struct udpInput
	{
		int32_t action;
		int32_t type;
		// extra data depending on type and/or action
	} __attribute__((packed));

	enum class timeType
	{
		REALTIME = 0,
		TIMESCALE,
	};

	struct udpTime
	{
		int32_t type;
		// extra data depending on type
	} __attribute__((packed));

	enum class stateType
	{

	};

	struct udpSetState
	{
		int32_t type;
		uint64_t objectId;
		// extra data depending on type;
	} __attribute__((packed));

	enum class destroyType
	{
		GAMEOBJECT = 0,
		COMPONENT,
	};

	struct udpDestroy
	{
		int32_t type;
		uint64_t objectId;
		// optionnal uint64_t component id
	} __attribute__((packed));

	enum class attackType
	{
		DEFAULT = 0,
		SPECIAL
	};

	struct udpAttack
	{
		int32_t attackType;
		float angle;
	} __attribute__((packed));

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
