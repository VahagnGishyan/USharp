//
//#include "../Tests.hpp"
//
//namespace Tester
//{
//	namespace Timer 
//	{
//		std::chrono::nanoseconds zero()
//		{
//			auto time = std::chrono::system_clock::now();
//			return std::chrono::duration_cast<std::chrono::nanoseconds>(time - time);
//		}
//	}
//
//	struct Settings
//	{
//	public:
//		Settings(const int tCount, const int iCount) : m_testCount(tCount), m_iterCount(iCount),
//			overhead(CalculateOverhead())
//		{
//
//		}
//
//	private:
//		std::chrono::nanoseconds CalculateOverhead()
//		{
//			using namespace std::chrono;
//			constexpr int count = 10000;
//			std::chrono::nanoseconds duration = Timer::zero();
//			std::chrono::time_point<std::chrono::system_clock> start, end;
//			for (int index = 0; index < count; ++index)
//			{
//				start = system_clock::now();
//				end = system_clock::now();
//				duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
//			}
//			return (duration / count);
//		}
//
//	public:
//		const int                      getTestCount() const { return (m_testCount); }
//		const int                      getIterCount() const { return (m_iterCount); }
//		const std::chrono::nanoseconds getOverhead () const
// 		{
//			return (overhead);
//		}
//
//	private:
//		const int m_testCount;
//		const int m_iterCount;
//		const std::chrono::nanoseconds overhead;
//	};
//
//	struct Results
//	{
//	private:
//		struct Data
//		{
//			std::chrono::nanoseconds exception;
//			std::chrono::nanoseconds state;
//		};
//
//	public:
//		Results(const Settings& settings)
//		{
//			const int tCount = settings.getTestCount();
//			m_durations.resize(tCount);
//			for (int index = 0; index < tCount; ++index)
//			{
//				m_durations[index].exception= Timer::zero();
//				m_durations[index].state = Timer::zero();
//			}
//		}
//
//		Data& get(const int index)
//		{
//			if (index < 0 || index >= m_durations.size())
//			{
//				throw(std::string("Results::get,s index not valid"));
//			}
//			return (m_durations[index]);
//		}
//
//	private:
//		std::vector<Data> m_durations;
//	};
//
//	class Loging
//	{
//	public:
//		Loging(const std::string& path) /*{ except { std::string } }*/
//		{
//			file.open(path);
//			if (!file)
//			{
//				throw(std::string("Can't open file[") + path + "]");
//			}
//		}
//		Loging(const std::string&& path) /*{ except { std::string } }*/
//		{
//			file.open(path);
//			if (!file)
//			{
//				throw(std::string("Can't open file[") + path + "]");
//			}
//		}
//
//		//void print(const std::string& log)
//		//{
//		//	std::cout << log;
//		//	file << log;
//		//}
//		//void print(      std::string&& log);
//
//		//void println();
//		//void println(const std::string& log);
//		//void println(std::string&& log);
//
//	public:
//		template<typename T>
//		Loging& operator<<(const T& value)
//		{
//			std::cout << value;
//			     file << value;
//
//			return *this;
//		}
//
//		typedef std::ostream& (*ostream_manipulator)(std::ostream&);
//		friend Loging& operator<<(Loging& os, ostream_manipulator pf)
//		{
//			std::cout << std::endl;
//			     os.file << std::endl;
//			return (os);
//		}
//
//	private:
//		std::ofstream file;
//	};
//}
//
//namespace TestCase
//{
//	namespace ExceptionMode
//	{
//		void fooK() { throw(5); }
//		void fooJ() { fooK();   }
//		void fooI() { fooJ();   }
//		void fooH() { fooI();   }
//		void fooG() { fooH();   }
//		void fooF() { fooG();   }
//		void fooE() { fooF();   }
//		void fooD() { fooE();   }
//		void fooC() { fooD();   }
//		void fooB() { fooC();   }
//		void fooA() 
//		{ 
//			try 
//			{ 
//				fooB(); 
//			} 
//			catch (const int) 
//			{ 
//				/*handling*/ 
//			} 
//		}
//		void run()
//		{
//			fooA();
//		}
//	}
//
//	struct CStateMode
//	{
//	private:
//		enum State
//		{
//			Unset = 0,
//			SomeError
//		};
//
//	public:
//		static void fooK() 
//		{
//			state = State::SomeError;
//		}
//		static void fooJ()
//		{
//			fooK(); 
//			if (state) { return; }
//			std::cout << "else(state)" << std::endl;
//			/*doSomething*/
//		}
//		static void fooI()
//		{
//			fooJ(); 
//			if (state) { return; }
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooH()
//		{
//			fooI(); 
//			if (state)
//			{
//				return;
//			}
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooG()
//		{
//			fooH(); 
//			if (state) { return; }
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooF()
//		{
//			fooG(); 
//			if (state) { return; }
//			/*doSomething*/
//		}
//		static void fooE()
//		{
//			fooF(); 
//			if (state) { return; }
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooD()
//		{
//			fooE(); 
//			if (state) { return; }
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooC()
//		{
//			fooD(); 
//			if (state) { return; }
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooB() 
//		{ 
//			fooC(); 
//			if (state) { return; }
//			/*doSomething*/
//			std::cout << "else(state)" << std::endl;
//		}
//		static void fooA() 
//		{ 
//			fooB(); 
//			if (state)
//			{ 
//				state = State::Unset; 
//				/*handling*/ 
//			} 
//		}
//
//	private:
//		static State state;
//	};
//
//	namespace StateMode
//	{
//		void run()
//		{
//			CStateMode::fooA();
//		}
//	}
//
//	CStateMode::State CStateMode::state = CStateMode::State::Unset;
//
//	std::chrono::nanoseconds zero()
//	{
//		auto time = std::chrono::system_clock::now();
//		return std::chrono::duration_cast<std::chrono::nanoseconds>(time - time);
//	}
//
//	enum class TCase
//	{
//		Exception, 
//		State
//	};
//
//	void runtest(Tester::Loging& log, const Tester::Settings& settings, Tester::Results& result, const TCase tCase)
//	{
//		std::string tCaseName;
//		std::function<void(void)> testfunc;
//		if (tCase == TCase::Exception)
//		{
//			tCaseName = "Exception";
//			testfunc = ExceptionMode::fooA;
//		}
//		else
//		{
//			tCaseName = "State";
//			testfunc = StateMode::run;
//		}
//
//		log << std::endl;
//		const int testCount = settings.getTestCount();
//		const int iterCount = settings.getIterCount();
//		for (int tindex = 0; tindex < testCount; ++tindex)
//		{
//			for (int index = 0; index < iterCount; ++index)
//			{
//				std::chrono::time_point<std::chrono::system_clock> start, end;
//
//				start = std::chrono::system_clock::now();
//				testfunc();
//				end = std::chrono::system_clock::now();
//
//				result.get(tindex).exception += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start) - 
//					settings.getOverhead());
//			}
//			log << "Duration<" << tCaseName << "> :: " << result.get(tindex).exception.count() / iterCount << "ns" << std::endl;
//		}
//	}
//
//	void calculate(Tester::Loging& log, const Tester::Settings& settings, Tester::Results& result)
//	{
//		log << std::endl;
//
//		const int testCount = settings.getTestCount();
//		std::vector<double> XTimesFaster(testCount);
//		for (int tindex = 0; tindex < testCount; ++tindex)
//		{
//			XTimesFaster[tindex] = ((result.get(tindex).exception.count()) / (result.get(tindex).state.count()));
//			log << "\"State\" is " << XTimesFaster[tindex] << " times faster than \"Exception\"" << std::endl;
//		}
//
//		log << std::endl;
//
//		log << "Max[time-faster] :: " << *std::max_element(XTimesFaster.begin(), XTimesFaster.end()) << std::endl;
//		log << "Min[time-faster] :: " << *std::min_element(XTimesFaster.begin(), XTimesFaster.end()) << std::endl;
//		log << "Mid[time-faster] :: " << std::accumulate(XTimesFaster.begin(), XTimesFaster.end(), 0) / testCount << std::endl;
//	}
//
//	namespace Empty
//	{
//		export void run()
//		{
//			Tester::Loging   log("D:\\Projects\\Tests\\Results\\ExceptionState\\Empty.txt");
//			Tester::Settings settings(10, 1000);
//			Tester::Results  result(settings);
//
//			log << "Test Exception/State";
//			log << "Test Count      = " << settings.getTestCount() << std::endl;
//			log << "Iteration Count = " << settings.getIterCount() << std::endl;
//			log << "Overhead        = " << settings.getOverhead().count() << std::endl;
//
//			runtest(log, settings, result, TCase::Exception);
//			runtest(log, settings, result, TCase::State);
//
//			calculate(log, settings, result);
//			std::cout << std::endl;
//		}
//	}
//}
