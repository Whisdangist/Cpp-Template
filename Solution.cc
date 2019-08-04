#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#include <windows.h>
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp) ((void)0)
#endif

#define INF 0x0FFFFFFF
#define IS_POS_INF(num) ((bool)(num > (INF / 2)))
#define IS_NEG_INF(num) ((bool)(num < (-INF / 2)))

#define MAX_N 1000


void solve() {
	// init
	
	// process
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	LARGE_INTEGER _frequency, _start_time, _end_time;
	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_start_time);
	#endif

	assert(sizeof(int) == 4);
	solve();
	
	#ifdef OFFLINE
	QueryPerformanceCounter(&_end_time);
	cout << endl << "The algorithm takes " << (_end_time.QuadPart-_start_time.QuadPart)*1000/_frequency.QuadPart << " ms to complete the run." << endl;
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
