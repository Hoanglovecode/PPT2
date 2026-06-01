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

/* =========================================================
   CHUONG 7 - NOI SUY VA BINH PHUONG BE NHAT
   Bien dich:
      gcc -std=c99 -Wall -Wextra chuong7_noi_suy_bpbnn.c -o chuong7 -lm
   ========================================================= */

/* =========================================================
   HAM TIEN ICH CHUNG
   ========================================================= */

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

void in_ma_tran_mo_rong(double a[MAX][MAX + 1], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) printf("%13.6lf ", gan_bang_0(a[i][j]) ? 0.0 : a[i][j]);
        printf("\n");
    }
}

/* =========================================================
   GIAI HE PHUONG TRINH TUYEN TINH (dung cho binh phuong be nhat)
   ========================================================= */

void doi_dong_mo_rong(double a[MAX][MAX + 1], int r1, int r2, int n) {
    int j;
    double t;
    if (r1 == r2) return;
    for (j = 0; j <= n; j++) {
        t = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = t;
    }
}

int hang_ma_tran(double a[MAX][MAX + 1], int rows, int cols) {
    double b[MAX][MAX + 1], t, m;
    int i, j, k, col, pivot, rank = 0;

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            b[i][j] = a[i][j];

    for (col = 0; col < cols && rank < rows; col++) {
        pivot = rank;
        for (i = rank + 1; i < rows; i++) {
            if (absd(b[i][col]) > absd(b[pivot][col])) pivot = i;
        }
        if (absd(b[pivot][col]) < EPS) continue;

        if (pivot != rank) {
            for (j = 0; j < cols; j++) {
                t = b[rank][j];
                b[rank][j] = b[pivot][j];
                b[pivot][j] = t;
            }
        }

        for (i = 0; i < rows; i++) {
            if (i != rank && absd(b[i][col]) > EPS) {
                m = b[i][col] / b[rank][col];
                for (k = col; k < cols; k++) b[i][k] -= m * b[rank][k];
            }
        }
        rank++;
    }
    return rank;
}

int phan_loai_he(double a[MAX][MAX + 1], int n) {
    int rankA  = hang_ma_tran(a, n, n);
    int rankAb = hang_ma_tran(a, n, n + 1);
    if (rankA < rankAb) return 0;
    if (rankA < n)      return 2;
    return 1;
}

void bao_loi_he(int status) {
    if (status == 0)      printf("Ket luan: he vo nghiem.\n");
    else if (status == 2) printf("Ket luan: he co vo so nghiem.\n");
    else if (status == 3) printf("Loi tinh toan: gia tri qua lon hoac khong hop le.\n");
    else                  printf("Khong giai duoc voi du lieu hien tai.\n");
}

int giai_gauss(double a[MAX][MAX + 1], int n, double x[MAX]) {
    int i, j, k, pivot, loai;
    double m, s;

    loai = phan_loai_he(a, n);
    if (loai != 1) return loai;

    for (i = 0; i < n - 1; i++) {
        pivot = i;
        for (j = i + 1; j < n; j++) {
            if (absd(a[j][i]) > absd(a[pivot][i])) pivot = j;
        }
        if (absd(a[pivot][i]) < EPS) return phan_loai_he(a, n);
        doi_dong_mo_rong(a, i, pivot, n);

        for (j = i + 1; j < n; j++) {
            m = -a[j][i] / a[i][i];
            for (k = i; k <= n; k++) a[j][k] += a[i][k] * m;
        }
    }

    if (absd(a[n - 1][n - 1]) < EPS) return phan_loai_he(a, n);

    for (i = n - 1; i >= 0; i--) {
        s = 0;
        for (j = i + 1; j < n; j++) s += a[i][j] * x[j];
        if (absd(a[i][i]) < EPS) return phan_loai_he(a, n);
        x[i] = (a[i][n] - s) / a[i][i];
        if (!so_hop_le(x[i])) return 3;
    }
    return 1;
}

/* =========================================================
   HAM NHAP DU LIEU CHUONG 7
   ========================================================= */

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
    for (i = 0; i < m; i++)
        for (j = i + 1; j < m; j++)
            if (absd(x[i] - x[j]) < EPS) return 0;
    return 1;
}

int x_cach_deu(double x[MAX], int m) {
    int i;
    double h;
    if (m < 2) return 0;
    h = x[1] - x[0];
    if (absd(h) < EPS) return 0;
    for (i = 2; i < m; i++)
        if (absd((x[i] - x[i - 1]) - h) > 1e-8) return 0;
    return 1;
}

void canh_bao_ngoai_khoang(double x[MAX], int m, double c) {
    int i;
    double mn = x[0], mx = x[0];
    for (i = 1; i < m; i++) {
        if (x[i] < mn) mn = x[i];
        if (x[i] > mx) mx = x[i];
    }
    if (c < mn || c > mx)
        printf("Luu y: c nam ngoai [%.6lf, %.6lf], ket qua la ngoai suy nen co the kem chinh xac.\n", mn, mx);
}

/* =========================================================
   1. NOI SUY LAGRANGE TONG QUAT
   ========================================================= */

double lagrange_tong_quat(double x[MAX], double y[MAX], int m, double c) {
    double s = 0, p;
    int i, j;
    for (i = 0; i < m; i++) {
        p = 1;
        for (j = 0; j < m; j++) {
            if (j != i) p *= (c - x[j]) / (x[i] - x[j]);
        }
        s += y[i] * p;
    }
    return s;
}

/* =========================================================
   2. NOI SUY LAGRANGE VOI MOC CACH DEU
   ========================================================= */

double lagrange_cach_deu(double x[MAX], double y[MAX], int m, double c) {
    double h = x[1] - x[0];
    double t = (c - x[0]) / h;
    double s = 0, p;
    int i, j;

    for (i = 0; i < m; i++) {
        p = 1;
        for (j = 0; j < m; j++) {
            if (j != i) p *= (t - j) / (double)(i - j);
        }
        s += y[i] * p;
    }
    return s;
}

/* =========================================================
   3 & 4. NOI SUY AYKEN (dang 1 va dang 2)
   ========================================================= */

double ayken_dang1(double x[MAX], double y[MAX], int m, double c) {
    double w = 1, s = 0, d;
    int i, j;

    for (i = 0; i < m; i++)
        if (absd(c - x[i]) < EPS) return y[i];

    for (i = 0; i < m; i++) w *= (c - x[i]);

    for (i = 0; i < m; i++) {
        d = c - x[i];
        for (j = 0; j < m; j++)
            if (j != i) d *= (x[i] - x[j]);
        s += y[i] / d;
    }
    return w * s;
}

double ayken_dang2(double x[MAX], double y[MAX], int m, double c) {
    double p[MAX][MAX];
    int i, j;

    for (i = 0; i < m; i++) p[i][0] = y[i];
    for (j = 1; j < m; j++)
        for (i = j; i < m; i++)
            p[i][j] = ((c - x[i - j]) * p[i][j - 1] - (c - x[i]) * p[i - 1][j - 1]) / (x[i] - x[i - j]);

    return p[m - 1][m - 1];
}

/* =========================================================
   5. NOI SUY NEWTON BANG SAI PHAN TIEN
   ========================================================= */

void lap_bang_sai_phan(double y[MAX], double d[MAX][MAX], int m) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) d[i][j] = 0.0;
    for (i = 0; i < m; i++) d[i][0] = y[i];
    for (j = 1; j < m; j++)
        for (i = 0; i < m - j; i++)
            d[i][j] = d[i + 1][j - 1] - d[i][j - 1];
}

void in_bang_sai_phan(double x[MAX], double d[MAX][MAX], int m) {
    int i, j;
    printf("Bang sai phan tien:\n");
    printf("%12s %14s", "x", "y");
    for (j = 1; j < m; j++) printf(" %14s%d", "Delta^", j);
    printf("\n");
    for (i = 0; i < m; i++) {
        printf("%12.6lf ", gan_bang_0(x[i]) ? 0.0 : x[i]);
        for (j = 0; j < m - i; j++) printf("%14.6lf ", gan_bang_0(d[i][j]) ? 0.0 : d[i][j]);
        printf("\n");
    }
}

double newton_sai_phan_tien(double x[MAX], double y[MAX], int m, double c) {
    double d[MAX][MAX];
    double h = x[1] - x[0];
    double t = (c - x[0]) / h;
    double kq, term;
    int i;

    lap_bang_sai_phan(y, d, m);
    kq = d[0][0];
    term = 1;
    for (i = 1; i < m; i++) {
        term *= (t - (i - 1)) / i;
        kq += d[0][i] * term;
    }
    return kq;
}

/* =========================================================
   6. NOI SUY HECMIT CAP 1
   ========================================================= */

double hermite_cap1(double x[MAX], double y[MAX], double yp[MAX], int m, double c) {
    double z[MAX2], Q[MAX2][MAX2];
    double result, term;
    int N = 2 * m;
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) Q[i][j] = 0;

    for (i = 0; i < m; i++) {
        z[2 * i]     = x[i];
        z[2 * i + 1] = x[i];
        Q[2 * i][0]     = y[i];
        Q[2 * i + 1][0] = y[i];
        Q[2 * i + 1][1] = yp[i];
        if (i == 0) Q[2 * i][1] = yp[i];
        else Q[2 * i][1] = (Q[2 * i][0] - Q[2 * i - 1][0]) / (z[2 * i] - z[2 * i - 1]);
    }

    for (j = 2; j < N; j++)
        for (i = j; i < N; i++)
            Q[i][j] = (Q[i][j - 1] - Q[i - 1][j - 1]) / (z[i] - z[i - j]);

    result = Q[0][0];
    term = 1;
    for (i = 1; i < N; i++) {
        term *= (c - z[i - 1]);
        result += Q[i][i] * term;
    }
    return result;
}

/* =========================================================
   7. BINH PHUONG BE NHAT
   ========================================================= */

int giai_binh_phuong_da_thuc(double x[MAX], double y[MAX], int m, int bac, double he_so[MAX]) {
    double a[MAX][MAX + 1];
    int i, j, k, status;

    for (i = 0; i <= bac; i++) {
        for (j = 0; j <= bac; j++) {
            a[i][j] = 0;
            for (k = 0; k < m; k++) a[i][j] += pow(x[k], i + j);
        }
        a[i][bac + 1] = 0;
        for (k = 0; k < m; k++) a[i][bac + 1] += y[k] * pow(x[k], i);
    }

    status = giai_gauss(a, bac + 1, he_so);
    if (status != 1) bao_loi_he(status);
    return status == 1;
}

double tinh_da_thuc_xap_xi(double he_so[MAX], int bac, double x) {
    double s = 0;
    int i;
    for (i = 0; i <= bac; i++) s += he_so[i] * pow(x, i);
    return s;
}

double sse_da_thuc(double x[MAX], double y[MAX], int m, double he_so[MAX], int bac) {
    int i;
    double e, sse = 0;
    for (i = 0; i < m; i++) {
        e = y[i] - tinh_da_thuc_xap_xi(he_so, bac, x[i]);
        sse += e * e;
    }
    return sse;
}

/* 7a. BPBNN - Da thuc */
void bpbnn_da_thuc(void) {
    in_tieu_de("BINH PHUONG BE NHAT - DA THUC");
    double x[MAX], y[MAX], he_so[MAX];
    int m, bac, i;

    nhap_bang_xy(x, y, &m);
    bac = doc_int_range("Nhap bac da thuc can xap xi (1..m-1): ", 1, m - 1);

    if (!giai_binh_phuong_da_thuc(x, y, m, bac, he_so)) return;

    printf("Ham xap xi: y = ");
    for (i = 0; i <= bac; i++) {
        if (i == 0) printf("%.10lf", he_so[i]);
        else printf(" + (%.10lf)*x^%d", he_so[i], i);
    }
    printf("\nTong binh phuong sai so S = %.10lf\n", sse_da_thuc(x, y, m, he_so, bac));
}

/* 7b. BPBNN - Ham mu */
void bpbnn_ham_mu(void) {
    in_tieu_de("BINH PHUONG BE NHAT - HAM MU");
    double x[MAX], y[MAX], Y[MAX], he_so[MAX], a, b, e, sse = 0;
    int m, i;

    nhap_bang_xy(x, y, &m);
    for (i = 0; i < m; i++) {
        if (y[i] <= 0) {
            printf("Dang y = a*e^(b*x) can y > 0 tai moi moc.\n");
            return;
        }
        Y[i] = log(y[i]);
    }

    if (!giai_binh_phuong_da_thuc(x, Y, m, 1, he_so)) return;
    a = exp(he_so[0]);
    b = he_so[1];
    for (i = 0; i < m; i++) {
        e = y[i] - a * exp(b * x[i]);
        sse += e * e;
    }
    printf("Dang y = a*e^(b*x)\n");
    printf("a = %.10lf\n", a);
    printf("b = %.10lf\n", b);
    printf("Tong binh phuong sai so S = %.10lf\n", sse);
}

/* 7c. BPBNN - Ham luy thua */
void bpbnn_ham_luy_thua(void) {
    in_tieu_de("BINH PHUONG BE NHAT - HAM LUY THUA");
    double x[MAX], y[MAX], X[MAX], Y[MAX], he_so[MAX], a, b, e, sse = 0;
    int m, i;

    nhap_bang_xy(x, y, &m);
    for (i = 0; i < m; i++) {
        if (x[i] <= 0 || y[i] <= 0) {
            printf("Dang y = a*x^b can x > 0 va y > 0 tai moi moc.\n");
            return;
        }
        X[i] = log(x[i]);
        Y[i] = log(y[i]);
    }

    if (!giai_binh_phuong_da_thuc(X, Y, m, 1, he_so)) return;
    a = exp(he_so[0]);
    b = he_so[1];
    for (i = 0; i < m; i++) {
        e = y[i] - a * pow(x[i], b);
        sse += e * e;
    }
    printf("Dang y = a*x^b\n");
    printf("a = %.10lf\n", a);
    printf("b = %.10lf\n", b);
    printf("Tong binh phuong sai so S = %.10lf\n", sse);
}

/* 7d. BPBNN - Ham luong giac */
void bpbnn_luong_giac(void) {
    in_tieu_de("BINH PHUONG BE NHAT - HAM LUONG GIAC");
    double x[MAX], y[MAX], a[MAX][MAX + 1], he_so[MAX];
    double phi[3], psi[3], du_doan, e, sse = 0;
    int m, i, r, c, status;

    nhap_bang_xy(x, y, &m);
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 4; c++) a[r][c] = 0;
    }

    for (i = 0; i < m; i++) {
        phi[0] = 1.0;
        phi[1] = cos(x[i]);
        phi[2] = sin(x[i]);
        for (r = 0; r < 3; r++) {
            for (c = 0; c < 3; c++) a[r][c] += phi[r] * phi[c];
            a[r][3] += y[i] * phi[r];
        }
    }

    status = giai_gauss(a, 3, he_so);
    if (status != 1) {
        bao_loi_he(status);
        return;
    }

    for (i = 0; i < m; i++) {
        psi[0] = 1.0;
        psi[1] = cos(x[i]);
        psi[2] = sin(x[i]);
        du_doan = he_so[0] + he_so[1] * psi[1] + he_so[2] * psi[2];
        e = y[i] - du_doan;
        sse += e * e;
    }

    printf("Dang y = a + b*cos(x) + c*sin(x)\n");
    printf("a = %.10lf\n", he_so[0]);
    printf("b = %.10lf\n", he_so[1]);
    printf("c = %.10lf\n", he_so[2]);
    printf("Tong binh phuong sai so S = %.10lf\n", sse);
}

/* =========================================================
   HAM CHAY TUNG PHUONG PHAP NOI SUY
   ========================================================= */

void chay_noi_suy_co_ban(int loai) {
    double x[MAX], y[MAX], c, kq, d[MAX][MAX];
    int m;

    in_tieu_de("NOI SUY");
    nhap_bang_xy(x, y, &m);
    if (!x_phan_biet(x, m)) {
        printf("Cac moc x bi trung nhau, khong the noi suy vi se chia cho 0.\n");
        return;
    }
    if ((loai == 2 || loai == 5) && !x_cach_deu(x, m)) {
        printf("Phuong phap da chon can cac moc x cach deu. Vui long kiem tra lai bang du lieu.\n");
        return;
    }

    c = doc_double("Nhap gia tri can tinh c = ");
    canh_bao_ngoai_khoang(x, m, c);

    if      (loai == 1) kq = lagrange_tong_quat(x, y, m, c);
    else if (loai == 2) kq = lagrange_cach_deu(x, y, m, c);
    else if (loai == 3) kq = ayken_dang1(x, y, m, c);
    else if (loai == 4) kq = ayken_dang2(x, y, m, c);
    else if (loai == 5) kq = newton_sai_phan_tien(x, y, m, c);
    else return;

    if (loai == 5) {
        in_muc("Bang sai phan");
        lap_bang_sai_phan(y, d, m);
        in_bang_sai_phan(x, d, m);
    }

    in_muc("Ket qua");
    printf("Gia tri gan dung f(%.10lf) = %.10lf\n", c, kq);
}

void chay_bang_sai_phan(void) {
    double x[MAX], y[MAX], d[MAX][MAX];
    int m;
    in_tieu_de("BANG SAI PHAN");
    nhap_bang_xy(x, y, &m);
    if (!x_cach_deu(x, m))
        printf("Luu y: bang sai phan Newton nen dung voi cac moc x cach deu.\n");
    lap_bang_sai_phan(y, d, m);
    in_muc("Ket qua");
    in_bang_sai_phan(x, d, m);
}

void chay_hermite(void) {
    double x[MAX], y[MAX], yp[MAX], c, kq;
    int m, i;
    char prompt[96];

    in_tieu_de("NOI SUY HECMIT CAP 1");
    printf("Can nhap f(x) va dao ham f'(x) tai tung moc.\n");
    nhap_bang_xy(x, y, &m);
    if (!x_phan_biet(x, m)) {
        printf("Cac moc x bi trung nhau, khong the lap bang Hecmit.\n");
        return;
    }
    if (2 * m > MAX2) {
        printf("So moc qua lon cho bang Hecmit cap 1.\n");
        return;
    }

    in_muc("Nhap dao ham cap 1");
    for (i = 0; i < m; i++) {
        sprintf(prompt, "f'(%g) = ", x[i]);
        yp[i] = doc_double(prompt);
    }
    c = doc_double("Nhap gia tri can tinh c = ");
    canh_bao_ngoai_khoang(x, m, c);

    kq = hermite_cap1(x, y, yp, m, c);
    in_muc("Ket qua");
    printf("Gia tri gan dung f(%.10lf) = %.10lf\n", c, kq);
}

/* =========================================================
   MENU CHUONG 7
   ========================================================= */

void menu_chuong7(void) {
    int chon;
    do {
        in_tieu_de("CHUONG 7 - NOI SUY VA BINH PHUONG BE NHAT");
        printf("1.  Noi suy Lagrange tong quat\n");
        printf("2.  Noi suy Lagrange voi moc cach deu\n");
        printf("3.  Noi suy Ayken dang 1\n");
        printf("4.  Noi suy Ayken dang 2\n");
        printf("5.  Noi suy Newton bang sai phan tien\n");
        printf("6.  Lap va in bang sai phan\n");
        printf("7.  Noi suy Hecmit cap 1\n");
        printf("8.  Binh phuong be nhat: y = a0 + a1*x + a2*x^2 + ...\n");
        printf("9.  Binh phuong be nhat: y = a*e^(b*x)\n");
        printf("10. Binh phuong be nhat: y = a*x^b\n");
        printf("11. Binh phuong be nhat: y = a + b*cos(x) + c*sin(x)\n");
        printf("0.  Thoat\n");
        chon = doc_int_range("Chon phuong phap: ", 0, 11);

        if      (chon >= 1 && chon <= 5) chay_noi_suy_co_ban(chon);
        else if (chon == 6)  chay_bang_sai_phan();
        else if (chon == 7)  chay_hermite();
        else if (chon == 8)  bpbnn_da_thuc();
        else if (chon == 9)  bpbnn_ham_mu();
        else if (chon == 10) bpbnn_ham_luy_thua();
        else if (chon == 11) bpbnn_luong_giac();
    } while (chon != 0);
}

/* =========================================================
   MAIN
   ========================================================= */

int main(void) {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    menu_chuong7();
    printf("Da thoat chuong trinh.\n");
    return 0;
}