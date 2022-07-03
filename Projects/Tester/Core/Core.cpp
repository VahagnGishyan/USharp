
#include "Core.hpp"

namespace Tester
{
	std::chrono::nanoseconds Timer::zero()
	{
		auto time = std::chrono::system_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(time - time);
	}

	//std::chrono::system_clock::time_point Timer::now()
	//{
	//	return (std::chrono::system_clock::now());
	//}

	std::chrono::nanoseconds Settings::CalculateOverhead() const
	{
		using namespace std::chrono;
		constexpr int count = 1000000;
		std::chrono::nanoseconds duration = Timer::zero();
		std::chrono::time_point<std::chrono::system_clock> start, end;
		for (int index = 0; index < count; ++index)
		{
			start = system_clock::now();
			end   = system_clock::now();
			duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		}
		return (duration / count);
	}

	const int                       Settings::getTestCount() const { return (m_testCount); }
	const int                       Settings::getIterCount() const { return (m_iterCount); }
	const TestCaseList&             Settings::getTestCases() const { return (m_testCases); }
	const std::chrono::nanoseconds& Settings::getOverhead() const
	{
		static auto overhead = CalculateOverhead();
		return (overhead);
	}

	static const int getNumberCount(int number)
	{
		if (number == 0)
			return (1);

		int count = 0;
		while (number != 0)
		{
			number /= 10;
			++count;
		}
		return (count);
	}

	const std::string getIndexAsStringWithSpaces(const int size, const int index)
	{
		std::string result = "";
		const int sizeNCount = getNumberCount(size - 1);
		const int indexNCount = getNumberCount(index);
		const int dif = sizeNCount - indexNCount;
		for (int index = 0; index < dif; ++index)
		{
			result += ' ';
		}
		return(result + std::to_string(index));
	}

	//class CSMART_EXPORT 

	const std::vector<Results::TestCaseResults>& Results::getResults() const
	{
		return (m_results);
	}

	Results::TestCaseResults& Results::getTestCase(const int tCaseIndex)
	{
		return (m_results[tCaseIndex]);
	}
	const Results::TestCaseResults& Results::getTestCase(const int tCaseIndex) const
	{
		return (m_results[tCaseIndex]);
	}

	const long long& Results::getTestCaseItr(const int tCaseIndex, const int test) const
	{
		return (m_results[tCaseIndex].m_durations[test]);
	}

	static void writeTestSettings(std::ofstream& file, const Settings& settings)
	{
#ifdef  _DEBUG
		file << "[DEBUG]" << std::endl;
#else   // RELEASE 
		file << "[RELEASE]" << std::endl;
#endif
		file << "Test Settings" << std::endl;
		file << "Cases                 :: { ";
		auto& tcases = settings.getTestCases();
		for (int index = 0; index < tcases.size(); ++index)
		{
			if (index != 0)
			{
				file << ", ";
			}
			file << tcases.getTestCase(index).getCaseName();
		}
		file << " }" << std::endl;
		file << "Case count            :: " << settings.getTestCount() << std::endl;
		file << "Iteration count       :: " << settings.getIterCount() << std::endl;
		file << "Overhead[std::chrono] :: " << settings.getOverhead().count() << "ns" << std::endl;
		file << std::endl;
	}

	void writeResults(std::ofstream& file, const std::vector<Results::TestCaseResults>& results)
	{
		const int size = results.size();
		for (int icase = 0; icase < size; ++icase)
		{
			file << "Test Case [" << results[icase].m_testname << "]" << std::endl;
			const int itrCount = results[icase].m_durations.size();
			for (int iitr = 0; iitr < itrCount; ++iitr)
			{
				file << "Itr[" << getIndexAsStringWithSpaces(itrCount, iitr) << "] :: " <<
					results[icase].m_durations[iitr] << std::endl;
			}
			file << std::endl;
		}
	}

	void writeDetails(std::ofstream& file, const std::vector<Results::TestCaseResults>& results)
	{
		file << "More details" << std::endl;

		const int size = results.size();
		std::vector<long long> awgList(size);
		std::vector<long long> maxList(size);
		std::vector<long long> minList(size);

		for (int index = 0; index < size; ++index)
		{
			auto& durations = results[index].m_durations;
			long long awg = std::accumulate(durations.begin(), durations.end(), 0) / durations.size();
			long long max = *std::max_element(durations.begin(), durations.end());
			long long min = *std::min_element(durations.begin(), durations.end());

			file << "AWG of Test Case [" << results[index].m_testname << "] :: " << awg << std::endl;
			file << "MAX of Test Case [" << results[index].m_testname << "] :: " << max << std::endl;
			file << "MIN of Test Case [" << results[index].m_testname << "] :: " << min << std::endl;

			if (index != size - 1)
			{
				file << std::endl;
			}
		}
	}

	void Results::saveResults(const std::string& path, const Settings& settings, Loging& loger)
	{
		std::ofstream file(path);
		if (!file)
		{
			loger.writeln("Can't open result-save file[" + path + "]");
			return;
		}

		writeTestSettings(file, settings);
		writeResults(file, m_results);
		writeDetails(file, m_results);
	}

	void Loging::write(const char symbol)
	{
		std::cout << symbol;
		file << symbol;
	}
	void Loging::writeln(const char symbol)
	{
		std::cout << symbol << std::endl;
		file << symbol << std::endl;
	}


	void Loging::write(const std::string& message)
	{
		std::cout << message;
		file << message;
	}
	void Loging::write(const std::string&& message)
	{
		std::cout << message;
		file << message;
	}

	void Loging::writeln()
	{
		std::cout << std::endl;
		file << std::endl;
	}

	void Loging::writeln(const std::string& message)
	{
		std::cout << message << std::endl;
		file << message << std::endl;
	}
	void Loging::writeln(const std::string&& message)
	{
		std::cout << message << std::endl;
		file << message << std::endl;
	}
}
