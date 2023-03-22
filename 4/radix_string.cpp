#include <iostream>
#include <string>

void bubbleSort(string array[], int len) {
    
    bool swapped = true;
    int j = 0;

    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < len - j; i++) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
    }
}

void countingSort(string array[], int len, int place) {
    const int max = 128;                                   

    string *output = new string[len];                       
    int *count = new int[max];                              

    for (int i = 0; i < max; ++i)                           
        count[i] = 0;                                       

    for (int i = 0; i < len; i++)
        count[array[i][array[i].length() - place]]++;       

    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];                           

    for (int i = len - 1; i >= 0; i--) {                    

        output[count[ array[i][array[i].length() - place] ] - 1] = array[i];  
        count[array[i][array[i].length() - place]]--;
    }

    for (int i = 0; i < len; i++)
        array[i] = output[i];

    delete[] output;
    delete[] count;
}

void radixsort(string array[], int len) {
    for (int place = 1; place <= array[0].length(); place++)
        countingSort(array, len, place);
}


int main() {
    string array1[] = { "aabaa", "caabc", "cddda", "dcbcd", "cbcbd", "ccccd", "bccca", "dadcd", "cdbdd", "aaddb", "cadbd", \
                       "cacac", "ddacb", "cbcab", "aabcc", "bcbda", "cddbd", "daacc", "cadba", "bbaaa", "bbdad", "adcda", \
                       "ddccb", "dbbab", "cdbbc", "cbdca", "dccac", "dbcbb", "aaaca", "dcccc", "bdbdd", "ccbca", "ccabd", \
                       "cbbac", "aacbc", "caddc", "aacbb", "cbdbd", "abdcc", "bcddb", "aaaab", "acdad", "bcdcc", "cacbb", \
                       "baccc", "aabdb", "cdcad", "bdcbd", "baccd", "bacbc", "acacb", "cbbcc", "dcdba", "acbdd", "cdddc", \
                       "adddb", "adcbb", "dcccd", "ccbdd", "adadb", "ddcbb", "aacbd", "acadd", "dddbd", "dbacb", "ccacd", \
                       "accbb", "caaca", "cbbbd", "babdc", "dbbba", "addcd", "baaad", "bbcad", "bdcdd", "dbbdb", "aaacc", \
                       "bbbdb", "dadca", "dabca", "bcdaa", "cccbd", "cccca", "badab", "abbbd", "aabcd", "dccdd", "bbbdc", \
                       "bbaad", "cbccc", "daadc", "cadcd", "acdbc", "cbdac", "ddcda", "dbbcb", "addad", "bbcbb", "cccdb", \
                       "bdcca", "abcad", "adaab", "adddd", "dacbb", "dadbb", "bbabd", "bbbca", "adabb", "cddbb", "dccaa", \
                       "bdcad", "baaaa", "dcbda", "cbbbb", "acaba", "bcbcb", "ddcad", "acdbb", "dbcbc", "dcabd", "dcacd", \
                       "adaad", "bcabd", "dbdcd", "cdaac", "bdbbd", "dcdcd", "ddbac", "aabbb", "cdcbb", "aaddc", "ddddb", \
                       "adaac", "dbdcb", "daddd", "bdddc", "bdacc", "adccc", "abccd", "ddbbb", "dcabb", "bccdb", "caaba", \
                       "adbaa", "bdaad", "ccaba", "ddcdd", "bcbbd", "babcb", "dcdbd", "addcb", "cdbcc", "ddcdb", "abbad" };

    string array2[] = {"aabaa", "caabc", "cddda", "dcbcd", "cbcbd", "ccccd", "bccca", "dadcd", "cdbdd", "aaddb", "cadbd", \
                       "cacac", "ddacb", "cbcab", "aabcc", "bcbda", "cddbd", "daacc", "cadba", "bbaaa", "bbdad", "adcda", \
                       "ddccb", "dbbab", "cdbbc", "cbdca", "dccac", "dbcbb", "aaaca", "dcccc", "bdbdd", "ccbca", "ccabd", \
                       "cbbac", "aacbc", "caddc", "aacbb", "cbdbd", "abdcc", "bcddb", "aaaab", "acdad", "bcdcc", "cacbb", \
                       "baccc", "aabdb", "cdcad", "bdcbd", "baccd", "bacbc", "acacb", "cbbcc", "dcdba", "acbdd", "cdddc", \
                       "adddb", "adcbb", "dcccd", "ccbdd", "adadb", "ddcbb", "aacbd", "acadd", "dddbd", "dbacb", "ccacd", \
                       "accbb", "caaca", "cbbbd", "babdc", "dbbba", "addcd", "baaad", "bbcad", "bdcdd", "dbbdb", "aaacc", \
                       "bbbdb", "dadca", "dabca", "bcdaa", "cccbd", "cccca", "badab", "abbbd", "aabcd", "dccdd", "bbbdc", \
                       "bbaad", "cbccc", "daadc", "cadcd", "acdbc", "cbdac", "ddcda", "dbbcb", "addad", "bbcbb", "cccdb", \
                       "bdcca", "abcad", "adaab", "adddd", "dacbb", "dadbb", "bbabd", "bbbca", "adabb", "cddbb", "dccaa", \
                       "bdcad", "baaaa", "dcbda", "cbbbb", "acaba", "bcbcb", "ddcad", "acdbb", "dbcbc", "dcabd", "dcacd", \
                       "adaad", "bcabd", "dbdcd", "cdaac", "bdbbd", "dcdcd", "ddbac", "aabbb", "cdcbb", "aaddc", "ddddb", \
                       "adaac", "dbdcb", "daddd", "bdddc", "bdacc", "adccc", "abccd", "ddbbb", "dcabb", "bccdb", "caaba", \
                       "adbaa", "bdaad", "ccaba", "ddcdd", "bcbbd", "babcb", "dcdbd", "addcb", "cdbcc", "ddcdb", "abbad" };


    int len = sizeof(array1) / sizeof(array1[0]);
   
    radixsort(array1, len);

    for (string x : array1) {
        cout << x << " ";
    }

    cout << endl << endl;

    bubbleSort(array2, len);

    for (string x : array2) {
        cout << x << " ";
    }
}
