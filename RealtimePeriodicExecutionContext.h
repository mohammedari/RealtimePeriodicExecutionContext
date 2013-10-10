#ifndef REALTIME_PERIODIC_EXECUTION_CONTEXT_H
#define REALTIME_PERIODIC_EXECUTION_CONTEXT_H

#include <rtm/RTC.h>
#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>
#include <time.h>

namespace RTC
{
  class RealtimePeriodicExecutionContext : public virtual PeriodicExecutionContext
  {
  private:
    static const int _priority = 49;
    static const int _prefaultStackSize = 8 * 1024;

    void addInterval(struct timespec &t, const coil::TimeValue& interval) const
    {
      t.tv_sec += interval.sec();
      t.tv_nsec += interval.usec() * 1000;

      while(t.tv_nsec >= 1e9)
      {
        t.tv_nsec -= 1e9;
        ++t.tv_sec;
      }
    }

    void prefaultStack()
    {
      unsigned char dummy[_prefaultStackSize];
      memset(dummy, 0, _prefaultStackSize);
      return;
    }

  public:
    RealtimePeriodicExecutionContext()
        : PeriodicExecutionContext()
    {
    }

    virtual ~RealtimePeriodicExecutionContext()
    {
    }

    virtual int svc(void);
  };
} //namespace RTC

extern "C"
{
  void RealtimeExecutionContextInit(RTC::Manager* manager);
} //extern "C"

#endif //REALTIME_PERIODIC_EXECUTION_CONTEXT_H
