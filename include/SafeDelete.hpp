#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if (x!=nullptr) { delete x; x = nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY1D
#define SAFE_DELETE_ARRAY1D(x) {if (x!=nullptr) { delete[] x; x = nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY2D
#define SAFE_DELETE_ARRAY2D(x,y) {if (x!=nullptr) { for (int i = 0; i < y; i++) delete[] x[i]; delete[] x; x = nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY3D
#define SAFE_DELETE_ARRAY3D(x) {if (x!=nullptr) { delete[][][] x; x = nullptr;}}
#endif
