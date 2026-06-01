#include <stdio.h>
#include <math.h>

#define MAX 10
#define EPS 1e-3

/*================= NHAP MA TRAN =================*/
void nhapmt(float a[][MAX + 2], int n)
{
    int i, j;

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n + 1; j++)
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%f", &a[i][j]);
        }
    }
}

/*================= XUAT MA TRAN =================*/
void xuatmt(float a[][MAX + 2], int n)
{
    int i, j;

    for(i = 1; i <= n; i++)
    {
        printf("\n");

        for(j = 1; j <= n + 1; j++)
        {
            printf("%10.3f", a[i][j]);
        }
    }
    printf("\n");
}

/*================= HOAN DOI =================*/
void hoandoi(float *a, float *b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

void doidong(float a[][MAX + 2], int n, int p, int q)
{
    int k;

    if(p != q)
    {
        for(k = 1; k <= n + 1; k++)
        {
            hoandoi(&a[p][k], &a[q][k]);
        }
    }
}

/*================= DINH THUC =================*/
float dinhThuc(float a[][MAX + 2], int n)
{
    float temp[MAX + 1][MAX + 2];
    int i, j, k;
    float det = 1;

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            temp[i][j] = a[i][j];

    for(i = 1; i < n; i++)
    {
        if(fabs(temp[i][i]) < 1e-9)
        {
            int p;

            for(p = i + 1; p <= n; p++)
            {
                if(fabs(temp[p][i]) > 1e-9)
                    break;
            }

            if(p > n)
                return 0;

            for(k = 1; k <= n; k++)
                hoandoi(&temp[i][k], &temp[p][k]);

            det = -det;
        }

        for(j = i + 1; j <= n; j++)
        {
            float m = temp[j][i] / temp[i][i];

            for(k = i; k <= n; k++)
                temp[j][k] -= m * temp[i][k];
        }
    }

    for(i = 1; i <= n; i++)
        det *= temp[i][i];

    return det;
}

/*================= GAUSS =================*/
void gauss(float a[][MAX + 2], int n)
{
    float x[MAX + 1];
    float m, s;
    int i, j, k;

    for(i = 1; i < n; i++)
    {
        if(a[i][i] == 0)
        {
            for(k = i + 1; k <= n; k++)
            {
                if(a[k][i] != 0)
                    break;
            }

            if(k <= n)
                doidong(a, n, i, k);
            else
            {
                printf("\nHe vo nghiem hoac vo so nghiem!\n");
                return;
            }
        }

        for(j = i + 1; j <= n; j++)
        {
            m = -a[j][i] / a[i][i];

            for(k = i; k <= n + 1; k++)
            {
                a[j][k] += a[i][k] * m;
            }
        }
    }

    printf("\nMa tran sau khu Gauss:\n");
    xuatmt(a, n);

    for(i = n; i >= 1; i--)
    {
        s = a[i][n + 1];

        for(k = i + 1; k <= n; k++)
            s -= a[i][k] * x[k];

        x[i] = s / a[i][i];
    }

    printf("\nNghiem he phuong trinh:\n");

    for(i = 1; i <= n; i++)
        printf("x%d = %.6f\n", i, x[i]);
}

/*================= GAUSS-SEIDEL =================*/
void gaussSeidel(float a[][MAX + 2], int n)
{
    float x[MAX + 1], y[MAX + 1];
    int i, j, dem, lap;

    printf("\nNhap nghiem gan dung ban dau:\n");

    for(i = 1; i <= n; i++)
    {
        printf("x[%d] = ", i);
        scanf("%f", &x[i]);
    }

    dem = 0;

    do
    {
        lap = 0;
        dem++;

        for(i = 1; i <= n; i++)
        {
            float s = 0;

            for(j = 1; j <= n; j++)
            {
                if(j != i)
                    s += a[i][j] * x[j];
            }

            y[i] = (a[i][n + 1] - s) / a[i][i];

            if(fabs(x[i] - y[i]) > EPS && dem < 30)
                lap = 1;
        }

        for(i = 1; i <= n; i++)
            x[i] = y[i];

    } while(lap);

    if(dem < 30)
    {
        printf("\nNghiem gan dung:\n");

        for(i = 1; i <= n; i++)
            printf("x%d = %.6f\n", i, y[i]);
    }
    else
    {
        printf("\nKhong hoi tu sau 30 lan lap!\n");
    }
}

/*================= KRAME =================*/
void krame(float a[][MAX + 2], int n)
{
    float A[MAX + 1][MAX + 2];
    float Ai[MAX + 1][MAX + 2];
    float B[MAX + 1];
    float x[MAX + 1];

    int i, j, k;

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            A[i][j] = a[i][j];

        B[i] = a[i][n + 1];
    }

    float d = dinhThuc(A, n);

    if(fabs(d) < 1e-9)
    {
        printf("\nDet(A)=0 -> Khong ap dung duoc Krame\n");
        return;
    }

    for(k = 1; k <= n; k++)
    {
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                Ai[i][j] = A[i][j];

        for(i = 1; i <= n; i++)
            Ai[i][k] = B[i];

        x[k] = dinhThuc(Ai, n) / d;
    }

    printf("\nNghiem theo Krame:\n");

    for(i = 1; i <= n; i++)
        printf("x%d = %.6f\n", i, x[i]);
}

/*================= GIAM DU =================*/
void giamDu(float a[][MAX + 2], int n)
{
    float x[MAX + 1];
    float r[MAX + 1];

    int i, j, k;
    float t, max, d;

    printf("\nNhap nghiem gan dung ban dau:\n");

    for(i = 1; i <= n; i++)
    {
        printf("x[%d] = ", i);
        scanf("%f", &x[i]);
    }

    for(i = 1; i <= n; i++)
    {
        t = a[i][i];

        for(j = 1; j <= n + 1; j++)
            a[i][j] /= t;
    }

    for(i = 1; i <= n; i++)
    {
        r[i] = a[i][n + 1];

        for(j = 1; j <= n; j++)
            r[i] -= a[i][j] * x[j];
    }

    do
    {
        t = 0;

        max = fabs(r[1]);
        k = 1;

        for(i = 2; i <= n; i++)
        {
            if(max < fabs(r[i]))
            {
                max = fabs(r[i]);
                k = i;
            }
        }

        x[k] += r[k];

        d = r[k];

        for(i = 1; i <= n; i++)
        {
            r[i] -= a[i][k] * d;

            if(fabs(r[i]) > EPS)
                t = 1;
        }

    } while(t);

    printf("\nNghiem theo phuong phap giam du:\n");

    for(i = 1; i <= n; i++)
        printf("x%d = %.6f\n", i, x[i]);
}

/*================= MAIN =================*/
int main()
{
    float a[MAX + 1][MAX + 2];
    float b[MAX + 1][MAX + 2];

    int n, choice;
    int i, j;

    do
    {
        printf("\n====================================");
        printf("\n GIAI HE PHUONG TRINH TUYEN TINH");
        printf("\n====================================");
        printf("\n1. Phuong phap Gauss");
        printf("\n2. Phuong phap Gauss-Seidel");
        printf("\n3. Phuong phap Krame");
        printf("\n4. Phuong phap Giam du");
        printf("\n0. Thoat");
        printf("\n====================================");
        printf("\nNhap lua chon: ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 4)
        {
            printf("\nNhap so an n = ");
            scanf("%d", &n);

            printf("\nNhap ma tran mo rong:\n");
            nhapmt(a, n);

            printf("\nHe phuong trinh vua nhap:\n");
            xuatmt(a, n);

            for(i = 1; i <= n; i++)
            {
                for(j = 1; j <= n + 1; j++)
                {
                    b[i][j] = a[i][j];
                }
            }
        }

        switch(choice)
        {
            case 1:
                gauss(b, n);
                break;

            case 2:
                gaussSeidel(b, n);
                break;

            case 3:
                krame(b, n);
                break;

            case 4:
                giamDu(b, n);
                break;

            case 0:
                printf("\nKet thuc chuong trinh!\n");
                break;

            default:
                printf("\nLua chon khong hop le!\n");
        }

    } while(choice != 0);

    return 0;
}