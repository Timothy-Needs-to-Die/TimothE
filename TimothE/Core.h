#pragma once

#include <iostream>

#define DEV_MODE 1

#define TIM_LOG_ERROR(...) if(DEV_MODE) std::cout << "[ERROR: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__ << std::endl
#define TIM_LOG_WARNING(...) if(DEV_MODE) std::cout << "[WARNING: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__ << std::endl
#define TIM_LOG_LOG(...) if(DEV_MODE) std::cout << "[LOG: " << __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__ << std::endl