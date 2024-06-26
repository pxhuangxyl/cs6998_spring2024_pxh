#ifndef _GLOBALS_HH_
#define _GLOBALS_HH_

using namespace std;

namespace CDC8600
{
    extern vector<word> 	MEM;				// shared memory
    extern u32	     		FreeMEM;			// beginning of shared heap
    extern vector<Processor>    PROC;				// Processors
    extern u32			me();				// Processor number of current thread
    extern u32			nump();				// Total number of processors available
    extern bool			prediction(u32, bool, label_t);	// Branch prediction hit (true) or miss (false)
    extern vector<string>	files;				// Source files for CDC8600 program
} // namespace CDC8600

#endif // _GLOBALS_HH
