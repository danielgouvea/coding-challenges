/**
 * The problem is the following: given an array of positive integers bigger than zero, is it possible to remove two
 * elements of this array in a way that the sum of the elements in each of the three remaining ranges are equal?
 *
 * Eg.
 *  For sample = [1, 3, 4, 2, 2, 2, 1, 1, 2], removing the elements in positions 2 and 5 yield:
 *  [1, 3], [2, 2], [1, 1, 2], having the sum of the elements in each range summing 4.
 */

#include <iostream>
#include <numeric>
#include <vector>

using std::accumulate;
using std::cout;
using std::vector;

bool isPossibleToSplitRemovingTwoElements(const vector<unsigned> &sample) {
    // Sample must has at least 5 elements: [a(0), pos0, a(2), pos1, a(4)]
    if (sample.size() < 5) {
        return false;
    }

    // Initial state: [a(0), pos0, a(2), pos1, a(4), ..., a(n - 1)]
    unsigned pos0 = 1;
    unsigned pos1 = pos0 + 2;
    unsigned sumA = sample[pos0 - 1];
    unsigned sumB = sample[pos1 - 1];
    unsigned sumC = accumulate(sample.begin() + pos1 + 1, sample.end(), 0u);

    // While sums are not equal, pos0 and pos1 will be moved iteratively to the right
    while (sumA != sumB || sumB != sumC) {

        // If sumA or sumB is already bigger than sumC, moving pos0 or pos1 to the right will only make sumC smaller
        if (sumA > sumC || sumB > sumC) {
            return false;
        }

        if (sumA >= sumB) {
            // No space to move pos1 more to the right
            if ((pos1 + 1) >= (sample.size() - 1)) {
                return false;
            }

            sumB += sample[pos1];
            sumC -= sample[pos1 + 1];
            pos1++;
        } else {
            // No space to move pos0 more to the right, so try to move pos1 to the right first as this can't change the
            // fact that sumA < sumB
            if ((pos0 + 1) >= (pos1 - 1)) {
                // No space to move pos1 more to the right
                if ((pos1 + 1) >= (sample.size() - 1)) {
                    return false;
                }

                sumB += sample[pos1];
                sumC -= sample[pos1 + 1];
                pos1++;
            }

            sumA += sample[pos0];
            sumB -= sample[pos0 + 1];
            pos0++;
        }
    }

    return true;
}

int main() {
    vector<unsigned> sampleTrue {1, 3, 4, 2, 2, 2, 1, 1, 2};
    vector<unsigned> sampleFalse {1, 1, 1, 1, 1, 1};

    cout << "sampleTrue: " << (isPossibleToSplitRemovingTwoElements(sampleTrue) ? "true\n" : "false\n");
    cout << "sampleFalse: " << (isPossibleToSplitRemovingTwoElements(sampleFalse) ? "true\n" : "false\n");

    return 0;
}
