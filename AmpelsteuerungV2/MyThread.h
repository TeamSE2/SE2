
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "HAWThread.h"

namespace thread{
	class MyThread : public HAWThread
	{
		public:

			MyThread();
			virtual ~MyThread();

			virtual void execute(void *arg);
			virtual void shutdown();
	};
}
#endif
