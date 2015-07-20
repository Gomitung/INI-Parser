#include "../INI Parser/INIFile.h"
#include <string>
#include <iostream>
#include <algorithm>

int main(int argc, char** argv) {
	if (argc == 1 || argc > 2) {
		std::cout << "USAGE: " << argv[0] << " <INI File>" << std::endl;
	}
	else {
		cINIFile file;
		try {
			file = cINIFile(argv[1]);
		}
		catch (std::string error) {
			std::cout << error << std::endl;
			return 0;
		}
		std::cout << argv[1] << " loaded." << std::endl;
		std::cout << "Type \"help\" for the list of commands" << std::endl;
		std::string input;
		while (std::getline(std::cin, input)) {
			if (input == "exit" || input == "close") {
				break;
			}
			else if (input == "help" || input == "list") {
				std::cout << "Commands:" << std::endl;
				std::cout << "set <section> <key> <value> - Sets the value of a command" << std::endl;
				std::cout << "get <section> <key> - Returns the value of a command" << std::endl;
				std::cout << "print [<section>]- Returns the names of the sections/Outputs a section" << std::endl;
				std::cout << "exit - Closes the software" << std::endl;
				std::cout << "close - Closes the software" << std::endl;
			}
			else if (input.substr(0, 3) == "set") {
				if (std::count(input.begin(), input.end(), ' ') != 3) {
					std::cout << "USAGE: set <section> <key> <value>" << std::endl;
					std::cout << "EXAMPLE: set account username Gomitung" << std::endl;
					continue;
				}
				std::string section = "";
				std::string key = "";
				std::string value = "";
				input = input.substr(4, input.size() - 3);
				section = input.substr(0, input.find(' '));
				input = input.substr(section.size() + 1, input.size() - section.size());
				key = input.substr(0, input.find(" "));
				input = input.substr(key.size() + 1, input.size() - key.size());
				value = input.substr(0, input.size());
				file.setValue(section, key, value);
				file.save();
			}
			else if (input.substr(0, 3) == "get") {
				if (std::count(input.begin(), input.end(), ' ') != 2) {
					std::cout << "USAGE: get <section> <key>" << std::endl;
					std::cout << "EXAMPLE: get account username" << std::endl;
					continue;
				}
				std::string section = "";
				std::string key = "";
				input = input.substr(4, input.size() - 3);
				section = input.substr(0, input.find(' '));
				input = input.substr(section.size() + 1, input.size() - section.size());
				key = input.substr(0, input.find(" "));
				std::cout << "[" << section << "]" << std::endl;
				std::cout << key << "=" << file.getValue(section, key) << std::endl;
			}
			else if (input.substr(0, 5) == "print") {
				if (input == "print") {
					std::map <std::string, std::map<std::string, std::string>> sections = file.getSections();
					std::cout << argv[1] << std::endl;
					for (auto section_it = sections.begin(); section_it != sections.end(); section_it++) {
						std::cout << "[" << section_it->first << "]" << std::endl;
					}
					continue;
				}
				std::string section = input.substr(6,input.size() - 5);
				std::map<std::string, std::string> keys;
				try {
					keys = file.getKeys(section);
				}
				catch (std::string error) {
					std::cout << error << std::endl;
					continue;
				}
				std::cout << "[" << section << "]" << std::endl;
				for (auto keys_it = keys.begin(); keys_it != keys.end(); keys_it++) {
					std::cout << keys_it->first << "=" << keys_it->second <<std::endl;
				}
			}
			else {
				std::cout << "Type \"help\" for the list of commands" << std::endl;
			}
		}
	}
	return 0;
}