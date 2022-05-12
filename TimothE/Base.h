#pragma once

#include "pch.h"

template<typename T, typename ... Args>
constexpr std::shared_ptr<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}