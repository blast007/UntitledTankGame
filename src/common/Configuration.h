#pragma once

#include <toml.hpp>
#include <string>
#include <vector>
#include <map>


//
// Configuration value constraints
//

template <typename T>
struct ConfigurationConstraint {
    virtual bool isValid(T checkValue) = 0;
};

// TODO: Add a RegexConstraint for strings
// TODO: Think about constraints for Array and Table types, though that's complicated because the values can be different types

struct IntRangeConstraint : public ConfigurationConstraint<std::int64_t> {
    IntRangeConstraint(std::int64_t minValue, std::int64_t maxValue) : _minValue(minValue), _maxValue(maxValue) {};
    bool isValid(std::int64_t checkValue) {
      return checkValue >= _minValue && checkValue <= _maxValue;
    }

  private:
    std::int64_t _minValue, _maxValue;
};

struct FloatRangeConstraint : public ConfigurationConstraint<double> {
    FloatRangeConstraint(double minValue, double maxValue) : _minValue(minValue), _maxValue(maxValue) {};
    bool isValid(double checkValue) {
      return checkValue >= _minValue && checkValue <= _maxValue;
    }

  private:
    double _minValue, _maxValue;
};

struct StringLengthConstraint : public ConfigurationConstraint<std::string> {
    StringLengthConstraint(std::size_t minLength, std::size_t maxLength) : minLength(minLength), maxLength(maxLength) {};
    bool isValid(std::string checkValue) {
      return checkValue.length() >= minLength && checkValue.length() <= maxLength;
    }

  private:
    std::size_t minLength, maxLength;
};


//
// Configuration item
//

// TODO: Add update callback support
// TODO: Specialization functions for Array and Table

template <class T>
struct ConfigurationItem {
    ConfigurationItem(T& value, T defaultValue) : _value(value), _defaultValue(defaultValue) {};
    T get() const { return _value; }
    T getDefault() const { return _defaultValue; }
    void reset() { _value = _defaultValue; }
    bool set(T newValue) { if (!isValid(newValue)) return false; _value = newValue; return true; }
    bool isValid(T checkValue) const {
      for (auto& constraint : constraints)
        if (!constraint->isValid(checkValue))
          return false;
      return true;
    };
    // TODO: Decide if this should return a bool indicating if the current value was reset due to failing the constraint
    void addConstraint(ConfigurationConstraint<T>* constraint) {
      // Add the constraint to the list
      constraints.push_back(constraint);
      // Check if the current value is valid according to the newly added constraint, and if not, reset to default
      if (!constraint->isValid(_value))
        reset();
    }
  private:
    T& _value;
    T _defaultValue;
    std::vector<ConfigurationConstraint<T>*> constraints;
};


//
// ConfigurationSection
//

// TODO: Implement support for Array and Table

struct ConfigurationSection {
    ConfigurationSection(std::string fileName, bool autoSave = true);
    ~ConfigurationSection();
    bool save();
    ConfigurationItem<bool>* addBool(std::string name, bool defaultValue);
    ConfigurationItem<std::int64_t>* addInt(std::string name, std::int64_t defaultValue);
    ConfigurationItem<double>* addFloat(std::string name, double defaultValue);
    ConfigurationItem<std::string>* addString(std::string name, std::string defaultValue);

  private:
    std::string _fileName;
    bool _autoSave;

    toml::basic_value<toml::preserve_comments, std::map, std::vector> tomlObj;

    std::map<std::string, ConfigurationItem<bool>*> boolItems;
    std::map<std::string, ConfigurationItem<std::int64_t>*> intItems;
    std::map<std::string, ConfigurationItem<double>*> floatItems;
    std::map<std::string, ConfigurationItem<std::string>*> stringItems;

    //std::map<std::string, ConfigurationItem<std::vector<toml::value>>*> arrayItems;
    //std::map<std::string, ConfigurationItem<std::map<toml::key, toml::value>>*> tableItems;
};


//
// Configuration
//


// TODO: Singleton pattern?
class Configuration
{
  private:
    std::map<std::string, ConfigurationSection*> sections;
    bool _autoSave;

  public:
    Configuration(bool autoSave = true);
    ~Configuration();

    ConfigurationSection* addSection(std::string name, std::string fileName);
    ConfigurationSection* getSection(std::string name);

    bool save();

    /*bool readFromFile(std::string fileName);
    bool writeToFile(std::string fileName);
    void test();
    ConfigurationData* get();*/


};
