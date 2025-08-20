#pragma once
#include <SFML/Network.hpp>
#include <cstdint>
#include <vector>

enum class PacketType : std::uint8_t {
    Join      = 1,
    AssignId  = 2,
    Input     = 3,
    State     = 4
};

struct PlayerState {
    std::uint32_t id{};
    float x{};
    float y{};
};

// ---- sf::Packet helpers ----
inline sf::Packet& operator<<(sf::Packet& p, const PacketType& t) {
    return p << static_cast<std::uint8_t>(t);
}
inline sf::Packet& operator>>(sf::Packet& p, PacketType& t) {
    std::uint8_t u{}; p >> u; t = static_cast<PacketType>(u); return p;
}

inline sf::Packet& operator<<(sf::Packet& p, const PlayerState& s) {
    return p << s.id << s.x << s.y;
}
inline sf::Packet& operator>>(sf::Packet& p, PlayerState& s) {
    return p >> s.id >> s.x >> s.y;
}
