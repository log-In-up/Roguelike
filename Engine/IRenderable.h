#pragma once

namespace GameEngine
{
class IRenderable
{
  public:
    explicit IRenderable(const int layer = 0);
    virtual ~IRenderable() = default;

    virtual void Render() = 0;

    const int &GetLayer() const;
    void SetLayer(const int newLayer);

  protected:
    int layer;
};
} // namespace GameEngine
