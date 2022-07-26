from cffi import FFI

ffiAPI = FFI()
ffiAPI.cdef("""double holt_win_add_signal(double* x, double* xi, double* p, double* y, int m, long n, 
                    double max_seen, int yLen, int xLen) ;""")

# with open('cffi_test.c', 'rt') as fid:
with open('./statsmodels/tsa/cffi_test.c', 'rt') as fid:
    code = fid.read()

ffiAPI.set_source('cffiTest', code)

ffiAPI.compile(verbose=True)

