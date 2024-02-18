#include "../Header Files/Controller.h"


int main(int argc, char* argv[])
{
    Controller controller(std::make_unique<cycfi::elements::app>(argc, argv, "Weather App", "com.mrt-stephens.weather-app"));

    controller.Init();

    return 0;
}
