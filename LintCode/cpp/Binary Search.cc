class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target number to find.
     * @return: The first position of target. Position starts from 0. 
     */
    int binarySearch(vector<int> &array, int target) {
        int n = array.size();
        
        int l = 0, r = n - 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (array[m] < target) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (array[l] == target) {
            return l;
        }
        return -1;
    }
};
