if __name__ == "__main__":
    dirname = 'data'
    filenames = [
        '2mm_kernel.c', 'bicg_kernel.c', 'covariance_kernel.c',
        'gemm-blocked_kernel.c', 'gemm-p_kernel.c', 'gemm-p-large_kernel.c',
        'jacobi-1d_kernel.c', 'symm-opt_kernel.c', 'trmm_kernel.c',
        'trmm-opt_kernel.c'
    ]

    for file in filenames:
        with open(f'./{dirname}/{file}', 'r') as f:
            lines = f.readlines()
        lines = [line for line in lines if not line.startswith('#pragma')]
        with open(f'{dirname}/processed-{file}', 'w') as f:
            f.writelines(lines)
