#include <stdio.h>

#include <stdlib.h>

#include "imageprocessing.h"

#define mx 255
#define z 0
#define g 3
#define o 1
#define d 2
#define forr(X) for (int i = z; i < X; i++)

  int ** * aloc(int n, int m) {
    int ** * res = (int ** * ) malloc(sizeof(int ** ) * n);
    forr(n) {
      res[i] = (int ** ) malloc(sizeof(int * ) * m);
      for (int j = z; j < m; j++) {
        res[i][j] = (int * ) malloc(sizeof(int) * g);
      }
    }

    return res;
  }

void fr(int ** * a, int n, int m) {
  forr(n) {
    for (int j = z; j < m; j++) {
      free(a[i][j]);
    }

    free(a[i]);
  }

  free(a);
}

int minn(int a, int b) {
  if (a < b) return a;
  return b;
}

int ** * flip_horizontal(int ** * image, int N, int M) {
  int ** * res = aloc(N, M);
  forr(g) {
    for (int j = z; j < N; j++) {
      for (int k = z; k < M; k++) {
        res[j][k][i] = image[j][M - k - o][i];
      }
    }
  }

  fr(image, N, M);
  return res;
}

int ** * rotate_left(int ** * image, int N, int M) {
  int ** * res = aloc(M, N);
  forr(g) {
    for (int j = z; j < M; j++) {
      for (int k = z; k < N; k++) {
        res[j][k][i] = image[k][M - o - j][i];
      }
    }
  }

  fr(image, N, M);

  return res;
}

int ** * crop(int ** * image, int N, int M, int x, int y, int h, int w) {
  int ** * res = aloc(h, w);
  forr(g) {
    for (int j = y; j < y + h; j++) {
      for (int k = x; k < x + w; k++) {
        res[j - y][k - x][i] = image[j][k][i];
      }
    }
  }

  fr(image, N, M);
  return res;
}

int ** * extend(int ** * image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
  int ** * res = aloc(N + d * rows, M + d * cols);
  int a[g] = {
    new_R,
    new_G,
    new_B
  };

  int nn = N + d * rows;
  int nm = M + d * cols;
  forr(g) {
    for (int j = rows; j < rows + N; j++) {
      for (int k = cols; k < cols + M; k++) {
        res[j][k][i] = image[j - rows][k - cols][i];
      }
    }
  }

  forr(g) {
    for (int j = z; j < rows; j++) {
      for (int k = z; k < nm; k++) {
        res[j][k][i] = a[i];
        res[j + N + rows][k][i] = a[i];
      }
    }

    for (int j = z; j < nn; j++) {
      for (int k = z; k < cols; k++) {
        res[j][k][i] = a[i];
        res[j][k + cols + M][i] = a[i];
      }
    }
  }

  fr(image, N, M);
  return res;
}

int ** * paste(int ** * image_dst, int N_dst, int M_dst, int ** * image_src, int N_src, int M_src, int x, int y) {
  forr(g) {
    for (int j = y; j < minn(N_dst, N_src + y); j++) {
      for (int k = x; k < minn(M_dst, M_src + x); k++) {
        image_dst[j][k][i] = image_src[j - y][k - x][i];
      }
    }
  }

  return image_dst;
}

int fl(int ** * image, int t, int y, int x, float ** fl, int fn, int N, int M) {
  float ans = z;
  int sty = y - (fn / d);
  int stx = x - (fn / d);

  for (int i = sty;
    (i - sty) < fn; i++) {
    for (int j = stx;
      (j - stx) < fn; j++) {
      if (i < z || j < z || i >= N || j >= M) {
        continue;
      }

      ans += ((float) image[i][j][t]) * fl[i - sty][j - stx];
    }
  }

  int res = (int) ans;
  if (res < z) res = z;
  if (res > mx) res = mx;
  return res;
}

int ** * apply_filter(int ** * image, int N, int M, float ** filter, int filter_size) {
  int ** * res = aloc(N, M);

  for (int i = z; i < g; i++) {
    for (int j = z; j < N; j++) {
      for (int k = z; k < M; k++) {
        res[j][k][i] = fl(image, i, j, k, filter, filter_size, N, M);
      }
    }
  }

  fr(image, N, M);
  return res;
}
