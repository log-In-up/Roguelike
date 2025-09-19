#pragma once
#include <memory>

namespace Roguelike
{
template <class T, class Y> class ISaveable
{
  public:
    std::shared_ptr<Y> Save() const
    {
        std::shared_ptr<Y> save = std::make_shared<Y>();
        Save(save);
        return save;
    };

    void Save(std::shared_ptr<Y> save) const
    {
        static_cast<const T *>(this)->SaveImpl(save);
    };

    void Load(std::shared_ptr<const Y> save)
    {
        static_cast<T *>(this)->LoadImpl(save);
    };
};
} // namespace Roguelike
