#pragma once
#include "Delegate.h"
#include "vector"
namespace Aether
{
	namespace EventSystems
	{

		template<typename... Params>
		class Action
		{
		public:

			Action(size_t&& reserve = 8)
			{
				_invocations.reserve(reserve);
			}

			Action(const Action&) = delete;


			template<void(*method)(Params...)>
			void AddListener()
			{
				Delegate<void, Params...> del;
				del.Bind<method>();
				_invocations.push_back(del);
			}

			template<typename T, void(T::*method)(Params...)>
			void AddListener(T* obj)
			{
				Delegate<void, Params...> del;
				del.Bind<T, method>(obj);
				_invocations.push_back(del);
			}


			template<void(*method)(Params...)>
			void RemoveListener()
			{	
				if (method == nullptr)
				{
					EDebug::Log("Null Check Prevention in Static  function call");
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

			template<typename T , void(T::* method)(Params...)>
			void RemoveListener(T* obj)
			{	
				if (obj == nullptr || method == nullptr)
				{
					EDebug::Log("Null Check Prevention in Member function call");
				}

				for (size_t i = _invocations.size() - 1; i >= 0; i--)
				{
					if (_invocations[i].CheckEquality<T , method>(obj))
					{
						_invocations.erase(_invocations.begin() + i);
						return;
					}
				}
			}

			void Invoke(Params... params)
			{
				for (auto& i : _invocations)
				{
					i.Invoke(params...);
				}
			}



		private:
			std::vector<Delegate<void, Params...>> _invocations;




		};

	}


}