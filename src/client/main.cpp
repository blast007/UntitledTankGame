#include "Configuration.h"
#include <iostream>

int main()
{
  auto config = new Configuration();

  auto display = config->addSection("display", "tests/Configuration/Display.toml");
  display->addBool("blending", true);
  display->addBool("fullScreen", true);
  display->addInt("lighting", 2)->addConstraint(new IntRangeConstraint(0, 2));

  auto gui = config->addSection("gui", "tests/Configuration/GUI.toml");
  gui->addBool("hideMottos", false);
  gui->addInt("mottoDisplayLength", 32)->addConstraint(new IntRangeConstraint(0, 64));

  auto servers = config->addSection("servers", "tests/Configuration/Servers.toml");
  servers->addString("filter", "")->addConstraint(new StringLengthConstraint(0, 128));

  delete config;
  return 0;
}
