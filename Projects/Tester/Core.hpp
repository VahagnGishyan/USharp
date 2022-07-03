#pragma once

//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <functional>
#include <memory> // always use smart pointers

//////////////////////////////////////////////////////////////////////////

#define DEBUG_MODE
#define EV_NM_DEBUG_LOG_SET "DEBUG_LOG_SET"
#define EV_VL_DEBUG_LOG_ON  "ON"
#define EV_VL_DEBUG_LOG_OFF "OFF"

//////////////////////////////////////////////////////////////////////////

#define CSMART_LIB

#ifdef CSMART_LIB
#define CSMART_EXPORT __declspec(dllexport)
#else
#define CSMART_EXPORT __declspec(dllimport)
#endif // CSMART_LIB

//////////////////////////////////////////////////////////////////////////

namespace Tester
{
	namespace Timer
	{
		CSMART_EXPORT std::chrono::nanoseconds zero();
		//std::chrono::system_clock::time_point  now();
		//std::chrono::system_clock::time_point  duration(std::chrono::system_clock::time_point& start, end);
	}

	// temp
	const std::string CSMART_EXPORT getIndexAsStringWithSpaces(const int size, const int index);

	class TestCase
	{
	public:
		TestCase(const std::string& caseName) : m_caseName(caseName), m_ID(getPrimaryKey()) {}

	public:
		const int          getID      () const { return (m_ID);       }
		const std::string& getCaseName() const { return (m_caseName); }

	private:
		int getPrimaryKey() const
		{
			static int ID = -1;
			return (++ID);
		}

	private:
		int         m_ID;
		std::string m_caseName;
	};

	class TestCaseList
	{
	public:
		TestCaseList(const std::vector<std::string>& tcases)
		{
			const int size = tcases.size();
			m_testCase.reserve(size);
			for (auto& tcase : tcases)
			{
				m_testCase.push_back(tcase);
			}
			if (m_testCase.size() != size)
			{
				throw std::string("DLL[Tester], file[Core.cpp], class[TestCaseList], ctor, m_testCase.size() != size");
			}
		}

		TestCase& getTestCase(const int index)
		{
			return (m_testCase[index]);
		}

		const TestCase& getTestCase(const int index) const
		{
			return (m_testCase[index]);
		}
		 
		const int size() const
		{
			return (m_testCase.size());
		}

	private:
		std::vector<TestCase> m_testCase;
	};

	struct CSMART_EXPORT Settings
	{
	public:
		Settings(const int tCount, const int iCount, const TestCaseList& testCaseNames) :
			m_testCount(tCount),
			m_iterCount(iCount),
			m_testCases(testCaseNames)
		{

		}

	private:
		std::chrono::nanoseconds CalculateOverhead() const;

	public:
		const int                       getTestCount() const;
		const int                       getIterCount() const;
		const TestCaseList&             getTestCases() const;
		const std::chrono::nanoseconds& getOverhead () const;

	private:
		const int          m_testCount;
		const int          m_iterCount;
		const TestCaseList m_testCases;
	};

	class CSMART_EXPORT Loging
	{
	public:

		Loging(const std::string& path) /*{ except { std::string } }*/
		{
			file.open(path);
			if (!file)
			{
				throw(std::string("Can't open file[") + path + "]");
			}
		}
		Loging(std::string&& path = std::string("D:\\Projects\\U#Leng\\Projects\\Tester\\loging\\messages.txt"))
			/* except { std::string } */
		{
			file.open(path);
			if (!file)
			{
				throw(std::string("Can't open file[") + path + "]");
			}
		}
		~Loging()
		{
			file.close();
		}

		void write  (const char symbol);
		void writeln(const char symbol);

		void write(const std::string& message);
		void write(const std::string&& message);

		void writeln();

		void writeln(const std::string& message);
		void writeln(const std::string&& message);

		//void print(const std::string& log)
		//{
		//	std::cout << log;
		//	file << log;
		//}
		//void print(      std::string&& log);

		//void println();
		//void println(const std::string& log);
		//void println(std::string&& log);

	private:
		std::ofstream file;
	};

	class CSMART_EXPORT Results
	{
	public:
		struct TestCaseResults
		{
			std::string            m_testname;
			std::vector<long long> m_durations;
		};

	public:
		Results(const Settings& settings)
		{
			const auto& tcases = settings.getTestCases();
			const int tCaseSize = tcases.size();
			m_results.resize(tCaseSize);
			const int   tCount = settings.getTestCount();

			for (int start = 0; start < tCaseSize; ++start)
			{
				m_results[start].m_testname = tcases.getTestCase(start).getCaseName();
				m_results[start].m_durations.resize(tCount);
				for (int index = 0; index < tCount; ++index)
				{
					m_results[start].m_durations[index] = Timer::zero().count();
				}
			}
		}

		const std::vector<TestCaseResults>& getResults() const;
		const Results::TestCaseResults&     getTestCase(const int tCaseIndex) const;
		      Results::TestCaseResults&     getTestCase(const int tCaseIndex);
		const long long&                    getTestCaseItr(const int tCaseIndex, const int test) const;

		void saveResults(const std::string& path, const Settings& settings, Loging& loger);

		//std::chrono::nanoseconds& get(const int testCase, const int index)
		//{
		//	if (testCase < 0 || testCase >= m_results.size() || index < 0 || index >= m_results[testCase].m_durations.size())
		//	{
		//		throw(std::string("Results::get,s index not valid"));
		//	}
		//	return (m_results[testCase].m_durations[index]);
		//}

	private:
		std::vector<TestCaseResults> m_results;
	};
}

//////////////////////////////////////////////////////////////////////////
