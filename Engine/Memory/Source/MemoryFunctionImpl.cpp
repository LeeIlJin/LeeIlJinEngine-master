#include "MemoryFunction.h"

namespace MemoryFunction
{
	//     * Calculate Padding
	//     = Returns the size of the padding in which the next address will remain aligned by the alignment size.
	const unsigned int CalculatePadding(const unsigned int& baseAddress, const unsigned int& alignment)
	{
		//     * Get Next Index By Alignment Size
		//     ! bassAddress <Last Allocated Address + Last Allocated Size>
		//     ! alignment <Current Allocating Alignment Size>
		//     ! (unsigned) 1 <It Mean "Next">
		//     = multiplier = <Next Address Index By Alignment Size>
		const unsigned int multiplier = (baseAddress / alignment) + (unsigned)1;
		//

		//     * Get Next Address From Multiplier(Next Address Index By Alignment Size)
		//     ! multiplier <Next Address Index By Alignment Size>
		//     ! alignment <Current Allocating Alignment Size>
		//     = alignedAddress = <Next Address>
		const unsigned int alignedAddress = multiplier * alignment;
		//

		//     * Get Padding By Alignment Size
		//     ! alignedAddress <Next Address>
		//     ! baseAddress <Last Allocated Address + Last Allocated Size>
		//     = padding = <Empty Space>
		const unsigned int padding = alignedAddress - baseAddress;
		//

		return padding;
	}

	//     * Calculate Padding Size With Header Size
	//     = Returns the size of the padding with header size (empty space + header space)
	const unsigned int CalculatePaddingWithHeader(const unsigned int& baseAddress, const unsigned int& alignment, const unsigned int& headerSize)
	{
		//     * Get Padding Size (Empty Space)
		unsigned int padding = CalculatePadding(baseAddress, alignment);
		unsigned int neededSpace = headerSize;

		//     * If (Padding Size < Header Size)
		//     * Expand Padding Size
		if (padding < neededSpace)
		{
			neededSpace -= padding;

			if (neededSpace % alignment >(unsigned)0)
				padding += alignment * ((unsigned)1 + (neededSpace / alignment));
			else
				padding += alignment * (neededSpace / alignment);
		}
		return padding;
	}
}
