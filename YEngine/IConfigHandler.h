#pragma once
#ifndef ICONFIGHANDLER_H
#define ICONFIGHANDLER_H

#include <vector>
#include <string>

enum class FILESORTSYSTEM { ORDERED, PREFIXED };

struct RawData {
	std::vector<std::vector<std::vector<std::string>>> dataSets;
};

class IConfigHandler
{
public:
	virtual bool loadRawData(RawData& data, const char* filename) = 0;
	virtual bool loadRawData(RawData& data, const char* filename, char rowBreaker, char paramBreaker) = 0;
};

#endif
