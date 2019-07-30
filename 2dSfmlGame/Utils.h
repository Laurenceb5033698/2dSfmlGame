#pragma once
#ifdef _DEBUG
#include <Windows.h>
#include <debugapi.h>
#include <sstream>
#include <iostream>

#endif

#ifdef _DEBUG
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s << "\n";                   \
   OutputDebugString( os_.str().c_str() );  \
}
#else
#define DBOUT( s )   {}

#endif

