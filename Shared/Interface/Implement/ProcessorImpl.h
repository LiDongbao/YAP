#ifndef ProcessorImp_h__20160813
#define ProcessorImp_h__20160813

#pragma once
#include "Interface/IProcessor.h"

#include <map>
#include <string>
#include <memory>
#include "Utilities/macros.h"
#include "interface/Implement/DataObject.h"
#include "Interface/Implement/SharedObjectImpl.h"
#include "Interface/Implement/ContainerImpl.h"
#include "Interface/IProperty.h"
#include "Interface/IMemory.h"
#include "variableManager.h"

namespace Yap
{
	class VariableManager;

	struct Anchor
	{
		IProcessor * processor;
		std::wstring port;
		Anchor(IProcessor* processor_, const wchar_t * in_port_) : processor(processor_), port(in_port_) {}
	};

	class ProcessorImpl :
		public IProcessor, 
		public SharedObjectImpl
	{
	public:
		explicit ProcessorImpl(const wchar_t * class_id);
		ProcessorImpl(const ProcessorImpl& rhs);

		virtual IPortContainer * Inputs() override;
		virtual IPortContainer * Outputs() override;

		virtual const wchar_t * GetClassId() override;
		virtual void SetClassId(const wchar_t * id) override;
		virtual const wchar_t * GetInstanceId() override;
		virtual void SetInstanceId(const wchar_t * instance_id) override;

		virtual IPropertyContainer * GetProperties() override;

		virtual bool LinkProperty(const wchar_t * property_id, const wchar_t * param_id) override;
		virtual bool UpdateProperties(IPropertyContainer * params) override;

		virtual bool Link(const wchar_t * output, IProcessor * next, const wchar_t * next_input) override;

	protected:
		/// Protect destructor to prevent this object to be created on stack.
		~ProcessorImpl();

		bool CanLink(const wchar_t * source_output_name, IProcessor * next, const wchar_t * next_input_name);
		bool OutportLinked(const wchar_t * out_port_name) const;

		bool AddInput(const wchar_t * name, unsigned int dimensions, int data_type);
		bool AddOutput(const wchar_t * name, unsigned int dimensions, int data_type);

		bool Feed(const wchar_t * name, IData * data);

		SmartPtr<ContainerImpl<IPort>> _input;
		SmartPtr<ContainerImpl<IPort>> _output;

		std::multimap<std::wstring, Anchor> _links;
		std::map<std::wstring, std::wstring> _property_links;

		std::wstring _instance_id;
		std::wstring _class_id;

		std::shared_ptr<VariableManager> _properties;
		IPropertyContainer * _system_variables;

	private:
		ProcessorImpl(const ProcessorImpl&& rhs);
		const ProcessorImpl& operator = (ProcessorImpl&& rhs);
		const ProcessorImpl& operator = (const ProcessorImpl& rhs);
	};
};

#endif // ProcessorImp_h__
