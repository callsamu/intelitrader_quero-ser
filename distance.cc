#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <utility>
#include <vector>

uint64_t
distance(int64_t const a, int64_t const b) {
	return std::abs(a - b);
}

void 
insertion_sort(std::vector<int64_t>& v) {
	auto const size = v.size();
	if (size == 1) return;

	for (auto i = 1; i < size; i++) {
		auto const key = v.at(i);
		auto j = i - 1;

		while ((j >= 0) && (v.at(j) > key)) {
			v.at(j + 1) = v.at(j);
			--j;
		}

		v.at(j + 1) = key;
	}
}

uint64_t
shortest_distance(
	std::vector<int64_t> const& A, 
	std::vector<int64_t> const& B
) {
	size_t cursor{0};
	size_t on_hold_cursor{0};

	auto selected = A[0] < B[0] ? A : B;
	auto on_hold = A[0] > B[0] ? A : B; 

	auto min_diff = distance(A[0], B[0]);

	while (cursor < selected.size()) {
		if (selected.at(cursor) >= on_hold.at(on_hold_cursor)) {
			min_diff = std::min(
				min_diff, 
				distance(
					selected.at(cursor - 1), 
					on_hold.at(on_hold_cursor)
				)
			);

			std::swap(selected, on_hold);
			std::swap(cursor, on_hold_cursor);
		} else {
			++cursor;
		}
	}

	min_diff = std::min(
		min_diff,
		distance(
			selected.at(cursor - 1), 
			on_hold.at(on_hold_cursor)
		)
	);

	return min_diff;
}

void
print_vector(std::string_view name, std::vector<int64_t> v) {
	std::cout << name << ": ";
	for (const auto i : v) {
		std::cout << i << " ";
	}
	std::cout << '\n';
}

int 
main() {
    std::vector<int64_t> A{12, 25, 17, 5, 1};
	std::vector<int64_t> B{-5, 30, 10};

	print_vector("A", A);
	print_vector("B", B);

	insertion_sort(A);
	insertion_sort(B);

	auto const min_diff = shortest_distance(A, B);

	std::cout << "A Menor Distância é: " << min_diff << '\n';
    
    return 0;
}
