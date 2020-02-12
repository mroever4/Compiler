// File:		Timer.cpp
// Language:	C++17
// Purpose:		Rudamentary timer class.
// License:		At bottom of document.

// Header
#include "Timer.h"


// Sets the start time to the current time.
//
// Error Handling:
//	+ Never throws.
void Timer::start() noexcept {
	startTime = std::chrono::high_resolution_clock::now();
}


// Sets the stop time to the current time.
//
// Error Handling:
//	+ Never throws.
void Timer::stop() noexcept {
	endTime = std::chrono::high_resolution_clock::now();
}


// Gets the difference between the start and stop times in nanoseconds.
//
// Result:
//	+ Time between start and stop in nanoseconds.
//
// Error Handling:
//	+ Never throws.
int64_t Timer::duration() const noexcept {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}


/******************************************************************************

This software is provided under two licenses. Choose whichever you prefer.


============================= Apache License V2.0 =============================

Copyright 2020 Matthew Roever

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


================================= MIT License =================================

Copyright (c) 2020 Matthew Roever

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/