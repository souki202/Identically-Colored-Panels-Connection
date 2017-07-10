#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

constexpr int NUM = 1 << (3*4);
int panel[8][8] = {0};
int w, h, c;
int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

int changeColor(int colors) {
	int newPanel[8][8];
	int colorCount = 1;
	for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) newPanel[i][j] = panel[i][j];
	for (int i = 0; i < 5; i++) {
		int color = c;
		if (i < 4) color = (colors >> (i*3)) & 0b111;
		if (color < 1 || 6 < color) return 0;
		int targetColor = newPanel[0][0];
		newPanel[0][0] = color;
		//DFS
		std::stack<std::pair<int, int>> s; s.push(std::make_pair(0, 0));
		while (!s.empty() && color != targetColor) {
			auto node = s.top(); s.pop();
			for (int i = 0; i < 4; i++) {
				auto next = node;
				next.first += dx[i]; next.second += dy[i];
				if (next.first < 0 || next.first >= w || next.second < 0 || next.second >= h) continue;
				if (newPanel[next.second][next.first] != targetColor) continue;
				newPanel[next.second][next.first] = color;
				s.push(next);
			}
		}
	}

	//DFS
	std::stack<std::pair<int, int>> s; s.push(std::make_pair(0, 0));
	newPanel[0][0] = 0;
	while (!s.empty()) {
		auto node = s.top(); s.pop();
		for (int i = 0; i < 4; i++) {
			auto next = node;
			next.first += dx[i]; next.second += dy[i];
			if (next.first < 0 || next.first >= w || next.second < 0 || next.second >= h) continue;
			if (newPanel[next.second][next.first] != c) continue;
			colorCount++;
			newPanel[next.second][next.first] = 0;
			s.push(next);
		}
	}
	return colorCount;
}

int main() {
	while (std::cin >> h >> w >> c && (h || w || c)) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				std::cin >> panel[i][j];
			}
		}

		int max = 0;
		for (int i = 0; i < NUM; i++) {
			max = std::max(changeColor(i), max);
		}
		std::cout << max << std::endl;
	}
	return 0;
}
