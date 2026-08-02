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
				DestroyAnyLambdaClosures();
				_function = &Delegate<ReturnType, Params...>::template MethodStub<method>;
			}

			template<typename T, ReturnType(T::* method)(Params...)>
			void Bind(T* obj)
			{	
				DestroyAnyLambdaClosures();
				this->obj = obj;
				_function = &Delegate<ReturnType, Params...>::template MemberMethodStub<T, method>;
			}

#pragma region Lambda Creation And Destruction
			template<typename Lambda>
			void Bind(const Lambda& lambdaObj)
			{	
				DestroyAnyLambdaClosures();
				LambdaBindInternal<Lambda, &Lambda::operator()>(new Lambda(lambdaObj));
			}

			template<typename T, ReturnType(T::* method)(Params...) const>
			void LambdaBindInternal(T* obj)
			{
				this->obj = obj;
				_function = &Delegate<ReturnType, Params...>::template LambdaMethodStub<T, method>;
				__lambdaClosureDestruction = &Delegate<ReturnType, Params...>::template LambdaDestructionStub<T>;
			}

			void DestroyAnyLambdaClosures()
			{
				if (__lambdaClosureDestruction)
				{
					(this->*__lambdaClosureDestruction)();
					__lambdaClosureDestruction = nullptr;
					obj = nullptr;
					_function = nullptr;
				}
			}
#pragma endregion


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

			template<typename T, ReturnType(T::*method)(Params...) const>
			ReturnType LambdaMethodStub(Params... params)
			{	
				return (static_cast<T*>(obj)->*method)(params...);
			}

			template<typename T>
			void LambdaDestructionStub()
			{
				delete static_cast<T*>(obj);
			}

		public:
			~Delegate()
			{
				DestroyAnyLambdaClosures();
			}

		private:

			void* obj = nullptr;
			StubSignature _function = nullptr;
			void (Delegate<ReturnType, Params...>::* __lambdaClosureDestruction)()  = nullptr;
		};
	}
}