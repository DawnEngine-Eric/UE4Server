#pragma once

#include "../Utils/var_helper.h"
#include "config.h"

enum CGPacket_Header
{
	HEADER_GC_BEGIN,
	HEADER_GC_VERSION,		// 1
	HEADER_GC_MAX
};

struct CGVersion
{
	BYTE	header;
	char	version[VERSION_MAX_LENGTH];
};