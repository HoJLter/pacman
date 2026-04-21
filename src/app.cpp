#include <iostream>
#include "utils/Log.h"


int main() {
	Log::setLogger(LoggerType::Console);
	Log::debug("WASSUP");
}