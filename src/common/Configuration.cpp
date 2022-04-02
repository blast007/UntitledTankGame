#include "Configuration.h"

#include <iostream>

ConfigurationSection::ConfigurationSection(std::string fileName, bool autoSave) : _fileName(fileName), _autoSave(autoSave)
{
  // TODO: Check if the configuration file exists
  tomlObj = toml::parse<toml::preserve_comments, std::map, std::vector>(fileName);
}

ConfigurationSection::~ConfigurationSection()
{
  if (_autoSave)
    save();
}

bool ConfigurationSection::save()
{
  // TODO: Implement saving the file.
  std::cout << "Writing configuration not yet implemented. This would have been written to " << _fileName << ":" << std::endl;
  std::cout << tomlObj << std::endl;

  return true;
}

// TODO: Figure out if it's possible to replace these with a template, since they're the same except for the type
// TODO: Handle creating a new entry in the TOML representation if it doesn't exist

ConfigurationItem<bool>* ConfigurationSection::addBool(std::string name, bool defaultValue)
{
  auto item = new ConfigurationItem<bool>(toml::find<bool>(tomlObj, name), defaultValue);
  boolItems[name] = item;
  return item;
}

ConfigurationItem<std::int64_t>* ConfigurationSection::addInt(std::string name, std::int64_t defaultValue)
{
  auto item = new ConfigurationItem<std::int64_t>(toml::find<std::int64_t>(tomlObj, name), defaultValue);
  intItems[name] = item;
  return item;
}

ConfigurationItem<double>* ConfigurationSection::addFloat(std::string name, double defaultValue)
{
  auto item = new ConfigurationItem<double>(toml::find<double>(tomlObj, name), defaultValue);
  floatItems[name] = item;
  return item;
}

ConfigurationItem<std::string>* ConfigurationSection::addString(std::string name, std::string defaultValue)
{
  auto item = new ConfigurationItem<std::string>(toml::find<std::string>(tomlObj, name), defaultValue);
  stringItems[name] = item;
  return item;
}








Configuration::Configuration(bool autoSave) : _autoSave(autoSave)
{
}

Configuration::~Configuration()
{
  for (auto& section : sections) {
    delete section.second;
    section.second = nullptr;
  }
}

ConfigurationSection* Configuration::addSection(std::string name, std::string fileName)
{
  sections[name] = new ConfigurationSection(fileName, _autoSave);
  return sections[name];
}

ConfigurationSection* Configuration::getSection(std::string name)
{
  return sections[name];
}

bool Configuration::save()
{
  bool success = true;
  for (auto& section : sections)
    if (!section.second->save())
      success = false;

  return success;
}