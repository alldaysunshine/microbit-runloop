#import "AsmBridge.h"
#import "SysTick.h"

#define STCSR 0xE000E010
#define STRVR 0xE000E014

SysTick::SysTick() {
	
}

SysTick& SysTick::getInstance()
{
	static SysTick instance; // Guaranteed to be destroyed.
						  // Instantiated on first use.
	return instance;
}

void SysTick::enable() {
	// Set clock
	PUT32(STRVR, 300000);
	PUT32(STCSR, 11);
}

void SysTick::disable() {
	PUT32(STCSR, 0);
}

