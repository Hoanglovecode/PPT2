#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ll long long
#define MAX 30
#define MAX2 60
#define EPS 1e-12
#define BIG 1e100

double absd(double x) {
    return x < 0 ? -x : x;
}

int gan_bang_0(double x) {
    return absd(x) < EPS;
}

int so_hop_le(double x) {
    return isfinite(x) && absd(x) < BIG;
}

void in_duong_ke(void) {
    printf("------------------------------------------------------------\n");
}

int doc_int_range(const char *msg, int min, int max) {
    char line[256], extra;
    long value;
    while (1) {
        printf("%s", msg);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nKhong doc duoc du lieu. Ket thuc chuong trinh.\n");
            exit(1);
        }
        if (sscanf(line, " %ld %c", &value, &extra) == 1 && value >= min && value <= max) {
            return (int)value;
        }
        printf("Gia tri khong hop le. Vui long nhap so nguyen trong [%d, %d].\n", min, max);
    }
}

double doc_double(const char *msg) {
    char line[256], extra;
    double value;
    while (1) {
        printf("%s", msg);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nKhong doc duoc du lieu. Ket thuc chuong trinh.\n");
            exit(1);
        }
        if (sscanf(line, " %lf %c", &value, &extra) == 1 && so_hop_le(value)) {
            return value;
        }
        printf("Gia tri khong hop le. Vui long nhap mot so thuc hop le.\n");
    }
}

double doc_double_duong(const char *msg) {
    double value;
    while (1) {
        value = doc_double(msg);
        if (value > 0) return value;
        printf("Gia tri phai lon hon 0.\n");
    }
}

int doc_co_khong(const char *msg) {
    return doc_int_range(msg, 0, 1);
}

void in_tieu_de(const char *ten) {
    in_duong_ke();
    printf("%s\n", ten);
    in_duong_ke();
}

void in_muc(const char *ten) {
    printf("\n[%s]\n", ten);
}

void in_vector(const char *ten, double x[MAX], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%s[%d] = %.10lf\n", ten, i + 1, gan_bang_0(x[i]) ? 0.0 : x[i]);
    }
}

void in_ma_tran_vuong(double a[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("%13.6lf ", gan_bang_0(a[i][j]) ? 0.0 : a[i][j]);
        printf("\n");
    }
}

void in_ma_tran_mo_rong(double a[MAX][MAX + 1], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) printf("%13.6lf ", gan_bang_0(a[i][j]) ? 0.0 : a[i][j]);
        printf("\n");
    }
}

void sao_chep_ma_tran_mo_rong(double src[MAX][MAX + 1], double dst[MAX][MAX + 1], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j <= n; j++)
            dst[i][j] = src[i][j];
}

void sao_chep_ma_tran_vuong(double src[MAX][MAX], double dst[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dst[i][j] = src[i][j];
}

void nhap_ma_tran_mo_rong(double a[MAX][MAX + 1], int *n) {
    int i, j;
    char prompt[96];
    in_muc("Nhap he phuong trinh A*x = b");
    printf("Dang nhap: moi dong gom cac he so cua mot phuong trinh va so hang tu do.\n");
    printf("Vi du voi 3 an: a1 a2 a3 b, tuong ung a1*x1 + a2*x2 + a3*x3 = b.\n");
    *n = doc_int_range("Nhap so an n (1..30): ", 1, MAX);
    for (i = 0; i < *n; i++) {
        printf("Dong %d:\n", i + 1);
        for (j = 0; j <= *n; j++) {
            if (j < *n) sprintf(prompt, "  he so cua x%d = ", j + 1);
            else sprintf(prompt, "  ve phai b%d = ", i + 1);
            a[i][j] = doc_double(prompt);
        }
    }
}

void nhap_ma_tran_vuong(double a[MAX][MAX], int *n) {
    int i, j;
    char prompt[96];
    in_muc("Nhap ma tran vuong A");
    *n = doc_int_range("Nhap cap ma tran n (1..30): ", 1, MAX);
    for (i = 0; i < *n; i++) {
        printf("Dong %d:\n", i + 1);
        for (j = 0; j < *n; j++) {
            sprintf(prompt, "  a[%d][%d] = ", i + 1, j + 1);
            a[i][j] = doc_double(prompt);
        }
    }
}

void nhap_bang_xy(double x[MAX], double y[MAX], int *m) {
    int i;
    char prompt[96];
    in_muc("Nhap bang gia tri (x, y)");
    printf("Nhap cac moc x khac nhau. Voi bang sai phan Newton, cac moc x can cach deu.\n");
    *m = doc_int_range("Nhap so moc du lieu m (2..30): ", 2, MAX);
    for (i = 0; i < *m; i++) {
        sprintf(prompt, "x[%d] = ", i);
        x[i] = doc_double(prompt);
        sprintf(prompt, "y[%d] = ", i);
        y[i] = doc_double(prompt);
    }
}

int x_phan_biet(double x[MAX], int m) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = i + 1; j < m; j++) {
            if (absd(x[i] - x[j]) < EPS) return 0;
        }
    }
    return 1;
}

int x_cach_deu(double x[MAX], int m) {
    int i;
    double h;
    if (m < 2) return 0;
    h = x[1] - x[0];
    if (absd(h) < EPS) return 0;
    for (i = 2; i < m; i++) {
        if (absd((x[i] - x[i - 1]) - h) > 1e-8) return 0;
    }
    return 1;
}

void canh_bao_ngoai_khoang(double x[MAX], int m, double c) {
    int i;
    double mn = x[0], mx = x[0];
    for (i = 1; i < m; i++) {
        if (x[i] < mn) mn = x[i];
        if (x[i] > mx) mx = x[i];
    }
    if (c < mn || c > mx) {
        printf("Luu y: c nam ngoai [%.6lf, %.6lf], ket qua la ngoai suy nen co the kem chinh xac.\n", mn, mx);
    }
}

double horner_da_thuc(double a[], int bac, double x) {
    int i;
    double p = a[0];
    for (i = 1; i <= bac; i++) p = p * x + a[i];
    return p;
}

void nhap_da_thuc_tong_quat(double hs[], int *bac) {
    int i;
    char prompt[120];
    in_muc("Nhap da thuc P(x)");
    printf("Dang nhap: P(x) = a0*x^n + a1*x^(n-1) + ... + an.\n");
    *bac = doc_int_range("Nhap bac n cua da thuc (0..30): ", 0, MAX);
    for (i = 0; i <= *bac; i++) {
        sprintf(prompt, "he so cua x^%d = ", *bac - i);
        hs[i] = doc_double(prompt);
    }
}

double tich_phan_hinh_thang_da_thuc(double hs[], int bac, double a, double b, int n) {
    int i;
    double h = (b - a) / n;
    double s = (horner_da_thuc(hs, bac, a) + horner_da_thuc(hs, bac, b)) / 2.0;
    for (i = 1; i <= n - 1; i++) {
        s += horner_da_thuc(hs, bac, a + i * h);
    }
    return h * s;
}

double tich_phan_parabol_da_thuc(double hs[], int bac, double a, double b, int so_doan_chan) {
    int i;
    double h = (b - a) / so_doan_chan;
    double s = horner_da_thuc(hs, bac, a) + horner_da_thuc(hs, bac, b);
    for (i = 1; i <= so_doan_chan - 1; i++) {
        if (i % 2 == 1) s += 4.0 * horner_da_thuc(hs, bac, a + i * h);
        else s += 2.0 * horner_da_thuc(hs, bac, a + i * h);
    }
    return h * s / 3.0;
}

/*
   Tinh trong so Newton-Cotes dong mot cach tong quat.
   Xet cac nut 0, 1, ..., n tren doan chuan [0,n].
   w[i] = tich phan tu 0 den n cua da thuc Lagrange co so L_i(t).
   Khi do: integral_a^b f(x) dx gan bang h * sum(w[i]*f(a+i*h)), h=(b-a)/n.
*/
int trong_so_newton_cotes_tong_quat(int n, double w[]) {
    double coef[MAX + 1], next[MAX + 1];
    double denom, integral;
    int i, j, k, deg;

    if (n < 1 || n > 10) return 0; /* Gioi han n de giam sai so lam tron khi tinh trong so. */

    for (i = 0; i <= n; i++) {
        for (k = 0; k <= n; k++) coef[k] = 0.0;
        coef[0] = 1.0;
        deg = 0;
        denom = 1.0;

        for (j = 0; j <= n; j++) {
            if (j == i) continue;
            for (k = 0; k <= n; k++) next[k] = 0.0;
            /* nhan voi (t - j) */
            for (k = 0; k <= deg; k++) {
                next[k] += -j * coef[k];
                next[k + 1] += coef[k];
            }
            deg++;
            denom *= (double)(i - j);
            for (k = 0; k <= deg; k++) coef[k] = next[k];
        }

        integral = 0.0;
        for (k = 0; k <= n; k++) {
            integral += coef[k] * pow((double)n, k + 1) / (k + 1);
        }
        w[i] = integral / denom;
        if (!so_hop_le(w[i])) return 0;
    }
    return 1;
}

double tich_phan_newton_cotes_da_thuc(double hs[], int bac, double a, double b, int n, int *ok) {
    double w[MAX + 1], h, s = 0.0;
    int i;
    *ok = 0;
    if (!trong_so_newton_cotes_tong_quat(n, w)) return 0.0;
    h = (b - a) / n;
    for (i = 0; i <= n; i++) s += w[i] * horner_da_thuc(hs, bac, a + i * h);
    *ok = 1;
    return h * s;
}

void nhap_bang_y_cho_tich_phan(double y[], int *n, double *h) {
    int i;
    char prompt[80];
    in_muc("Nhap bang gia tri de tinh tich phan");
    printf("Bang gom y[0], y[1], ..., y[n] voi khoang cach deu h.\n");
    *n = doc_int_range("Nhap so doan chia n (1..30): ", 1, MAX);
    *h = doc_double_duong("Nhap khoang cach h (>0): ");
    for (i = 0; i <= *n; i++) {
        sprintf(prompt, "y[%d] = ", i);
        y[i] = doc_double(prompt);
    }
}

double tich_phan_hinh_thang_tu_bang(double y[], int n, double h) {
    int i;
    double s = (y[0] + y[n]) / 2.0;
    for (i = 1; i <= n - 1; i++) s += y[i];
    return h * s;
}

double tich_phan_parabol_tu_bang(double y[], int n, double h) {
    int i;
    double s = y[0] + y[n];
    for (i = 1; i <= n - 1; i++) {
        if (i % 2 == 1) s += 4.0 * y[i];
        else s += 2.0 * y[i];
    }
    return h * s / 3.0;
}

double tich_phan_newton_cotes_tu_bang(double y[], int n, double h, int *ok) {
    double w[MAX + 1], s = 0.0;
    int i;
    *ok = 0;
    if (!trong_so_newton_cotes_tong_quat(n, w)) return 0.0;
    for (i = 0; i <= n; i++) s += w[i] * y[i];
    *ok = 1;
    return h * s;
}

void in_goi_y_du_lieu_chuong8(void) {
    in_muc("Cach chon du lieu");
    printf("- Co bang gia tri: dung y[0..n] va h.\n");
    printf("- Co ham da thuc: nhap bac, he so, can duoi a va can tren b.\n");
}

void tich_phan_tu_bang_tong_quat(void) {
    double y[MAX + 1], h, kq;
    int n, chon, ok;

    in_tieu_de("TINH TICH PHAN TU BANG GIA TRI");
    in_goi_y_du_lieu_chuong8();
    nhap_bang_y_cho_tich_phan(y, &n, &h);

    printf("\nChon cong thuc tinh:\n");
    printf("1. Hinh thang\n");
    printf("2. Parabol/Simpson, can n chan\n");
    printf("3. Newton-Cotes, nen dung n <= 10\n");
    chon = doc_int_range("Chon cong thuc: ", 1, 3);

    in_muc("Ket qua");
    if (chon == 1) {
        kq = tich_phan_hinh_thang_tu_bang(y, n, h);
        printf("Tich phan gan dung = %.10lf\n", kq);
    } else if (chon == 2) {
        if (n % 2 != 0) {
            printf("Cong thuc Parabol/Simpson can n la so chan.\n");
            return;
        }
        kq = tich_phan_parabol_tu_bang(y, n, h);
        printf("Tich phan gan dung = %.10lf\n", kq);
    } else {
        if (n > 10) {
            printf("n qua lon de tinh Newton-Cotes on dinh. Vui long dung n <= 10.\n");
            return;
        }
        kq = tich_phan_newton_cotes_tu_bang(y, n, h, &ok);
        if (ok) printf("Tich phan gan dung = %.10lf\n", kq);
        else printf("Khong tinh duoc trong so Newton-Cotes.\n");
    }
}

void tich_phan_tu_da_thuc_tong_quat(void) {
    double hs[MAX + 1], a, b, kq;
    int bac, chon, n, ok;

    in_tieu_de("TINH TICH PHAN CUA DA THUC");
    in_goi_y_du_lieu_chuong8();
    nhap_da_thuc_tong_quat(hs, &bac);
    a = doc_double("Nhap can duoi a = ");
    b = doc_double("Nhap can tren b = ");
    if (absd(a - b) < EPS) {
        printf("a = b nen tich phan bang 0.\n");
        return;
    }

    printf("\nChon cong thuc tinh:\n");
    printf("1. Hinh thang ghep\n");
    printf("2. Parabol/Simpson ghep, can n chan\n");
    printf("3. Newton-Cotes, chon n trong [1..10]\n");
    chon = doc_int_range("Chon cong thuc: ", 1, 3);

    if (chon == 1) {
        n = doc_int_range("Nhap so doan chia n (1..100000): ", 1, 100000);
        kq = tich_phan_hinh_thang_da_thuc(hs, bac, a, b, n);
        in_muc("Ket qua");
        printf("Tich phan gan dung = %.10lf\n", kq);
    } else if (chon == 2) {
        n = doc_int_range("Nhap so doan chia chan n (2..100000): ", 2, 100000);
        if (n % 2 != 0) {
            printf("n phai la so chan de dung cong thuc Parabol/Simpson.\n");
            return;
        }
        kq = tich_phan_parabol_da_thuc(hs, bac, a, b, n);
        in_muc("Ket qua");
        printf("Tich phan gan dung = %.10lf\n", kq);
    } else {
        n = doc_int_range("Nhap bac Newton-Cotes n (1..10): ", 1, 10);
        kq = tich_phan_newton_cotes_da_thuc(hs, bac, a, b, n, &ok);
        in_muc("Ket qua");
        if (ok) printf("Tich phan gan dung = %.10lf\n", kq);
        else printf("Khong tinh duoc trong so Newton-Cotes.\n");
    }
}

void menu_chuong8(void) {
    int chon;
    do {
        in_tieu_de("CHUONG 8 - TINH GAN DUNG TICH PHAN XAC DINH");
        printf("1. Tinh tu bang gia tri y[0..n] voi khoang cach h\n");
        printf("2. Tinh tu da thuc P(x) tren doan [a, b]\n");
        printf("0. Quay lai menu chinh\n");
        chon = doc_int_range("Chon kieu du lieu: ", 0, 2);

        if (chon == 1) tich_phan_tu_bang_tong_quat();
        else if (chon == 2) tich_phan_tu_da_thuc_tong_quat();
    } while (chon != 0);
}
int main(){
 menu_chuong8();
 return 0;
}