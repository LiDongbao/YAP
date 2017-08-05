#pragma once


#ifndef ProcessorImpl_h_20160830
#define ProcessorImpl_h_20160830

#include "Interface/IContainer.h"
#include "Interface/IMemory.h"

#include <map>
#include <string>

namespace Yap
{
	template <typename TYPE>
	class ContainerImpl :
		public IContainer<TYPE>, 
		public SharedObjectImpl,
		public IClonable
	{
		template <typename TYPE>
		class Iterator : 
			public IIterator<TYPE>,
			public IDynamicObject
		{
			explicit Iterator(ContainerImpl& container) : _container(container)
			{
			}

			virtual ~Iterator()
			{
			}

			// Inherited via IIterator
			virtual TYPE * GetFirst() override
			{
				_current = _container._elements.begin();

				return  (_current != _container._elements.end()) ? _current->second.get() : nullptr;

			}

			virtual TYPE * GetNext() override
			{
				return  (_current != _container._elements.end() && 
						 ++_current != _container._elements.end()) ?
					_current->second.get() : nullptr;

			}

			virtual void DeleteThis() override
			{
				delete this;
			}

			ContainerImpl& _container;
			typename std::map<std::wstring, SmartPtr<TYPE>>::iterator _current;

			
			friend class ContainerImpl;
		};

	public:
		ContainerImpl() {}

		IClonable * Clone() const override
		{
			auto cloned = new (std::nothrow) ContainerImpl;
			if (cloned == nullptr)
				return nullptr;

			for (auto element : _elements)
			{
				auto clonable = dynamic_cast<IClonable*>(element.second.get());
				if (clonable != nullptr)
				{
					auto cloned_element = dynamic_cast<TYPE *>(clonable->Clone());
					if (cloned_element != nullptr)
					{
						cloned->Add(element.first.c_str(), cloned_element);
					}
				}
			}

			return cloned;
		}

		virtual TYPE * Find(const wchar_t * name) override
		{
			auto iter = _elements.find(name);
			return  (iter != _elements.end()) ? iter->second.get() : nullptr;

		}

		virtual IIterator<TYPE> * GetIterator() override
		{
			return new (std::nothrow) Iterator<TYPE>(*this);
		}

		virtual bool Add(const wchar_t * name, TYPE * element) override
		{
			if (element == nullptr)
				return false;

			_elements.insert(std::make_pair(std::wstring(name), YapShared(element)));

			return true;
		}

	private:
		// protect the destructor to ensure the object can only be dynamically allocated
		~ContainerImpl() {}

		std::map<std::wstring, SmartPtr<TYPE>> _elements;
	};
}

#endif // ProcessorImpl_h_20160830
