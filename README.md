RealtimePeriodicExecutionContext
=================

Realtime modded periodic execution context (EC) for OpenRTM-aist 1.1.0.

When RT component is activated, this EC set scheduling policy of the working thread to realtime.
This EC drives RT components periodically with lower latency (typically under 50us) under RT-PREEMPT patched Linux.

Build Environment
------

This source repository contains a project of Eclipse CDT.
Please install it and build source code.

This source code depends on OpenRTM-aist.
Please install OpenRTM-aist 1.1.0 C++ distribution package from [official page][openrtm].

This EC could be built under normal linux environment.
However realtime performance could be obtained under RT-PREEMPT Linux.
Please install RT-PREEMPT kernel such as Abogani realtime kernel ppa.

[openrtm]: http://www.openrtm.org

Using in RT components
------

Basically the same as [ART execution context case][art] (Japanse document).

First, modify *.Comp.cpp file and rebuild your RT component.  
Please add line

    manager->load("ArtExecutionContext.so", "ArtExecutionContextInit");

before setting module init procedure code `setModuleInitProc(MyModuleInit)`.

Second, modify rtc.conf.  
Please add execution context configuration lines.

    exec_cxt.periodic.type: RealtimePeriodicExecutionContext
    exec_cxt.periodic.rate: 1000
    
Third, run your EC with super user permission.  
Changing scheduling policy requires super user permission.
Please run RT components with sudo option or by root.

[art]:http://www.openrtm.org/openrtm/ja/content/artlinux%E7%94%A8%E5%AE%9F%E8%A1%8C%E3%82%B3%E3%83%B3%E3%83%86%E3%82%AD%E3%82%B9%E3%83%88

Lisence
------

Copyright &copy; 2013 Kazuyuki Arimatsu  
Licensed under the [GNU Lesser General Public License][LGPL].

[LGPL]: http://www.gnu.org/copyleft/lesser.html 
