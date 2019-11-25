#include <cstring>
#include <iostream>

#include "Serializer.hpp"

namespace cf {
Serializer::Serializer(Serializer &other, size_t len) noexcept
	: Serializer()
{
	nativeSet(other.getNativeHandle(), len);
	other.shift(len);
}
Serializer::Serializer() noexcept
	: _data(nullptr)
	, _size(0)
	, _alloc_size(0)
{
}

Serializer::~Serializer() noexcept
{
	delete[] _data;
}

Serializer::Serializer(UdpPrctl &header) noexcept
	: Serializer()
{
	nativeSet(header);
}

Serializer::Serializer(const Serializer &packet, TcpPrctl::Type type) noexcept
	: Serializer()
{
	TcpPrctl header(type, packet._size);
	nativeSet(header);
	nativeSet(packet._data, packet._size);
}

Serializer::Serializer(const Serializer &packet, enum UdpPrctl::Type type, uint16_t index) noexcept
	: Serializer()
{
	UdpPrctl header(type, packet._size, index);
	nativeSet(header.getNativeHandle());
	nativeSet(packet._data, packet._size);
}

Serializer::Serializer(const Serializer &packet) noexcept
	: Serializer()
{
	nativeSet(packet._data, packet._size);
}

void Serializer::setHeader(TcpPrctl::Type type) noexcept
{
	TcpPrctl header(type, _size);
	header.display(false);
	forceSetFirst(header);
}

size_t Serializer::get(UdpPrctl &header) const noexcept
{
	auto &p = header.getNativeHandle();

	return get(p);
}

void Serializer::shift(size_t from) noexcept
{
	std::memmove(_data, _data + from, _size - from);
	_size -= from;
}

Serializer Serializer::splice(size_t len) noexcept
{
	return Serializer(*this, len);
}

void Serializer::clear() noexcept
{
	_size = 0;
}

int Serializer::resizeForNewElement(size_t newElementSize) noexcept
{
	if (_alloc_size - _size >= newElementSize)
		return 0;
	size_t newAllocSize = _size + newElementSize;
	int8_t *newBuffer = new int8_t[newAllocSize];
	if (newBuffer == nullptr)
		return -1;
	std::memcpy(newBuffer, _data, _size);
	_alloc_size = newAllocSize;
	delete[] _data;
	_data = newBuffer;
	return 0;
}

size_t Serializer::nativeSet(const void *data, size_t len) noexcept
{
	if (resizeForNewElement(len) == -1)
		return false;
	std::memcpy(_data + _size, data, len);
	_size += len;
	return len;
}

size_t Serializer::set(const std::string &str) noexcept
{
	uint64_t len = (uint64_t)str.length();

	return nativeSet(len) + nativeSet(str.c_str(), len);
}

size_t Serializer::set(const Asset &asset) noexcept
{
	std::ifstream file(asset.getFileName(), std::ios::binary);
	size_t rsize = 0;

	if (!file.is_open())
		return 0;
	rsize = nativeSet(asset.getFileSize()) + set(asset.getFileName())
		+ nativeSet(asset.getChksum());
	if (reserve(asset.getFileSize()) != 0)
		return false;
	for (uint64_t size = 0; size < asset.getFileSize(); ++size) {
		char buffer[512];
		std::streamsize rd;
		rd = file.readsome(buffer, sizeof(buffer));
		if (rd <= 0)
			return rsize;
		rsize += nativeSet(buffer, rd);
		size += rd;
	}
	file.close();
	return rsize;
}

size_t Serializer::set(const UdpPrctl &header) noexcept
{
	const auto &data = header.getNativeHandle();

	return nativeSet(data);
}

size_t Serializer::set(const TcpPrctl &header) noexcept
{
	const auto &data = header.getNativeHandle();

	return nativeSet(data);
}

size_t Serializer::set(const sf::Color &color) noexcept
{
	return nativeSet(color.r) + nativeSet(color.g) + nativeSet(color.b) + nativeSet(color.a);
}

size_t Serializer::get(sf::Color &color) const noexcept
{
	size_t size;

	size = get(color.r);
	size += get(size, color.g);
	size += get(size, color.b);
	size += get(size, color.a);
	return size;
}

size_t Serializer::get(std::string &str) const noexcept
{
	size_t len;
	size_t size;

	size = get(len);
	str.assign((char *)_data + size, len);
	size += len;
	return size;
}

size_t Serializer::get(size_t offset, void *dest, size_t len) const noexcept
{
	if (_size < len + offset)
		return 0;
	std::memcpy(dest, _data + offset, len);
	return len;
}

size_t Serializer::get(void *dest, size_t len) const noexcept
{
	return get(0, dest, len);
}

void *Serializer::getNativeHandle() const noexcept
{
	return _data;
}

int Serializer::reserve(uint64_t size) noexcept
{
	return resizeForNewElement(size);
}

bool Serializer::forceSize(size_t newSize) noexcept
{
	if (newSize > _alloc_size)
		return false;
	_size = newSize;
	return true;
}

size_t Serializer::getSize() const noexcept
{
	return _size;
}

size_t Serializer::set(bool value) noexcept
{
	uint8_t b = value;
	return set(b);
}

size_t Serializer::set(const sf::Vector2f &v) noexcept
{
	return nativeSet(v.x) + nativeSet(v.y);
}

size_t Serializer::set(const sfs::Sprite &sprite) noexcept
{
	return set(sprite.getOffset()) + set(sprite.getScale()) + nativeSet(sprite.getRotation());
}

size_t Serializer::get(bool &value) const noexcept
{
	uint8_t b;
	auto ret = get(b);
	value = b;
	return ret;
}

size_t Serializer::get(sf::Vector2f &v) const noexcept
{
	size_t size = get(v.x);

	size += get(size, v.y);
	return size;
}

size_t Serializer::get(sfs::Sprite &sprite) const noexcept
{
	float rotation;
	sf::Vector2f scale;
	sf::Vector2f offset;
	size_t size = get(offset);

	size += get(size, scale);
	size += get(size, rotation);

	sprite.setOffset(offset);
	sprite.setScale(scale);
	sprite.setRotation(rotation);
	return size;
}

size_t Serializer::set(const sfs::Velocity &velocity) noexcept
{
	return set(velocity.speed) + set(velocity.acceleration);
}

size_t Serializer::get(sfs::Velocity &velocity) const noexcept
{
	sf::Vector2f speed;
	sf::Vector2f acceleration;
	size_t size;

	size = get(speed);
	size += get(size, acceleration);
	velocity.acceleration = acceleration;
	velocity.speed = speed;
	return size;
}

} // namespace cf