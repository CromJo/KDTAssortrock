#pragma once
#include <iostream>
#include <time.h>

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }