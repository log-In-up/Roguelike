#include "pch.h"

#include "IRenderable.h"

namespace GameEngine
{
IRenderable::IRenderable(const int layer) : layer(layer)
{
}

const int &IRenderable::GetLayer() const
{
    return layer;
}

void IRenderable::SetLayer(const int newLayer)
{
    layer = newLayer;
}
} // namespace GameEngine