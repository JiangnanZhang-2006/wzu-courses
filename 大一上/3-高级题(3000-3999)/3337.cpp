int calcSumOfNumber(int x) {	//@2103
    int cnt = 0;

    while (x != 0) {
        cnt += x % 10;
        x /= 10;
    }

    return cnt;

}