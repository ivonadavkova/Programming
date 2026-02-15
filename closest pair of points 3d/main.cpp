#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point3D {
    double x, y, z;
};

// rastojanie
double calculateDistance(Point3D p1, Point3D p2) {
    return sqrt(pow(p2.x - p1.x, 2) +
                pow(p2.y - p1.y, 2) +
                pow(p2.z - p1.z, 2));
}

int main() {
    srand(time(0));

    int n = 100;
    vector<Point3D> points;


    for (int i = 0; i < n; i++) {
        Point3D p;
        p.x = (rand() % 1000) / 10.0;
        p.y = (rand() % 1000) / 10.0;
        p.z = (rand() % 1000) / 10.0;
        points.push_back(p);
    }

    // BRUTE FORCE PREBARUVANJE
    double minDistance = DBL_MAX;
    int idx1 = -1, idx2 = -1;

    // fiksiraj edna tochka
    for (int i = 0; i < n; i++) {
        // sporedi ja so site ostanati
        for (int j = i + 1; j < n; j++) {
            double dist = calculateDistance(points[i], points[j]);

            // Ako najdeme pomalo rastojanie,go pamtetme
            if (dist < minDistance) {
                minDistance = dist;
                idx1 = i;
                idx2 = j;
            }
        }
    cout << "Prebaruvani se " << (n * (n - 1)) / 2 << " mozhni parovi." << endl;
    cout << fixed << setprecision(3);
    cout << "Najbliski se tochkite so indeksi: " << idx1 << " i " << idx2 << endl;
    cout << "Tochka " << idx1 << ": (" << points[idx1].x << ", " << points[idx1].y << ", " << points[idx1].z << ")" << endl;
    cout << "Tochka " << idx2 << ": (" << points[idx2].x << ", " << points[idx2].y << ", " << points[idx2].z << ")" << endl;
    cout << "Minimalnoto rastojanie e: " << minDistance << endl;

    return 0;
}
