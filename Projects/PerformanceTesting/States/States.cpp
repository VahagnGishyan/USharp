
#include "PerformanceTesting/State.hpp"

namespace CSmart
{
	namespace PerformanceTesting
	{
		namespace ExcaptionErrHandling
		{
			enum class SomeStates
			{
				NoSet,	 // no handle
				CallCpp, // no handle
				SomeError
			};

			void SomeFunction()
			{
				throw (SomeStates::SomeError);
			}
			void foo(void)
			{
				try
				{
					SomeFunction();
				}
				catch(SomeStates state)
				{
					/*handling*/
				}
			}
		}

		namespace StateErrHandling
		{
			enum class SomeStates
			{
				NoSet,	 // no handle
				CallCpp, // no handle
				SomeError
			};

			struct SomeFunction
			{
			public:
				SomeFunction()
				{
					state = SomeStates::SomeError;
				}

			public:
				static SomeStates state;
			};

			SomeStates SomeFunction::state = SomeStates::NoSet;

			void foo(void)
			{
				SomeFunction();
				if (SomeFunction::state == SomeStates::SomeError)
				{
					/*handling*/
				}
			}
		}

		//template<std::function<void(void)> T>
		//template<void (*T)(void)>
		//void test(const Tester::Settings& settings, Tester::Results& results, Tester::Loging& loger)
		//{
		//	const int   tCount = settings.getTestCount();
		//	const int   iCount = settings.getIterCount();
		//	const auto& overhead = settings.getOverhead();

		//	auto& tCase = results.getTestCase(0);

		//	for (int tIndex = 0; tIndex < tCount; ++tIndex)
		//	{
		//		std::chrono::nanoseconds duration = Tester::Timer::zero();

		//		for (int iIndex = 0; iIndex < iCount; ++iIndex)
		//		{
		//			auto start = std::chrono::system_clock::now();
		//			T();
		//			auto end = std::chrono::system_clock::now();
		//			duration += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)/*must be - overhead*/);
		//		}

		//		tCase.m_durations[tIndex] = (duration.count() / iCount);
		//	}
		//}

		template<void (*TestFunc)(void), int index>
		void test_caller    (const Tester::Settings& settings, Tester::Results& results, Tester::Loging& loger)
		{
			const int   tCount   = settings.getTestCount();
			const int   iCount   = settings.getIterCount();
			const auto& overhead = settings.getOverhead();

			auto& tCase = results.getTestCase(index);

			loger.writeln(std::string("TestCase :: ") + tCase.m_testname);

			for (int tIndex = 0; tIndex < tCount; ++tIndex)
			{
				loger.write('[' + Tester::getIndexAsStringWithSpaces(tCount, tIndex) + "] :: { ");
				std::chrono::nanoseconds duration = Tester::Timer::zero();
				
				for (int iIndex = 0; iIndex < iCount; ++iIndex)
				{
					auto start = std::chrono::system_clock::now();
					TestFunc();
					auto end = std::chrono::system_clock::now();
					duration += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));
					//must be
					//duration += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start) - overhead);
					if (duration.count() < 0)
					{
						duration = Tester::Timer::zero();
					}

					if ((iIndex + 1) % (iCount / 10) == 0)
					{
						loger.write('#');
					}
				}
				loger.writeln(" }");

				tCase.m_durations[tIndex] = (duration.count() / iCount);
			}
			loger.writeln();
		}

		void state()
		{
			Tester::Loging loger;
			const std::string resultFilePath = "D:\\Projects\\U#Leng\\Projects\\Tester\\loging\\results.txt";

			Tester::TestCaseList testCase({ "excaption", "state"});
			Tester::Settings settings(10, 100, testCase);
			Tester::Results  results(settings);

			test_caller<ExcaptionErrHandling::foo, 0>(settings, results, loger);
			test_caller<StateErrHandling    ::foo, 1>(settings, results, loger);

			results.saveResults(resultFilePath, settings, loger);
			loger.writeln("Close testing()");
		}
	}
}
