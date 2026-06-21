#pragma once
#pragma once
#include "Delegate.h"
#include "vector"
namespace Aether
{
	namespace EventSystems
	{
		template<typename ReturnType , typename = std::enable_if_t<!std::is_void_v<ReturnType>> , typename... Params>
		class Func
		{
		public:

			Func(size_t&& reserve = 8)
			{
				_invocations.reserve(reserve);
			}
			Func(const Func&) = delete;


			template<ReturnType(*method)(Params...)>
			void AddListener()
			{	
				if (!method)
					return;
				Delegate<ReturnType, Params...> del;
				del.Bind<method>();
				_invocations.push_back(del);
			}

			template<typename T, ReturnType(T::* method)(Params...)>
			void AddListener(T* obj)
			{	
				if (!obj || !method)
					return;

				Delegate<ReturnType, Params...> del;
				del.Bind<T, method>(obj);
				_invocations.push_back(del);
			}


			template<ReturnType(*method)(Params...)>
			void RemoveListener()
			{
				if (method == nullptr)
				{
					EDebug::Log("Null Check Prevention in Static function call");
				}

				for (size_t i = _invocations.size() - 1; i >= 0; i--)
				{
					if (_invocations[i].CheckEquality<method>())
					{
						_invocations.erase(_invocations.begin() + i);
						return;
					}
				}
			}

			template<typename T, ReturnType(T::* method)(Params...)>
			void RemoveListener(T* obj)
			{
				if (obj == nullptr || method == nullptr)
				{
					EDebug::Log("Null Check Prevention in Member function call");
				}

				for (size_t i = _invocations.size() - 1; i >= 0; i--)
				{
					if (_invocations[i].CheckEquality<T, method>(obj))
					{
						_invocations.erase(_invocations.begin() + i);
						return;
					}
				}
			}

			void RemoveAllListeners()
			{
				this->_invocations.erase(_invocations.begin(), _invocations.end());
			}

			ReturnType Invoke(Params... params)
			{	
				ReturnType res;
				for (auto& i : _invocations)
				{
					res = i.Invoke(params...);
				}

				return res;
			}



		private:
			std::vector<Delegate<ReturnType, Params...>> _invocations;
		};

	}


}