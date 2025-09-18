#pragma once
#include <memory>
#include <vector>

namespace GameEngine
{
class IObservable;

class IObserver
{
  public:
    virtual void Notify(std::shared_ptr<IObservable> observable) = 0;
};

class IObservable : public std::enable_shared_from_this<IObservable>
{
  public:
    virtual void AddObserver(const std::weak_ptr<IObserver> observer);

  protected:
    virtual void Emit();
    std::vector<std::weak_ptr<IObserver>> observers;
};
} // namespace GameEngine
