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
	Serializer() noexcept;
	Serializer(Serializer &other, size_t len) noexcept;
	Serializer(const UdpPrctl &header) noexcept;
	Serializer(const Serializer &packet) noexcept;
	Serializer(const Serializer &packet, TcpPrctl::Type type) noexcept;
	Serializer(const Serializer &packet, UdpPrctl::Type type, uint16_t index) noexcept;
	~Serializer() noexcept;
	Serializer splice(size_t len) noexcept;
	void clear() noexcept;
	void setHeader(TcpPrctl::Type type) noexcept;
	template <typename T> Serializer &operator>>=(T &object) noexcept
	{
		get(object);
		return *this;
	}
	template <typename T> Serializer &operator>>(T &object) noexcept
	{
		size_t size = get(object);
		shift(size);
		return *this;
	}
	template <typename T> Serializer &operator<<(const T &object) noexcept
	{
		set(object);
		return *this;
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

	size_t nativeSet(const void *data, size_t len) noexcept;
	template <typename T> size_t nativeSet(const T &obj) noexcept
	{
		return nativeSet(&obj, sizeof(obj));
	}
	template <typename T> void shift(const T &object) noexcept
	{
		shift(sizeof(object));
	}
	void shift(size_t from) noexcept;
	void dump() const noexcept;

      private:
	size_t get(UdpPrctl &header) const noexcept;
	size_t get(bool &value) const noexcept;
	size_t get(const Asset &asset) const noexcept;
	size_t get(std::string &str) const noexcept;
	size_t get(void *dest, size_t len) const noexcept;
	size_t get(size_t offset, void *dest, size_t len) const noexcept;
	size_t get(sf::Vector2f &v) const noexcept;
	size_t get(sfs::Sprite &sprite) const noexcept;
	size_t get(sfs::Velocity &velocity) const noexcept;
	size_t get(sf::Color &color) const noexcept;
	template <typename T> size_t get(size_t offset, T &dest) const noexcept
	{
		return get(offset, &dest, sizeof(dest));
	}
	template <typename T> size_t get(T &dest) const noexcept
	{
		return get(&dest, sizeof(dest));
	}
	size_t set(const Serializer &serializer) noexcept;
	size_t set(bool value) noexcept;
	size_t set(const std::string &str) noexcept;
	size_t set(const UdpPrctl &header) noexcept;
	size_t set(const TcpPrctl &header) noexcept;
	size_t set(const Asset &asset) noexcept;
	size_t set(const sf::Vector2f &v) noexcept;
	size_t set(const sfs::Sprite &sprite) noexcept;
	size_t set(const sfs::Velocity &velocity) noexcept;
	size_t set(const sf::Color &color) noexcept;
	template <typename T> size_t set(const std::vector<T> &vec)
	{
		size_t size = nativeSet(vec.size());
		for (auto &&i : vec)
			size += set(i);
		return size;
	}
	template <typename T> size_t set(const T &nativeObject) noexcept
	{
		return nativeSet(nativeObject);
	}
	int8_t *_data;
	size_t _size;
	size_t _alloc_size;
	int resizeForNewElement(size_t newElementSize) noexcept;
};
} // namespace cf
