#pragma once

//-----------------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class BitmapWriter
{
private:

public:
	static bool Write( const char* path, uint32_t* data, int32_t width, int32_t height );
};