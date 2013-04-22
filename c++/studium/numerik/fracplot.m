%fracplot(file,x_res,y_res)
%zeigt den Plot einer Matrix, die in der Datei file
%seriell abgelegt wurde.
%x_res und y_res charakterisieren die Dimensionen
%der Matrix
%
%Beispiel: fracplot('infile.dat',120,120);
%

function fracplot(file,x_res,y_res)

if nargin<3
	error('Zu wenige Argumente');
end

[fid,message]=fopen(file,'r');
[A,count]=fscanf(fid,'%d',[x_res,y_res]);
fclose(fid);

map=[    0         0    0.7500;
         0         0    1.0000;
         0    0.2500    1.0000;
         0    0.5000    1.0000;
         0    0.7500    1.0000;
         0    1.0000    1.0000;
    0.2500    1.0000    1.0000;
    0.5000    1.0000    0.7500;
    0.7500    1.0000    0.5000;
    1.0000    1.0000    0.2500;
    1.0000    1.0000         0;
    1.0000    0.7500         0;
    1.0000    0.5000         0;
    1.0000    0.2500         0;
    1.0000         0         0;
    0.7500         0         0;
    0		   0         0];
   
colormap(map);
image(A);
axis off;
