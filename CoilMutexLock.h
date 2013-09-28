/*
 * CoilMutexLock.h
 *
 *  Created on: 2013/09/28
 *      Author: cgs
 */

#ifndef COILMUTEXLOCK_H_
#define COILMUTEXLOCK_H_

#include <coil/Mutex.h>

class CoilMutexLock
{
private:
  coil::Mutex& _mutex;

  CoilMutexLock(const CoilMutexLock&);
  CoilMutexLock& operator=(const CoilMutexLock&);

public:
  CoilMutexLock(coil::Mutex& mutex) : _mutex(mutex) { _mutex.lock(); };
  ~CoilMutexLock() { _mutex.unlock(); };
};

#endif /* COILMUTEXLOCK_H_ */
