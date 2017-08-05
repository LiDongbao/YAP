
#include "Interface/Implement/ProcessorImpl.h"

namespace Yap
{
	class SubSampling :
		public ProcessorImpl
	{
	public:
		SubSampling();

		virtual IProcessor * Clone() override;
		virtual bool Input(const wchar_t * port, IData * data) override;
	protected:
		~SubSampling();

		void GetSubSampledData(std::complex<float> * input_data, float * mask, std::complex<float> * output_data, unsigned int width, unsigned int height);

	private:
		SmartPtr<IData> _mask;

	};
}