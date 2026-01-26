#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

/// @brief A simple periodic scheduler for subdividing a base timer.
///        Autoware-style deterministic scheduling.
///        Example: 100 Hz base tick → 20ms, 40ms tasks.
class RateScheduler
{
public:
  using Callback = std::function<void()>;

  struct Task
  {
    uint32_t period_ticks{};  // number of base ticks between runs
    uint32_t counter{};       // internal counter
    Callback callback{};      // function
  };

  explicit RateScheduler(uint32_t base_hz) : base_period_ms_{static_cast<uint32_t>(1000 / base_hz)}
  {
  }

  /// @brief Add a task that runs every (period_ms)
  void add_task(uint32_t period_ms, Callback cb)
  {
    const uint32_t ticks = period_ms / base_period_ms_;
    tasks_.push_back(Task{ticks, 0U, std::move(cb)});
  }

  /// @brief Must be called by the base timer tick (e.g., 100 Hz)
  void tick()
  {
    for (auto & task : tasks_) {
      task.counter++;
      if (task.counter >= task.period_ticks) {
        task.counter = 0U;
        if (task.callback) {
          task.callback();
        }
      }
    }
  }

private:
  uint32_t base_period_ms_;
  std::vector<Task> tasks_;
};