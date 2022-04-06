#include "Configuration.h"
#include <iostream>

int main()
{
  // Create a configuration instance without autosave enabled
  auto config = new Configuration(false);

  auto display = config->addSection("display", "tests/Configuration/Display.toml");
  display->addBool("blending", true);
  display->addBool("fullScreen", true);
  display->addInt("lighting", 2)->addConstraint(new IntRangeConstraint(0, 2));
  if (!display->save("out/Display.toml"))
    std::cout << "Error writing Display configuration" << std::endl;

  auto gui = config->addSection("gui", "tests/Configuration/GUI.toml");
  gui->addBool("hideMottos", false);
  gui->addInt("mottoDisplayLength", 32)->addConstraint(new IntRangeConstraint(0, 64));
  if (!gui->save("out/GUI.toml"))
    std::cout << "Error writing GUI configuration" << std::endl;

  auto servers = config->addSection("servers", "tests/Configuration/Servers.toml");
  servers->addString("filter", "")->addConstraint(new StringLengthConstraint(0, 128));
  if (!servers->save("out/Servers.toml"))
    std::cout << "Error writing Servers configuration" << std::endl;

  delete config;
  return 0;
}
