function D = mult_row_uniform(A,B,c,f)
    [m,n] = size(A);
    [n,p] = size(B);

    C = zeros(m,c);
    R = zeros(c,p);
    probabilities = ones(1,n)/n;

    for t = 1:c
        p_it = randsample(1:n, 1 , true, probabilities);
        C(:,t) = A(:, p_it) * (1/sqrt(c*probabilities(p_it)));
        R(t,:) = B(p_it, :) * (1/sqrt(c*probabilities(p_it)));
    end
    D = f(C,R);
end