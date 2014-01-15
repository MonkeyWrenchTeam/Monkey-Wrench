Monkey-Wrench
=============
Monkey Wrench is a WIP library that is designed with the idea of reducing code size and increasing speed.

We have many diverse features and documentation to boot.

Installation:

Compile the Visual Studio solution (or Code::Block project) or port the Source Code into another editor and compiler.

Copy the generated .dll (Wrench.dll or Wrench.so on Linux) into wherever your program is attempting to start from.

Link against the .lib (Wrench.lib or Wrench.so on Linux) file in your project.

Include Wrench.h

Include what ever other Wrench extension you may need.

Enjoy!

Documentation for functions and files can be found on the wiki!


#NOTE: It should be said that not all features are currently Linux and Windows compatible. We are working to fix this as fast as we can. As of this moment (1/15/2013) the only non-Linux compatible functions are ModifyMemory and FreezeMemory from Wrench_Memory.h. However, mem_sPointer is still fully functional on both systems.
