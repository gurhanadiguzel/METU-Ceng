function D = mult_proj_Gauss(A,B,c,f)
    [m,n] = size(A);
    [n,p] = size(B);

    C = zeros(m,c);
    R = zeros(c, p);

    P = randn(n,c);
    P = normalize(P, 'norm', 2);

    C= A * P;
    R = P' * B;

    D = f(C,R);
end