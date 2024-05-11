function D = mult_proj_Gauss_orth(A,B,c,f)
    [m,n] = size(A);
    [n,p] = size(B);

    C = zeros(m,c);
    R = zeros(c, p);
    P = randn(n,c);
    
    %Gram-Schmidth orthogonality
    for i= 1:c
        for j= 1:i-1
            P(:,i) = P(:,i)  - dot(P(:,i),P(:,j)) * P(:,j);
        end
        P(:, i) = P(:,i) / norm(P(:,i));
    end

    C = A * P;
    R = P' * B;
    D = f(C,R);
end