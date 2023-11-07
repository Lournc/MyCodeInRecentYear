#include <stdio.h>
#include <ctype.h>
#include <string.h>
void solve(char *s, int len, int key)
{
    if (key < 0)
        key += 26;
    for (int i = 0; i < len; i++)
    {
        if (s[i] != ' ')
            s[i] = (s[i] - 'A' + key) % 26 + 'A';
    }
}
int main()
{
    char *s;
    gets(s);
    getchar();
    int len = strlen(s);
    int opt, key;
    scanf("%d %d", &opt, &key);
    for (int i = 0; i < len; i++)
        s[i] = toupper(s[i]);
    if (opt == 1)
        solve(s, len, key);
    else
        solve(s, len, -key);
    printf("%s", s);
}