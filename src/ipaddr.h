//
// File: ipaddr.h
//

#ifndef _IPADDR_H_GUARD
#define _IPADDR_H_GUARD

#include <array>
#include <string>

struct IPAddr {
  // Объявим внутри класса псевдонимы классов, которые понадобятся
  // для хранения и получения данных. Для внутреннего хранения выбран
  // тип uint8_t, т.к. октет IPv4 адреса принимает значения от 0 до 255,
  // поэтому весь адрес может храниться в четырёх байтах, что особенно удобно
  // при выравнивании данных.
  using internal_type = uint8_t;
  using external_type = int;
  // Для хранения данных внутри класса будем использовать обёртку для массивов.
  using container_type = std::array<internal_type, 4>;

  // Конструктор адреса из строки
  explicit IPAddr(const std::string &);
  constexpr IPAddr(const IPAddr &other) = default;
  IPAddr &operator=(const IPAddr &other) = default;
  IPAddr(IPAddr &&other) : _addr(std::move(other._addr)) {}

  // Получение строкового представления адреса
  std::string str() const;

  bool operator<(const IPAddr &other) const;
  bool operator>(const IPAddr &other) const { return !(*this <= other); };
  bool operator<=(const IPAddr &other) const { return *this < other || *this == other; };
  bool operator>=(const IPAddr &other) const { return !(*this < other); };

  bool operator==(const IPAddr &other) const;
  bool operator!=(const IPAddr &other) const { return !(*this == other); };

  internal_type &operator[](std::size_t idx) { return _addr[idx]; };
  external_type operator[](std::size_t idx) const { return _addr[idx]; };

  constexpr container_type::size_type size() const { return _addr.size(); }

private:
  container_type _addr;
};

#endif // _IPADDR_H_GUARD
