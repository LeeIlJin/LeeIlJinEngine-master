#pragma once


namespace MemoryFunction
{
	//     * Calculate Padding
	//     = Returns the size of the padding in which the next address will remain aligned by the alignment size.
	const unsigned int CalculatePadding(const unsigned int& baseAddress, const unsigned int& alignment);

	//     * Calculate Padding Size With Header Size
	//     = Returns the size of the padding with header size (empty space + header space)
	const unsigned int CalculatePaddingWithHeader(const unsigned int& baseAddress, const unsigned int& alignment, const unsigned int& headerSize);

}
