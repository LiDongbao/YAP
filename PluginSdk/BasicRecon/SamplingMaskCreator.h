#pragma once

#ifndef SamplingMaskCreator_h__20160814
#define SamplingMaskCreator_h__20160814

#include "Interface/Implement/ProcessorImpl.h"
#include "Interface/Client/DataHelper.h"
#include <vector>
#include <fftw3.h>
#include <complex>

namespace Yap
{
	class SamplingMaskCreator :
		public ProcessorImpl
	{
	public:
		SamplingMaskCreator();
		virtual ~SamplingMaskCreator();

		virtual IProcessor * Clone() override;
		virtual bool Input(const wchar_t * name, IData * data) override;

	protected:
		std::vector<unsigned int> GetRandomSamplingPattern(unsigned int row_count,
			float pow, float sample_percent, float radius);
		std::vector<unsigned int> GetEqualSamplingPattern(unsigned int height, unsigned int acs, unsigned int rate);

		// Pdf ���������д����䡣
		std::vector<float> GeneratePdf(unsigned int row_count, float p, float sample_percent, float radius);

		std::vector<float> LineSpace(float begin, float end, unsigned int count);

		std::vector<float> GenerateRandomMask(unsigned int width, unsigned int height, float pow, float sample_percent, float radius);
		std::vector<float> GenerateEqualMask(unsigned int width, unsigned int height, unsigned int acs, unsigned int rate);

	private:
		unsigned int _try_count;
		unsigned int _tolerance;
	};
}

#endif // SamplingMaskCreator_h__


