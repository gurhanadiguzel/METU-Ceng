function D = mult_row_nonuni(A,B,c,f)
    [m,n] = size(A);
    [n,p] = size(B);

    C = zeros(m,c);
    R = zeros(c, p);
    probabilities = zeros(1,m);
    for i = 1:n
        probabilities(i) = norm(A(:,i),2) * norm(B(i,:),2); 
    end
    probabilities = probabilities /sum(probabilities);
    
    for t = 1:c
        p_it = randsample(1:n, 1 , true, probabilities);
        C(:,t) = A(:, p_it) * (1/sqrt(c*probabilities(p_it)));
        R(t,:) = B(p_it, :) * (1/sqrt(c*probabilities(p_it)));
    end
    D = f(C,R);
end