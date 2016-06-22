#include "stdafx.h"
#include "DataHelper.h"

using namespace Yap;

DataType CDataHelper::GetDataType()
{
	return _data_interface.GetDataType();
}

unsigned int CDataHelper::GetDimensionCount()
{
	auto dimension = _data_interface.GetDimension();

	return (dimension != nullptr) ? dimension->GetDimensionCount() : 0;
}

unsigned int CDataHelper::GetWidth()
{
	auto dimension = _data_interface.GetDimension();
	DimensionType dimension_type;
	unsigned int start, length;
	dimension->GetDimensionInfo(0, dimension_type, start, length);

	return length;
}

unsigned int CDataHelper::GetHeight()
{
	auto dimension = _data_interface.GetDimension();
	DimensionType dimension_type;
	unsigned int start, length;
	dimension->GetDimensionInfo(1, dimension_type, start, length);

	return length;
}

void * CDataHelper::GetData()
{
	return _data_interface.GetData();
}

size_t Yap::CDataHelper::GetDataSize() const
{
	size_t count = 1;
	auto dimension = _data_interface.GetDimension();
	DimensionType dimension_type;
	unsigned int start, length;

	for (size_t i = 0; i < dimension->GetDimensionCount(); ++i)
	{
		dimension->GetDimensionInfo(i, dimension_type, start, length);
		count *= length;
	}

	return count;
}

