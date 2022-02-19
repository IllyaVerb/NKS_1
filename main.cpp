#include <bits/stdc++.h>
#include "windows.h"

#define INTERVALS 10

using namespace std;

static int array_size = 100;
static int array_list[] = {647, 1948, 1204, 1757, 16, 0, 2279, 353,
                        450, 660, 950, 1210, 114, 1017, 1595, 370,
                        32, 1725, 327, 209, 121, 1427, 1324, 293,
                        602, 606, 1057, 1586, 393, 2835, 12, 866,
                        353, 55, 47, 1586, 149, 604, 586, 671, 726,
                        1024, 224, 998, 99, 300, 781, 232, 239, 312,
                        47, 312, 1813, 257, 1602, 2422, 247, 240,
                        2255, 28, 694, 1657, 102, 353, 3195, 141,
                        1980, 143, 440, 1974, 472, 169, 358, 1207,
                        824, 30, 39, 2167, 1761, 696, 1384, 1656,
                        73, 184, 224, 873, 1117, 2667, 107, 2278,
                        246, 484, 1408, 1873, 1864, 1399, 331,
                        1764, 326, 12};
static double ty = 0.84;
static int time1 = 2748;
static int time2 = 2308;


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double divider = *max_element(array_list , array_list + array_size)/10.0;
    cout << "Середній наробіток до відмови Tср = " << divider << endl;

    sort(array_list, array_list + array_size);
    cout << "Відсортована вибірка:" << endl;
    for (int i=0; i < array_size; i++)
        cout << array_list[i] << " ";
    cout << endl << endl;

    cout    << "Максимальним значенням наробітку до відмови є "
            << *max_element(array_list , array_list + array_size) << endl << endl;

    cout    << "Поділимо інтервал від 0 до максимального наробітку до відмови на " << INTERVALS
            << " частин (інтервалів), тоді довжина одного інтервалу буде дорівнювати "
            << divider << ", а границі інтервалів будуть наступними:" << endl;
    for (int i=0; i < INTERVALS; i++)
        printf("%dй інтервал від %.1f до %.1f\n",
               i+1, i * divider, (i+1) * divider);
    cout << endl;

    cout << "Значення статистичної щільності розподілу ймовірності відмови для кожного інтервалу:" << endl;
    double f[INTERVALS];
    for (int i=0; i < INTERVALS; i++) {
        f[i] = 0.0;
        for (int j=0; j < array_size; j++)
            if (array_list[j] >= i * divider && array_list[j] <= (i + 1) * divider)
                f[i]++;
        f[i] /= array_size * divider;
    }
    for (int i=0; i < INTERVALS; i++)
        printf("для %d-го інтервалу f = %.20f\n",
               i+1, f[i]);
    cout << endl;

    cout    << "Значення ймовірності безвідмовної роботи пристрою на час правої границі інтервалу для кожного інтервалу:"
            << endl << "P(0) = 1.00" << endl;

    double p[INTERVALS] = {1.0};
    double counter = 0.0;
    for (int i=1; i <= INTERVALS; i++) {
        counter += f[i-1]*divider;
        p[i] = 1.0 - counter;
    }
    for (int i=1; i <= INTERVALS; i++)
        printf("для %d-го інтервалу P(%.1f) = %.2f\n",
               i, (i)*divider, p[i]);
    cout << endl;

    double d = 0.0;
    for (int i=0; i < INTERVALS; i++)
        if (ty <= p[i] && ty > p[i + 1]) {
            d = (p[i+1] - ty)/(p[i+1] - p[i]);
            printf("d(%d,%d) = (%.2f - %.2f) / (%.2f - %.2f) = %.20f\n",
                   i, i+1, p[i+1], ty, p[i+1], p[i], d);
                   break;
        }
    printf("T(%.2f) = %.1f - %.1f * %.20f = %.20f\n\n",
           ty, divider, divider, d, divider - divider*d);

    cout << "Ймовірність безвідмовної роботи на час " << time1 << " годин:\nP(" << time1 << ") = 1 - (";
    for (int i=0; i < INTERVALS; i++) {
        printf("f%d*%.1f + ",
               i+1, divider);
        if (time1 < (i+2)*divider) {
            printf("f%d*(%d - %.1f)) = %.20f\n\n",
                   i+2, time1, (i+1)*divider, p[i+1] - f[i+1]*(time1 - (i+1)*divider));
            break;
        }
    }

    double p2 = 0.0;
    cout << "Ймовірність відмов на час " << time2 << " годин:\nP(" << time2 << ") = 1 - (";
    for (int i=0; i < INTERVALS; i++) {
        printf("f%d*%.1f + ",
               i+1, divider);
        if (time2 < (i+2)*divider) {
            p2 = p[i+1] - f[i+1]*(time2 - (i+1)*divider);
            printf("f%d*(%d - %.1f)) = %.20f\nlambda(%d) = f%d/P(%d) = %.20f\n",
                   i+2, time2, (i+1)*divider, p2, time2, i+2, time2, f[i+1]/p2);
            break;
        }
    }

    return 0;
}
