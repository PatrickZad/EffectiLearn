#include "layer.h"
using namespace patrick;
Layer::Layer(ActivationFunc& activation, unsigned long width)
    : activation{activation}, width{width}
{
    initParemeters();
}