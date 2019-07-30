#pragma once
#include <SFML/System/Vector2.hpp>

//vectormath
namespace sfm {

	template <typename T>
	float length(const sf::Vector2<T>& a) {
		return sqrtf(a.x*a.x + a.y*a.y);
	}

	template <typename T>
	float squaredLength(const sf::Vector2<T>& a) {
		return a.x*a.x + a.y*a.y;
	}

	template <typename T>
	float dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
		return a.x*b.x + a.y*b.y;
	}
}
