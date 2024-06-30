#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>

const std::byte INVERT_MASK      {0x03};
const std::byte FIRST_HALF_MASK  {0xF0};
const std::byte SECOND_HALF_MASK {0x0F};

const std::string_view MESSAGE {R"(
	10010110 11110111 01010110 00000001 
	00010111 00100110 01010111 00000001 
	00010111 01110110 01010111 00110110 
	11110111 11010111 01010111 00000011
)"};

constexpr bool 
is_binary(char const c) {
	return c == '0' || c == '1';
}

std::vector<std::byte> 
parse(std::string_view message) {
	std::vector<std::byte> bytes{};

	auto is_in_number = false;
	std::byte b{0};

	for (auto const c : message) {
		if (is_binary(c)) {
			is_in_number = true;
			auto const digit = std::byte(c == '0' ? 0 : 1);
			b = (b << 1) | digit;
		} else {
			if (is_in_number) {
				is_in_number = false;
				bytes.push_back(b);
				b = std::byte(0);
			}
		}
	}

	return bytes;
}

char 
decrypt(std::byte b) {
	b ^= INVERT_MASK;

	b = ((b & FIRST_HALF_MASK) >> 4) |
		((b & SECOND_HALF_MASK) << 4);

	return std::to_integer<char>(b);
}

int 
main() {
	auto const bytes = parse(MESSAGE);

	for (auto const b : bytes) {
		std::cout << decrypt(b);
	}
	std::cout << '\n';
}
