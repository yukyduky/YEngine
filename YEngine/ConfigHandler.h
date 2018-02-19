#pragma once
#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include "IConfigHandler.h"

class ConfigHandler : public IConfigHandler
{
public:
	bool loadRawData(RawData& data, const char* filename) override;
	bool loadRawData(RawData& data, const char* filename, char setBreaker, char paramBreaker) override;
};

#endif
