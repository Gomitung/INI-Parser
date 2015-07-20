#include "INIFile.h"
#include <fstream>
#include <iostream>
#include <regex>

cINIFile::cINIFile() {

}

cINIFile::cINIFile(const std::string filepath) : m_filePath(filepath) {
	load();
}

std::map <std::string, std::map<std::string, std::string>> cINIFile::getSections() {
	return m_sections;
}

std::map<std::string, std::string> cINIFile::getKeys(std::string section) {
	if (m_sections.find(section) != m_sections.end()) {
		return m_sections[section];
	}
	throw std::string("ERROR: Section not found");
}

std::string cINIFile::getValue(std::string section, std::string key) {
	if (m_sections.find(section) != m_sections.end()) {
		if (m_sections[section].find(key) != m_sections[section].end()) {
			return m_sections[section][key];
		}
		return "ERROR: Key not found";
	}
	return "ERROR: Section not found";
}

void cINIFile::setValue(std::string section, std::string key, std::string value){
	m_sections[section][key] = value;
}

void cINIFile::load() {
	std::fstream file(m_filePath, std::ios::in);
	if (!file) {
		throw std::string("ERROR: File not found/Couldn't be open");
	}
	std::string current_section;
	std::string line;
	std::regex key_regex("[A-Za-z0-9_]*[ \t\r\n\v\f]?[=][ \t\r\n\v\f]?.*", std::regex_constants::egrep);
	std::regex section_regex("[[][A-Za-z0-9_]*[]]", std::regex_constants::egrep);
	while (std::getline(file, line)) {
		if (line == "") {
			continue;
		}
		auto findComment = line.find(';');
		if (findComment != std::string::npos) {
			line = line.substr(0, findComment);
			if (line == "") {
				continue;
			}
		}


		auto findEquals = line.find('=');
		if (std::regex_match(line, key_regex) && current_section != "") {
			m_sections[current_section][line.substr(0, findEquals)] =
				line.substr(findEquals + 1, line.size() - findEquals);
			continue;
		}

		auto findOpenBracket = line.find('[');
		auto findCloseBracket = line.find(']');
		if (std::regex_match(line, section_regex) && findCloseBracket != std::string::npos) {
			current_section = line.substr(findOpenBracket + 1, findCloseBracket - 1);
			continue;
		}
	}
}

void cINIFile::save() {
	std::fstream file(m_filePath, std::ios::out | std::ios::trunc);
	if (!file) {
		throw std::string("Error opening file!");
	}
	for (auto section_it = m_sections.begin(); section_it != m_sections.end(); section_it++) {
		file << "[" << section_it->first << "]" << std::endl << std::endl;
		for (auto key_it = section_it->second.begin(); key_it != section_it->second.end(); key_it++) {
			file << key_it->first << "=" << key_it->second << std::endl;
		}
		file << std::endl;
	}
	file.close();
}