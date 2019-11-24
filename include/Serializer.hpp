#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include <BasicShape.hpp>
#include <Velocity.hpp>

#include "Asset.hpp"
#include "Tcp.hpp"
#include "Udp.hpp"

namespace cf {
class Serializer {
      public:
	Serializer(Serializer &other, size_t len) noexcept;
	Serializer() noexcept;
	Serializer(UdpPrctl &header) noexcept;
	Serializer(const Serializer &packet) noexcept;
	Serializer(const Serializer &packet, TcpPrctl::Type type) noexcept;
	Serializer(const Serializer &packet, UdpPrctl::Type type, uint16_t index) noexcept;
	~Serializer() noexcept;
	Serializer splice(size_t len) noexcept;
	void clear() noexcept;
	void setHeader(TcpPrctl::Type type) noexcept;
	template <typename T> Serializer &operator<<(const T &object) noexcept
	{
		set(object);
		return *this;
	}
	bool set(const std::string &str) noexcept;
	bool set(const TcpPrctl &header) noexcept;
	bool set(const Asset &asset) noexcept;
	bool set(const sf::Vector2f &v) noexcept;
	bool set(const sfs::Sprite &sprite) noexcept;
	bool set(const sfs::Velocity &velocity) noexcept;
	bool set(const sf::Color &color) noexcept;
	template <typename T> bool set(const std::vector<T> &vec)
	{
		if (!nativeSet(vec.size()))
			return false;
		for (auto &&i : vec)
			if (!set(i))
				return false;
		return true;
	}
	template <typename T> bool set(const T &nativeObject) noexcept
	{
		return nativeSet(nativeObject);
	}
	template <typename T> Serializer &operator>>(T &object) noexcept
	{
		get(object);
		return *this;
	}
	bool get(const Asset &asset) noexcept;
	bool get(std::string &str) noexcept;
	bool get(void *dest, size_t len) noexcept;
	bool get(sf::Vector2f &v) noexcept;
	bool get(sfs::Sprite &sprite) noexcept;
	bool get(sfs::Velocity &velocity) noexcept;
	bool get(sf::Color &color) noexcept;
	template <typename T> bool get(T &dest) noexcept
	{
		return get(&dest, sizeof(dest));
	}
	void *getNativeHandle() const noexcept;
	bool forceSize(size_t newSize) noexcept;
	template <typename T> bool forceSetFirst(const T &obj)
	{
		if (resizeForNewElement(sizeof(obj)) == -1)
			return false;
		std::memmove(_data + sizeof(obj), _data, _size);
		std::memcpy(_data, &obj, sizeof(obj));
		_size += sizeof(obj);
		return true;
	}
	int reserve(uint64_t size) noexcept;
	size_t getSize() const noexcept;

	bool nativeSet(const void *data, size_t len) noexcept
	{
		if (resizeForNewElement(len) == -1)
			return false;
		std::memcpy(_data + _size, data, len);
		_size += len;
		return true;
	}
	template <typename T> bool nativeSet(const T &obj) noexcept
	{
		return nativeSet(&obj, sizeof(obj));
	}
	void shift(size_t from) noexcept;

      private:
	int8_t *_data;
	size_t _size;
	size_t _alloc_size;
	int resizeForNewElement(size_t newElementSize) noexcept;
};
} // namespace cf
