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
					return (this->*_function)(params...);
				}

				throw std::runtime_error("Delegate is NULL");
			}

		private:

			using StubSignature =
				ReturnType(Delegate<ReturnType, Params...>::*)(Params...);
			
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