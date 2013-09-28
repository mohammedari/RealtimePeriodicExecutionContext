#include "RealtimePeriodicExecutionContext.h"
#include <rtm/ECFactory.h>

#include <errno.h>
#include <pthread.h>
#include "CoilMutexLock.h"

namespace RTC
{
  int RealtimePeriodicExecutionContext::svc()
  {
    RTC_TRACE(("svc()@realtime"));

    struct sched_param param;
    param.sched_priority = _priority;
    int result = pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    if (result != 0)
    {
      std::string message("pthread_setscheduler failed");
      if (result == EPERM)
        message.append(" : NO PERMISSION");

      RTC_ERROR_STR(message);
      return 1;
    }

    RTC_TRACE(("thread is set to realtime priority"));

    do
    {
      struct timespec t;
      clock_gettime(CLOCK_MONOTONIC, &t);
      {
        CoilMutexLock(m_worker.mutex_);
        while (!m_worker.running_)
        {
          m_worker.cond_.wait();
        }

        if (m_worker.running_)
        {
          std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
        }
      }

      if (!m_nowait)
      {
        addInterval(t, m_period);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
      }
    }
    while (m_svc);

    return 0;
  }
} //namespace RTC

extern "C"
{
  void RealtimePeriodicExecutionContextInit(RTC::Manager* manager)
  {
    RTC::Manager::instance().registerECFactory(
        "RealtimePeriodicExecutionContext",
        RTC::ECCreate<RTC::RealtimePeriodicExecutionContext>,
        RTC::ECDelete<RTC::RealtimePeriodicExecutionContext>);
  }
} //extern "C"
