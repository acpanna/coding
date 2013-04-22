x=[0 6 10 13 17 20 28];
y=[6.67 17.33 42.67 37.33 30.10 29.31 28.74];

for j=1:6
  h(j+1)=x(j+1)-x(j);
end

for j=2:6
  lambda(j) = h(j+1)/(h(j) + h(j+1));
  mu(j) = 1 - lambda(j);
end

for j=1:4
  A(j,j)=2;
  A(j,j+1)=lambda(j+1);
  A(j+1,j)=mu(j+2);
end

A(5,5) = 2;
A(4,5) = lambda(5);
A(5,4)=  mu(6);

for j=1:5
  d(j)=(6/(h(j+2)+h(j+1))) * ((y(j+2)-y(j+1))/h(j+2) - (y(j+1)-y(j))/h(j+1));
end
  
gamma2 = inv(A)*d';
gamma = [0, gamma2', 0];

for j=1:6
  delta(j) = (gamma(j+1)-gamma(j))/h(j+1);
  beta(j) = (y(j+1)-y(j))/h(j+1) - (2*gamma(j)+gamma(j+1))*h(j+1)/6;
end

alpha = y'
beta
gamma = gamma'
delta

for j=1:6
  tx = x(j):0.01:x(j+1);
  ty = y(j) + beta(j) * (tx-x(j)) + (1/2) * gamma(j) * (tx-x(j)) .* (tx-x(j)) + (1/6) * delta(j) * (tx-x(j)) .* (tx-x(j)) .* (tx-x(j));
  plot(tx,ty)
  hold on;
end

