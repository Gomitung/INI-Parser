#ifndef _INIFILE_
#define _INIFILE_
#include <string>
#include <map>
class cINIFile {
private:
	std::map <std::string, std::map<std::string, std::string>> m_sections;
	std::string m_filePath;
public:
	cINIFile();
	cINIFile(const std::string filePath);
	std::map <std::string, std::map<std::string, std::string>> getSections();
	std::map<std::string, std::string> getKeys(std::string section);
	std::string getValue(std::string section,std::string key);
	void setValue(std::string section, std::string key, std::string value);
	void load();
	void save();
};
#endif
