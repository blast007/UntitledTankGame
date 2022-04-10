#include <catch2/catch.hpp>
#include <Configuration.h>


TEST_CASE( "Configuration handling", "[configuration]" ) {
    auto config = new Configuration(false);

    auto display = config->addSection("display", "data/Display.toml");
    auto blending = display->addBool("blending", true);
    auto fullScreen = display->addBool("fullScreen", true);
    auto lighting = display->addInt("lighting", 2)->addConstraint(new IntRangeConstraint(0, 2));

    // The configuration file has this set to false, so it should be false here as well
    REQUIRE(blending->get() == false);
    // The configuration file doesn't have this option, so it should reset to the default of true
    REQUIRE(fullScreen->get() == true);
    // The configuration file has an invalid value of 12, so this should reset to the default of 2
    REQUIRE(lighting->get() == 2);

    // Let's set lighting to 0 and verify that it worked
    lighting->set(0);
    REQUIRE(lighting->get() == 0);

    // Let's also try setting it to an invalid value and verify it failed to change
    REQUIRE(lighting->set(-1) == false);
    REQUIRE(lighting->get() == 0);
    REQUIRE(lighting->set(3) == false);
    REQUIRE(lighting->get() == 0);


    auto gui = config->addSection("gui", "data/GUI.toml");
    gui->addBool("hideMottos", false);
    gui->addInt("mottoDisplayLength", 32)->addConstraint(new IntRangeConstraint(0, 64));
    auto pulseDepth = gui->addFloat("pulseDepth", 0.4)->addConstraint(new FloatRangeConstraint(0.1, 0.9));
    auto pulseRate = gui->addFloat("pulseRate", 1.0)->addConstraint(new FloatRangeConstraint(0.2, 1.8));
    auto anotherFloat = gui->addFloat("anotherFloat", 1000000000.0)->addConstraint(new FloatRangeConstraint(0.0, 9223372036854775807.0));

    // The configuration file has this set to 0.6
    REQUIRE(pulseDepth->get() == 0.6);
    // The configuration file has this set to 2.0, which is outside the range, so it should be at the default of 1.0
    REQUIRE(pulseRate->get() == 1.0);
    // The option doesn't exist in the config file, so it should be the default
    REQUIRE(anotherFloat->get() == 1000000000.0);

    // Test setting the value to the extreme ranges of the constraints
    REQUIRE(pulseDepth->set(0.1) == true);
    REQUIRE(pulseDepth->get() == 0.1);
    REQUIRE(pulseDepth->set(0.9) == true);
    REQUIRE(pulseDepth->get() == 0.9);

    REQUIRE(pulseRate->set(0.2) == true);
    REQUIRE(pulseRate->get() == 0.2);
    REQUIRE(pulseRate->set(1.8) == true);
    REQUIRE(pulseRate->get() == 1.8);

    REQUIRE(anotherFloat->set(9223372036854775807.0));
    REQUIRE(anotherFloat->get() == 9223372036854775807.0);


    auto servers = config->addSection("servers", "data/Servers.toml");
    auto filter = servers->addString("filter", "")->addConstraint(new StringLengthConstraint(0, 128));

    REQUIRE(filter->get() == "");
    REQUIRE(filter->set("This is a test of the string type") == true);
    REQUIRE(filter->get() == "This is a test of the string type");


    delete config;
}
