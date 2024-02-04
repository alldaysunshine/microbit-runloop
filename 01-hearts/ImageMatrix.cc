#import "ImageMatrix.h"


#define BITS_PER_PIXEL 1

/*
 * Colums are rounded to a multiple of a byte
 */

#define BITMAP_FONT_WIDTH 5
#define BITMAP_FONT_HEIGHT 5
#define BITMAP_FONT_ASCII_START 32
#define BITMAP_FONT_ASCII_END 126
#define BITMAP_FONT_SPACE 1

ImageMatrix::ImageMatrix(unsigned int _columns, 
	unsigned int _rows, std::vector<unsigned char> _matrix) {
	columns = _columns; 
	rows = _rows; 
	
	bytesPerRow = BITS_PER_PIXEL * ((columns + 8 - 1) / 8);
	
	matrix = _matrix; 
}

ImageMatrix::ImageMatrix(unsigned char character) {
	columns = BITMAP_FONT_WIDTH; 
	rows = BITMAP_FONT_HEIGHT; 
	
	bytesPerRow = BITS_PER_PIXEL * ((columns + 8 - 1) / 8);

	matrix.resize(BITMAP_FONT_HEIGHT * bytesPerRow);

    auto start = font + (character-BITMAP_FONT_ASCII_START) * ((1 + (BITMAP_FONT_WIDTH / 8)) * BITMAP_FONT_HEIGHT);
    
	matrix.assign(start, start + BITMAP_FONT_HEIGHT);
}

ImageMatrix::ImageMatrix(std::string str) {
	columns = (BITMAP_FONT_WIDTH + BITMAP_FONT_SPACE) * str.length(); 
	rows = BITMAP_FONT_HEIGHT; 
	
	bytesPerRow = BITS_PER_PIXEL * ((columns + 8 - 1) / 8);

	matrix.resize(BITMAP_FONT_HEIGHT * bytesPerRow);
	
	for (int characterIndex = 0; characterIndex < str.length(); characterIndex++) {
		unsigned char character = str.at(characterIndex);
		
		for (int rowIndex = 0; rowIndex < BITMAP_FONT_HEIGHT; rowIndex++) {
			auto sourceByteIndex = font + (character-BITMAP_FONT_ASCII_START) * ((1 + (BITMAP_FONT_WIDTH / 8)) * BITMAP_FONT_HEIGHT);
			auto sourceByteWithRowIndex = sourceByteIndex + rowIndex; 
			
			unsigned char sourceByte = *(sourceByteWithRowIndex) & 0x1f;

			for (int colIndex = 0; colIndex < BITMAP_FONT_WIDTH; colIndex++) {
				unsigned int sourceBitPosition = BITMAP_FONT_WIDTH - 1 - colIndex; 
				
				unsigned int destBytePosition = rowIndex * bytesPerRow + (characterIndex * (BITMAP_FONT_WIDTH + BITMAP_FONT_SPACE) + colIndex) / 8; 
				unsigned int destBitPosition = 7 - (characterIndex * (BITMAP_FONT_WIDTH + BITMAP_FONT_SPACE) + colIndex) % 8; 
				
				unsigned char b = matrix.at(destBytePosition);
				
				unsigned int flag = ((sourceByte >> sourceBitPosition)  & 0x01);

				b = (b & ~(1 << destBitPosition)) | (flag << destBitPosition);

				matrix.at(destBytePosition) = b;
			}
		}
	}
}

ImageMatrix::ImageMatrix() {
	columns = 54; 
	rows = 5; 
	
	bytesPerRow = 7; 
	
	matrix.resize(35);
	
	matrix.at(0 + 0 * bytesPerRow) = 0b0;
	matrix.at(0 + 1 * bytesPerRow) = 0b0;
	matrix.at(0 + 2 * bytesPerRow) = 0b0;
	matrix.at(0 + 3 * bytesPerRow) = 0b0;
	matrix.at(0 + 4 * bytesPerRow) = 0b1;
	
	matrix.at(1 + 0 * bytesPerRow) = 0b11;
	matrix.at(1 + 1 * bytesPerRow) = 0b11;
	matrix.at(1 + 2 * bytesPerRow) = 0b11;
	matrix.at(1 + 3 * bytesPerRow) = 0b11;
	matrix.at(1 + 4 * bytesPerRow) = 0b11;
	
	matrix.at(2 + 0 * bytesPerRow) = 0b111;
	matrix.at(2 + 1 * bytesPerRow) = 0b111;
	matrix.at(2 + 2 * bytesPerRow) = 0b0;
	matrix.at(2 + 3 * bytesPerRow) = 0b111;
	matrix.at(2 + 4 * bytesPerRow) = 0b111;
	
	matrix.at(3 + 0 * bytesPerRow) = 0b11111;
	matrix.at(3 + 1 * bytesPerRow) = 0b11111;
	matrix.at(3 + 2 * bytesPerRow) = 0b11111;
	matrix.at(3 + 3 * bytesPerRow) = 0b11111;
	matrix.at(3 + 4 * bytesPerRow) = 0b11111;
	
	matrix.at(4 + 0 * bytesPerRow) = 0b1111111;
	matrix.at(4 + 1 * bytesPerRow) = 0b1111111;
	matrix.at(4 + 2 * bytesPerRow) = 0b0;
	matrix.at(4 + 3 * bytesPerRow) = 0b1111111;
	matrix.at(4 + 4 * bytesPerRow) = 0b1111111;

	matrix.at(5 + 0 * bytesPerRow) = 0b1111111;
	matrix.at(5 + 1 * bytesPerRow) = 0b1111111;
	matrix.at(5 + 2 * bytesPerRow) = 0b0;
	matrix.at(5 + 3 * bytesPerRow) = 0b0;
	matrix.at(5 + 4 * bytesPerRow) = 0b1111111;

	matrix.at(6 + 0 * bytesPerRow) = 0b1111111;
	matrix.at(6 + 1 * bytesPerRow) = 0b000000;
	matrix.at(6 + 2 * bytesPerRow) = 0b0;
	matrix.at(6 + 3 * bytesPerRow) = 0b1111111;
	matrix.at(6 + 4 * bytesPerRow) = 0b1111111;
	
}

const unsigned char ImageMatrix::font[475] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x8, 0x8, 0x0, 0x8, 0xa, 0x4a, 0x40, 0x0, 0x0, 0xa, 0x5f, 0xea, 0x5f, 0xea, 0xe, 0xd9, 0x2e, 0xd3, 0x6e, 0x19, 0x32, 0x44, 0x89, 0x33, 0xc, 0x92, 0x4c, 0x92, 0x4d, 0x8, 0x8, 0x0, 0x0, 0x0, 0x4, 0x88, 0x8, 0x8, 0x4, 0x8, 0x4, 0x84, 0x84, 0x88, 0x0, 0xa, 0x44, 0x8a, 0x40, 0x0, 0x4, 0x8e, 0xc4, 0x80, 0x0, 0x0, 0x0, 0x4, 0x88, 0x0, 0x0, 0xe, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x1, 0x22, 0x44, 0x88, 0x10, 0xc, 0x92, 0x52, 0x52, 0x4c, 0x4, 0x8c, 0x84, 0x84, 0x8e, 0x1c, 0x82, 0x4c, 0x90, 0x1e, 0x1e, 0xc2, 0x44, 0x92, 0x4c, 0x6, 0xca, 0x52, 0x5f, 0xe2, 0x1f, 0xf0, 0x1e, 0xc1, 0x3e, 0x2, 0x44, 0x8e, 0xd1, 0x2e, 0x1f, 0xe2, 0x44, 0x88, 0x10, 0xe, 0xd1, 0x2e, 0xd1, 0x2e, 0xe, 0xd1, 0x2e, 0xc4, 0x88, 0x0, 0x8, 0x0, 0x8, 0x0, 0x0, 0x4, 0x80, 0x4, 0x88, 0x2, 0x44, 0x88, 0x4, 0x82, 0x0, 0xe, 0xc0, 0xe, 0xc0, 0x8, 0x4, 0x82, 0x44, 0x88, 0xe, 0xd1, 0x26, 0xc0, 0x4, 0xe, 0xd1, 0x35, 0xb3, 0x6c, 0xc, 0x92, 0x5e, 0xd2, 0x52, 0x1c, 0x92, 0x5c, 0x92, 0x5c, 0xe, 0xd0, 0x10, 0x10, 0xe, 0x1c, 0x92, 0x52, 0x52, 0x5c, 0x1e, 0xd0, 0x1c, 0x90, 0x1e, 0x1e, 0xd0, 0x1c, 0x90, 0x10, 0xe, 0xd0, 0x13, 0x71, 0x2e, 0x12, 0x52, 0x5e, 0xd2, 0x52, 0x1c, 0x88, 0x8, 0x8, 0x1c, 0x1f, 0xe2, 0x42, 0x52, 0x4c, 0x12, 0x54, 0x98, 0x14, 0x92, 0x10, 0x10, 0x10, 0x10, 0x1e, 0x11, 0x3b, 0x75, 0xb1, 0x31, 0x11, 0x39, 0x35, 0xb3, 0x71, 0xc, 0x92, 0x52, 0x52, 0x4c, 0x1c, 0x92, 0x5c, 0x90, 0x10, 0xc, 0x92, 0x52, 0x4c, 0x86, 0x1c, 0x92, 0x5c, 0x92, 0x51, 0xe, 0xd0, 0xc, 0x82, 0x5c, 0x1f, 0xe4, 0x84, 0x84, 0x84, 0x12, 0x52, 0x52, 0x52, 0x4c, 0x11, 0x31, 0x31, 0x2a, 0x44, 0x11, 0x31, 0x35, 0xbb, 0x71, 0x12, 0x52, 0x4c, 0x92, 0x52, 0x11, 0x2a, 0x44, 0x84, 0x84, 0x1e, 0xc4, 0x88, 0x10, 0x1e, 0xe, 0xc8, 0x8, 0x8, 0xe, 0x10, 0x8, 0x4, 0x82, 0x41, 0xe, 0xc2, 0x42, 0x42, 0x4e, 0x4, 0x8a, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x8, 0x4, 0x80, 0x0, 0x0, 0x0, 0xe, 0xd2, 0x52, 0x4f, 0x10, 0x10, 0x1c, 0x92, 0x5c, 0x0, 0xe, 0xd0, 0x10, 0xe, 0x2, 0x42, 0x4e, 0xd2, 0x4e, 0xc, 0x92, 0x5c, 0x90, 0xe, 0x6, 0xc8, 0x1c, 0x88, 0x8, 0xe, 0xd2, 0x4e, 0xc2, 0x4c, 0x10, 0x10, 0x1c, 0x92, 0x52, 0x8, 0x0, 0x8, 0x8, 0x8, 0x2, 0x40, 0x2, 0x42, 0x4c, 0x10, 0x14, 0x98, 0x14, 0x92, 0x8, 0x8, 0x8, 0x8, 0x6, 0x0, 0x1b, 0x75, 0xb1, 0x31, 0x0, 0x1c, 0x92, 0x52, 0x52, 0x0, 0xc, 0x92, 0x52, 0x4c, 0x0, 0x1c, 0x92, 0x5c, 0x90, 0x0, 0xe, 0xd2, 0x4e, 0xc2, 0x0, 0xe, 0xd0, 0x10, 0x10, 0x0, 0x6, 0xc8, 0x4, 0x98, 0x8, 0x8, 0xe, 0xc8, 0x7, 0x0, 0x12, 0x52, 0x52, 0x4f, 0x0, 0x11, 0x31, 0x2a, 0x44, 0x0, 0x11, 0x31, 0x35, 0xbb, 0x0, 0x12, 0x4c, 0x8c, 0x92, 0x0, 0x11, 0x2a, 0x44, 0x98, 0x0, 0x1e, 0xc4, 0x88, 0x1e, 0x6, 0xc4, 0x8c, 0x84, 0x86, 0x8, 0x8, 0x8, 0x8, 0x8, 0x18, 0x8, 0xc, 0x88, 0x18, 0x0, 0x0, 0xc, 0x83, 0x60};

