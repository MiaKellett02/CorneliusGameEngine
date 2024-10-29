#pragma once
//Library includes.
#include <iostream>
#include <assert.h>
#include <string>

namespace CorneliusEngine {


	//Function definitions.
	inline void Log(const std::string& a_message)
	{
#ifdef _DEBUG
		//Only log messages in debug mode.
		std::cout << "MESSAGE - " << a_message << std::endl;
#else
		//Do nothing in release.
#endif
	}

	inline void LogWarning(const std::string& a_message)
	{
#ifdef _DEBUG
		//Only log warnings in debug mode.
		std::cout << "WARNING - " << a_message << std::endl;
#else
		//Do nothing in release.
#endif
	}

	inline void LogError(const std::string& a_message)
	{
#ifdef _DEBUG
		//Only log errors in debug mode.
		std::cout << "ERROR - " << a_message << std::endl;
		bool error = true;
		assert(error == false); // Trigger an assert so error stops execution.
#else
		//Do nothing in release.
#endif

	}

}