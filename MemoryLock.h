/*
 * MemoryLock.h
 *
 *  Created on: 2013/10/04
 *      Author: cgs
 */

#ifndef MEMORYLOCK_H_
#define MEMORYLOCK_H_

#include <sys/mman.h>
#include <string>

class MemoryLock
{
private:
  int _result;
  std::string _message;

  MemoryLock(const MemoryLock&);
  MemoryLock& operator=(const MemoryLock&);

public:
  MemoryLock()
  {
    _result = mlockall(MCL_CURRENT | MCL_FUTURE);
    if (_result != 0)
    {
      std::string message("mlockall failed");
      if (_result == EPERM)
        message.append(" : NO PERMISSION");

      _message = message;
    }
  };
  ~MemoryLock() { munlockall(); };

  const std::string GetMessage() const { return _message; };
  bool IsSucceeded() const { return _result == 0; };
};



#endif /* MEMORYLOCK_H_ */
