#include <stdio.h>

int n;

int main() {
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Array size: %d\n", sizeof(arr) / sizeof(arr[0]));
    return 0;
}