#include <stdio.h>
#include <time.h>

int __FunctionsExecuted__  = 0;
time_t __TimeNow__;
time_t __TimeLater__;
double __TotalTimeElapsed__ = 0.0;
void *first_fn;


__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){
	if(__FunctionsExecuted__ == 0) {
		first_fn = this_fn;
		time(&__TimeNow__);
	}
	printf("          Function entered\n");
	__FunctionsExecuted__++;
	

}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){	
	printf("          Function exited\n");
	if(first_fn == this_fn) {
		time(&__TimeLater__);
		__TotalTimeElapsed__ = difftime(__TimeLater__, __TimeNow__);
		printf("%.f seconds elapsed\n", __TotalTimeElapsed__);
		printf("Functions executed: %d\n", __FunctionsExecuted__);
	}
}

