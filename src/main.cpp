#include "controller.h"
#include <ge211.h>

int main()
{
    Model model;
    Controller controller(model);

    controller.run();
}