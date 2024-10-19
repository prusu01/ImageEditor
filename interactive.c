#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "imageprocessing.h"

#include "bmp.h"
#define bi 100

#define forr(X) for (int i = 0; i < X; i++)

  typedef struct {
    int ** * img;
    int N;
    int M;
  }

imagine;

int ** * alocc(int n, int m) {
  int ** * res = (int ** * ) malloc(sizeof(int ** ) * n);
  forr(n) {
    res[i] = (int ** ) malloc(sizeof(int * ) * m);
    for (int j = 0; j < m; j++) {
      res[i][j] = (int * ) malloc(sizeof(int) * 3);
    }
  }

  return res;
}

void frr(int ** * a, int n, int m) {
  forr(n) {
    for (int j = 0; j < m; j++) {
      free(a[i][j]);
    }

    free(a[i]);
  }

  free(a);
}

void load(imagine ** imagini, int * img_c) {
  int N = 0, M = 0;
  scanf("%d%d", & N, & M);
  char path[bi] = {
    0
  };
  ( * imagini)[ * img_c].N = N;
  ( * imagini)[ * img_c].img = alocc(N, M);
  ( * imagini)[ * img_c].M = M;
  scanf("%s", path);
  read_from_bmp((* imagini)[ * img_c].img, N, M, path);
  * img_c = * img_c + 1;
}

void save(imagine * imagini) {
  int in = 0;
  char path[bi] = {
    0
  };
  scanf("%d", & in);
  scanf("%s", path);
  write_to_bmp(imagini[in].img, imagini[in].N, imagini[in].M, path);
}

void delete_image(imagine ** imagini, int in , int * img_c) {
  frr((* imagini)[in].img, (* imagini)[in].N, (* imagini)[in].M);
  for (int i = in; i < (* img_c - 1); i++) {
    (* imagini)[i] = (* imagini)[i + 1];
  }

  * img_c = * img_c - 1;
}

void apply_horizontal(imagine ** imagini) {
  int in = 0;
  scanf("%d", & in);
  ( * imagini)[in].img = flip_horizontal(( * imagini)[in].img, ( * imagini)[in].N, ( * imagini)[in].M);
}

void apply_rotate(imagine ** imagini) {
  int in = 0;
  scanf("%d", & in);

  int ** * tmp = NULL;
  tmp = rotate_left(( * imagini)[in].img, ( * imagini)[in].N, ( * imagini)[in].M);

  int t = ( * imagini)[in].M;
  ( * imagini)[in].M = ( * imagini)[in].N;
  ( * imagini)[in].N = t;
  ( * imagini)[in].img = tmp;
}

void apply_crop(imagine ** imagini) {
  int in = 0, x = 0, y = 0, w = 0, h = 0;
  scanf("%d%d%d%d%d", & in, & x, & y, & w, & h);
  int N = ( * imagini)[in].N;
  int M = ( * imagini)[in].M;
  ( * imagini)[in].img = crop(( * imagini)[in].img, N, M, x, y, h, w);
  ( * imagini)[in].N = h;
  ( * imagini)[in].M = w;
}

void apply_extend(imagine ** imagini) {
  int in = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
  scanf("%d%d%d%d%d%d", & in, & rows, & cols, & R, & G, & B);
  int N = ( * imagini)[in].N;
  int M = ( * imagini)[in].M;

  ( * imagini)[in].img = extend(( * imagini)[in].img, N, M, rows, cols, R, G, B);
  ( * imagini)[in].N = N + 2 * rows;
  ( * imagini)[in].M = M + 2 * cols;
}

void apply_paste(imagine ** imagini) {
  int dst = 0, src = 0, x = 0, y = 0;
  scanf("%d%d%d%d", & dst, & src, & x, & y);
  int ND = ( * imagini)[dst].N;
  int MD = ( * imagini)[dst].M;
  int NS = ( * imagini)[src].N;
  int MS = ( * imagini)[src].M;

  ( * imagini)[dst].img = paste(( * imagini)[dst].img, ND, MD, ( * imagini)[src].img, NS, MS, x, y);
}

void create_filter(float ** * filters, int * filt_sz, int * flt_n) {
  int sz = 0;
  scanf("%d", & sz);
  * filt_sz = sz;
  filters[ * flt_n] = (float ** ) malloc(sizeof(float * ) * sz);
  for (int i = 0; i < sz; i++) {
    filters[ * flt_n][i] = (float * ) malloc(sizeof(float) * sz);
    for (int j = 0; j < sz; j++) {
      scanf("%f", & filters[ * flt_n][i][j]);
    }
  }

  * flt_n = * flt_n + 1;
}

void delete_filter(float ** * filters, int * filt_sz, int * flt_n, int in ) {
  for (int i = 0; i < filt_sz[in]; i++) {
    free(filters[in][i]);
  }

  free(filters[in]);

  for (int i = in; i < (*flt_n - 1); i++) {
    filters[i] = filters[i + 1];
    filt_sz[i] = filt_sz[i + 1];
  }

  * flt_n = * flt_n - 1;
}

void delete_all(imagine ** imagini, int * img_c, float ** * filters, int * filt_sz, int * flt_n) {
  while (*img_c != 0) {
    delete_image(imagini, 0, img_c);
  }

  while (*flt_n != 0) {
    delete_filter(filters, filt_sz, flt_n, 0);
  }
}

void aply_filter(imagine ** imagini, float ** * filters, int * filt_sz) {
  int img_i = 0, filt_i = 0;
  scanf("%d%d", & img_i, & filt_i);
  int N = ( * imagini)[img_i].N;
  int M = ( * imagini)[img_i].M;
  ( * imagini)[img_i].img = apply_filter(( * imagini)[img_i].img, N, M, filters[filt_i], filt_sz[filt_i]);
}

int main() {
  char com[3] = {
    0
  };
  imagine * imagini = (imagine * ) malloc(sizeof(imagine) * (bi));
  forr(4) {
    imagini[i].img = NULL;
    imagini[i].M = 0;
    imagini[i].N = 0;
  }

  float ** * filters = NULL;
  int * filt_sz = (int * ) malloc(sizeof(int) * bi);
  int flt_n = 0;
  int img_c = 0;
  while (1) {
    scanf("%s", com);
    if (!strcmp(com, "e")) {
      delete_all(&imagini, & img_c, filters, filt_sz, & flt_n);
      free(imagini);
      free(filters);
      free(filt_sz);
      return 0;
    }

    if (!strcmp(com, "l")) {
      load(&imagini, & img_c);
    }

    if (!strcmp(com, "s")) {
      save(imagini);
    }

    if (!strcmp(com, "di")) {
      int in = 0;
      scanf("%d", & in);
      delete_image(&imagini, in, & img_c);
    }

    if (!strcmp(com, "ah")) {
      apply_horizontal(&imagini);
    }

    if (!strcmp(com, "ar")) {
      apply_rotate(&imagini);
    }

    if (!strcmp(com, "ac")) {
      apply_crop(&imagini);
    }

    if (!strcmp(com, "ae")) {
      apply_extend(&imagini);
    }

    if (!strcmp(com, "ap")) {
      apply_paste(&imagini);
    }

    if (!strcmp(com, "cf")) {
      filters = (float ** * ) realloc(filters, sizeof(float ** ) * (flt_n + 1));
      int sz = 0;
      scanf("%d", & sz);
      filt_sz[flt_n] = sz;
      filters[flt_n] = (float ** ) malloc(sizeof(float * ) * sz);
      for (int i = 0; i < sz; i++) {
        filters[flt_n][i] = (float * ) malloc(sizeof(float) * sz);
        for (int j = 0; j < sz; j++) {
          scanf("%f", & filters[flt_n][i][j]);
        }
      }

      flt_n = flt_n + 1;
    }

    if (!strcmp(com, "df")) {
      int in = 0;
      scanf("%d", & in);
      delete_filter(filters, filt_sz, & flt_n, in);
    }

    if (!strcmp(com, "af")) {
      aply_filter(&imagini, filters, filt_sz);
    }
  }

  free(imagini);
  return 0;
}
