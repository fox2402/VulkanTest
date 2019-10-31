#include "VulkanBaseContext.h"

#include<iostream>


int main() {
	VulkanBaseContext app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}