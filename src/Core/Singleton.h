#pragma once

// TODO: Make Input and Window singletons
// Example: Input : public Singleton<Input>

template<typename T>
class Singleton
{
public:
	static constexpr inline T& Instance()
	{
		static T s_instance;
		return s_instance;
	}
};