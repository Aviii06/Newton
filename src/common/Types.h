#pragma once
#include <vector>
#include <memory>

template <class T>
using Vector = std::vector<T>;

// std::unique_ptr
template <class T>
using Ptr = std::unique_ptr<T>;
template <class T, typename... Args>
constexpr Ptr<T> MakePtr(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}
// std::shared_ptr
template <class T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> MakeRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
// std::weak_ptr
template <class T>
using Weak = std::weak_ptr<T>;

namespace Newton
{
	struct Vec2
	{
		float x, y;
	};

	struct Vec3
	{
		float x, y, z;
	};
}

