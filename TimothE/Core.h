#pragma once

#include <iostream>

#define TIM_LOG_ERROR(...) "[ERROR: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__
#define TIM_LOG_WARNING(...) "[WARNING: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__
#define TIM_LOG_LOG(...) "[LOG: " __FILE__ << "::" << __LINE__ << "]: " << __VA_ARGS__

