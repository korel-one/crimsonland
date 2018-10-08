#pragma once

#if defined(FRAMEWORK_PROJECT)
#define FRAMEWORK_API __declspec(dllexport)
#else
#define FRAMEWORK_API __declspec(dllimport)
#endif