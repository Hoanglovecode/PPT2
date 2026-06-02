#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 30
#define MAX2 60
#define EPS 1e-12
#define BIG 1e100

/* =========================================================
   CHUONG TRINH PHUONG PHAP TINH - CHUONG 5, 6, 7, 8
   Ngon ngu: C99
   Muc tieu: nhap du lieu tong quat, menu de dung, ket qua ro rang.
   Bien dich:
      gcc -std=c99 -Wall -Wextra phuong_phap_tinh_chuong_5_8_ascii_clean.c -o pptinh -lm
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

void in_menu(const char *cac_tuy_chon[], int n_tuy_chon) {
    int max_w = 60;
    int i, j, p;
    for (i = 0; i < n_tuy_chon; i++) {
        int char_len = 0;
        j = 0;
        while (cac_tuy_chon[i][j] != '\0') {
            if ((cac_tuy_chon[i][j] & 0xC0) != 0x80) char_len++;
            j++;
        }
        if (char_len > max_w - 6) max_w = char_len + 6;
    }

    printf("┌");
    for (i = 0; i < max_w - 2; i++) printf("─");
    printf("┐\n");

    for (i = 0; i < n_tuy_chon; i++) {
        int char_len = 0;
        j = 0;
        while (cac_tuy_chon[i][j] != '\0') {
            if ((cac_tuy_chon[i][j] & 0xC0) != 0x80) char_len++;
            j++;
        }
        int padding = max_w - 4 - char_len;
        printf("│ %s", cac_tuy_chon[i]);
        for (p = 0; p < padding; p++) printf(" ");
        printf(" │\n");
    }

    printf("└");
    for (i = 0; i < max_w - 2; i++) printf("─");
    printf("┘\n");
}

int doc_int_range(const char *msg, int min, int max) {
    char line[256], extra;
    long value;
    while (1) {
        printf("%s", msg);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nKhông đọc được dữ liệu. Kết thúc chương trình.\n");
            exit(1);
        }
        if (sscanf(line, " %ld %c", &value, &extra) == 1 && value >= min && value <= max) {
            return (int)value;
        }
        printf("Giá trị không hợp lệ. Vui lòng nhập số nguyên trong [%d, %d].\n", min, max);
    }
}

double doc_double(const char *msg) {
    char line[256], extra;
    double value;
    while (1) {
        printf("%s", msg);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nKhông đọc được dữ liệu. Kết thúc chương trình.\n");
            exit(1);
        }
        if (sscanf(line, " %lf %c", &value, &extra) == 1 && so_hop_le(value)) {
            return value;
        }
        printf("Giá trị không hợp lệ. Vui lòng nhập một số thực hợp lệ.\n");
    }
}

double doc_double_duong(const char *msg) {
    double value;
    while (1) {
        value = doc_double(msg);
        if (value > 0) return value;
        printf("Giá trị phải lớn hơn 0.\n");
    }
}

int doc_co_khong(const char *msg) {
    return doc_int_range(msg, 0, 1);
}

void in_tieu_de(const char *ten) {
    int max_width = 70;
    int char_len = 0;
    int i = 0;
    while (ten[i] != '\0') {
        if ((ten[i] & 0xC0) != 0x80) {
            char_len++;
        }
        i++;
    }
    int padding = max_width - 4 - char_len;
    if (padding < 0) padding = 0;
    int pad_left = padding / 2;
    int pad_right = padding - pad_left;

    printf("┌");
    for (i = 0; i < max_width - 2; i++) printf("─");
    printf("┐\n");

    printf("│ ");
    for (i = 0; i < pad_left; i++) printf(" ");
    printf("%s", ten);
    for (i = 0; i < pad_right; i++) printf(" ");
    printf(" │\n");

    printf("└");
    for (i = 0; i < max_width - 2; i++) printf("─");
    printf("┘\n");
}

void in_muc(const char *ten) {
    printf("\n❖ %s\n", ten);
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
    in_muc("Nhập hệ phương trình A*x = b");
    printf("Dạng nhập: mỗi dòng gồm các hệ số của một phương trình và số hạng tự do.\n");
    printf("Ví dụ với 3 ẩn: a1 a2 a3 b, tương ứng a1*x1 + a2*x2 + a3*x3 = b.\n");
    *n = doc_int_range("Nhập số ẩn n (1..30): ", 1, MAX);
    for (i = 0; i < *n; i++) {
        printf("Dòng %d:\n", i + 1);
        for (j = 0; j <= *n; j++) {
            if (j < *n) sprintf(prompt, "  hệ số của x%d = ", j + 1);
            else sprintf(prompt, "  vế phải b%d = ", i + 1);
            a[i][j] = doc_double(prompt);
        }
    }
}

void nhap_ma_tran_vuong(double a[MAX][MAX], int *n) {
    int i, j;
    char prompt[96];
    in_muc("Nhập ma trận vuông A");
    *n = doc_int_range("Nhập cấp ma trận n (1..30): ", 1, MAX);
    for (i = 0; i < *n; i++) {
        printf("Dòng %d:\n", i + 1);
        for (j = 0; j < *n; j++) {
            sprintf(prompt, "  a[%d][%d] = ", i + 1, j + 1);
            a[i][j] = doc_double(prompt);
        }
    }
}

void nhap_bang_xy(double x[MAX], double y[MAX], int *m) {
    int i;
    char prompt[96];
    in_muc("Nhập bảng giá trị (x, y)");
    printf("Nhập các mốc x khác nhau. Với bảng sai phân Newton, các mốc x cần cách đều.\n");
    *m = doc_int_range("Nhập số mốc dữ liệu m (2..30): ", 2, MAX);
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
        printf("Lưu ý: c nằm ngoài [%.6lf, %.6lf], kết quả là ngoại suy nên có thể kém chính xác.\n", mn, mx);
    }
}

/* =========================================================
   CHUONG 5 - GIAI HE PHUONG TRINH TUYEN TINH
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

void doi_dong_vuong(double a[MAX][MAX], int r1, int r2, int n) {
    int j;
    double t;
    if (r1 == r2) return;
    for (j = 0; j < n; j++) {
        t = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = t;
    }
}

int tim_hoan_vi_cheo(double a[MAX][MAX + 1], int n, int cot, int used[MAX], int perm[MAX]) {
    int row;
    if (cot == n) return 1;
    for (row = 0; row < n; row++) {
        if (!used[row] && absd(a[row][cot]) > EPS) {
            used[row] = 1;
            perm[cot] = row;
            if (tim_hoan_vi_cheo(a, n, cot + 1, used, perm)) return 1;
            used[row] = 0;
        }
    }
    return 0;
}

int de_quy_cheo_troi(double a[MAX][MAX + 1], int n, int cot, int used[MAX], int perm[MAX], int kieu) {
    int row;
    if (cot == n) return 1;
    for (row = 0; row < n; row++) {
        if (!used[row]) {
            double tong = 0;
            int col;
            for (col = 0; col < n; col++) {
                if (col != cot) tong += absd(a[row][col]);
            }
            int ok = 0;
            if (kieu == 0) { // Cheo troi nghiem ngat
                if (absd(a[row][cot]) > tong + EPS) ok = 1;
            } else if (kieu == 1) { // Cheo troi khong nghiem ngat
                if (absd(a[row][cot]) >= tong - EPS) ok = 1;
            } else if (kieu == 2) { // Phan tu troi nhat trong dong
                int max_col = 0;
                double max_val = absd(a[row][0]);
                for (col = 1; col < n; col++) {
                    if (absd(a[row][col]) > max_val) {
                        max_val = absd(a[row][col]);
                        max_col = col;
                    }
                }
                if (max_col == cot && absd(a[row][cot]) > EPS) ok = 1;
            }

            if (ok) {
                used[row] = 1;
                perm[cot] = row;
                if (de_quy_cheo_troi(a, n, cot + 1, used, perm, kieu)) return 1;
                used[row] = 0;
            }
        }
    }
    return 0;
}

int sap_xep_cheo_troi(double a[MAX][MAX + 1], int n) {
    int i, j, used[MAX] = {0}, perm[MAX];
    double b[MAX][MAX + 1];

    // Buoc 1: Thu sap xep cheo troi nghiem ngat
    if (de_quy_cheo_troi(a, n, 0, used, perm, 0)) {
        printf("Đã sắp xếp các dòng để đạt chéo trội nghiêm ngặt.\n");
        goto thanh_cong;
    }

    // Buoc 2: Thu sap xep cheo troi khong nghiem ngat
    for (i = 0; i < n; i++) used[i] = 0;
    if (de_quy_cheo_troi(a, n, 0, used, perm, 1)) {
        printf("Đã sắp xếp các dòng để đạt chéo trội (yếu).\n");
        goto thanh_cong;
    }

    // Buoc 3: Thu sap xep sao cho phan tu tren cheo la lon nhat trong dong
    for (i = 0; i < n; i++) used[i] = 0;
    if (de_quy_cheo_troi(a, n, 0, used, perm, 2)) {
        printf("Đã sắp xếp các dòng để phần tử chéo là lớn nhất mỗi dòng.\n");
        goto thanh_cong;
    }

    // Buoc 4: Giong nhu sap_xep_duong_cheo_khac_0 (chi can khac 0)
    for (i = 0; i < n; i++) used[i] = 0;
    if (tim_hoan_vi_cheo(a, n, 0, used, perm)) {
        printf("Cảnh báo: Không thể sắp xếp chéo trội, chỉ hoán vị để các phần tử a_ii khác 0.\n");
        goto thanh_cong;
    }

    return 0;

thanh_cong:
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) b[i][j] = a[perm[i]][j];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) a[i][j] = b[i][j];
    }
    return 1;
}

double dinh_thuc(double a[MAX][MAX], int n) {
    double b[MAX][MAX], det = 1.0, m;
    int i, j, k, pivot, sign = 1;

    sao_chep_ma_tran_vuong(a, b, n);

    for (i = 0; i < n; i++) {
        pivot = i;
        for (j = i + 1; j < n; j++) {
            if (absd(b[j][i]) > absd(b[pivot][i])) pivot = j;
        }
        if (absd(b[pivot][i]) < EPS) return 0.0;
        if (pivot != i) {
            doi_dong_vuong(b, i, pivot, n);
            sign = -sign;
        }
        for (j = i + 1; j < n; j++) {
            m = b[j][i] / b[i][i];
            for (k = i; k < n; k++) b[j][k] -= m * b[i][k];
        }
    }
    for (i = 0; i < n; i++) det *= b[i][i];
    return sign * det;
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
    int rankA = hang_ma_tran(a, n, n);
    int rankAb = hang_ma_tran(a, n, n + 1);
    if (rankA < rankAb) return 0;  /* vo nghiem */
    if (rankA < n) return 2;       /* vo so nghiem */
    return 1;                      /* nghiem duy nhat */
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

double sai_so_he_lon_nhat(double a[MAX][MAX + 1], double x[MAX], int n) {
    int i, j;
    double s, e, maxe = 0;
    for (i = 0; i < n; i++) {
        s = 0;
        for (j = 0; j < n; j++) s += a[i][j] * x[j];
        e = absd(s - a[i][n]);
        if (e > maxe) maxe = e;
    }
    return maxe;
}

void bao_loi_he(int status) {
    if (status == 0) printf("Kết luận: hệ vô nghiệm.\n");
    else if (status == 2) printf("Kết luận: hệ có vô số nghiệm, không có nghiệm duy nhất.\n");
    else if (status == 3) printf("Lỗi tính toán: giá trị quá lớn hoặc không hợp lệ.\n");
    else printf("Không giải được với dữ liệu hiện tại.\n");
}

void phuong_phap_krame(void) {
    double a[MAX][MAX + 1], goc[MAX][MAX + 1], A[MAX][MAX], Ai[MAX][MAX];
    double d, x[MAX], ds[MAX];
    int n, i, j, k, loai;

    in_tieu_de("PHƯƠNG PHÁP CRAMER");
    printf("Nhập hệ A*x = b. Chương trình tính D, từng D_i và nghiệm x_i = D_i/D.\n");
    nhap_ma_tran_mo_rong(a, &n);
    sao_chep_ma_tran_mo_rong(a, goc, n);

    loai = phan_loai_he(a, n);
    if (loai != 1) {
        printf("Kết luận: phương pháp Cramer chỉ dùng trực tiếp khi hệ có nghiệm duy nhất.\n");
        bao_loi_he(loai);
        return;
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = a[i][j];

    d = dinh_thuc(A, n);
    if (absd(d) < EPS) {
        printf("D gần bằng 0 nên không thể tính nghiệm duy nhất bằng Cramer.\n");
        return;
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                Ai[i][j] = A[i][j];
        for (i = 0; i < n; i++) Ai[i][k] = a[i][n];
        ds[k] = dinh_thuc(Ai, n);
        x[k] = ds[k] / d;
    }

    in_muc("Kết quả");
    printf("D = %.10lf\n", d);
    for (k = 0; k < n; k++) {
        printf("D_%d = %.10lf  =>  x%d = D_%d/D = %.10lf\n", k + 1, ds[k], k + 1, k + 1, x[k]);
    }
    printf("\nNghiệm của hệ:\n");
    in_vector("x", x, n);
}


void phuong_phap_gauss(void) {
    double a[MAX][MAX + 1], goc[MAX][MAX + 1], x[MAX];
    int n, status;

    in_tieu_de("PHƯƠNG PHÁP GAUSS");
    printf("Nhập hệ A*x = b. Chương trình khử về ma trận tam giác trên rồi thế ngược.\n");
    nhap_ma_tran_mo_rong(a, &n);
    sao_chep_ma_tran_mo_rong(a, goc, n);

    status = giai_gauss(a, n, x);
    if (status == 1) {
        in_muc("Ma trận sau khi khử Gauss");
        in_ma_tran_mo_rong(a, n);

        in_muc("Kết quả");
        printf("Nghiệm của hệ:\n");
        in_vector("x", x, n);
    } else {
        bao_loi_he(status);
    }
}


void danh_gia_hoi_tu_lap(double a[MAX][MAX + 1], int n) {
    double r1 = 0, r2 = 0, r3 = 0, s, bij;
    int i, j;

    for (i = 0; i < n; i++) {
        s = 0;
        for (j = 0; j < n; j++) {
            if (j != i) {
                bij = -a[i][j] / a[i][i];
                s += absd(bij);
                r3 += bij * bij;
            }
        }
        if (s > r1) r1 = s;
    }

    for (j = 0; j < n; j++) {
        s = 0;
        for (i = 0; i < n; i++) {
            if (j != i) {
                bij = -a[i][j] / a[i][i];
                s += absd(bij);
            }
        }
        if (s > r2) r2 = s;
    }

    in_muc("Kiểm tra nhanh điều kiện hội tụ");
    printf("r1 = max tổng dòng |b_ij|       = %.6lf\n", r1);
    printf("r2 = max tổng cột  |b_ij|       = %.6lf\n", r2);
    printf("r3 = tổng bình phương b_ij      = %.6lf\n", r3);
    if (r1 < 1 || r2 < 1 || r3 < 1) {
        printf("Nhận xét: thỏa ít nhất một điều kiện đủ, phép lặp có khả năng hội tụ.\n");
    } else {
        printf("Nhận xét: chưa có bảo đảm hội tụ. Nên chọn ma trận có đường chéo trội hoặc đổi dạng hệ.\n");
    }
}

void phuong_phap_gauss_siedel(void) {
    double a[MAX][MAX + 1], goc[MAX][MAX + 1], x[MAX], cu[MAX];
    double eps, s, sai_so, moi;
    int n, i, j, lap, max_lap, hoi_tu = 0;
    char prompt[96];

    in_tieu_de("PHƯƠNG PHÁP LẶP GAUSS-SEIDEL");
    printf("Nhập hệ A*x = b và xấp xỉ ban đầu. Trong mỗi vòng lặp, giá trị mới được dùng ngay.\n");
    nhap_ma_tran_mo_rong(a, &n);
    sao_chep_ma_tran_mo_rong(a, goc, n);

    if (!sap_xep_cheo_troi(a, n)) {
        printf("Không thể sắp xếp để các phần tử trên đường chéo khác 0.\n");
        return;
    }
    danh_gia_hoi_tu_lap(a, n);

    in_muc("Nhập xấp xỉ ban đầu");
    for (i = 0; i < n; i++) {
        sprintf(prompt, "x[%d] = ", i + 1);
        x[i] = doc_double(prompt);
    }
    eps = doc_double_duong("Nhập sai số epsilon (>0): ");
    max_lap = doc_int_range("Nhập số lần lặp tối đa (1..100000): ", 1, 100000);

    for (lap = 1; lap <= max_lap; lap++) {
        for (i = 0; i < n; i++) cu[i] = x[i];
        for (i = 0; i < n; i++) {
            s = 0;
            for (j = 0; j < n; j++) {
                if (j != i) s += a[i][j] * x[j];
            }
            moi = (a[i][n] - s) / a[i][i];
            if (!so_hop_le(moi)) {
                printf("Quá trình lặp tạo giá trị không hợp lệ. Dừng tính.\n");
                return;
            }
            x[i] = moi;
        }

        sai_so = 0;
        for (i = 0; i < n; i++) {
            if (absd(x[i] - cu[i]) > sai_so) sai_so = absd(x[i] - cu[i]);
        }
        if (sai_so < eps) {
            hoi_tu = 1;
            break;
        }
    }

    in_muc("Kết quả");
    if (!hoi_tu) printf("Cảnh báo: đã đạt số lần lặp tối đa nhưng sai số lặp chưa đạt epsilon.\n");
    printf("Số lần lặp đã thực hiện: %d\n", lap <= max_lap ? lap : max_lap);
    printf("Nghiệm gần đúng:\n");
    in_vector("x", x, n);
}

void phuong_phap_giam_du(void) {
    double a[MAX][MAX + 1], goc[MAX][MAX + 1], x[MAX], r[MAX];
    double eps, d, maxr = 0.0, t;
    int n, i, j, k, lap, max_lap, hoi_tu = 0;
    char prompt[96];

    in_tieu_de("PHƯƠNG PHÁP GIẢM DƯ");
    printf("Nhập hệ A*x = b và xấp xỉ ban đầu. Mỗi bước sẽ chọn số dư lớn nhất để sửa.\n");
    nhap_ma_tran_mo_rong(a, &n);
    sao_chep_ma_tran_mo_rong(a, goc, n);

    if (!sap_xep_cheo_troi(a, n)) {
        printf("Không thể sắp xếp để các phần tử trên đường chéo khác 0.\n");
        return;
    }

    in_muc("Nhập xấp xỉ ban đầu");
    for (i = 0; i < n; i++) {
        sprintf(prompt, "x[%d] = ", i + 1);
        x[i] = doc_double(prompt);
    }
    eps = doc_double_duong("Nhập sai số epsilon (>0): ");
    max_lap = doc_int_range("Nhập số lần lặp tối đa (1..100000): ", 1, 100000);

    for (i = 0; i < n; i++) {
        if (absd(a[i][i]) < EPS) {
            printf("Không thể chia cho a[%d][%d] vì giá trị gần bằng 0.\n", i + 1, i + 1);
            return;
        }
        t = a[i][i];
        for (j = 0; j <= n; j++) a[i][j] /= t;
    }

    for (i = 0; i < n; i++) {
        r[i] = a[i][n];
        for (j = 0; j < n; j++) r[i] -= a[i][j] * x[j];
    }

    for (lap = 1; lap <= max_lap; lap++) {
        k = 0;
        maxr = absd(r[0]);
        for (i = 1; i < n; i++) {
            if (absd(r[i]) > maxr) {
                maxr = absd(r[i]);
                k = i;
            }
        }
        if (maxr < eps) {
            hoi_tu = 1;
            break;
        }

        d = r[k];
        x[k] += d;
        if (!so_hop_le(x[k])) {
            printf("Quá trình giảm dư tạo giá trị không hợp lệ. Dừng tính.\n");
            return;
        }

        for (i = 0; i < n; i++) r[i] -= a[i][k] * d;
    }

    in_muc("Kết quả");
    if (!hoi_tu) printf("Cảnh báo: đã đạt số lần lặp tối đa nhưng số dư chưa đạt epsilon.\n");
    printf("Số lần lặp đã thực hiện: %d\n", lap <= max_lap ? lap : max_lap);
    printf("Nghiệm gần đúng:\n");
    in_vector("x", x, n);
    printf("Số dư lớn nhất hiện tại = %.3e\n", maxr);
    printf(" max|A*x - b| = %.3e\n", sai_so_he_lon_nhat(goc, x, n));
}

void menu_chuong5(void) {
    int chon;
    do {
        in_tieu_de("CHƯƠNG 5 - GIẢI HỆ PHƯƠNG TRÌNH TUYẾN TÍNH");
        printf("1. Cramer: tính bằng định thức\n");
        printf("2. Gauss: khử về tam giác trên và thế ngược\n");
        printf("3. Gauss-Seidel: lặp gần đúng\n");
        printf("4. Giảm dư: sửa nghiệm bằng số dư lớn nhất\n");
        printf("0. Quay lại menu chính\n");
        chon = doc_int_range("Chon phuong phap: ", 0, 4);

        if (chon == 1) phuong_phap_krame();
        else if (chon == 2) phuong_phap_gauss();
        else if (chon == 3) phuong_phap_gauss_siedel();
        else if (chon == 4) phuong_phap_giam_du();
    } while (chon != 0);
}

/* =========================================================
   CHUONG 6 - GIA TRI RIENG, VECTO RIENG
   ========================================================= */

void ma_tran_don_vi(double e[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            e[i][j] = (i == j) ? 1.0 : 0.0;
}

void nhan_ma_tran(double A[MAX][MAX], double B[MAX][MAX], double C[MAX][MAX], int n) {
    int i, j, k;
    double s;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            s = 0;
            for (k = 0; k < n; k++) s += A[i][k] * B[k][j];
            C[i][j] = s;
        }
    }
}

void gan_ma_tran(double A[MAX][MAX], double B[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = B[i][j];
}

int danilevsky(double A[MAX][MAX], int n, double P[MAX][MAX], double T[MAX][MAX]) {
    double M[MAX][MAX], M1[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    double pivot;
    int j, k;

    gan_ma_tran(P, A, n);
    ma_tran_don_vi(T, n);

    for (k = n - 2; k >= 0; k--) {
        pivot = P[k + 1][k];
        if (absd(pivot) < EPS) {
            int found_j = -1;
            int col;
            for (col = k - 1; col >= 0; col--) {
                if (absd(P[k + 1][col]) > EPS) {
                    found_j = col;
                    break;
                }
            }
            if (found_j == -1) {
                printf("Không thể tiếp tục Danilevsky vì dòng %d không có phần tử nào khác 0 từ cột 1 đến cột %d.\n", k + 2, k + 1);
                return 0;
            }
            // Hoan vi dong found_j va k trong P
            doi_dong_vuong(P, found_j, k, n);
            // Hoan vi cot found_j va k trong P
            int r;
            for (r = 0; r < n; r++) {
                double temp = P[r][found_j];
                P[r][found_j] = P[r][k];
                P[r][k] = temp;
            }
            // Hoan vi cot found_j va k trong T
            for (r = 0; r < n; r++) {
                double temp = T[r][found_j];
                T[r][found_j] = T[r][k];
                T[r][k] = temp;
            }
            printf("Danilevsky: Đã hoán vị dòng/cột %d và %d để pivot khác 0.\n", found_j + 1, k + 1);
            pivot = P[k + 1][k];
        }

        ma_tran_don_vi(M, n);
        ma_tran_don_vi(M1, n);

        for (j = 0; j < n; j++) {
            M1[k][j] = P[k + 1][j];
            if (j == k) M[k][j] = 1.0 / pivot;
            else M[k][j] = -P[k + 1][j] / pivot;
        }

        nhan_ma_tran(P, M, B, n);
        nhan_ma_tran(M1, B, C, n);
        gan_ma_tran(P, C, n);

        nhan_ma_tran(T, M, B, n);
        gan_ma_tran(T, B, n);
    }
    return 1;
}

void in_da_thuc_dac_trung(double P[MAX][MAX], int n) {
    int i, mu, da_in = 0;
    double p;
    printf("Đa thức đặc trưng:\n");
    printf("p(lambda) = lambda^%d", n);
    for (i = 0; i < n; i++) {
        p = P[0][i];
        mu = n - 1 - i;
        if (absd(p) < EPS) continue;

        if (p >= 0) printf(" - %.10lf", p);
        else printf(" + %.10lf", -p);

        if (mu > 1) printf("lambda^%d", mu);
        else if (mu == 1) printf("lambda");
        da_in = 1;
    }
    (void)da_in;
    printf(" = 0\n");
}


double gia_tri_da_thuc_dac_trung(double P[MAX][MAX], int n, double lambda) {
    double value = lambda - P[0][0];
    int i;
    for (i = 1; i < n; i++) {
        value = value * lambda - P[0][i];
    }
    return value;
}

void evaluate_poly_double(double coeffs[], int degree, double x, double *val, double *deriv) {
    *val = coeffs[0];
    *deriv = 0.0;
    for (int i = 1; i <= degree; i++) {
        *deriv = (*deriv) * x + *val;
        *val = (*val) * x + coeffs[i];
    }
}

double tim_nghiem_newton(double coeffs[], int degree, double start_x) {
    double x = start_x;
    for (int iter = 0; iter < 500; iter++) {
        double val, deriv;
        evaluate_poly_double(coeffs, degree, x, &val, &deriv);
        if (absd(deriv) < 1e-12) {
            x += 0.1;
            continue;
        }
        double dx = val / deriv;
        x -= dx;
        if (absd(dx) < 1e-8) {
            return x;
        }
    }
    return x;
}

int tim_tri_rieng_thuc(double coeffs[], int degree, double roots[]) {
    double current_coeffs[MAX + 1];
    for (int i = 0; i <= degree; i++) {
        current_coeffs[i] = coeffs[i];
    }
    int num_roots = 0;
    int deg = degree;
    double guesses[] = {0.0, 1.0, -1.0, 5.0, -5.0, 10.0, -10.0, 0.5, -0.5, 20.0, -20.0, 50.0, -50.0};
    int num_guesses = sizeof(guesses) / sizeof(guesses[0]);

    while (deg > 0) {
        double root = 0;
        int found = 0;
        for (int g = 0; g < num_guesses; g++) {
            double candidate = tim_nghiem_newton(current_coeffs, deg, guesses[g]);
            double val, deriv;
            evaluate_poly_double(current_coeffs, deg, candidate, &val, &deriv);
            if (absd(val) < 1e-5) {
                int duplicate = 0;
                for (int r = 0; r < num_roots; r++) {
                    if (absd(roots[r] - candidate) < 1e-4) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    root = candidate;
                    found = 1;
                    break;
                }
            }
        }
        if (!found) {
            break;
        }
        roots[num_roots++] = root;

        // Deflation
        double next_coeffs[MAX + 1];
        next_coeffs[0] = current_coeffs[0];
        for (int i = 1; i < deg; i++) {
            next_coeffs[i] = current_coeffs[i] + root * next_coeffs[i - 1];
        }
        deg--;
        for (int i = 0; i <= deg; i++) {
            current_coeffs[i] = next_coeffs[i];
        }
    }

    // Sort roots in ascending order
    for (int i = 0; i < num_roots - 1; i++) {
        for (int j = i + 1; j < num_roots; j++) {
            if (roots[i] > roots[j]) {
                double temp = roots[i];
                roots[i] = roots[j];
                roots[j] = temp;
            }
        }
    }
    return num_roots;
}

double sai_so_vecto_rieng(double A[MAX][MAX], double x[MAX], int n, double lambda) {
    int i, j;
    double s, e, maxe = 0;
    for (i = 0; i < n; i++) {
        s = 0;
        for (j = 0; j < n; j++) s += A[i][j] * x[j];
        e = absd(s - lambda * x[i]);
        if (e > maxe) maxe = e;
    }
    return maxe;
}

void tim_tri_rieng_danilevsky(void) {
    double A[MAX][MAX], P[MAX][MAX], T[MAX][MAX];
    int n;

    in_tieu_de("DANILEVSKY - LẬP ĐA THỨC ĐẶC TRƯNG");
    printf("Nhập ma trận vuông A. Chương trình đưa A về dạng Frobenius để lập p(lambda) = det(lambda*I - A).\n");
    nhap_ma_tran_vuong(A, &n);
    if (danilevsky(A, n, P, T)) {
        in_muc("Ma trận dạng Frobenius P");
        printf("Dòng đầu của P dùng để lập đa thức đặc trưng.\n");
        in_ma_tran_vuong(P, n);

        in_muc("Đa thức đặc trưng");
        in_da_thuc_dac_trung(P, n);

        // Tim va in cac gia tri rieng thuc
        double coeffs[MAX + 1];
        coeffs[0] = 1.0;
        for (int j = 1; j <= n; j++) {
            coeffs[j] = -P[0][j - 1];
        }
        double roots[MAX + 1];
        int num_roots = tim_tri_rieng_thuc(coeffs, n, roots);

        in_muc("Các giá trị riêng thực tìm được (nghiệm của đa thức đặc trưng)");
        if (num_roots == 0) {
            printf("Không tìm thấy giá trị riêng thực nào (hoặc tất cả các nghiệm là phức).\n");
        } else {
            printf("Tìm thấy %d giá trị riêng thực:\n", num_roots);
            for (int r = 0; r < num_roots; r++) {
                printf("  lambda_%d = %.10lf\n", r + 1, roots[r]);
            }
        }

        in_muc("Ma trận chuyển T");
        printf("Khi đã có một giá trị riêng lambda, lập y = (lambda^(n-1), lambda^(n-2), ..., 1), sau đó tính x = T*y để được vectơ riêng.\n");
        in_ma_tran_vuong(T, n);
    }
}


void tim_vecto_rieng_danilevsky(void) {
    double A[MAX][MAX], A_goc[MAX][MAX], P[MAX][MAX], T[MAX][MAX];
    double lambda, y[MAX], x[MAX], maxv, val;
    int n, i, j;

    in_tieu_de("DANILEVSKY - TÍNH VECTƠ RIÊNG");
    printf("Nhập ma trận A và một giá trị riêng lambda đã tìm được từ đa thức đặc trưng.\n");
    nhap_ma_tran_vuong(A, &n);
    sao_chep_ma_tran_vuong(A, A_goc, n);
    if (!danilevsky(A, n, P, T)) return;

    in_muc("Ma trận dạng Frobenius P");
    in_ma_tran_vuong(P, n);

    in_muc("Đa thức đặc trưng");
    in_da_thuc_dac_trung(P, n);

    lambda = doc_double("Nhap gia tri rieng lambda = ");
    val = gia_tri_da_thuc_dac_trung(P, n, lambda);
    if (absd(val) > 1e-6) {
        printf("Cảnh báo: p(lambda) chưa gần 0, giá trị kiểm tra p(lambda) = %.3e.\n", val);
    }

    double current_lambda_pow = 1.0;
    for (i = n - 1; i >= 0; i--) {
        y[i] = current_lambda_pow;
        current_lambda_pow *= lambda;
    }

    for (i = 0; i < n; i++) {
        x[i] = 0;
        for (j = 0; j < n; j++) x[i] += T[i][j] * y[j];
    }

    in_muc("Vectơ y của dạng Frobenius");
    printf("y = (lambda^(n-1), lambda^(n-2), ..., 1) với lambda = %.10lf\n", lambda);
    in_vector("y", y, n);

    in_muc("Ma trận chuyển T");
    printf("Dùng công thức x = T*y.\n");
    in_ma_tran_vuong(T, n);

    in_muc("Kết quả");
    printf("Vectơ riêng ứng với lambda = %.10lf:\n", lambda);
    in_vector("x", x, n);

    maxv = absd(x[0]);
    for (i = 1; i < n; i++) if (absd(x[i]) > maxv) maxv = absd(x[i]);
    if (maxv > EPS) {
        printf("\nVectơ riêng chuẩn hóa theo phần tử có trị tuyệt đối lớn nhất:\n");
        for (i = 0; i < n; i++) printf("x[%d] = %.10lf\n", i + 1, x[i] / maxv);
    } else {
        printf("\nVectơ riêng có tất cả phần tử gần bằng 0, không thể chuẩn hóa.\n");
    }
}


void menu_chuong6(void) {
    int chon;
    do {
        in_tieu_de("CHƯƠNG 6 - GIÁ TRỊ RIÊNG VÀ VECTƠ RIÊNG");
        printf("1. Lập đa thức đặc trưng bằng Danilevsky\n");
        printf("2. Tính vectơ riêng khi đã có lambda\n");
        printf("0. Quay lại menu chính\n");
        chon = doc_int_range("Chon phuong phap: ", 0, 2);

        if (chon == 1) tim_tri_rieng_danilevsky();
        else if (chon == 2) tim_vecto_rieng_danilevsky();
    } while (chon != 0);
}

/* =========================================================
   CHUONG 7 - NOI SUY VA BINH PHUONG BE NHAT
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

double ayken_dang1(double x[MAX], double y[MAX], int m, double c) {
    double w = 1, s = 0, d;
    int i, j;

    for (i = 0; i < m; i++) {
        if (absd(c - x[i]) < EPS) return y[i];
    }
    for (i = 0; i < m; i++) w *= (c - x[i]);

    for (i = 0; i < m; i++) {
        d = c - x[i];
        for (j = 0; j < m; j++) {
            if (j != i) d *= (x[i] - x[j]);
        }
        s += y[i] / d;
    }
    return w * s;
}

double ayken_dang2(double x[MAX], double y[MAX], int m, double c) {
    double p[MAX][MAX];
    int i, j;

    for (i = 0; i < m; i++) p[i][0] = y[i];
    for (j = 1; j < m; j++) {
        for (i = j; i < m; i++) {
            p[i][j] = ((c - x[i - j]) * p[i][j - 1] - (c - x[i]) * p[i - 1][j - 1]) / (x[i] - x[i - j]);
        }
    }
    return p[m - 1][m - 1];
}

void lap_bang_sai_phan(double y[MAX], double d[MAX][MAX], int m) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) d[i][j] = 0.0;
    }
    for (i = 0; i < m; i++) d[i][0] = y[i];
    for (j = 1; j < m; j++) {
        for (i = 0; i < m - j; i++) d[i][j] = d[i + 1][j - 1] - d[i][j - 1];
    }
}

void in_bang_sai_phan(double x[MAX], double d[MAX][MAX], int m) {
    int i, j;
    printf("Bảng sai phân tiến:\n");
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

double hermite_cap1(double x[MAX], double y[MAX], double yp[MAX], int m, double c) {
    double z[MAX2], Q[MAX2][MAX2];
    double result, term;
    int N = 2 * m;
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) Q[i][j] = 0;

    for (i = 0; i < m; i++) {
        z[2 * i] = x[i];
        z[2 * i + 1] = x[i];
        Q[2 * i][0] = y[i];
        Q[2 * i + 1][0] = y[i];
        Q[2 * i + 1][1] = yp[i];
        if (i == 0) Q[2 * i][1] = yp[i];
        else Q[2 * i][1] = (Q[2 * i][0] - Q[2 * i - 1][0]) / (z[2 * i] - z[2 * i - 1]);
    }

    for (j = 2; j < N; j++) {
        for (i = j; i < N; i++) {
            Q[i][j] = (Q[i][j - 1] - Q[i - 1][j - 1]) / (z[i] - z[i - j]);
        }
    }

    result = Q[0][0];
    term = 1;
    for (i = 1; i < N; i++) {
        term *= (c - z[i - 1]);
        result += Q[i][i] * term;
    }
    return result;
}

int giai_binh_phuong_da_thuc(double x[MAX], double y[MAX], int m, int bac, double he_so[MAX]) {
    double a[MAX][MAX + 1];
    double tong_mu[2 * MAX + 1] = {0};
    double tong_y_mu[MAX + 1] = {0};
    int i, j, k, p, status;
    int p_max = 2 * bac;

    for (k = 0; k < m; k++) {
        double x_luy_thua = 1.0;
        for (p = 0; p <= p_max; p++) {
            tong_mu[p] += x_luy_thua;
            if (p <= bac) {
                tong_y_mu[p] += y[k] * x_luy_thua;
            }
            x_luy_thua *= x[k];
        }
    }

    for (i = 0; i <= bac; i++) {
        for (j = 0; j <= bac; j++) {
            a[i][j] = tong_mu[i + j];
        }
        a[i][bac + 1] = tong_y_mu[i];
    }

    status = giai_gauss(a, bac + 1, he_so);
    if (status != 1) bao_loi_he(status);
    return status == 1;
}

double tinh_da_thuc_xap_xi(double he_so[MAX], int bac, double x) {
    double p = he_so[bac];
    int i;
    for (i = bac - 1; i >= 0; i--) {
        p = p * x + he_so[i];
    }
    return p;
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

void bpbnn_da_thuc(void) {
    in_tieu_de("BÌNH PHƯƠNG BÉ NHẤT - ĐA THỨC");
    double x[MAX], y[MAX], he_so[MAX];
    int m, bac, i;

    nhap_bang_xy(x, y, &m);
    bac = doc_int_range("Nhập bậc đa thức cần xấp xỉ (1..m-1): ", 1, m - 1);

    if (!giai_binh_phuong_da_thuc(x, y, m, bac, he_so)) return;

    printf("Hàm xấp xỉ: y = ");
    for (i = 0; i <= bac; i++) {
        if (i == 0) printf("%.10lf", he_so[i]);
        else printf(" + (%.10lf)*x^%d", he_so[i], i);
    }
    printf("\nTổng bình phương sai số S = %.10lf\n", sse_da_thuc(x, y, m, he_so, bac));
}

void bpbnn_ham_mu(void) {
    in_tieu_de("BÌNH PHƯƠNG BÉ NHẤT - HÀM MŨ");
    double x[MAX], y[MAX], Y[MAX], he_so[MAX], a, b, e, sse = 0;
    int m, i;

    nhap_bang_xy(x, y, &m);
    for (i = 0; i < m; i++) {
        if (y[i] <= 0) {
            printf("Dạng y = a*e^(b*x) cần y > 0 tại mỗi mốc.\n");
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
    printf("Dạng y = a*e^(b*x)\n");
    printf("a = %.10lf\n", a);
    printf("b = %.10lf\n", b);
    printf("Tong binh phuong sai so S = %.10lf\n", sse);
}

void bpbnn_ham_luy_thua(void) {
    in_tieu_de("BÌNH PHƯƠNG BÉ NHẤT - HÀM LŨY THỪA");
    double x[MAX], y[MAX], X[MAX], Y[MAX], he_so[MAX], a, b, e, sse = 0;
    int m, i;

    nhap_bang_xy(x, y, &m);
    for (i = 0; i < m; i++) {
        if (x[i] <= 0 || y[i] <= 0) {
            printf("Dạng y = a*x^b cần x > 0 và y > 0 tại mỗi mốc.\n");
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
    printf("Dạng y = a*x^b\n");
    printf("a = %.10lf\n", a);
    printf("b = %.10lf\n", b);
    printf("Tong binh phuong sai so S = %.10lf\n", sse);
}

void bpbnn_luong_giac(void) {
    in_tieu_de("BÌNH PHƯƠNG BÉ NHẤT - HÀM LƯỢNG GIÁC");
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

    printf("Dạng y = a + b*cos(x) + c*sin(x)\n");
    printf("a = %.10lf\n", he_so[0]);
    printf("b = %.10lf\n", he_so[1]);
    printf("c = %.10lf\n", he_so[2]);
    printf("Tong binh phuong sai so S = %.10lf\n", sse);
}

void chay_noi_suy_co_ban(int loai) {
    double x[MAX], y[MAX], c, kq, d[MAX][MAX];
    int m;

    in_tieu_de("NỘI SUY");
    nhap_bang_xy(x, y, &m);
    if (!x_phan_biet(x, m)) {
        printf("Cac moc x bi trung nhau, khong the noi suy vi se chia cho 0.\n");
        return;
    }
    if ((loai == 2 || loai == 5) && !x_cach_deu(x, m)) {
        printf("Phuong phap da chon can cac moc x cach deu. Vui long kiem tra lai bang du lieu.\n");
        return;
    }

    c = doc_double("Nhập giá trị cần tính c = ");
    canh_bao_ngoai_khoang(x, m, c);

    if (loai == 1) kq = lagrange_tong_quat(x, y, m, c);
    else if (loai == 2) kq = lagrange_cach_deu(x, y, m, c);
    else if (loai == 3) kq = ayken_dang1(x, y, m, c);
    else if (loai == 4) kq = ayken_dang2(x, y, m, c);
    else if (loai == 5) kq = newton_sai_phan_tien(x, y, m, c);
    else return;

    if (loai == 5) {
        in_muc("Bảng sai phân");
        lap_bang_sai_phan(y, d, m);
        in_bang_sai_phan(x, d, m);
    }

    in_muc("Kết quả");
    printf("Gia tri gan dung f(%.10lf) = %.10lf\n", c, kq);
}


void chay_bang_sai_phan(void) {
    double x[MAX], y[MAX], d[MAX][MAX];
    int m;
    in_tieu_de("BẢNG SAI PHÂN");
    nhap_bang_xy(x, y, &m);
    if (!x_cach_deu(x, m)) printf("Lưu ý: bảng sai phân Newton nên dùng với các mốc x cách đều.\n");
    lap_bang_sai_phan(y, d, m);
    in_muc("Kết quả");
    in_bang_sai_phan(x, d, m);
}

void chay_hermite(void) {
    double x[MAX], y[MAX], yp[MAX], c, kq;
    int m, i;
    char prompt[96];

    in_tieu_de("NỘI SUY HERMITE CẤP 1");
    printf("Can nhap f(x) va dao ham f'(x) tai tung moc.\n");
    nhap_bang_xy(x, y, &m);
    if (!x_phan_biet(x, m)) {
        printf("Các mốc x bị trùng nhau, không thể lập bảng Hermite.\n");
        return;
    }
    if (2 * m > MAX2) {
        printf("Số mốc quá lớn cho bảng Hermite cấp 1.\n");
        return;
    }

    in_muc("Nhập đạo hàm cấp 1");
    for (i = 0; i < m; i++) {
        sprintf(prompt, "f'(%g) = ", x[i]);
        yp[i] = doc_double(prompt);
    }
    c = doc_double("Nhập giá trị cần tính c = ");
    canh_bao_ngoai_khoang(x, m, c);

    kq = hermite_cap1(x, y, yp, m, c);
    in_muc("Kết quả");
    printf("Gia tri gan dung f(%.10lf) = %.10lf\n", c, kq);
}

void menu_chuong7(void) {
    int chon;
    do {
        in_tieu_de("CHƯƠNG 7 - NỘI SUY VÀ BÌNH PHƯƠNG BÉ NHẤT");
        printf("1. Nội suy Lagrange tổng quát\n");
        printf("2. Nội suy Lagrange với mốc cách đều\n");
        printf("3. Nội suy Aitken dạng 1\n");
        printf("4. Nội suy Aitken dạng 2\n");
        printf("5. Nội suy Newton bằng sai phân tiến\n");
        printf("6. Lập và in bảng sai phân\n");
        printf("7. Nội suy Hermite cấp 1\n");
        printf("8. Bình phương bé nhất: y = a0 + a1*x + a2*x^2 + ...\n");
        printf("9. Bình phương bé nhất: y = a*e^(b*x)\n");
        printf("10. Bình phương bé nhất: y = a*x^b\n");
        printf("11. Bình phương bé nhất: y = a + b*cos(x) + c*sin(x)\n");
        printf("0. Quay lại menu chính\n");
        chon = doc_int_range("Chon phuong phap: ", 0, 11);

        if (chon >= 1 && chon <= 5) chay_noi_suy_co_ban(chon);
        else if (chon == 6) chay_bang_sai_phan();
        else if (chon == 7) chay_hermite();
        else if (chon == 8) bpbnn_da_thuc();
        else if (chon == 9) bpbnn_ham_mu();
        else if (chon == 10) bpbnn_ham_luy_thua();
        else if (chon == 11) bpbnn_luong_giac();
    } while (chon != 0);
}

/* =========================================================
   CHUONG 8 - TINH GAN DUNG TICH PHAN XAC DINH
   ========================================================= */

double horner_da_thuc(double a[], int bac, double x) {
    int i;
    double p = a[0];
    for (i = 1; i <= bac; i++) p = p * x + a[i];
    return p;
}

void nhap_da_thuc_tong_quat(double hs[], int *bac) {
    int i;
    char prompt[120];
    in_muc("Nhập đa thức P(x)");
    printf("Dạng nhập: P(x) = a0*x^n + a1*x^(n-1) + ... + an.\n");
    *bac = doc_int_range("Nhập bậc n của đa thức (0..30): ", 0, MAX);
    for (i = 0; i <= *bac; i++) {
        sprintf(prompt, "hệ số của x^%d = ", *bac - i);
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
    in_muc("Nhập bảng giá trị để tính tích phân");
    printf("Bảng gồm y[0], y[1], ..., y[n] với khoảng cách đều h.\n");
    *n = doc_int_range("Nhập số đoạn chia n (1..30): ", 1, MAX);
    *h = doc_double_duong("Nhập khoảng cách h (>0): ");
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
    in_muc("Cách chọn dữ liệu");
    printf("- Có bảng giá trị: dùng y[0..n] và h.\n");
    printf("- Có hàm đa thức: nhập bậc, hệ số, cận dưới a và cận trên b.\n");
}

void tich_phan_tu_bang_tong_quat(void) {
    double y[MAX + 1], h, kq;
    int n, chon, ok;

    in_tieu_de("TÍNH TÍCH PHÂN TỪ BẢNG GIÁ TRỊ");
    in_goi_y_du_lieu_chuong8();
    nhap_bang_y_cho_tich_phan(y, &n, &h);

    printf("\nChọn công thức tính:\n");
    printf("1. Hình thang\n");
    printf("2. Parabol/Simpson, cần n chẵn\n");
    printf("3. Newton-Cotes, nên dùng n <= 10\n");
    chon = doc_int_range("Chọn công thức: ", 1, 3);

    in_muc("Kết quả");
    if (chon == 1) {
        kq = tich_phan_hinh_thang_tu_bang(y, n, h);
        printf("Tích phân gần đúng = %.10lf\n", kq);
    } else if (chon == 2) {
        if (n % 2 != 0) {
            printf("Công thức Parabol/Simpson cần n là số chẵn.\n");
            return;
        }
        kq = tich_phan_parabol_tu_bang(y, n, h);
        printf("Tích phân gần đúng = %.10lf\n", kq);
    } else {
        if (n > 10) {
            printf("n quá lớn để tính Newton-Cotes ổn định. Vui lòng dùng n <= 10.\n");
            return;
        }
        kq = tich_phan_newton_cotes_tu_bang(y, n, h, &ok);
        if (ok) printf("Tích phân gần đúng = %.10lf\n", kq);
        else printf("Không tính được trọng số Newton-Cotes.\n");
    }
}

void tich_phan_tu_da_thuc_tong_quat(void) {
    double hs[MAX + 1], a, b, kq;
    int bac, chon, n, ok;

    in_tieu_de("TÍNH TÍCH PHÂN CỦA ĐA THỨC");
    in_goi_y_du_lieu_chuong8();
    nhap_da_thuc_tong_quat(hs, &bac);
    a = doc_double("Nhập cận dưới a = ");
    b = doc_double("Nhập cận trên b = ");
    if (absd(a - b) < EPS) {
        printf("a = b nên tích phân bằng 0.\n");
        return;
    }

    printf("\nChọn công thức tính:\n");
    printf("1. Hình thang ghép\n");
    printf("2. Parabol/Simpson ghép, cần n chẵn\n");
    printf("3. Newton-Cotes, chọn n trong [1..10]\n");
    chon = doc_int_range("Chọn công thức: ", 1, 3);

    if (chon == 1) {
        n = doc_int_range("Nhập số đoạn chia n (1..100000): ", 1, 100000);
        kq = tich_phan_hinh_thang_da_thuc(hs, bac, a, b, n);
        in_muc("Kết quả");
        printf("Tích phân gần đúng = %.10lf\n", kq);
    } else if (chon == 2) {
        n = doc_int_range("Nhập số đoạn chia chẵn n (2..100000): ", 2, 100000);
        if (n % 2 != 0) {
            printf("n phải là số chẵn để dùng công thức Parabol/Simpson.\n");
            return;
        }
        kq = tich_phan_parabol_da_thuc(hs, bac, a, b, n);
        in_muc("Kết quả");
        printf("Tích phân gần đúng = %.10lf\n", kq);
    } else {
        n = doc_int_range("Nhập bậc Newton-Cotes n (1..10): ", 1, 10);
        kq = tich_phan_newton_cotes_da_thuc(hs, bac, a, b, n, &ok);
        in_muc("Kết quả");
        if (ok) printf("Tích phân gần đúng = %.10lf\n", kq);
        else printf("Không tính được trọng số Newton-Cotes.\n");
    }
}

void menu_chuong8(void) {
    int chon;
    do {
        in_tieu_de("CHƯƠNG 8 - TÍNH GẦN ĐÚNG TÍCH PHÂN XÁC ĐỊNH");
        const char *options[] = {
            "1. Tính từ bảng giá trị y[0..n] với khoảng cách h",
            "2. Tính từ đa thức P(x) trên đoạn [a, b]",
            "0. Quay lại menu chính"
        };
        in_menu(options, 3);
        chon = doc_int_range("Chọn kiểu dữ liệu: ", 0, 2);

        if (chon == 1) tich_phan_tu_bang_tong_quat();
        else if (chon == 2) tich_phan_tu_da_thuc_tong_quat();
    } while (chon != 0);
}

/* =========================================================
   MENU CHINH
   ========================================================= */

int main(void) {
    int chon;
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    do {
        in_tieu_de("CHƯƠNG TRÌNH MÔN PHƯƠNG PHÁP TÍNH");
        printf("Mục lục hướng dẫn sẽ xuất hiện trước khi bạn nhập số liệu ở từng chương.\n\n");
        const char *options[] = {
            "1. Chương 5: Giải hệ phương trình tuyến tính",
            "2. Chương 6: Giá trị riêng và vectơ riêng",
            "3. Chương 7: Nội suy và bình phương bé nhất",
            "4. Chương 8: Tính gần đúng tích phân xác định",
            "0. Thoát"
        };
        in_menu(options, 5);
        chon = doc_int_range("Chọn chương bạn muốn chạy: ", 0, 4);

        if (chon == 1) menu_chuong5();
        else if (chon == 2) menu_chuong6();
        else if (chon == 3) menu_chuong7();
        else if (chon == 4) menu_chuong8();
    } while (chon != 0);

    printf("Đã thoát chương trình.\n");
    return 0;
}
