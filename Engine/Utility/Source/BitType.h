#pragma once


//		BIT Type
//		8 Bit	: 1 Byte
//		16 Bit	: 2 Byte 
//		32 Bit	: 4 Byte

///////////////////////////////////////////////////////////////////////////////



namespace my_type
{

#define _BIT_C(index) bool bit_##index : 1
	//
#define _BIT_GET(index) case (index-1) : return bit_##index
	//
#define _BIT_SET(index,b) case (index-1) : bit_##index = b
	//

	//

	typedef struct BIT_8
	{
		BIT_8() :data(0) {}
		BIT_8(unsigned int init_data) :data((unsigned char)init_data) {}

	public:
		union
		{
			unsigned char data;
			struct
			{
				_BIT_C(1);
				_BIT_C(2);
				_BIT_C(3);
				_BIT_C(4);
				_BIT_C(5);
				_BIT_C(6);
				_BIT_C(7);
				_BIT_C(8);
			};

			struct
			{
				unsigned short bit2_1 : 2;
				unsigned short bit2_2 : 2;
				unsigned short bit2_3 : 2;
				unsigned short bit2_4 : 2;
			};

			struct
			{
				unsigned short bit4_1 : 4;
				unsigned short bit4_2 : 4;
			};
		};

		bool bit_get(unsigned int index)
		{
			switch (index)
			{
				_BIT_GET(1);
				_BIT_GET(2);
				_BIT_GET(3);
				_BIT_GET(4);
				_BIT_GET(5);
				_BIT_GET(6);
				_BIT_GET(7);
				_BIT_GET(8);
			}

			return false;
		}

		void bit_set(unsigned int index, const bool& b)
		{
			switch (index)
			{
				_BIT_SET(1, b);
				_BIT_SET(2, b);
				_BIT_SET(3, b);
				_BIT_SET(4, b);
				_BIT_SET(5, b);
				_BIT_SET(6, b);
				_BIT_SET(7, b);
				_BIT_SET(8, b);
			}
		}

		inline bool operator[] (unsigned int index)
		{
			return bit_get(index);
		}

		operator unsigned char()
		{
			return (unsigned char)data;
		}
		operator unsigned short()
		{
			return (unsigned short)data;
		}
		operator unsigned int()
		{
			return (unsigned int)data;
		}

	}BYTE_1;

	typedef struct BIT_16
	{
		BIT_16() :data(0) {}
		BIT_16(unsigned int init_data) :data((unsigned short)init_data) {}

	public:
		union
		{
			unsigned short data;
			struct
			{
				_BIT_C(1);
				_BIT_C(2);
				_BIT_C(3);
				_BIT_C(4);
				_BIT_C(5);
				_BIT_C(6);
				_BIT_C(7);
				_BIT_C(8);

				_BIT_C(9);
				_BIT_C(10);
				_BIT_C(11);
				_BIT_C(12);
				_BIT_C(13);
				_BIT_C(14);
				_BIT_C(15);
				_BIT_C(16);
			};

			struct
			{
				unsigned short bit2_1 : 2;
				unsigned short bit2_2 : 2;
				unsigned short bit2_3 : 2;
				unsigned short bit2_4 : 2;

				unsigned short bit2_5 : 2;
				unsigned short bit2_6 : 2;
				unsigned short bit2_7 : 2;
				unsigned short bit2_8 : 2;
			};

			struct
			{
				unsigned short bit4_1 : 4;
				unsigned short bit4_2 : 4;
				unsigned short bit4_3 : 4;
				unsigned short bit4_4 : 4;
			};

			struct
			{
				unsigned short bit8_1 : 8;
				unsigned short bit8_2 : 8;
			};
		};

		bool bit_get(unsigned int index)
		{
			switch (index)
			{
				_BIT_GET(1);
				_BIT_GET(2);
				_BIT_GET(3);
				_BIT_GET(4);
				_BIT_GET(5);
				_BIT_GET(6);
				_BIT_GET(7);
				_BIT_GET(8);

				_BIT_GET(9);
				_BIT_GET(10);
				_BIT_GET(11);
				_BIT_GET(12);
				_BIT_GET(13);
				_BIT_GET(14);
				_BIT_GET(15);
				_BIT_GET(16);
			}

			return false;
		}

		void bit_set(unsigned int index, const bool& b)
		{
			switch (index)
			{
				_BIT_SET(1, b);
				_BIT_SET(2, b);
				_BIT_SET(3, b);
				_BIT_SET(4, b);
				_BIT_SET(5, b);
				_BIT_SET(6, b);
				_BIT_SET(7, b);
				_BIT_SET(8, b);

				_BIT_SET(9, b);
				_BIT_SET(10, b);
				_BIT_SET(11, b);
				_BIT_SET(12, b);
				_BIT_SET(13, b);
				_BIT_SET(14, b);
				_BIT_SET(15, b);
				_BIT_SET(16, b);
			}
		}

		inline bool operator[] (unsigned int index)
		{
			return bit_get(index);
		}

		operator unsigned char()
		{
			return (unsigned char)data;
		}
		operator unsigned short()
		{
			return (unsigned short)data;
		}
		operator unsigned int()
		{
			return (unsigned int)data;
		}

	}BYTE_2;

	typedef struct BIT_32
	{
		BIT_32() :data(0) {}
		BIT_32(unsigned int init_data) :data((unsigned int)init_data) {}

	public:
		union
		{
			unsigned int data;
			struct
			{
				_BIT_C(1);
				_BIT_C(2);
				_BIT_C(3);
				_BIT_C(4);
				_BIT_C(5);
				_BIT_C(6);
				_BIT_C(7);
				_BIT_C(8);

				_BIT_C(9);
				_BIT_C(10);
				_BIT_C(11);
				_BIT_C(12);
				_BIT_C(13);
				_BIT_C(14);
				_BIT_C(15);
				_BIT_C(16);

				_BIT_C(17);
				_BIT_C(18);
				_BIT_C(19);
				_BIT_C(20);
				_BIT_C(21);
				_BIT_C(22);
				_BIT_C(23);
				_BIT_C(24);

				_BIT_C(25);
				_BIT_C(26);
				_BIT_C(27);
				_BIT_C(28);
				_BIT_C(29);
				_BIT_C(30);
				_BIT_C(31);
				_BIT_C(32);
			};

			struct
			{
				unsigned short bit2_1 : 2;
				unsigned short bit2_2 : 2;
				unsigned short bit2_3 : 2;
				unsigned short bit2_4 : 2;

				unsigned short bit2_5 : 2;
				unsigned short bit2_6 : 2;
				unsigned short bit2_7 : 2;
				unsigned short bit2_8 : 2;

				unsigned short bit2_9 : 2;
				unsigned short bit2_10 : 2;
				unsigned short bit2_11 : 2;
				unsigned short bit2_12 : 2;

				unsigned short bit2_13 : 2;
				unsigned short bit2_14 : 2;
				unsigned short bit2_15 : 2;
				unsigned short bit2_16 : 2;
			};

			struct
			{
				unsigned short bit4_1 : 4;
				unsigned short bit4_2 : 4;
				unsigned short bit4_3 : 4;
				unsigned short bit4_4 : 4;

				unsigned short bit4_5 : 4;
				unsigned short bit4_6 : 4;
				unsigned short bit4_7 : 4;
				unsigned short bit4_8 : 4;
			};

			struct
			{
				unsigned short bit8_1 : 8;
				unsigned short bit8_2 : 8;
				unsigned short bit8_3 : 8;
				unsigned short bit8_4 : 8;
			};

			struct
			{
				unsigned short bit16_1;
				unsigned short bit16_2;
			};
		};

		bool bit_get(unsigned int index)
		{
			switch (index)
			{
				_BIT_GET(1);
				_BIT_GET(2);
				_BIT_GET(3);
				_BIT_GET(4);
				_BIT_GET(5);
				_BIT_GET(6);
				_BIT_GET(7);
				_BIT_GET(8);

				_BIT_GET(9);
				_BIT_GET(10);
				_BIT_GET(11);
				_BIT_GET(12);
				_BIT_GET(13);
				_BIT_GET(14);
				_BIT_GET(15);
				_BIT_GET(16);

				_BIT_GET(17);
				_BIT_GET(18);
				_BIT_GET(19);
				_BIT_GET(20);
				_BIT_GET(21);
				_BIT_GET(22);
				_BIT_GET(23);
				_BIT_GET(24);

				_BIT_GET(25);
				_BIT_GET(26);
				_BIT_GET(27);
				_BIT_GET(28);
				_BIT_GET(29);
				_BIT_GET(30);
				_BIT_GET(31);
				_BIT_GET(32);
			}

			return false;
		}

		void bit_set(unsigned int index, const bool& b)
		{
			switch (index)
			{
				_BIT_SET(1, b);
				_BIT_SET(2, b);
				_BIT_SET(3, b);
				_BIT_SET(4, b);
				_BIT_SET(5, b);
				_BIT_SET(6, b);
				_BIT_SET(7, b);
				_BIT_SET(8, b);

				_BIT_SET(9, b);
				_BIT_SET(10, b);
				_BIT_SET(11, b);
				_BIT_SET(12, b);
				_BIT_SET(13, b);
				_BIT_SET(14, b);
				_BIT_SET(15, b);
				_BIT_SET(16, b);

				_BIT_SET(17, b);
				_BIT_SET(18, b);
				_BIT_SET(19, b);
				_BIT_SET(20, b);
				_BIT_SET(21, b);
				_BIT_SET(22, b);
				_BIT_SET(23, b);
				_BIT_SET(24, b);

				_BIT_SET(25, b);
				_BIT_SET(26, b);
				_BIT_SET(27, b);
				_BIT_SET(28, b);
				_BIT_SET(29, b);
				_BIT_SET(30, b);
				_BIT_SET(31, b);
				_BIT_SET(32, b);
			}
		}

		inline bool operator[] (unsigned int index)
		{
			return bit_get(index);
		}

		operator unsigned char()
		{
			return (unsigned char)data;
		}
		operator unsigned short()
		{
			return (unsigned short)data;
		}
		operator unsigned int()
		{
			return (unsigned int)data;
		}

	}BYTE_4;

#undef _BIT_C
#undef _BIT_SET
#undef _BIT_GET
}


using namespace my_type;

//