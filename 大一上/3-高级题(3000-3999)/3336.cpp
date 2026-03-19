int Power(int x, int y) {				//@2102函数名区分大小写
	int temp = x;
	for (int i = 0; i < y - 1; i++) {
		x *= temp;
	}
	return x;
}