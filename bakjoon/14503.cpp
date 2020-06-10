#include<iostream>

using namespace std;


int N, M;
int R, C, dist, ans = 0, hist = 0;
int MAP[50][50];
int dist_R[4] = { -1, 0, 1, 0 };
int dist_C[4] = { 0, 1, 0, -1 };
int Rule_Two() {
	if (hist == 4) {
		int back_pos = (dist + 2) % 4;
		if (MAP[R + dist_R[back_pos]][C + dist_C[back_pos]] != 1) {
			R += dist_R[back_pos];
			C += dist_C[back_pos];
			hist = 0;
			return 2;
		}
		else {
			return 0;
		}
	}
	else {
		int dist_go = (dist - 1 < 0 ? 3 : dist - 1); // 현재 방향에서 왼쪽 바라본다.
		if (MAP[R + dist_R[dist_go]][C + dist_C[dist_go]] == 0) {
			dist = dist_go;
			R += dist_R[dist_go];
			C += dist_C[dist_go];
			hist = 0;
			return 1;
		}
		else if (MAP[R + dist_R[dist_go]][C + dist_C[dist_go]] != 0) {
			dist = dist_go;
			hist += 1;
			return 2;
		}
	}
}
int main() {
	cin >> N >> M;
	cin >> R >> C >> dist;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}
	while (true) {
		if (MAP[R][C] == 0) {
			MAP[R][C] = 2;
			ans++;
		} // 현재 위치 청소
		int chk = Rule_Two();
		if (chk == 2) Rule_Two();
		else if (chk == 1) continue;
		else break;
	}
	cout << ans << endl;
}