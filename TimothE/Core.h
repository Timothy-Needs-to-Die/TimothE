#pragma once

#include <iostream>

#define TIM_LOG_ERROR(...) std::cout << "[ERROR: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__ << std::endl
#define TIM_LOG_WARNING(...) std::cout << "[WARNING: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__ << std::endl
#define TIM_LOG_LOG(...) std::cout << "[LOG: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__ << std::endl