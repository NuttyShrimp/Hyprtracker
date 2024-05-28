#pragma once

template <typename T> class Singleton {
public:
  static T &instance() {
    static T inst;
    return inst;
  }
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

protected:
  Singleton() = default;

private:
};
