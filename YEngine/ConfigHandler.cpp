#include "ConfigHandler.h"
#include <fstream>
#include <array>
#include <tiny_obj_loader.h>


bool ConfigHandler::loadRawData(RawData& data, const char* filename)
{
	return this->loadRawData(data, filename, '*', ',');
}

bool ConfigHandler::loadRawData(RawData& data, const char* filename, char setBreaker, char paramBreaker)
{
	bool success = false;
	// Open file
	std::ifstream file(filename);
	// Check success of opening file
	if (file.is_open())
	{
		success = true;
		int dataSetCount = 0;
		int row = 0;
		std::string line;
		std::vector<std::vector<std::string>> dataSet;
		// While there is another line to grab from the file; get it
		while (std::getline(file, line))
		{
			// Jump to next row if line is empty
			if (line.empty())
			{
			}
			// Ignore any rows with '#' for use as comments
			else if (line[0] == '#')
			{
			}
			// New Data set if '*' is found in the first slot
			else if (line[0] == setBreaker)
			{
				dataSetCount++;
				data.dataSets.push_back(dataSet);
				dataSet.clear();
			}
			// Disect the line into parameters and store them in the data set, line by line
			else {
				std::vector<std::string> parameters;
				int charPos = 0;
				std::string param = "";

				while (charPos != line.size())
				{
					// New parameter after every ','
					if (line[charPos] == paramBreaker)
					{
						parameters.push_back(param);
						param = "";
					}
					else {
						param += line[charPos];
					}

					charPos++;
				}

				dataSet.push_back(parameters);
			}

			row++;
		}

		file.close();
	}

	return success;
}
