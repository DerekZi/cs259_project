if __name__ == "__main__":
    dirname = 'data'
    filenames = [
        'mm-krnl.cpp',
        'dotprod-krnl2.cpp',
        'dotprod-krnl.cpp',
        'ewmm-krnl.cpp',
        'jacobi_1d-krnl.cpp',
        'madd-krnl.cpp',
        'syrk-krnl.cpp',
        'trmm-krnl.cpp',
        'trmm-opt-krnl.cpp',
        'vadd-krnl.cpp'
    ]

    for file in filenames:
        with open(f'{file}', 'r') as f:
            lines = f.readlines()
        lines = [line for line in lines if '#pragma' not in line]
        with open(f'processed-{file}', 'w') as f:
            f.writelines(lines)
