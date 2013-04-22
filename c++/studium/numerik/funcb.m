t=[0.0:0.01:1.0];
b=[-1.0 0.0; -1.0 4.0/3.0; 1.0 4.0/3.0; 1.0 0.0];


x = 0;
y = 0;

for i=1:4
 
  ifak = 1;
  for j=1:i-1
    ifak = ifak * j;
  end
  
  nfak = 1;  
  for j=1:3
    nfak = nfak * j;
  end
  
  nminifak = 1;
  for j=1:4-i;
    nminifak = nminifak * j;
  end
  
  x = x + b(i,1) * (nfak/(ifak * nminifak)) * (t.^(i-1)) .* ((1-t).^(4-i));
  y = y + b(i,2) * (nfak/(ifak * nminifak)) * (t.^(i-1)) .* ((1-t).^(4-i));

end 

plot(x,y,'r');
hold on;

b=[-1.0 0.0; -1.0 2.0/3.0; 0.0 2.0/3.0; 0.0 0.0; 0.0 0.0; 0.0 2.0/3.0; 1.0 2.0/3.0; 1.0 0.0];

x = 0;
y = 0;

for i=1:4
 
  ifak = 1;
  for j=1:i-1
    ifak = ifak * j;
  end
  
  nfak = 1;  
  for j=1:3
    nfak = nfak * j;
  end
  
  nminifak = 1;
  for j=1:4-i;
    nminifak = nminifak * j;
  end
  
  x = x + b(i,1) * (nfak/(ifak * nminifak)) * (t.^(i-1)) .* ((1-t).^(4-i));
  y = y + b(i,2) * (nfak/(ifak * nminifak)) * (t.^(i-1)) .* ((1-t).^(4-i));

end 

plot(x,y,'k');

x = 0;
y = 0;

for i=5:8
   
  ifak = 1;
  for j=1:i-5
    ifak = ifak * j;
  end
  
  nfak = 1;  
  for j=1:3
    nfak = nfak * j;
  end
  
  nminifak = 1;
  for j=1:8-i;
    nminifak = nminifak * j;
  end
  
  x = x + b(i,1) * (nfak/(ifak * nminifak)) * (t.^(i-5)) .* ((1-t).^(8-i));
  y = y + b(i,2) * (nfak/(ifak * nminifak)) * (t.^(i-5)) .* ((1-t).^(8-i));

end 

plot(x,y,'k');
