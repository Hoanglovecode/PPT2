#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX 10

void clear_input_buffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/*================= HOAN DOI =================*/
void hoandoi(float *a, float *b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

void hoandoiCot(float A[][MAX + 1], int n, int col1, int col2)
{
    for(int i = 1; i <= n; i++)
    {
        hoandoi(&A[i][col1], &A[i][col2]);
    }
}

void hoandoiHang(float A[][MAX + 1], int n, int row1, int row2)
{
    for(int j = 1; j <= n; j++)
    {
        hoandoi(&A[row1][j], &A[row2][j]);
    }
}

/*================= NHAN MA TRAN =================*/
void nhanMaTran(float A[][MAX + 1], float B[][MAX + 1], float C[][MAX + 1], int n)
{
    float temp[MAX + 1][MAX + 1];

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            temp[i][j] = 0.0f;
        }

        for(int k = 1; k <= n; k++)
        {
            float r = A[i][k];
            for(int j = 1; j <= n; j++)
            {
                temp[i][j] += r * B[k][j];
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            C[i][j] = temp[i][j];
        }
    }
}

/*================= BIEN DOI DANHILEPSKI =================*/
void danhilepskiBienDoi(float A[][MAX + 1], float C[][MAX + 1], int n, bool *success)
{
    float M[MAX + 1][MAX + 1];
    float M1[MAX + 1][MAX + 1];
    float B[MAX + 1][MAX + 1];

    // Khoi tao ma tran C la ma tran don vi
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
                C[i][j] = 1.0f;
            else
                C[i][j] = 0.0f;
        }
    }

    *success = true;

    for(int k = n - 1; k >= 1; k--)
    {
        // Kiem tra neu phan tu xoay bang 0
        if(fabs(A[k + 1][k]) < 1e-9)
        {
            int p = -1;

            // Tim cot p < k sao cho phan tu hang k+1 tai cot p khac 0
            for(int col = 1; col < k; col++)
            {
                if(fabs(A[k + 1][col]) > 1e-9)
                {
                    p = col;
                    break;
                }
            }

            if(p != -1)
            {
                // Hoan doi cot p va k tren A
                hoandoiCot(A, n, p, k);
                // Hoan doi hang p va k tren A
                hoandoiHang(A, n, p, k);
                // Hoan doi cot p va k tren C de bao toan bien doi
                hoandoiCot(C, n, p, k);
                printf("\n[Pivoting] Hoan doi hang/cot %d va %d tai buoc k = %d\n", p, k, k);
            }
            else
            {
                // Decoupling: cac phan tu tu cot 1 den k tren hang k+1 deu bang 0
                printf("\n[Decoupling] Hang %d co cac cot <= %d bang 0. Bo qua buoc k = %d.\n", k + 1, k, k);
                continue;
            }
        }

        // Thiet lap ma tran M va M1
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(i != k)
                {
                    if(i == j)
                    {
                        M[i][j] = 1.0f;
                        M1[i][j] = 1.0f;
                    }
                    else
                    {
                        M[i][j] = 0.0f;
                        M1[i][j] = 0.0f;
                    }
                }
                else
                {
                    M1[i][j] = A[k + 1][j];

                    if(j == k)
                        M[i][j] = 1.0f / A[k + 1][k];
                    else
                        M[i][j] = -A[k + 1][j] / A[k + 1][k];
                }
            }
        }

        // A = M1 * A * M
        nhanMaTran(A, M, B, n);
        nhanMaTran(M1, B, A, n);

        // C = C * M
        nhanMaTran(C, M, B, n);
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                C[i][j] = B[i][j];
            }
        }
    }
}

/*================= TINH GIA TRI DA THUC VA DAO HAM =================*/
void evaluate_poly(float coeffs[], int degree, float x, float *val, float *deriv)
{
    *val = coeffs[0];
    *deriv = 0.0f;

    for(int i = 1; i <= degree; i++)
    {
        *deriv = (*deriv) * x + *val;
        *val = (*val) * x + coeffs[i];
    }
}

/*================= NEWTON-RAPHSON TIM NGHIEM =================*/
float find_root_newton(float coeffs[], int degree, float start_x)
{
    float x = start_x;

    for(int iter = 0; iter < 500; iter++)
    {
        float val, deriv;
        evaluate_poly(coeffs, degree, x, &val, &deriv);

        if(fabs(deriv) < 1e-9)
        {
            x += 0.1f; // Nudge neu gap dao ham bang 0
            continue;
        }

        float dx = val / deriv;
        x -= dx;

        if(fabs(dx) < 1e-6)
            return x;
    }

    return x;
}

/*================= TIM TAT CA TRI RIENG THUC =================*/
int timTriRiengThuc(float coeffs[], int degree, float roots[])
{
    float current_coeffs[MAX + 1];

    for(int i = 0; i <= degree; i++)
        current_coeffs[i] = coeffs[i];

    int num_roots = 0;
    int deg = degree;

    // Cac gia tri doan ban dau phong phu de tim duoc nhieu nghiem thuc phan biet
    float guesses[] = {0.0f, 1.0f, -1.0f, 5.0f, -5.0f, 10.0f, -10.0f, 0.5f, -0.5f, 20.0f, -20.0f};
    int num_guesses = sizeof(guesses) / sizeof(guesses[0]);

    while(deg > 0)
    {
        float root = 0;
        bool found = false;

        for(int g = 0; g < num_guesses; g++)
        {
            float candidate = find_root_newton(current_coeffs, deg, guesses[g]);

            // Kiem tra lai xem candidate co phai la nghiem thuc su khong
            float val, deriv;
            evaluate_poly(current_coeffs, deg, candidate, &val, &deriv);

            if(fabs(val) < 1e-3)
            {
                // Kiem tra trung lap nghiem da tim thay
                bool duplicate = false;

                for(int r = 0; r < num_roots; r++)
                {
                    if(fabs(roots[r] - candidate) < 1e-3)
                    {
                        duplicate = true;
                        break;
                    }
                }

                if(!duplicate)
                {
                    root = candidate;
                    found = true;
                    break;
                }
            }
        }

        if(!found)
        {
            break; // Khong tim them duoc nghiem thuc nao
        }

        roots[num_roots++] = root;

        // Giam cap da thuc (Deflation): P(x) = (x - root) * Q(x)
        float next_coeffs[MAX + 1];
        next_coeffs[0] = current_coeffs[0];

        for(int i = 1; i < deg; i++)
        {
            next_coeffs[i] = current_coeffs[i] + root * next_coeffs[i - 1];
        }

        deg--;

        for(int i = 0; i <= deg; i++)
        {
            current_coeffs[i] = next_coeffs[i];
        }
    }

    return num_roots;
}

/*================= TINH VECTOR RIENG THUC =================*/
void tinhVectorRieng(float C[][MAX + 1], int n, float lambda, float X[])
{
    float Y[MAX + 1];

    // Vectơ rieng Y cua ma tran Frobenius tuong ung voi lambda la:
    // Y = [lambda^(n-1), lambda^(n-2), ..., lambda, 1]^T
    for(int j = 1; j <= n; j++)
    {
        Y[j] = powf(lambda, (float)(n - j));
    }

    // Vectơ rieng cua ma tran goc la X = C * Y
    for(int i = 1; i <= n; i++)
    {
        X[i] = 0.0f;
        for(int j = 1; j <= n; j++)
        {
            X[i] += C[i][j] * Y[j];
        }
    }
}

/*================= HIEN THI MA TRAN SQUARRE =================*/
void xuatMaTran(float A[][MAX + 1], int n)
{
    for(int i = 1; i <= n; i++)
    {
        printf("\n");
        for(int j = 1; j <= n; j++)
        {
            printf("%10.4f", A[i][j]);
        }
    }
    printf("\n");
}

/*================= MAIN =================*/
int main()
{
    float A[MAX + 1][MAX + 1];
    float A_orig[MAX + 1][MAX + 1];
    float C[MAX + 1][MAX + 1];

    int n = 0;
    int choice;
    bool checked_frobenius = false;
    bool has_matrix = false;

    do
    {
        printf("\n====================================");
        printf("\n CHUONG 6: PHUONG PHAP DANHILEPSKI");
        printf("\n====================================");
        printf("\n1. Nhap ma tran he so A");
        printf("\n2. Dua ma tran A ve dang Frobenius");
        printf("\n3. Tim cac tri rieng va vector rieng thuc");
        printf("\n0. Thoat");
        printf("\n====================================");
        printf("\nNhap lua chon: ");

        if(scanf("%d", &choice) != 1)
        {     printf("\nLua chon khong hop le! Vui long nhap lai.\n");
            clear_input_buffer();
            choice = -1;
            continue;
        }

        switch(choice)
        {
            case 1:
                while(1)
                {
                    printf("\nNhap kich thuoc ma tran n (1 den %d) = ", MAX);
                    if(scanf("%d", &n) == 1 && n >= 1 && n <= MAX)
                    {
                        break;
                    }
                    printf("Kich thuoc khong hop le! Vui long nhap lai.\n");
                    clear_input_buffer();
                }

                printf("\nNhap cac phan tu cua ma tran A:\n");
                for(int i = 1; i <= n; i++)
                {
                    for(int j = 1; j <= n; j++)
                    {
                        while(1)
                        {
                            printf("A[%d][%d] = ", i, j);
                            if(scanf("%f", &A[i][j]) == 1)
                            {
                                A_orig[i][j] = A[i][j];
                                break;
                            }
                            printf("Gia tri khong hop le! Vui long nhap lai.\n");
                            clear_input_buffer();
                        }
                    }
                }

                printf("\nMa tran A vua nhap:");
                xuatMaTran(A, n);
                has_matrix = true;
                checked_frobenius = false;
                break;

            case 2:
                if(!has_matrix)
                {
                    printf("\nVui long nhap ma tran A truoc (Chon 1)!\n");
                    break;
                }

                // Sao chep lai tu A_orig vi buoc truoc co the da thay doi A
                for(int i = 1; i <= n; i++)
                    for(int j = 1; j <= n; j++)
                        A[i][j] = A_orig[i][j];

                bool success;
                danhilepskiBienDoi(A, C, n, &success);

                if(success)
                {
                    printf("\nMa tran sau bien doi Frobenius (F):");
                    xuatMaTran(A, n);
                    printf("\nMa tran chuyen doi C:");
                    xuatMaTran(C, n);
                    checked_frobenius = true;
                }
                else
                {
                    printf("\nKhong the thuc hien bien doi Danilevsky!\n");
                }
                break;

            case 3:
                if(!has_matrix)
                {
                    printf("\nVui long nhap ma tran A truoc (Chon 1)!\n");
                    break;
                }

                // Neu chua bien doi Frobenius thi tu dong thuc hien
                if(!checked_frobenius)
                {
                    for(int i = 1; i <= n; i++)
                        for(int j = 1; j <= n; j++)
                            A[i][j] = A_orig[i][j];
                    
                    bool ok;
                    danhilepskiBienDoi(A, C, n, &ok);
                    if(!ok)
                    {
                        printf("\nKhong the dua ma tran ve dang Frobenius!\n");
                        break;
                    }
                    checked_frobenius = true;
                }

                // Lay cac he so cua da thuc dac trung tu hang dau cua ma tran Frobenius
                // P(lambda) = lambda^n + p_1*lambda^(n-1) + ... + p_n = 0
                // p_j = -F[1][j]
                float coeffs[MAX + 1];
                coeffs[0] = 1.0f; // He so lambda^n
                for(int j = 1; j <= n; j++)
                {
                    coeffs[j] = -A[1][j];
                }

                // In da thuc dac trung
                printf("\nDa thuc dac trung: P(lambda) = lambda^%d", n);
                for(int j = 1; j <= n; j++)
                {
                    float pj = coeffs[j];
                    int power = n - j;
                    if(fabs(pj) < 1e-5)
                        continue;

                    if(pj >= 0.0f)
                        printf(" + %.4f", pj);
                    else
                        printf(" - %.4f", -pj);

                    if(power > 1)
                        printf("lambda^%d", power);
                    else if(power == 1)
                        printf("lambda");
                }
                printf(" = 0\n");

                // Tim nghiem cua da thuc dac trung (Tri rieng thuc)
                float roots[MAX + 1];
                int num_roots = timTriRiengThuc(coeffs, n, roots);

                if(num_roots == 0)
                {
                    printf("\nKhong tim thay gia tri rieng thuc nao (co the tat ca la nghiem phuc)!\n");
                }
                else
                {
                    printf("\nTim thay %d gia tri rieng thuc:\n", num_roots);
                    for(int r = 0; r < num_roots; r++)
                    {
                        float lambda = roots[r];
                        printf("\n------------------------------------");
                        printf("\nTri rieng thuc lambda_%d = %.6f\n", r + 1, lambda);

                        // Tinh vector rieng X = C * Y
                        float X[MAX + 1];
                        tinhVectorRieng(C, n, lambda, X);

                        printf("Vector rieng tuong ung X_%d = [", r + 1);
                        for(int i = 1; i <= n; i++)
                        {
                            printf(" %.6f", X[i]);
                        }
                        printf(" ]^T\n");

                        // Kiem tra tinh dung dan: AX = lambda * X
                        printf("\nKiểm tra kiem chung AX = lambda * X:\n");
                        printf("  AX = [");
                        float AX[MAX + 1];
                        for(int i = 1; i <= n; i++)
                        {
                            AX[i] = 0.0f;
                            for(int j = 1; j <= n; j++)
                            {
                                AX[i] += A_orig[i][j] * X[j];
                            }
                            printf(" %.6f", AX[i]);
                        }
                        printf(" ]^T\n");

                        printf("  lX = [");
                        for(int i = 1; i <= n; i++)
                        {
                            printf(" %.6f", lambda * X[i]);
                        }
                        printf(" ]^T\n");
                    }
                }
                break;

            case 0:
                printf("\nKet thuc chuong trinh!\n");
                break;

            default:
                if(choice != -1)
                {
                    printf("\nLua chon khong hop le!\n");
                }
        }

    } while(choice != 0);

    return 0;
}
       