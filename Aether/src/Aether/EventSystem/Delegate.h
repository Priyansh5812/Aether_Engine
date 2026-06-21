#pragma once
#include <memory>
namespace Aether
{
	namespace EventSystems
	{	
		// Type info ... Done
		// Param List
		// Obj ref
		// Method Reference
		
		//template<typename Signature>
		//struct Delegate;


		template<typename ReturnType , typename... Params>
		struct Delegate
		{	
		
		public:
			template<ReturnType(*method)(Params...)>
			void Bind()
			{	
				_function = &Delegate<ReturnType , Params...>::template MethodStub<method>;
			}

			template<typename T , ReturnType(T::*method)(Params...)>
			void Bind(T* obj)
			{	
				this->obj = obj;
				_function = &Delegate<ReturnType, Params...>::template MemberMethodStub<T , method>;
			}


			ReturnType Invoke(Params... params)
			{	
				if (this->_function)
				{	
					if constexpr (std::is_void_v<ReturnType>)
					{
						(this->*_function)(params...);
						return;
					}

					return (this->*_function)(params...);
				}

				throw std::runtime_error("Delegate is NULL");
			}

			template<ReturnType(* method)(Params...)>
			bool CheckEquality()
			{
				return _function == &Delegate<ReturnType, Params...>::template MethodStub<method>;
			}

			template<typename T, ReturnType(T::* method)(Params...)>
			bool CheckEquality(T* obj)
			{
				return this->obj == obj && _function == &Delegate<ReturnType, Params...>::template MemberMethodStub<T, method>;			
			}

		private:

			using StubSignature =
				ReturnType(Delegate<ReturnType, Params...>::*)(Params...);

			using MethodCheckSignature = bool (Delegate<ReturnType, Params...>::*)();

			
			template<ReturnType(*method)(Params...)>
			ReturnType MethodStub(Params... params)
			{
				return method(params...);
			}

			template<typename T, ReturnType(T::*method)(Params...)>
			ReturnType MemberMethodStub(Params... params)
			{	
				

				return (static_cast<T*>(obj)->*method)(params...);
			}


		private:

			void* obj = nullptr;
			StubSignature _function = nullptr;
			
		};
	}
}