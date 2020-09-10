#pragma once

#include "PowerDataSource.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

class Registry
{
public:
	struct SourceInfo
	{
		std::vector<std::string> availableCounters;
		std::function<PowerDataSourcePtr(const std::string &)> openCounter;

		bool available() const
		{
			return !availableCounters.empty();
		}
	};

	template<typename DataSourceT>
	static int registerSource()
	{
		SourceInfo sourceInfo;
		sourceInfo.availableCounters = DataSourceT::detectAvailableCounters();
		sourceInfo.openCounter = [](const std::string & counterName){
			return DataSourceT::openCounter(counterName);
		};

		s_sources.at(DataSourceT::sourceName()) = sourceInfo;
		return s_sources.size();
	}

	static void setup();

private:
	static std::map<std::string,SourceInfo> s_sources;

};