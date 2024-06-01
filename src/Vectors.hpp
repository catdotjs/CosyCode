#pragma once

#include <SFML/System/Vector2.hpp>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
namespace cc {
template <typename T> struct Vector2 {
  T x;
  T y;
  Vector2(T x = 0, T y = 0) : x(x), y(y){};
  Vector2(sf::Vector2u vec) : x(vec.x), y(vec.y){};

  operator sf::Vector2<int>() const { return Vector2((T)x, (T)y); }
  operator sf::Vector2u() const { return Vector2((T)x, (T)y); }
  operator sf::Vector2f() const { return Vector2((T)x, (T)y); }
  operator b2Vec2() const { return Vector2((T)x, (T)y); }
};
} // namespace cc
