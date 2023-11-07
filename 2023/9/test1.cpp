#include <stdio.h>
#include <string.h>
int main()
{
    unsigned int a;
    scanf("%ud", &a);
    char s[1001];
    getchar();
    scanf("%s", s);
    int q = strlen(s);
    char p[1001];
    for (int m = 0; m < q; m++)
    {
        int n = (m + a) % q;
        p[n] = s[m];
    }
    p[q] = '\0';
    printf("%s", p);
    return 0;
}