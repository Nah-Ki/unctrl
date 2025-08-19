#pragma once
#include <SFML/Network.hpp>

enum class PacketType {
    HELLO,
    POSITION
};

struct PositionPacket {
    float x, y;
};

