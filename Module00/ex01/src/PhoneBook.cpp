#include <iostream>
#include <string>

int main(int argc, char **argv) {
	std::string message;
	if (argc == 1)
		message = "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	if (argc > 1) {
		for (int i = 1; i < argc; ++i)
			message += (std::string)argv[i];
		message += "\n";
		for (std::size_t i = 0; i < message.size(); ++i)
		message[i] = std::toupper(message[i]);	
	}
	std::cout << message;
}