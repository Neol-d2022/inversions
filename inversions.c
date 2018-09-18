#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int merge(unsigned int *a, unsigned int p, unsigned int r, unsigned int q)
{
    unsigned int *b;
    unsigned int n = r - p, m = q - r, i, j, k, l;

    if (n == 0 || m == 0)
        return 0;
    b = (unsigned int*)malloc(n * sizeof(*b));
    memcpy(b, a + p, n * sizeof(*b));
    i = j = k = l = 0;
    while (i < n || j < m)
    {
        if (i >= n)
        {
            memcpy(a + p + k, a + r + j, (m - j) * sizeof(*a));
            j = m;
        }
        else if (j >= m)
        {
            memcpy(a + p + k, b + i, (n - i) * sizeof(*a));
            i = n;
        }
        else if (b[i] > a[r + j])
        {
            a[p + k] = a[r + j];
            l += (n - i);
            j++;
        }
        else
        {
            a[p + k] = b[i];
            i++;
        }
        k++;
    }
    free(b);
    return l;
}

static unsigned int inversions(unsigned int *a, unsigned int p, unsigned int q)
{
    unsigned int r, i[3];

    if (q - p <= 1)
        return 0;
    r = (p + q) >> 1;
    i[0] = inversions(a, p, r);
    i[1] = inversions(a, r, q);
    i[2] = merge(a, p, r, q);

    return (i[0] + i[1] + i[2]);
}

int main(void)
{
    char buf[32];
    unsigned int n, i, j;
    unsigned int *a;

    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 1;
    sscanf(buf, "%u", &n);
    a = (unsigned int*)malloc(n * sizeof(*a));
    for (i = 0; i < n; i++)
        if (scanf("%u", a + i) != 1)
            return 2;

    j = inversions(a, 0, n);
    printf("%u\n", j);
    for (i = 0; i < n; i++)
        printf("%u ", a[i]);
    free(a);
    printf("\n");
    return 0;
}
