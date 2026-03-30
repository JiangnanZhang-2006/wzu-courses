int a[2005];
for (int i = 0; i < 2005; i++) {
    a[i] = 0;
}
int idx = 0 , count = 0;
while (idx < L->length) {
    if (a[L->data[idx] + 1000] == 0) {
        a[L->data[idx]] = 1;
    } else {
        count++;
    }
    L->data[idx - count] = L->data[idx];
    idx++;
}